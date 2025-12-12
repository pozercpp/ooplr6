#pragma once
#include <string>
#include <map>
#include "INpcFactory.hpp"

class NpcFactory : public INpcFactory {
private:
    std::map<std::string, CreatorFunc> creators;
public:
    virtual ~NpcFactory() = default;

    void registerCreator(const std::string& type, CreatorFunc creator) override;

    NpcPtr createNPC(const std::string& type, const std::string& name, int x, int y) override;
    NpcPtr loadNPC(const std::string& data) override;
};