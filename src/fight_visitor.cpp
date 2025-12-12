#include "fight_visitor.hpp"

FightVisitor::FightVisitor(NpcPtr attacker) : attacker(attacker) {}

void FightVisitor::visit(const NpcPtr& defender) {
    if (can_kill.find(attacker->getType()) != can_kill.end() &&  can_kill.at(attacker->getType()) == defender->getType()) {defender->die();}
    if (can_kill.find(defender->getType()) != can_kill.end() &&  can_kill.at(defender->getType()) == attacker->getType()) { attacker->die();}
}