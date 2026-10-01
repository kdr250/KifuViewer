#include "StringConverter.h"

#ifdef _WIN32
typedef unsigned char u_char;
#endif
#include <iconv.h>

#include <sstream>

std::string StringConverter::Encode(const std::string& input, std::string inputCode, std::string outputCode)
{
    const u_char* inputString = reinterpret_cast<const unsigned char*>(input.c_str());
    size_t inputLength = input.size();

    if (inputString == nullptr) {
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
        // ひとまず、UTF-8にしておく。
        outputCode = "UTF-8";
    }

    iconv_t ic;

    size_t strInLength = inputLength;
    size_t strOutLength = inputLength * 4; // 変換後のバイト数がどうなるか分からない。1バイトが4バイトになることを考慮しておく。

    std::vector<char> strIn(strInLength + 1, 0);
    std::vector<char> strOut(strOutLength + 1, 0);

    // const u_char -> char
    for (size_t i = 0; i < inputLength; ++i) {
        strIn[i] = (char)inputString[i];
    }

    // iconvに渡すのは、charの配列の先頭を指すポインタ、のポインタ。
    char* ptrIn = strIn.data();
    char* ptrOut = strOut.data();

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
        return (strOut.data());
    }
}

size_t StringConverter::GetUTF8CharLength(unsigned char loadingByte)
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

std::vector<std::string> StringConverter::Split(const std::string& utf8Str)
{
    std::vector<std::string> actual;

    // 1文字ずつに分割
    for (size_t i = 0; i < utf8Str.size();) {
        // 現在の文字のバイト数を取得
        size_t length = GetUTF8CharLength(static_cast<unsigned char>(utf8Str[i]));

        // 1文字分(漢字なら通常3バイト分)を切り出す
        std::string singleChar = utf8Str.substr(i, length);

        actual.push_back(singleChar);

        // 次の文字のインデックスへ進める
        i += length;
    }

    return actual;
}