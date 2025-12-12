#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <random>
#include <fstream>
#include <sstream>
#include <functional>

#include "BattleManager.hpp"
#include "npc.hpp"
#include "druid.hpp"
#include "squirrel.hpp"
#include "ork.hpp"
#include "INpcFactory.hpp"
#include "npc_factory.hpp"
#include "fight_visitor.hpp"
#include "IFightObserver.hpp"
#include "ConsoleLogger.hpp"
#include "FileLogger.hpp"


int main() {
    BattleManager manager;
    
    manager.addObserver(ConsoleLogger::get());
    manager.addObserver(FileLogger::get());

    auto factory = std::make_shared<NpcFactory>();
    factory->registerCreator("Druid", [](const std::string& name, int x, int y) {
        return std::make_shared<Druid>(name, x, y);
    });
    factory->registerCreator("Squirrel", [](const std::string& name, int x, int y) {
        return std::make_shared<Squirrel>(name, x, y);
    });
    factory->registerCreator("Ork", [](const std::string& name, int x, int y) {
        return std::make_shared<Ork>(name, x, y);
    });

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> typeDist(0, 2);
    std::uniform_int_distribution<> coordDist(0, 100);
    std::uniform_int_distribution<> nameDist(1, 1000);

    std::vector<std::string> types = {"Druid", "Squirrel", "Ork"};

    for (int i = 0; i < 50; ++i) {
        std::string type = types[typeDist(gen)];
        std::string name = "NPC_" + std::to_string(nameDist(gen));
        int x = coordDist(gen);
        int y = coordDist(gen);
        
        auto npc = factory->createNPC(type, name, x, y);
        manager.addNPC(npc);
    }

    std::cout << "Initial NPCs:\n";
    manager.printNPCs();

    for (int distance = 10; distance <= 100 && manager.getAliveCount() > 1; distance += 10) {
        std::cout << "\n=== Battle with distance " << distance << " ===\n";
        manager.battle(distance);
        manager.printNPCs();
    }

    manager.saveToFile("survivors.txt");
    std::cout << "\nSurvivors saved to survivors.txt\n";

    return 0;
}