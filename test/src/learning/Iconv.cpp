#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iconv.h>

#include <string>
#include <fstream>
#include <sstream>

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

    EXPECT_EQ(expected, actual);
}
