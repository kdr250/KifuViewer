#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <reader/KifuReader.h>
#include <shogi/Shogi.h>

#include <fstream>

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
