#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iconv.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string Encode(const u_char* inputString, size_t inputLength, std::string inputCode, std::string outputCode)
{

    if (inputString == NULL) {

        fprintf(stderr, "input string is empty.\n");
        return ("");
    }

    if (inputLength == 0) {

        fprintf(stderr, "input length is zero.\n");
        return ("");
    }

    if (inputCode.empty()) {

        // iconvに文字列判定機能は無い。
        // 入力した文字列の文字コードを与える必要がある。
        fprintf(stderr, "input code is empty.\n");
        return ("");
    }

    if (outputCode.empty()) {

        // 変換したい文字コードが無い場合は、
        // ひとまず、自分の環境の文字コードに変換されるようにしておく。
        outputCode = "UTF-8";
    }

    iconv_t ic;

    size_t strInLength = inputLength;
    size_t strOutLength = inputLength * 4; // 変換後のバイト数がどうなるか分からない。1バイトが4バイトになることを考慮しておく。

    char strIn[strInLength + 1];
    char strOut[strOutLength + 1];

    memset(strIn, 0, sizeof(strIn));
    memset(strOut, 0, sizeof(strOut));

    // const u_char -> char
    for (size_t i = 0; i < inputLength; ++i) {

        strIn[i] = (char)inputString[i];
    }

    // iconvに渡すのは、charの配列の先頭を指すポインタ、のポインタ。
    char* ptrIn = strIn;
    char* ptrOut = strOut;

    errno = 0;

    ic = iconv_open(outputCode.c_str(), inputCode.c_str());

    if (errno) {

        fprintf(stderr, "iconv_open failed. %s\n", strerror(errno));
        return ("");
    }

    // それぞれポインタを渡す。
    iconv(ic, &ptrIn, &strInLength, &ptrOut, &strOutLength);

    if (errno) {

        fprintf(stderr, "iconv failed. %s\n", strerror(errno));

        iconv_close(ic);
        return ("");
    } else {

        iconv_close(ic);
        return (strOut);
    }
}

size_t GetUTF8CharLength(unsigned char loadingByte)
{
    if ((loadingByte & 0x80) == 0x00)
        return 1; // ASCII
    if ((loadingByte & 0xE0) == 0xC0)
        return 2;
    if ((loadingByte & 0xF0) == 0xE0)
        return 3; // 一般的な漢字、ひらがな(3バイト)
    if ((loadingByte & 0xF8) == 0xF0)
        return 4; // 特殊文字、絵文字など
    return 1; // 不正なバイトの場合はフォールバック
}

TEST(Iconv, Encode)
{
    std::string expected = "   1 ２六歩(27)   ( 0:00/00:00:00)";

    std::ifstream in("resources/kifu/test.kif");
    ASSERT_TRUE(in.is_open());

    std::stringstream ss;
    std::string line;
    while (std::getline(in, line)) {
        ss << line;
    }
    std::string target = ss.str();

    std::string actual = Encode(reinterpret_cast<const unsigned char*>(target.c_str()), target.size(), "SHIFT_JIS", "UTF-8");

    // 1文字ずつに分割
    for (size_t i = 0; i < actual.size();) {
        // 現在の文字のバイト数を取得
        size_t length = GetUTF8CharLength(static_cast<unsigned char>(actual[i]));

        // 1文字分(漢字なら通常3バイト分)を切り出す
        std::string singleChar = actual.substr(i, length);

        // 出力
        std::cout << singleChar << std::endl;

        // 次の文字のインデックスへ進める
        i += length;
    }

    std::cout << std::endl;

    EXPECT_EQ(expected, actual);
}
