#pragma once

#include<string>
#include<memory>

#include<npc.hpp>

struct Druid : public NPC {
    Druid();
    Druid(const std::string& name_, int x_, int y_);
    ~Druid() noexcept;
};