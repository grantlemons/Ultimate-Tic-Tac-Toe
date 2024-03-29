/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#include "lib/graphical_board/LeafGraphicalBoard.h"

#include "gsl/narrow"
#include "lib/Shared.h"
#include "lib/graphical_board/AGraphicalBoard.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <memory>
#include <notcurses/notcurses.h>

LeafGraphicalBoard::LeafGraphicalBoard(INcHandler *const P_ncHandler,
                                       const int Y, const int X, const int ROWS,
                                       const int COLS)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, Y, X, ROWS, COLS} {
    init_child_planes();
}

LeafGraphicalBoard::LeafGraphicalBoard(INcHandler *const P_ncHandler,
                                       const ncplane_options NOPTS)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, NOPTS} {
    init_child_planes();
}

LeafGraphicalBoard::LeafGraphicalBoard(INcHandler *const P_ncHandler,
                                       std::unique_ptr<INcPlaneWrapper> P_plane)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, std::move(P_plane)} {
    init_child_planes();
}

void LeafGraphicalBoard::init_child_planes() {
    const unsigned int ROWS_PER_BCELL =
        (gsl::narrow<unsigned int>(mRows) - 2u) / 3u;
    const unsigned int COLS_PER_BCELL =
        (gsl::narrow<unsigned int>(mCols) - 2u) / 3u;

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        const unsigned int COLUMN = i % 3u;
        const unsigned int ROW = (i - COLUMN) / 3u;

        const int NEW_Y = 1 + gsl::narrow<int>((ROWS_PER_BCELL * ROW));
        const int NEW_X = 1 + gsl::narrow<int>((COLS_PER_BCELL * COLUMN));

        const ncplane_options CHILD_NOPTS = NcPlaneWrapper::createNopts(
            NEW_Y, NEW_X, ROWS_PER_BCELL - 1u, COLS_PER_BCELL - 1u);
        IGraphicalArea *const P_tmp = create_child(&CHILD_NOPTS);

        mChildren.at(i) = std::unique_ptr<IGraphicalArea>{P_tmp};
    }
}
