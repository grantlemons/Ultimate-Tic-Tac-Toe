#ifndef G_BOARD_DUMMY
#define G_BOARD_DUMMY

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/IGraphicalBoard.h"

#include <array>
#include <cstdint>
#include <memory>

/**
 * @class GraphicalBoardDummy
 * Dummy class used as a substitute for GraphicalBoardI classes for testing
 * purposes.
 */
class GraphicalBoardDummy : virtual public IGraphicalBoard {
private:
    std::shared_ptr<INcPlaneWrapper> _primaryPlane;
    std::array<std::unique_ptr<IGraphicalArea>, CELL_COUNT> _children;

    void init_child_planes();

    GraphicalBoardDummy(std::shared_ptr<INcPlaneWrapper> plane);

public:
    /**
     * Constructor for GraphicalBoard dummy.
     *
     * @param plane The primary plane used by the methods of the class.
     *
     * This is needed to create child planes.
     *
     * @see init_child_planes()
     */
    GraphicalBoardDummy(INcPlaneWrapper *const P_plane);

    void draw_board(const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
                    const uint64_t CELL_CHANNELS) override final;
    void draw_x(const int INDEX) override final;
    void draw_o(const int INDEX) override final;
    std::array<IGraphicalArea *, CELL_COUNT> get_children() override final;

    void dim_yx(int &ROWS, int &COLS) const override final;
    [[nodiscard]] int get_rows() const override final;
    [[nodiscard]] int get_cols() const override final;

    IGraphicalArea *create_child(const ncplane_options *nopts) override final;

    int load_nccell(nccell *const P_c, const char *gcluster) override final;
    int set_base_cell(const nccell *const P_c) override final;

    int cursor_move_yx(const int X, const int Y) override final;
    int hline(const nccell *const P_c, const unsigned LEN) override final;
    int vline(const nccell *const P_c, const unsigned LEN) override final;
    int putc_yx(const int Y, const int X,
                const nccell *const P_c) override final;
    void erase() override final;
};

#endif
