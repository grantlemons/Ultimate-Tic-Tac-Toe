#ifndef G_BOARD
#define G_BOARD

#include "lib/NcHandler.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

class GraphicalBoard {
private:
    std::shared_ptr<NcHandler> _ncHandler;
    ncplane *_primaryPlane;
    std::array<ncplane *, 9> _childPlanes;

    unsigned int _rows, _cols;
    std::array<const char *, 3> _symbols;
    uint64_t _cell_channels;

    int draw_board_yx(const int Y, const int X);
    // int draw_x_yx(const int Y, const int X);
    // int draw_o_yx(const int Y, const int X);

public:
    GraphicalBoard(std::shared_ptr<NcHandler> ncHandler, const int Y,
                   const int X, const unsigned int ROWS,
                   const unsigned int COLS, const uint64_t CELL_CHANNELS,
                   std::array<const char *, 3> SYMBOLS);
    GraphicalBoard(std::shared_ptr<NcHandler> ncHandler, ncplane_options nopts,
                   const uint64_t CELL_CHANNELS,
                   std::array<const char *, 3> SYMBOLS);
    GraphicalBoard(std::shared_ptr<NcHandler> ncHandler, ncplane *const PLANE,
                   const uint64_t CELL_CHANNELS,
                   std::array<const char *, 3> SYMBOLS);

    GraphicalBoard(GraphicalBoard &) = delete;
    void operator=(const GraphicalBoard &) = delete;
    ~GraphicalBoard() = default;

    void draw_board();
    void draw_x(const unsigned int INDEX);
    void draw_o(const unsigned int INDEX);
    void fill_x();
    void fill_o();

    std::array<ncplane *, 9> get_child_planes() const;
};

#endif // !G_BOARD
