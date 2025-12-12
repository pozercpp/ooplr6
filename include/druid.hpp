#pragma once

#include "npc.hpp"
#include <iostream>


class Druid : public NPC, public std::enable_shared_from_this<Druid> {
public:
    Druid(const std::string& name, int x, int y) : NPC(name, x, y) {type = DruidType;}
    
    std::string Type() const override { return "Druid"; }
};