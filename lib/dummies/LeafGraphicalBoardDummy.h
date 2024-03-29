/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#ifndef LEAF_G_BOARD_DUMMY
#define LEAF_G_BOARD_DUMMY

#include "lib/dummies/AGraphicalBoardDummy.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <memory>

/**
 * @class LeafGraphicalBoardDummy
 * Dummy used as a substitute for LeafGraphicalBoard for testing purposes.
 */
class LeafGraphicalBoardDummy : virtual public AGraphicalBoardDummy {
public:
    /**
     * Constructor for LeafGraphicalBoardDummy.
     *
     * @param P_plane The primary plane used by the methods of the class.
     *
     * This is needed to create child planes.
     */
    LeafGraphicalBoardDummy(std::shared_ptr<INcPlaneWrapper> P_plane);

    std::array<std::unique_ptr<IGraphicalArea>, CELL_COUNT>
    create_children() override final;
};

#endif
