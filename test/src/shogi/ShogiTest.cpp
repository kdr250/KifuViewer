#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <shogi/Shogi.h>

TEST(Shogi, Shogi)
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

    Shogi shogi;
    std::string actual = shogi.DebugString();

    EXPECT_EQ(expected, actual);
}

TEST(Shogi, Forward)
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

    std::shared_ptr<Kifu> kifu = std::make_shared<Kifu>(commands);

    Shogi shogi;
    shogi.SetKifu(kifu);

    shogi.Forward(commands.size() - 1);

    std::string actual = shogi.DebugString();

    EXPECT_EQ(expected, actual);
}

TEST(Shogi, Backward)
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

    std::shared_ptr<Kifu> kifu = std::make_shared<Kifu>(commands);

    Shogi shogi;
    shogi.SetKifu(kifu);

    shogi.Forward(commands.size() - 1);
    shogi.Backward();

    std::string actual = shogi.DebugString();

    EXPECT_EQ(expected, actual);
}
