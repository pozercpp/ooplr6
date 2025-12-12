#pragma once

#include "npc.hpp"
#include "fight_visitor.hpp"
#include "IFightObserver.hpp"
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

class BattleManager {
private:
    std::vector<NpcPtr> npcs;
    std::vector<IFightObserverPtr> observers;
public:
    BattleManager() = default;
    ~BattleManager() noexcept = default;
    void addObserver(const IFightObserverPtr& obs);
    void notifyObservers(const std::string& message);
    void addNPC(const NpcPtr& npc);
    void printNPCs() const;
    void battle(double maxDistance);
    void saveToFile(const std::string& filename);
    size_t getAliveCount() const;
    void clear() { npcs.clear(); }
    const std::vector<NpcPtr>& getNPCs() const { return npcs; }
    void removeDeadNPCs();
};