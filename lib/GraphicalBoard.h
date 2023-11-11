#ifndef G_BOARD
#define G_BOARD

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/GraphicalBoardI.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

/**
 * @class GraphicalBoard
 * Representation of a Tic-Tac-Toe board's graphical elements.
 *
 * Contains functionality for drawing Tic-Tac-Toe boards as well as marking
 * their cells.
 */
class GraphicalBoard : public GraphicalBoardI {
private:
    /** The handler object used to access the underlying
     * notcurses instance.
     */
    std::shared_ptr<NcHandlerI> _ncHandler;

    /** The primary plane used as a canvas for drawing the board. */
    ncplane *_primaryPlane;

    /** The child planes used to represent the cells of the board
     *
     * Child planes contain the planes for the cells in order from left to
     * right, top to bottom.
     *
     * Layout:
     * 0|1|2
     * 3|4|5
     * 6|7|8
     */
    std::array<ncplane *, CELL_COUNT> _childPlanes;

    /** The height and width of the primary plane */
    unsigned int _rows, _cols;

public:
    /**
     * A constructor that takes in the raw info for a plane and forms its
     * primary plane from those options.
     *
     * Calls the constructor that takes an ncplane_options struct.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param Y The Y coordinate of the new plane's top left corner.
     * @param X The X coordinate of the new plane's top left corner.
     * @param ROWS The number of rows composing the new plane. (Height)
     * @param COLS The number of columns composing the new plane. (Width)
     *
     * @see create_nopts()
     * @see _primaryPlane
     * @see _childPlanes
     */
    GraphicalBoard(std::shared_ptr<NcHandlerI> ncHandler, const int Y,
                   const int X, const unsigned int ROWS,
                   const unsigned int COLS);

    /**
     * A constructor that takes in an ncplane_options struct for a plane and
     * forms its primary plane from those options.
     *
     * Calls the constructor that takes an ncplane pointer.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param NOPTS The configuration used to form the primary plane.
     *
     * @see ncplane_create()
     * @see _primaryPlane
     * @see _childPlanes
     */
    GraphicalBoard(std::shared_ptr<NcHandlerI> ncHandler,
                   const ncplane_options NOPTS);

    /**
     * A constructor that takes in an notcurses plane and uses it as its primary
     * plane.
     *
     * Creates child planes used for the cells of the board.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param PLANE The plane used as the primary plane.
     *
     * @see _primaryPlane
     * @see _childPlanes
     */
    GraphicalBoard(std::shared_ptr<NcHandlerI> ncHandler, ncplane *const PLANE);

    GraphicalBoard(GraphicalBoard &) = delete;
    void operator=(const GraphicalBoard &) = delete;
    ~GraphicalBoard() = default;

    void draw_board(const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
                    const uint64_t CELL_CHANNELS) override final;
    void draw_x(const unsigned int INDEX) override final;
    void draw_o(const unsigned int INDEX) override final;
    void fill_x() override final;
    void fill_o() override final;
    std::array<ncplane *, CELL_COUNT> get_child_planes() const override final;
    std::array<std::unique_ptr<GraphicalBoardI>, CELL_COUNT>
    create_child_boards() const override final;
};

// Helper functions

/**
 * Forms an struct describing the configuration of a notcurses plane from the
 * data passed in.
 *
 * @param Y The Y coordinate of the new plane's top left corner.
 * @param X The X coordinate of the new plane's top left corner.
 * @param ROWS The number of rows composing the new plane. (Height)
 * @param COLS The number of columns composing the new plane. (Width)
 * @return An ncplane_options struct describing the configuration options.
 */
ncplane_options create_nopts(const int Y, const int X, const unsigned int ROWS,
                             const unsigned int COLS);

/**
 * Extracts the configuration used to form the given plane.
 *
 * @param PLANE The plane to extract the configuration from.
 * @return An ncplane_options struct describing the plane's configuration
 * options.
 */
ncplane_options extract_nopts(ncplane *PLANE);

#endif // !G_BOARD
