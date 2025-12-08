#include <cstring>
#include <ctime>
#include <fstream>
#include <set>


#include "factory.hpp"
#include "npc.hpp"

void save(const std::set<std::shared_ptr<NPC>>& array, const std::string& filename) {
  std::ofstream fs(filename);
  fs << array.size() << std::endl;
  for (auto &n : array) {n->save(fs);}
  fs.flush();
  fs.close();
}

std::set<std::shared_ptr<NPC>> load(const std::string &filename) {
  std::set<std::shared_ptr<NPC>> res;
  std::ifstream is(filename);
  if (is.good() && is.is_open()) {
    int count;
    is >> count;
    for (int i = 0; i < count; ++i) {res.insert(factory(is));}
    is.close();
  } else {
    std::cerr << "Error: " << std::strerror(errno) << std::endl;
  }
  return res;
}

std::ostream &operator<<(std::ostream &os, const std::set<std::shared_ptr<NPC>>& array) {
  for (const auto& n : array) {n->print();}
  return os;
}

std::set<std::shared_ptr<NPC>> fight(const std::set<std::shared_ptr<NPC>>& array, size_t distance) {
  std::set<std::shared_ptr<NPC>> dead_list;
  for (const auto& attacker : array) {
    for (const auto& defender : array) {
      if ((attacker != defender) && attacker->is_close(defender, distance) && !dead_list.count(defender)) {
        if (defender->accept(attacker)) {
          dead_list.insert(defender);
          attacker->fight_notify(defender, true);
        }
      }
    }
  }
  return dead_list;
}

int main() {
  std::srand(std::time(0));
  std::set<std::shared_ptr<NPC>> array;
  std::cout << "Generating ..." << std::endl;
  for (size_t i = 0; i < 10; ++i) {
    auto type = static_cast<NpcType>(std::rand() % 3 + 1);
    array.insert(factory(type, "NPC_" + std::to_string(i), std::rand() % 100, std::rand() % 100));
  }
  std::cout << "Saving ..." << std::endl;
  save(array, "npc.txt");
  std::cout << "Loading ..." << std::endl;
  array = load("npc.txt");
  std::cout << "Initial state:" << std::endl << array;
  std::cout << "Fighting ..." << std::endl;
  for (size_t distance = 20; (distance <= 100) && !array.empty(); distance += 10) {
    auto dead_list = fight(array, distance);
    for (auto &d : dead_list) {array.erase(d);}
    std::cout << "Fight stats ----------" << std::endl
              << "distance: " << distance << std::endl
              << "killed: " << dead_list.size() << std::endl
              << "survivors: " << array.size() << std::endl
              << std::endl;
  }
  std::cout << "Survivors:" << std::endl;
  for (auto &n : array) {n->print();}
  return 0;
}