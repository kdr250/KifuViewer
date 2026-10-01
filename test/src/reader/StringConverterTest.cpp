#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <reader/StringConverter.h>

#include <fstream>

TEST(StringConverter, EncodeSJISToUTF8)
{
    std::string expected = "   1 ２六歩(27)   ( 0:00/00:00:00)";

    std::ifstream in("resources/kifu/test.kif");
    ASSERT_TRUE(in.is_open());

    std::stringstream ss;
    ss << in.rdbuf();
    std::string target = ss.str();

    std::string actual = StringConverter::Encode(target, "SHIFT_JIS", "UTF-8");
    EXPECT_EQ(expected, actual);
}

TEST(StringConverter, SplitCharacters)
{
    std::string expected[] = { "２", "六", "歩", "(", "2", "7", ")" };

    std::ifstream in("resources/kifu/test.kif");
    ASSERT_TRUE(in.is_open());

    std::stringstream ss;
    ss << in.rdbuf();
    std::string target = ss.str();

    std::string utf8Str = StringConverter::Encode(target, "SHIFT_JIS", "UTF-8");

    ss.str(utf8Str);
    ss.clear();
    std::string id, move;
    ss >> id >> move;

    std::vector<std::string> actual = StringConverter::Split(move);

    EXPECT_THAT(actual, testing::ElementsAreArray(expected));
}
