#pragma once

#include<iostream>
#include <memory>
#include <string>

class IFightVisitor;

enum NpcType {SquirrelType, OrkType, DruidType};

class NPC {
protected:
    std::string name;
    int x, y;
    bool alive = true;
    NpcType type;
public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    void save (std::ostream& os) const;

    std::string getName() const { return name; }
    NpcType getType() const { return type; }
    int getX() const { return x; }
    int getY() const { return y; }

    void fight(const std::shared_ptr<IFightVisitor>& visitor);
    bool isAlive() const { return alive; }
    void die() { alive = false; }

    double dist(const std::shared_ptr<NPC>& other) const;

    virtual std::string Type() const = 0;
    void print() const {std::cout << Type() << " " << name << " at (" << x << ", " << y << ")" << (alive ? " Alive" : " Dead") << std::endl;}
};

using NpcPtr = std::shared_ptr<NPC>;