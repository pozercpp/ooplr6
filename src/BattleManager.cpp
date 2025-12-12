#include "BattleManager.hpp"

void BattleManager::addObserver(const IFightObserverPtr& obs) { observers.push_back(obs); }

void BattleManager::notifyObservers(const std::string& message) {
    for (const auto& observer : observers) { observer->onFightOutcome(message); }
}

void BattleManager::addNPC(const NpcPtr& npc) { npcs.push_back(npc); }

void BattleManager::printNPCs() const {
    std::cout << "NPCs alive: " << getAliveCount() << "\n";
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            auto posx = npc->getX(), posy = npc->getY();
            std::cout << npc->getType() << " " << npc->getName() << " at (" << posx << ", " << posy << ")\n";
        }
    }
}

void BattleManager::battle(double maxDistance) {
    bool changes = true;
    while (changes && npcs.size() >= 2) {
        changes = false;
        for (size_t i = 0; i < npcs.size(); ++i) {
            if (!npcs[i]->isAlive()) continue;
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (!npcs[j]->isAlive()) continue;
                NpcPtr npc1 = npcs[i];
                NpcPtr npc2 = npcs[j];
                if (npc1->dist(npc2) <= maxDistance) {
                    bool npc1WasAlive = npc1->isAlive();
                    bool npc2WasAlive = npc2->isAlive();
                    auto visitor1 = std::make_shared<FightVisitor>(npc1);
                    npc2->fight(visitor1);
                    if (npc1->isAlive() && npc2->isAlive()) {
                        auto visitor2 = std::make_shared<FightVisitor>(npc2);
                        npc1->fight(visitor2);
                    }
                    bool someoneDied = (npc1WasAlive && !npc1->isAlive()) || (npc2WasAlive && !npc2->isAlive());
                    if (someoneDied) {
                        changes = true;
                        std::stringstream ss;
                        if (!npc1->isAlive() && !npc2->isAlive()) {
                            ss << "BOTH DIED: " << npc1->Type() << " (" << npc1->getName() 
                               << ") and " << npc2->Type() << " (" << npc2->getName() 
                               << ") killed each other.";
                        } else if (!npc2->isAlive()) {
                            ss << "KILL: " << npc1->Type() << " (" << npc1->getName() 
                               << ") killed " << npc2->Type() << " (" << npc2->getName() << ").";
                        } else if (!npc1->isAlive()) {
                            ss << "KILL: " << npc2->Type() << " (" << npc2->getName() 
                               << ") killed " << npc1->Type() << " (" << npc1->getName() << ").";
                        }
                        
                        notifyObservers(ss.str());
                    }
                }
            }
        }
        if (changes) {
            removeDeadNPCs();
        }
    }
}

void BattleManager::removeDeadNPCs() {
    npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
               [](const NpcPtr& npc) { return !npc->isAlive(); }),
               npcs.end());
}

void BattleManager::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << " for writing.\n";
        return;
    }
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            npc->save(file);
            file << '\n';
        }
    }
    
    file.close();
}
size_t BattleManager::getAliveCount() const { 
    return std::count_if(npcs.begin(), npcs.end(),
                        [](const NpcPtr& npc) { return npc->isAlive(); });
}