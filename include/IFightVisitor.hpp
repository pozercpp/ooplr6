#pragma once

#include "npc.hpp"

#include<map>


class IFightVisitor {
protected:
    const std::map<NpcType, NpcType> can_kill = {{DruidType, SquirrelType}, {OrkType, SquirrelType}};
public:
    virtual ~IFightVisitor() noexcept = default;
    virtual void visit(const NpcPtr& defender) = 0;
};