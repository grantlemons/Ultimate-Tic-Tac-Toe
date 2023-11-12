#include "lib/board/LeafBoard.h"

#include "gsl/assert"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

std::array<const char *, SYMBOL_COUNT> LeafBoard::_symbols =
    std::array<const char *, SYMBOL_COUNT>{"\u2500", "\u2502", "\u253C"};

LeafBoard::LeafBoard(std::shared_ptr<NcHandlerI> ncHandler,
                     std::unique_ptr<GraphicalBoardI> gBoard)
    : Board::Board{ncHandler, std::move(gBoard)}, _cells{}, _winner{None} {}

LeafBoard::LeafBoard(std::shared_ptr<NcHandlerI> ncHandler,
                     std::unique_ptr<NcPlaneWrapperI> plane)
    : Board::Board{ncHandler, std::move(plane)}, _cells{}, _winner{None} {}

CellOwner LeafBoard::get_cell_owner(const int INDEX) const {
    Expects(INDEX >= 0 && INDEX <= 9);

    return _cells.at(gsl::narrow<unsigned int>(INDEX));
}

void LeafBoard::set_cell_owner(const int INDEX, const CellOwner OWNER) {
    Expects(INDEX >= 0 && INDEX <= 9);
    Expects(_cells.at(gsl::narrow<unsigned int>(INDEX)) == None);

    _cells.at(gsl::narrow<unsigned int>(INDEX)) = OWNER;
    mark_cell(INDEX, OWNER);

    if (check_win(INDEX, OWNER)) {
        _winner = OWNER;
    }

    Ensures(_cells.at(gsl::narrow<unsigned int>(INDEX)) == OWNER);
}

CellOwner LeafBoard::get_winner() const {
    return _winner;
}

void LeafBoard::mark_fill(const CellOwner OWNER) {
    switch (OWNER) {
    case X:
        getGraphicalBoard()->fill_x();
        break;
    case O:
        getGraphicalBoard()->fill_o();
        break;
    default:
        break;
    }
}

void LeafBoard::draw() {
    getGraphicalBoard()->draw_board(
        _symbols,
        NcHandler::combine_channels(getNcHandler()->get_default_bg_channel(),
                                    NcHandler::GREY_CHANNEL));
}
