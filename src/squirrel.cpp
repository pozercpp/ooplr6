#include<squirrel.hpp>

Squirrel::Squirrel() : NPC() {
    type = SquirrelType;
}

Squirrel::Squirrel(const std::string& name_, int x_, int y_) : NPC(name_, x_, y_) {
    type = SquirrelType;
}

Squirrel::~Squirrel() noexcept = default;