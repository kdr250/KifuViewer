#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <shogi/Board.h>

TEST(Board, Reset)
{
    std::string expected = R"(
後: 
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
｜　｜飛｜　｜　｜　｜　｜　｜角｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜角｜　｜　｜　｜　｜　｜飛｜　｜
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
先: 
)";

    Board board;
    board.Initialize();
    std::string actual = board.DebugString();

    EXPECT_EQ(expected, actual);
}

TEST(Board, Move)
{
    std::string expected = R"(
後: 
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
｜　｜飛｜　｜　｜　｜　｜　｜角｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜歩｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜　｜歩｜歩｜歩｜歩｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜角｜　｜　｜　｜　｜　｜飛｜　｜
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
先: 
)";

    Board board;
    board.Initialize();

    MoveCommand command {
        .origin = std::make_pair(6, 6),
        .destination = std::make_pair(6, 5),
        .type = KomaType::Fu,
        .direction = Direction::Black,
    };
    board.Add(command);
    board.Replay();

    std::string actual = board.DebugString();

    EXPECT_EQ(expected, actual);
}

TEST(Board, IllegalMove)
{
    std::string expected = R"(
後: 
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
｜　｜飛｜　｜　｜　｜　｜　｜角｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜角｜　｜　｜　｜　｜　｜飛｜　｜
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
先: 
)";

    Board board;
    board.Initialize();

    MoveCommand command {
        .origin = std::make_pair(4, 4),
        .destination = std::make_pair(4, 3),
        .type = KomaType::Fu,
        .direction = Direction::Black,
    };
    board.Add(command);
    bool result = board.Replay();

    std::string actual = board.DebugString();

    EXPECT_FALSE(result);
    EXPECT_EQ(expected, actual);
}

TEST(Board, Toru)
{
    std::string expected = R"(
後: 歩x1 
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
｜　｜飛｜　｜　｜　｜　｜　｜角｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜　｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜飛｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜歩｜歩｜歩｜歩｜歩｜　｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜角｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
先: 歩x1 
)";

    Board board;
    board.Initialize();

    std::vector<MoveCommand> commands = {
        {
            .origin = std::make_pair(1, 6),
            .destination = std::make_pair(1, 5),
            .type = KomaType::Fu,
            .direction = Direction::Black,
        },
        {
            .origin = std::make_pair(1, 2),
            .destination = std::make_pair(1, 3),
            .type = KomaType::Fu,
            .direction = Direction::White,
        },
        {
            .origin = std::make_pair(1, 5),
            .destination = std::make_pair(1, 4),
            .type = KomaType::Fu,
            .direction = Direction::Black,
        },
        {
            .origin = std::make_pair(1, 3),
            .destination = std::make_pair(1, 4),
            .type = KomaType::Fu,
            .direction = Direction::White,
        },
        {
            .origin = std::make_pair(1, 7),
            .destination = std::make_pair(1, 4),
            .type = KomaType::Hisha,
            .direction = Direction::Black,
        },
    };

    board.Add(commands);
    board.Replay();

    std::string actual = board.DebugString();

    EXPECT_EQ(expected, actual);
}

TEST(Board, Naru)
{
    std::string expected = R"(
後: 
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
｜　｜飛｜　｜　｜　｜　｜　｜馬｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜歩｜歩｜歩｜歩｜　｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜歩｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜歩｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜　｜歩｜歩｜歩｜歩｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜飛｜　｜
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
先: 角x1 
)";

    Board board;
    board.Initialize();

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
    };

    board.Add(commands);
    board.Replay();

    std::string actual = board.DebugString();

    EXPECT_EQ(expected, actual);
}

TEST(Board, NaruAndToru)
{
    std::string expected = R"(
後: 角x1 
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜　｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
｜　｜飛｜　｜　｜　｜　｜　｜銀｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜歩｜歩｜歩｜歩｜　｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜歩｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜歩｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜　｜歩｜歩｜歩｜歩｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜飛｜　｜
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
先: 角x1 
)";

    Board board;
    board.Initialize();

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
    };

    board.Add(commands);
    board.Replay();

    std::string actual = board.DebugString();

    EXPECT_EQ(expected, actual);
}

TEST(Board, Komadai)
{
    std::string expected = R"(
後: 
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜　｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
｜　｜飛｜　｜　｜　｜　｜　｜銀｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜歩｜歩｜歩｜歩｜　｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜歩｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜角｜　｜角｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜歩｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜　｜歩｜歩｜歩｜歩｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜飛｜　｜
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
先: 
)";

    Board board;
    board.Initialize();

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

    board.Add(commands);
    board.Replay();

    std::string actual = board.DebugString();

    EXPECT_EQ(expected, actual);
}

TEST(Board, Back)
{
    std::string expected = R"(
後: 角x1 
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜　｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
｜　｜飛｜　｜　｜　｜　｜　｜銀｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜歩｜歩｜歩｜歩｜　｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜歩｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜角｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜歩｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜　｜歩｜歩｜歩｜歩｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜飛｜　｜
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
先: 
)";

    Board board;
    board.Initialize();

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

    board.Add(commands);
    board.Back();
    board.Replay();

    std::string actual = board.DebugString();

    EXPECT_EQ(expected, actual);
}
