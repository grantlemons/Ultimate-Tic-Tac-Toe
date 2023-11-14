#ifndef ABSTRACT_BOARD_FACTORY
#define ABSTRACT_BOARD_FACTORY

#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

/**
 * @class AbstractBoardFactory
 * Interface for BoardFactories as a part of the Abstract Factory design
 * pattern.
 */
class AbstractBoardFactory {
public:
    virtual ~AbstractBoardFactory() = default;

    /**
     * Getter for NcHandler instance.
     */
    virtual NcHandlerI *getNcHandler() = 0;

    /**
     * Getter for PrimaryBoard instance.
     */
    virtual PrimaryBoard *getPrimaryBoard() = 0;

    /**
     * Getter for Primary GraphicalBoard instance.
     */
    virtual GraphicalAreaI *getPrimaryGraphicalBoard() = 0;

    /**
     * Getter for LeafBoard instance of a certain index.
     *
     * @param INDEX The index of the LeafBoard within the PrimaryBoard.
     */
    virtual LeafBoard *getLeafBoard(const int INDEX) = 0;

    /**
     * Getter for the GraphicalBoard associated with a certain LeafBoard.
     *
     * @param INDEX The index of the LeafBoard within the PrimaryBoard.
     */
    virtual GraphicalAreaI *getLeafGraphicalBoard(const int INDEX) = 0;
};

#endif // !ABSTRACT_BOARD_FACTORY