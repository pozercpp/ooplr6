#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>

#include <npc.hpp>
#include <squirrel.hpp>
#include <druid.hpp>
#include <ork.hpp>

const int FIELD_SIZE = 200;
const int KILL_RADIUS = 30;

void print_field(const std::vector<std::shared_ptr<NPC>>& npcs) {
    std::cout << "\n=== Текущее состояние ===\n";
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            char symbol = ' ';
            switch (npc->getType()) {
                case SquirrelType: symbol = 'S'; break;
                case DruidType:    symbol = 'D'; break;
                case OrkType:      symbol = 'O'; break;
                default:           symbol = '?'; break;
            }
            std::cout << symbol << " " << npc->getName() 
                      << " (" << npc->getX() << "," << npc->getY() << ")\n";
        }
    }
    std::cout << "==========================\n\n";
}

int main() {
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(std::make_shared<Squirrel>("Бельчонок", 10, 10));
    npcs.push_back(std::make_shared<Squirrel>("Шустрик",   15, 20));
    npcs.push_back(std::make_shared<Druid>("Мерлин",      50, 50));
    npcs.push_back(std::make_shared<Druid>("Радагайс",    60, 45));
    npcs.push_back(std::make_shared<Ork>("Громмаш",       100, 100));
    npcs.push_back(std::make_shared<Ork>("Тралл",         110, 95));
    npcs.push_back(std::make_shared<Squirrel>("Пушистик", 120, 80));
    std::cout << "Игра началась! Всего NPC: " << npcs.size() << "\n\n";
    int turn = 1;
    const int MAX_TURNS = 20;
    while (turn <= MAX_TURNS) {
        std::cout << "=== Ход " << turn << " ===\n";
        bool any_fight = false;
        std::vector<std::shared_ptr<NPC>*> alive;
        for (auto& npc : npcs) {
            if (npc->isAlive()) {
                alive.push_back(&npc);
            }
        }
        for (size_t i = 0; i < alive.size(); ++i) {
            for (size_t j = 0; j < alive.size(); ++j) {
                if (i == j) continue;
                auto& attacker = *alive[i];
                auto& victim = *alive[j];
                if (!attacker->isAlive() || !victim->isAlive()) continue;
                double dist = attacker->distanceTo(victim);
                if (dist <= KILL_RADIUS) {
                    any_fight = true;
                    std::cout << attacker->getName() << " ("  << (attacker->getType() == SquirrelType ? "S" : attacker->getType() == DruidType ? "D" : "O") << ") атакует " << victim->getName() << " на расстоянии " << static_cast<int>(dist) << "\n";
                    attacker->fight(victim);
                    if (!victim->isAlive()) {
                        std::cout << "  >>> " << victim->getName() << " погибает!\n";
                    }
                    if (!attacker->isAlive()) {
                        std::cout << "  >>> " << attacker->getName() << " погибает в бою!\n";
                    }
                }
            }
        }
        print_field(npcs);
        if (!any_fight) {
            std::cout << "Больше никто не дерётся. Бои окончены.\n";
            break;
        }

        turn++;
    }
    std::ofstream out("alive.txt");
    if (out.is_open()) {
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                npc->save(out);
            }
        }
        std::cout << "Выжившие сохранены в alive.txt\n";
    }
    std::cout << "\nИгра завершена.\n";
    return 0;
}