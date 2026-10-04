#pragma once

/**
 * 手番
 */
enum class Direction {
    Black, // 先手側
    White, // 後手側
};

inline std::string ToString(Direction direction)
{
    if (direction == Direction::Black) {
        return "先手";
    } else {
        return "後手";
    }
}
