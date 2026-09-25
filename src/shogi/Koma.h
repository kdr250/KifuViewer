#pragma once

#include <string>
#include <memory>

/**
 * 駒の種類
 */
enum class KomaType {
    Fu, // 歩
    Tokin, // と金
    Kyo, // 香
    NariKyo, // 成香
    Keima, // 桂
    NariKei, // 成桂
    Gin, // 銀
    NariGin, // 成銀
    Kin, // 金
    Hisha, // 飛車
    Ryu, // 龍
    Kaku, // 角
    Uma, // 馬
    Gyoku, // 玉
};

/**
 * 向き
 */
enum class Direction {
    Black, // 先手側
    White, // 後手側
};

/**
 * 駒
 */
class Koma {
private:
    KomaType mType;
    Direction mDirection;

public:
    inline Koma(KomaType type, Direction direction)
        : mType(type)
        , mDirection(direction) { };

    inline static std::shared_ptr<Koma> New(KomaType type, Direction direction)
    {
        return std::make_shared<Koma>(type, direction);
    }

    inline KomaType Type() const
    {
        return mType;
    }

    inline Direction Direction() const
    {
        return mDirection;
    }

    /**
     * 文字にする
     */
    inline std::string ToString()
    {
        switch (mType) {
            case KomaType::Fu:
                return "歩";
            case KomaType::Tokin:
                return "と";

            case KomaType::Kyo:
                return "香";
            case KomaType::NariKyo:
                return "杏";

            case KomaType::Keima:
                return "桂";
            case KomaType::NariKei:
                return "圭";

            case KomaType::Gin:
                return "銀";
            case KomaType::NariGin:
                return "全";

            case KomaType::Kin:
                return "金";

            case KomaType::Hisha:
                return "飛";
            case KomaType::Ryu:
                return "竜";

            case KomaType::Kaku:
                return "角";
            case KomaType::Uma:
                return "馬";

            case KomaType::Gyoku:
                return "玉";

            default:
                break;
        }
    }

    /**
     * 成る
     */
    inline void Naru()
    {
        switch (mType) {
            case KomaType::Fu:
                mType = KomaType::Tokin;
                break;

            case KomaType::Kyo:
                mType = KomaType::NariKyo;
                break;

            case KomaType::Keima:
                mType = KomaType::NariKei;
                break;

            case KomaType::Gin:
                mType = KomaType::NariGin;
                break;

            case KomaType::Hisha:
                mType = KomaType::Ryu;
                break;

            case KomaType::Kaku:
                mType = KomaType::Uma;
                break;

            default:
                break;
        }
    }

    /**
     * 取る
     */
    inline void Toru()
    {
        mDirection = mDirection == Direction::Black ? Direction::White : Direction::Black;

        switch (mType) {
            case KomaType::Tokin:
                mType = KomaType::Fu;
                break;

            case KomaType::NariKyo:
                mType = KomaType::Kyo;
                break;

            case KomaType::NariKei:
                mType = KomaType::Keima;
                break;

            case KomaType::NariGin:
                mType = KomaType::Gin;
                break;

            case KomaType::Ryu:
                mType = KomaType::Hisha;
                break;

            case KomaType::Uma:
                mType = KomaType::Kaku;
                break;

            default:
                break;
        }
    }
};

using KomaRef = std::shared_ptr<Koma>;
