#include "factory.hpp"

#include "squirrel.hpp"
#include "druid.hpp"
#include "ork.hpp"
#include "observers.hpp"

std::shared_ptr<NPC> factory(NpcType type, const std::string &name, int x, int y) {
  std::shared_ptr<NPC> res;
  switch (type) {
    case SquirrelType:
        res = std::make_shared<Squirrel>(name, x, y);
        break;
    case DruidType:
        res = std::make_shared<Druid>(name, x, y);
        break;
    case OrkType:
        res = std::make_shared<Ork>(name, x, y);
        break;
    default:
        break;
  }
  if (res) {
    res->subscribe(TextObserver::get());
    res->subscribe(FileObserver::get());
  }
  return res;
}

std::shared_ptr<NPC> factory(std::istream &is) {
    std::shared_ptr<NPC> res;
    int type = 0;
    if (is >> type) {
        std::string name;
        int x, y;
        if (!(is >> name >> x >> y)) {
            std::cerr << "Invalid NPC entry in file\n";
            return nullptr;
        }
        switch (type) {
            case SquirrelType:
                res = std::make_shared<Squirrel>(name, x, y);
                break;
            case DruidType:
                res = std::make_shared<Druid>(name, x, y);
                break;
            case OrkType:
                res = std::make_shared<Ork>(name, x, y);
                break;
            default:
                break;
        }
    }
    if (res) {
        res->subscribe(TextObserver::get());
        res->subscribe(FileObserver::get());
    }
    return res;
}