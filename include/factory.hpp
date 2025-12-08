#pragma once

#include "npc.hpp"

enum NpcType { SquirrelType = 1,
    DruidType = 2,
    OrkType = 3 
};

std::shared_ptr<NPC> factory(NpcType type, const std::string &name, int x, int y);
std::shared_ptr<NPC> factory(std::istream &is);