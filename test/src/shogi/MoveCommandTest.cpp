#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <shogi/MoveCommand.h>

TEST(MoveCommand, ToDisplayString)
{
    std::string expected = "76歩";

    MoveCommand command {
        .origin = std::make_pair(6, 6),
        .destination = std::make_pair(6, 5),
        .type = KomaType::Fu,
        .direction = Direction::Black,
    };

    std::string actual = command.ToDisplayString();

    EXPECT_EQ(expected, actual);
}

TEST(MoveCommand, ToDisplayStringNari)
{
    std::string expected = "22角成";

    MoveCommand command {
        .origin = std::make_pair(7, 7),
        .destination = std::make_pair(1, 1),
        .type = KomaType::Kaku,
        .direction = Direction::Black,
        .isNaru = true,
    };

    std::string actual = command.ToDisplayString();

    EXPECT_EQ(expected, actual);
}
