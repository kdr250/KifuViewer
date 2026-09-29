#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <shogi/Kifu.h>

TEST(Kifu, GetMoveCommands)
{
    std::vector<MoveCommand> expected = {
        {
            .origin = std::make_pair(6, 6),
            .destination = std::make_pair(6, 5),
            .type = KomaType::Fu,
            .direction = Direction::Black,
        },
    };

    Kifu kifu(expected);
    std::span<MoveCommand> actual = kifu.GetMoveCommands();

    EXPECT_THAT(actual, testing::ElementsAreArray(expected));
}
