#include "npc_factory.hpp"
#include <stdexcept>
#include <sstream>

void NpcFactory::registerCreator(const std::string& type, CreatorFunc creator) { creators[type] = creator; }

NpcPtr NpcFactory::createNPC(const std::string& type, const std::string& name, int x, int y) {
    auto it = creators.find(type);
    if (it != creators.end()) {
        return it->second(name, x, y);
    }
    throw std::invalid_argument("Unknown NPC type: " + type);
}

NpcPtr NpcFactory::loadNPC(const std::string& data) {
    std::istringstream iss(data);
    std::string type, name;
    int x, y;
    
    if (!(iss >> type >> name >> x >> y)) {
        throw std::invalid_argument("Invalid NPC data format");
    }
    
    return createNPC(type, name, x, y);
}