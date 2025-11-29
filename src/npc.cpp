#include<iostream>
#include<cmath>
#include<string>
#include<map>

#include<npc.hpp>

NPC::NPC() : name(""), x(0), y(0), alive(true) {}

NPC::NPC(const std::string& name_, int x_, int y_) : name(name_), x(x_), y(y_), alive(true) {}

NPC::~NPC() noexcept = default;

double NPC::distanceTo(const std::shared_ptr<NPC>& other) const {
    int dx = x - other->x;
    int dy = y - other->y;
    return std::sqrt(dx * dx + dy * dy);
}

std::string NPC::getName() const { return name; }

NpcType NPC::getType() const { return type; }

int NPC::getX() const { return x; }

int NPC::getY() const { return y; }

bool NPC::isAlive() const { return alive; }

void NPC::die() { alive = false; }

void NPC::fight(std::shared_ptr<NPC> other) {
    auto cankill = [&]() -> bool {
        return (can_kill.find(type) != can_kill.end() && can_kill.at(type) == other->type);
    };
    auto candie = [&]() -> bool {
        return (can_kill.find(other->type) != can_kill.end() && can_kill.at(other->type) == type);
    };
    if (cankill()) {
        other->die();
    }
    if (candie()) {
        die();
    }
}

void NPC::save(std::ostream& os) const {
    os << getType() << " " << getName() << " " << getX() << " " << getY() << std::endl;
}