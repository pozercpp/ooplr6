#pragma once
#include "npc.hpp"
#include <iostream>

class IFightVisitor;

class Ork : public NPC, public std::enable_shared_from_this<Ork> {
public:
    Ork(const std::string& name, int x, int y) : NPC(name, x, y) {type = OrkType;}

    std::string Type() const override { return "Ork"; }
};