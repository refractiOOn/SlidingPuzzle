#pragma once

namespace game
{

class Tile
{
public:
    Tile() = default;
    Tile(const size_t value);
    ~Tile() = default;

    size_t value() const;
    void setValue(const size_t newValue);

    bool operator==(const Tile &other);

private:
    size_t m_value{};

};

} // namespace game
