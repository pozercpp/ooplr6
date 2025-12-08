#pragma once

#include<string>
#include<memory>

#include<npc.hpp>

struct Squirrel : public NPC {
    Squirrel() = default;
    Squirrel(const std::string &name_, int x_, int y_);
    Squirrel(std::istream &is);
    bool accept(const std::shared_ptr<NPC>& attacker);
    bool visit_ork(const std::shared_ptr<Ork>& defender);
    bool visit_squirrel(const std::shared_ptr<Squirrel>& defender);
    bool visit_druid(const std::shared_ptr<Druid>& defender);
    void print() const;
    void save(std::ostream &os) const;
};