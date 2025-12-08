#include "ork.hpp"

#include "factory.hpp"

Ork::Ork(const std::string &name_, int x_, int y_) : NPC(name_, x_, y_) {}

Ork::Ork(std::istream &is) {
  is >> name;
  is >> x >> y;
}

bool Ork::accept(const std::shared_ptr<NPC>& attacker) {
  return attacker->visit_ork(std::static_pointer_cast<Ork>(shared_from_this()));
}

bool Ork::visit_ork(const std::shared_ptr<Ork>& defender) { return true; }

bool Ork::visit_squirrel(const std::shared_ptr<Squirrel>& defender) {return true;}

bool Ork::visit_druid(const std::shared_ptr<Druid>& defender) {return true;}

void Ork::print() const { std::cout << "Ork: " << *this << std::endl; }

void Ork::save(std::ostream &os) const {
  os << OrkType << std::endl;
  NPC::save(os);
}