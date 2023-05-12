#include "Tile.hpp"

game::Tile::Tile(const size_t value) : m_value(value)
{}

size_t game::Tile::value() const
{
    return m_value;
}

void game::Tile::setValue(size_t newValue)
{
    m_value = newValue;
}

bool game::Tile::operator==(const Tile &other)
{
    return m_value == other.m_value;
}
