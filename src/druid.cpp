#include<druid.hpp>

Druid::Druid() : NPC() {
    type = DruidType;
}

Druid::Druid(const std::string& name_, int x_, int y_) : NPC(name_, x_, y_) {
    type = DruidType;
}

Druid::~Druid() noexcept = default;