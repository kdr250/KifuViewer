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
    kifu.Forward();
    std::span<MoveCommand> actual = kifu.GetMoveCommands();

    EXPECT_THAT(actual, testing::ElementsAreArray(expected));
}

TEST(Kifu, Forward)
{
    std::vector<MoveCommand> commands = {
        {
            .origin = std::make_pair(6, 6),
            .destination = std::make_pair(6, 5),
            .type = KomaType::Fu,
            .direction = Direction::Black,
        },
        {
            .origin = std::make_pair(2, 2),
            .destination = std::make_pair(2, 3),
            .type = KomaType::Fu,
            .direction = Direction::White,
        },
        {
            .origin = std::make_pair(7, 7),
            .destination = std::make_pair(1, 1),
            .type = KomaType::Kaku,
            .direction = Direction::Black,
            .isNaru = true,
        },
        {
            .origin = std::make_pair(2, 0),
            .destination = std::make_pair(1, 1),
            .type = KomaType::Gin,
            .direction = Direction::White,
        },
        {
            .origin = MoveCommand::KOMADAI_BLACK,
            .destination = std::make_pair(3, 4),
            .type = KomaType::Kaku,
            .direction = Direction::Black,
        },
        {
            .origin = MoveCommand::KOMADAI_WHITE,
            .destination = std::make_pair(5, 4),
            .type = KomaType::Kaku,
            .direction = Direction::White,
        },
    };

    std::vector<MoveCommand> expected = {
        commands[0], commands[1], commands[2], commands[3], commands[4]
    };

    Kifu kifu(commands);
    kifu.Forward(5);
    std::span<MoveCommand> actual = kifu.GetMoveCommands();

    EXPECT_THAT(actual, testing::ElementsAreArray(expected));
}

TEST(Kifu, Backward)
{
    std::vector<MoveCommand> commands = {
        {
            .origin = std::make_pair(6, 6),
            .destination = std::make_pair(6, 5),
            .type = KomaType::Fu,
            .direction = Direction::Black,
        },
        {
            .origin = std::make_pair(2, 2),
            .destination = std::make_pair(2, 3),
            .type = KomaType::Fu,
            .direction = Direction::White,
        },
        {
            .origin = std::make_pair(7, 7),
            .destination = std::make_pair(1, 1),
            .type = KomaType::Kaku,
            .direction = Direction::Black,
            .isNaru = true,
        },
        {
            .origin = std::make_pair(2, 0),
            .destination = std::make_pair(1, 1),
            .type = KomaType::Gin,
            .direction = Direction::White,
        },
        {
            .origin = MoveCommand::KOMADAI_BLACK,
            .destination = std::make_pair(3, 4),
            .type = KomaType::Kaku,
            .direction = Direction::Black,
        },
        {
            .origin = MoveCommand::KOMADAI_WHITE,
            .destination = std::make_pair(5, 4),
            .type = KomaType::Kaku,
            .direction = Direction::White,
        },
    };

    std::vector<MoveCommand> expected = {
        commands[0], commands[1], commands[2]
    };

    Kifu kifu(commands);
    kifu.Forward(5);
    kifu.Backward(2);
    std::span<MoveCommand> actual = kifu.GetMoveCommands();

    EXPECT_THAT(actual, testing::ElementsAreArray(expected));
}
