#pragma once

#include "npc.hpp"
#include <iostream>

class IFightVisitor;

struct Squirrel : public NPC, public std::enable_shared_from_this<Squirrel> {
    Squirrel(const std::string& name, int x, int y) : NPC(name, x, y) {type = SquirrelType;}

    std::string Type() const override { return "Squirrel"; }
};