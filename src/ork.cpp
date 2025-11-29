#include<ork.hpp>

Ork::Ork() : NPC() {
    type = OrkType;
}

Ork::Ork(const std::string& name_, int x_, int y_) : NPC(name_, x_, y_) {
    type = OrkType;
}

Ork::~Ork() noexcept = default;