/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#ifndef BOARD
#define BOARD

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/IGraphicalBoard.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <array>
#include <cmath>
#include <cstdint>
#include <optional>
#include <ostream>

/**
 * @class ABoard
 * Abstract class representation of a logical board.
 */
class ABoard {
private:
    /** The handler object used to access the underlying
     * notcurses instance.
     */
    INcHandler *_ncHandler;

protected:
    /**
     * A constructor that uses dependency injection.
     *
     * @param P_ncHandler The handler object used to access the underlying
     * notcurses instance.
     */
    ABoard(INcHandler *const P_ncHandler);

    /**
     * Getter for the associated NcHandler instance.
     *
     * @return A pointer to the private NcHandler.
     */
    [[nodiscard]] INcHandler *getNcHandler() const;

    virtual ~ABoard() = default;

public:
    ABoard(ABoard &) = delete;
    void operator=(const ABoard &) = delete;

    /**
     * Getter for the associated GraphicalBoard instance.
     *
     * @return A pointer to the private GraphicalBoard.
     */
    [[nodiscard]] virtual IGraphicalBoard *getGraphicalBoard() const = 0;

    /**
     * Checks if the given player has won the current board.
     *
     * Can be called after any move with the player that just moved.
     * Since a player can only win after making a move, checking a single player
     * is optimal.
     *
     * @param INDEX The index of a cell known to be owned by the given player.
     * @param OWNER The player to check the victory of.
     * @return If the given player won or not.
     */
    [[nodiscard]] bool check_win(const int INDEX, const CELL_OWNER OWNER) const;

    /**
     * Gets the owner of a given index.
     *
     * @param INDEX the index of the cell to check ownership.
     * @return The owner of the cell (Can be NONE variant).
     */
    [[nodiscard]] virtual CELL_OWNER get_cell_owner(const int INDEX) const = 0;

    /**
     * Uses the component GraphicalBoard to draw a Tic-Tac-Toe board.
     */
    virtual void draw() = 0;

    /**
     * Uses the component GraphicalBoard to mark the owner of a cell
     * appropriately.
     *
     * @param INDEX The index of the cell to mark.
     * @param OWNER The user for whom to mark the cell.
     */
    void mark_cell(const int INDEX, const CELL_OWNER OWNER);

    /**
     * Defines the way Board types are outputted to streams.
     */
    friend std::ostream &operator<<(std::ostream &out, const ABoard &BRD);
};

// Helper functions

/**
 * Mod function that takes into account negative numbers.
 *
 * @code{.cpp}
 * negative_mod(-1, 10) == 9
 * @endcode
 *
 * @code{.cpp}
 * negative_mod(1, 10) == 1
 * @endcode
 *
 * @param A The dividend of the modulus operation.
 * @param B The divisor of the modulus operation.
 * @return The result of the modulus operation.
 *
 * @relates ABoard
 */
inline constexpr int negative_mod(const int A, const int B) {
    return A - (B * gsl::narrow<int>(std::floor(static_cast<double>(A) / B)));
}

/**
 * Gets the other indicies on a certain row of a 3x3 grid.
 *
 * Indicies are arranged like so:
 * 0|1|2
 * 3|4|5
 * 6|7|8
 *
 * @param [in] INDEX The known index on a row.
 * @param [out] other1 The first other index in the same row.
 * @param [out] other2 The second other index in the same row.
 *
 * @see vertical_others()
 *
 * @relates ABoard
 */
inline constexpr void horizontal_others(const int INDEX, int &other1,
                                        int &other2) {
    Expects(INDEX >= 0 && INDEX <= 9);

    const int ROW_LEN = 3;
    other1 = negative_mod(INDEX - 1, ROW_LEN) + (INDEX / ROW_LEN) * ROW_LEN;
    other2 = negative_mod(INDEX + 1, ROW_LEN) + (INDEX / ROW_LEN) * ROW_LEN;

    Ensures(other1 != other2);
    Ensures(other1 != INDEX && other2 != INDEX);
    Ensures(other1 >= 0 && other1 <= 9);
    Ensures(other2 >= 0 && other2 <= 9);
}

/**
 * Gets the other indicies on a certain column of a 3x3 grid.
 *
 * Indicies are arranged like so:
 * 0|1|2
 * 3|4|5
 * 6|7|8
 *
 * @param [in] INDEX The known index on a column.
 * @param [out] other1 The first other index in the same column.
 * @param [out] other2 The second other index in the same column.
 *
 * @see horizontal_others()
 *
 * @relates ABoard
 */
inline constexpr void vertical_others(const int INDEX, int &other1,
                                      int &other2) {
    Expects(INDEX >= 0 && INDEX <= 9);

    const int ROW_LEN = 3;
    other1 = negative_mod(INDEX - ROW_LEN, CELL_COUNT);
    other2 = negative_mod(INDEX + ROW_LEN, CELL_COUNT);

    Ensures(other1 != other2);
    Ensures(other1 != INDEX && other2 != INDEX);
    Ensures(other1 >= 0 && other1 <= 9);
    Ensures(other2 >= 0 && other2 <= 9);
}

/**
 * Gets the other indicies of a diagonal line on a 3x3 grid.
 *
 * Indicies are arranged like so:
 * 0|1|2
 * 3|4|5
 * 6|7|8
 *
 * This function is only used for the diagonal from index 0 to 8.
 *
 * @param [in] INDEX The known index in the diagonal. Must be a multiple of 4.
 * @param [out] other1 The first other index in the diagonal.
 * @param [out] other2 The second other index in the diagonal.
 *
 * @see diagonal_twos_others()
 *
 * @relates ABoard
 */
inline constexpr void diagonal_fours_others(const int INDEX, int &other1,
                                            int &other2) {
    Expects(INDEX == 0 || INDEX == 4 || INDEX == 8);

    other1 = negative_mod(INDEX - 4, CELL_COUNT + 3);
    other2 = negative_mod(INDEX + 4, CELL_COUNT + 3);

    Ensures(other1 != other2);
    Ensures(other1 != INDEX && other2 != INDEX);
    Ensures(other1 == 0 || other1 == 4 || other1 == 8);
    Ensures(other2 == 0 || other2 == 4 || other2 == 8);
}

/**
 * Gets the other indicies of a diagonal line on a 3x3 grid.
 *
 * Indicies are arranged like so:
 * 0|1|2
 * 3|4|5
 * 6|7|8
 *
 * This function is only used for the diagonal from index 2 to 6.
 *
 * @param [in] INDEX The known index in the diagonal. Must be a multiple of 2
 * (that is not a multiple of 4 with the exception of 4 itself).
 * @param [out] other1 The first other index in the diagonal.
 * @param [out] other2 The second other index in the diagonal.
 *
 * @see diagonal_twos_others()
 *
 * @relates ABoard
 */
inline constexpr void diagonal_twos_others(const int INDEX, int &other1,
                                           int &other2) {
    Expects(INDEX == 2 || INDEX == 4 || INDEX == 6);

    other1 = negative_mod(INDEX, 6) + 2;
    other2 = negative_mod(INDEX + 2, 6) + 2;

    Ensures(other1 != other2);
    Ensures(other1 != INDEX && other2 != INDEX);
    Ensures(other1 == 2 || other1 == 4 || other1 == 6);
    Ensures(other2 == 2 || other2 == 4 || other2 == 6);
}

#endif // !BOARD
