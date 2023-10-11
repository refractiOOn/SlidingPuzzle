#include <GameTile.hpp>

game::GameTile::GameTile(const uint64_t value) : m_value { value } {}

uint64_t game::GameTile::value() const noexcept { return m_value; }

void game::GameTile::setValue(const uint64_t value) { m_value = value; }