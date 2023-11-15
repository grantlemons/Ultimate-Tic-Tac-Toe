#include "lib/dummies/PrimaryGraphicalBoardDummy.h"

#include "lib/dummies/AGraphicalBoardDummy.h"
#include "lib/dummies/LeafGraphicalBoardDummy.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <memory>

PrimaryGraphicalBoardDummy::PrimaryGraphicalBoardDummy(
    std::shared_ptr<INcPlaneWrapper> plane)
    : AGraphicalBoardDummy(std::move(plane)) {
    set_children(create_children());
}

std::array<std::unique_ptr<IGraphicalArea>, CELL_COUNT>
PrimaryGraphicalBoardDummy::create_children() {
    std::array<std::unique_ptr<IGraphicalArea>, CELL_COUNT> children{};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        children.at(i) =
            std::make_unique<LeafGraphicalBoardDummy>(get_primary_plane());
    }

    return children;
}
