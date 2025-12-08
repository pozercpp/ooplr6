#include<npc.hpp>
#include "squirrel.hpp"

#include "factory.hpp"


Squirrel::Squirrel(const std::string &name_, int x_, int y_) : NPC(name_, x_, y_) {}

Squirrel::Squirrel(std::istream &is) {
  is >> name;
  is >> x >> y;
}

bool Squirrel::accept(const std::shared_ptr<NPC>& attacker) {
  return attacker->visit_squirrel(std::static_pointer_cast<Squirrel>(shared_from_this()));
}

bool Squirrel::visit_squirrel(const std::shared_ptr<Squirrel>& defender) { return true; }

bool Squirrel::visit_ork(const std::shared_ptr<Ork>& defender) {return true;}

bool Squirrel::visit_druid(const std::shared_ptr<Druid>& defender) {return false;}

void Squirrel::print() const { std::cout << "Squirrel: " << *this << std::endl; }

void Squirrel::save(std::ostream &os) const {
  os << SquirrelType << std::endl;
  NPC::save(os);
}