/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#ifndef PRIMARY_G_BOARD_DUMMY
#define PRIMARY_G_BOARD_DUMMY

#include "lib/Shared.h"
#include "lib/dummies/AGraphicalBoardDummy.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <array>
#include <memory>

/**
 * @class PrimaryGraphicalBoardDummy
 * Dummy used as a substitute for PrimaryGraphicalBoard for testing purposes.
 */
class PrimaryGraphicalBoardDummy : virtual public AGraphicalBoardDummy {
public:
    /**
     * Constructor for PrimaryGraphicalBoardDummy.
     *
     * @param plane The primary plane used by the methods of the class.
     *
     * This is needed to create child planes.
     */
    PrimaryGraphicalBoardDummy(std::shared_ptr<INcPlaneWrapper> plane);

    std::array<std::unique_ptr<IGraphicalArea>, CELL_COUNT>
    create_children() override final;
};

#endif
