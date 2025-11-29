#pragma once

#include<string>
#include<memory>

#include<npc.hpp>

struct Ork : public NPC {
    Ork();
    Ork(const std::string& name_, int x_, int y_);
    ~Ork() noexcept;
};