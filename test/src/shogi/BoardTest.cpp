#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <shogi/Board.h>

TEST(Board, Reset)
{
    std::string expected = R"(
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
)";

    Board board;
    board.Reset();
    std::string actual = board.DebugString();

    EXPECT_EQ(expected, actual);
}
