#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <reader/KifuReader.h>
#include <shogi/Shogi.h>

#include <fstream>

using Parameters = std::pair<std::string, MoveCommand>;

class Parameterized : public testing::TestWithParam<Parameters> { };

std::vector<Parameters> parameters = {
    { "1 ７六歩(77)", MoveCommand({ 6, 6 }, { 6, 5 }, KomaType::Fu, Direction::Black, false) },
    { "2 ３四歩(33)", MoveCommand({ 2, 2 }, { 2, 3 }, KomaType::Fu, Direction::White, false) },
    { "1 ２六歩(27)", MoveCommand({ 1, 6 }, { 1, 5 }, KomaType::Fu, Direction::Black, false) },
    { "3 ２二角成(88)", MoveCommand({ 7, 7 }, { 1, 1 }, KomaType::Kaku, Direction::Black, true) },
    { "3 ２二角不成(88)", MoveCommand({ 7, 7 }, { 1, 1 }, KomaType::Kaku, Direction::Black, false) },
    { "4 同　銀(31)", MoveCommand({ 2, 0 }, KifuReader::PreviousDestination(), KomaType::Gin, Direction::White, false) },
    { "23 ３三銀直(32)", MoveCommand({ 2, 1 }, { 2, 2 }, KomaType::Gin, Direction::Black, false) },
    { "79 ３三銀直成(34)", MoveCommand({ 2, 3 }, { 2, 2 }, KomaType::Gin, Direction::Black, true) },
    { "58 ５七成香(47)", MoveCommand({ 3, 6 }, { 4, 6 }, KomaType::NariKyo, Direction::White, false) },
    { "58 ５七香成(51)", MoveCommand({ 4, 0 }, { 4, 6 }, KomaType::Kyo, Direction::White, true) },
    { "58 ５七香不成(51)", MoveCommand({ 4, 0 }, { 4, 6 }, KomaType::Kyo, Direction::White, false) },
    { "58 同　香成(51)", MoveCommand({ 4, 0 }, KifuReader::PreviousDestination(), KomaType::Kyo, Direction::White, true) },
    { "58 同　香不成(51)", MoveCommand({ 4, 0 }, KifuReader::PreviousDestination(), KomaType::Kyo, Direction::White, false) },
    { "57 同　成銀(56)", MoveCommand({ 4, 5 }, KifuReader::PreviousDestination(), KomaType::NariGin, Direction::Black, false) },
};

INSTANTIATE_TEST_SUITE_P(
    KifuReader,
    Parameterized,
    ::testing::ValuesIn(parameters));

TEST_P(Parameterized, Parse)
{
    auto [value, expected] = GetParam();

    std::stringstream ss(value);
    auto actual = KifuReader::Parse(ss);

    EXPECT_TRUE(actual.has_value());
    EXPECT_EQ(expected, actual.value());
}

TEST(KifuReader, Read)
{
    std::string expected = R"(
後: 
ーーーーーーーーーーーーーーーーーー
｜香｜桂｜銀｜金｜玉｜　｜　｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
｜　｜飛｜　｜　｜　｜銀｜金｜角｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜歩｜歩｜歩｜歩｜歩｜歩｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜歩｜　｜　｜　｜　｜　｜　｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜　｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜　｜歩｜　｜　｜　｜　｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜歩｜桂｜歩｜歩｜歩｜歩｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜角｜金｜　｜　｜　｜　｜飛｜　｜
ーーーーーーーーーーーーーーーーーー
｜香｜　｜銀｜　｜玉｜金｜銀｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
先: 
)";

    std::shared_ptr<Kifu> kifu = KifuReader::Read("resources/kifu/joban.kif");

    Shogi shogi;
    shogi.SetKifu(kifu);
    shogi.Last();

    std::string actual = shogi.DebugString();

    EXPECT_EQ(expected, actual);
}

TEST(KifuReader, ReadAllKifu)
{
    std::string expected = R"(
後: 歩x4 銀x1 
ーーーーーーーーーーーーーーーーーー
｜香｜　｜　｜馬｜　｜　｜玉｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜　｜金｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜桂｜歩｜金｜歩｜銀｜歩｜歩｜
ーーーーーーーーーーーーーーーーーー
｜歩｜　｜歩｜金｜玉｜　｜歩｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜杏｜　｜歩｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜歩｜　｜　｜　｜歩｜　｜　｜
ーーーーーーーーーーーーーーーーーー
｜歩｜　｜桂｜　｜　｜　｜　｜　｜歩｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜金｜　｜　｜　｜　｜飛｜　｜
ーーーーーーーーーーーーーーーーーー
｜　｜　｜　｜　｜　｜竜｜　｜桂｜香｜
ーーーーーーーーーーーーーーーーーー
先: 歩x2 銀x2 角x1 
)";

    std::shared_ptr<Kifu> kifu = KifuReader::Read("resources/kifu/all.kif");

    Shogi shogi;
    shogi.SetKifu(kifu);
    shogi.Last();

    std::string actual = shogi.DebugString();

    EXPECT_EQ(expected, actual);
}
