#include "lib/graphical_board/PrimaryGraphicalBoard.h"

#include "gsl/narrow"
#include "lib/Shared.h"
#include "lib/graphical_board/AGraphicalBoard.h"
#include "lib/graphical_board/LeafGraphicalBoard.h"
#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <memory>
#include <notcurses/notcurses.h>

PrimaryGraphicalBoard::PrimaryGraphicalBoard(INcHandler *const P_ncHandler,
                                             const int Y, const int X,
                                             const int ROWS, const int COLS)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, Y, X, ROWS, COLS} {
    init_child_planes();
}

PrimaryGraphicalBoard::PrimaryGraphicalBoard(INcHandler *const P_ncHandler,
                                             const ncplane_options NOPTS)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, NOPTS} {
    init_child_planes();
}

PrimaryGraphicalBoard::PrimaryGraphicalBoard(INcHandler *const P_ncHandler,
                                             INcPlaneWrapper *const P_plane)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, P_plane} {
    init_child_planes();
}

PrimaryGraphicalBoard::~PrimaryGraphicalBoard() {
    delete mprimaryPlane;
}

void PrimaryGraphicalBoard::init_child_planes() {
    const unsigned int ROWS_PER_BCELL =
        (gsl::narrow<unsigned int>(mrows) - 2u) / 3u;
    const unsigned int COLS_PER_BCELL =
        (gsl::narrow<unsigned int>(mcols) - 2u) / 3u;

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        const unsigned int COLUMN = i % 3u;
        const unsigned int ROW = (i - COLUMN) / 3u;

        int newY = 1 + gsl::narrow<int>((ROWS_PER_BCELL * ROW));
        int newX = 1 + gsl::narrow<int>((COLS_PER_BCELL * COLUMN));

        ncplane_options childNopts = NcPlaneWrapper::createNopts(
            newY, newX, ROWS_PER_BCELL - 1u, COLS_PER_BCELL - 1u);
        auto *const P_newPlane =
            dynamic_cast<INcPlaneWrapper *>(create_child(&childNopts));
        IGraphicalArea *pTmp = new LeafGraphicalBoard{mncHandler, P_newPlane};

        mchildren.at(i) = std::unique_ptr<IGraphicalArea>{pTmp};
    }
}

void PrimaryGraphicalBoard::draw_x(const int INDEX) {
    AGraphicalBoard::draw_x(INDEX);
    fill_x(INDEX);
}

void PrimaryGraphicalBoard::draw_o(const int INDEX) {
    AGraphicalBoard::draw_o(INDEX);
    fill_o(INDEX);
}

void PrimaryGraphicalBoard::fill_x(const int INDEX) {
    auto *const P_target{dynamic_cast<AGraphicalBoard *>(
        mchildren.at(gsl::narrow<unsigned int>(INDEX)).get())};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        IGraphicalArea *const P_child = P_target->get_children().at(i);
        const nccell RED = NCCELL_INITIALIZER(
            '\0', 0,
            NcHandler::combineChannels(NcHandler::RED_CHANNEL,
                                       mncHandler->get_default_fg_channel()));

        P_child->erase();
        P_child->set_base_cell(&RED);
    }

    // update the screen with the new changes
    mncHandler->render();
}

void PrimaryGraphicalBoard::fill_o(const int INDEX) {
    AGraphicalBoard *const P_target{dynamic_cast<AGraphicalBoard *>(
        mchildren.at(gsl::narrow<unsigned int>(INDEX)).get())};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        IGraphicalArea *const P_child = P_target->get_children().at(i);
        const nccell RED = NCCELL_INITIALIZER(
            '\0', 0,
            NcHandler::combineChannels(NcHandler::RED_CHANNEL,
                                       mncHandler->get_default_fg_channel()));

        P_child->erase();
        P_child->set_base_cell(&RED);
    }

    // update the screen with the new changes
    mncHandler->render();
}
