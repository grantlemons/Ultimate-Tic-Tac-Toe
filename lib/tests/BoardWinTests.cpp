#include "doctest.h"
#include "lib/board/BoardA.h"
#include "lib/board/LeafBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/factories/DummyBoardFactory.h"

#include <memory>

TEST_SUITE("Board CheckWin Tests") {
    TEST_CASE("Check Win Horizontal") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        LeafBoard *board = factory->getLeafBoard(0);

        SUBCASE("No Win Row 1") {
            board->set_cell_owner(0, X);
            board->set_cell_owner(1, X);

            REQUIRE_EQ(board->get_cell_owner(2), None);
            CHECK_FALSE(board->check_win(1, X));
        }
        SUBCASE("No Win Row 2") {
            board->set_cell_owner(3, X);
            board->set_cell_owner(4, X);

            REQUIRE_EQ(board->get_cell_owner(5), None);
            CHECK_FALSE(board->check_win(4, X));
        }
        SUBCASE("No Win Row 3") {
            board->set_cell_owner(6, X);
            board->set_cell_owner(7, X);

            REQUIRE_EQ(board->get_cell_owner(8), None);
            CHECK_FALSE(board->check_win(7, X));
        }
        SUBCASE("Win Row 1") {
            board->set_cell_owner(0, X);
            board->set_cell_owner(1, X);
            board->set_cell_owner(2, X);

            CHECK(board->check_win(2, X));
        }
        SUBCASE("Win Row 2") {
            board->set_cell_owner(3, X);
            board->set_cell_owner(4, X);
            board->set_cell_owner(5, X);

            CHECK(board->check_win(5, X));
        }
        SUBCASE("Win Row 3") {
            board->set_cell_owner(6, X);
            board->set_cell_owner(7, X);
            board->set_cell_owner(8, X);

            CHECK(board->check_win(8, X));
        }
    }

    TEST_CASE("Check Win Vertical") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        LeafBoard *board = factory->getLeafBoard(0);

        SUBCASE("No Win Column 1") {
            board->set_cell_owner(0, X);
            board->set_cell_owner(3, X);

            REQUIRE_EQ(board->get_cell_owner(6), None);
            CHECK_FALSE(board->check_win(3, X));
        }
        SUBCASE("No Win Column 2") {
            board->set_cell_owner(1, X);
            board->set_cell_owner(4, X);

            REQUIRE_EQ(board->get_cell_owner(7), None);
            CHECK_FALSE(board->check_win(4, X));
        }
        SUBCASE("No Win Column 3") {
            board->set_cell_owner(2, X);
            board->set_cell_owner(5, X);

            REQUIRE_EQ(board->get_cell_owner(8), None);
            CHECK_FALSE(board->check_win(5, X));
        }
        SUBCASE("Win Column 1") {
            board->set_cell_owner(0, X);
            board->set_cell_owner(3, X);
            board->set_cell_owner(6, X);

            CHECK(board->check_win(6, X));
        }
        SUBCASE("Win Column 2") {
            board->set_cell_owner(1, X);
            board->set_cell_owner(4, X);
            board->set_cell_owner(7, X);

            CHECK(board->check_win(7, X));
        }
        SUBCASE("Win Column 3") {
            board->set_cell_owner(2, X);
            board->set_cell_owner(5, X);
            board->set_cell_owner(8, X);

            CHECK(board->check_win(8, X));
        }
    }

    TEST_CASE("Check Win Diagonal") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        LeafBoard *board = factory->getLeafBoard(0);

        SUBCASE("No Win Twos") {
            board->set_cell_owner(2, X);
            board->set_cell_owner(6, X);

            REQUIRE_EQ(board->get_cell_owner(4), None);
            CHECK_FALSE(board->check_win(6, X));
        }
        SUBCASE("Win Twos") {
            board->set_cell_owner(2, X);
            board->set_cell_owner(6, X);
            board->set_cell_owner(4, X);

            CHECK(board->check_win(4, X));
        }

        SUBCASE("No Win Fours") {
            board->set_cell_owner(0, X);
            board->set_cell_owner(8, X);

            REQUIRE_EQ(board->get_cell_owner(4), None);
            CHECK_FALSE(board->check_win(8, X));
        }
        SUBCASE("Win Fours") {
            board->set_cell_owner(0, X);
            board->set_cell_owner(8, X);
            board->set_cell_owner(4, X);

            CHECK(board->check_win(4, X));
        }
    }
}