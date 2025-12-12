#pragma once

#include "IFightVisitor.hpp"
#include "npc.hpp"

class FightVisitor : public IFightVisitor {
private:
    NpcPtr attacker;
public:
    FightVisitor(NpcPtr attacker);
    ~FightVisitor() noexcept override = default;
    void visit(const NpcPtr& defender) override;
    NpcPtr getAttacker() const {return attacker;}
};