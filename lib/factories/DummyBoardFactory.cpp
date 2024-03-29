/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#include "lib/factories/DummyBoardFactory.h"

#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/dummies/NcHandlerDummy.h"
#include "lib/dummies/NcPlaneWrapperDummy.h"
#include "lib/dummies/PrimaryGraphicalBoardDummy.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <memory>

DummyBoardFactory::DummyBoardFactory()
    : _ncHandler{std::unique_ptr<INcHandler>{new NcHandlerDummy{}}},
      _primaryPlane{new NcPlaneWrapperDummy{}},
      _graphicalBoard{
          std::unique_ptr<IGraphicalBoard>{new PrimaryGraphicalBoardDummy{
              std::shared_ptr<INcPlaneWrapper>{_primaryPlane}}}},
      _primaryBoard{_ncHandler.get(), std::move(_graphicalBoard)} {}

INcHandler *DummyBoardFactory::getNcHandler() {
    return _ncHandler.get();
}
PrimaryBoard *DummyBoardFactory::getPrimaryBoard() {
    return &_primaryBoard;
}
IGraphicalArea *DummyBoardFactory::getPrimaryGraphicalBoard() {
    return _primaryBoard.getGraphicalBoard();
}
LeafBoard *DummyBoardFactory::getLeafBoard(const int INDEX) {
    return _primaryBoard.getLeafBoard(INDEX);
}
IGraphicalArea *DummyBoardFactory::getLeafGraphicalBoard(const int INDEX) {
    return getLeafBoard(INDEX)->getGraphicalBoard();
}
