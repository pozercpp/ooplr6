#include "druid.hpp"

#include "factory.hpp"

Druid::Druid(const std::string &name_, int x_, int y_) : NPC(name_, x_, y_) {}

Druid::Druid(std::istream &is) {
  is >> name;
  is >> x >> y;
}

bool Druid::accept(const std::shared_ptr<NPC>& attacker) {
  return attacker->visit_druid(std::static_pointer_cast<Druid>(shared_from_this()));
}

bool Druid::visit_druid(const std::shared_ptr<Druid> &defender) { return true; }

bool Druid::visit_squirrel(const std::shared_ptr<Squirrel>& defender) {return true;}

bool Druid::visit_ork(const std::shared_ptr<Ork> &defender) {return false;}

void Druid::print() const { std::cout << "Druid: " << *this << std::endl; }

void Druid::save(std::ostream &os) const {
  os << DruidType << std::endl;
  NPC::save(os);
}