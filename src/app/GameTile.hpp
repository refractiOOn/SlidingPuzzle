#pragma once

#include <cstdint>

namespace game
{

class GameTile
{
public:
    GameTile(const uint64_t value);

    GameTile() = default;
    GameTile(const GameTile &) = default;
    GameTile(GameTile &&) = default;

    ~GameTile() = default;

    GameTile &operator=(const GameTile &) = default;
    GameTile &operator=(GameTile &&) = default;

    [[nodiscard]] uint64_t value() const noexcept;
    void setValue(const uint64_t value);

    auto operator<=>(const GameTile &) const = default;

private:
    uint64_t m_value;

}; // class GameTile

} // namespace game