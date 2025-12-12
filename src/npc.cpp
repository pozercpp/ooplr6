#include "npc.hpp"

#include <cmath>
#include <limits>
#include <ostream>

#include "IFightVisitor.hpp"

NPC::NPC(const std::string& name, int x, int y) : name(name), x(x), y(y) {}

double NPC::dist(const NpcPtr& other) const {
    double dx = static_cast<double>(x - other->x);
    double dy = static_cast<double>(y - other->y);
    return std::sqrt(dx * dx + dy * dy);
}

void NPC::fight(const std::shared_ptr<IFightVisitor>& visitor) {
    if (visitor && alive) {
        visitor->visit(std::shared_ptr<NPC>(this, [](NPC*){}));
    }
}

void NPC::save(std::ostream& os) const {
    os << Type() << std::endl;
    os << name << " " << x << " " << y << " " << "\n";
}