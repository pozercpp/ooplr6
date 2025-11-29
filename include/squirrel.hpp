#pragma once

#include<string>
#include<memory>

#include<npc.hpp>

struct Squirrel : public NPC {
    Squirrel();
    Squirrel(const std::string& name_, int x_, int y_);
    ~Squirrel() noexcept;
};