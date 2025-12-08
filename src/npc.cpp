#include "npc.hpp"

#include <cmath>

NPC::NPC(const std::string &name_, int x_, int y_)
    : name(name_), x(x_), y(y_) {}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
  observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC>& defender, bool win) {
  for (auto &o : observers)
    if (o)
      o->on_fight(shared_from_this(), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const {
  if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <=
      std::pow(distance, 2))
    return true;
  else
    return false;
}

void NPC::save(std::ostream &os) const {
  os << name << std::endl;
  os << x << " " << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, const NPC &npc) {
  os << "{ name: " << npc.name << ", x: " << npc.x << ", y: " << npc.y << " }";
  return os;
}