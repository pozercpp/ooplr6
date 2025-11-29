#pragma once

#include<vector>
#include<string>
#include<memory>
#include<map>

enum NpcType {
    Unknown = 0,
    SquirrelType = 1,
    DruidType = 2,
    OrkType = 3
};

const std::map<NpcType, NpcType> can_kill = {{DruidType, SquirrelType}, {OrkType, DruidType}};

struct NPC {
    NpcType type;
    std::string name;

    int x, y;
    bool alive;

    NPC();
    virtual ~NPC() noexcept;
    NPC(const std::string& name_, int x_, int y_);

    void fight(std::shared_ptr<NPC> other);
    
    std::string getName() const;
    NpcType getType() const;
    int getX() const;
    int getY() const;

    bool isAlive() const;
    void die();

    double distanceTo(const std::shared_ptr<NPC>& other) const;

    void save(std::ostream& os) const;
};