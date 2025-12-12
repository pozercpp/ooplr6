#include <gtest/gtest.h>
#include "druid.hpp"
#include "squirrel.hpp"
#include "ork.hpp"
#include <cmath>
#include <sstream>

TEST(NPCTest, InitialState) {
    auto druid = std::make_shared<Druid>("S", 0, 0);
    EXPECT_TRUE(druid->isAlive());
    EXPECT_EQ(druid->getName(), "S");
    EXPECT_EQ(druid->Type(), "Druid");
}

TEST(NPCTest, KillNPC) {
    auto squirrel_npc = std::make_shared<Squirrel>("Arthur", 10, 10);
    EXPECT_TRUE(squirrel_npc->isAlive());
    squirrel_npc->die();
    EXPECT_FALSE(squirrel_npc->isAlive());
}

TEST(NPCTest, DistanceCalculation) {
    auto druid_npc = std::make_shared<Druid>("D", 0, 0);
    auto squirrel_npc = std::make_shared<Squirrel>("K", 3, 4);
    double distance = druid_npc->dist(squirrel_npc);
    EXPECT_DOUBLE_EQ(distance, 5.0);
}

TEST(NPCTest, SaveToStream) {
    auto druid_npc = std::make_shared<Druid>("s", 100, 200);
    std::ostringstream oss;
    druid_npc->save(oss);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("s"), std::string::npos);
}

TEST(NPCTest, TypeCheck) {
    auto druid = std::make_shared<Druid>("Druid1", 0, 0);
    auto squirrel = std::make_shared<Squirrel>("Squirrel1", 0, 0);
    auto ork = std::make_shared<Ork>("Ork1", 0, 0);
    EXPECT_EQ(druid->Type(), "Druid");
    EXPECT_EQ(squirrel->Type(), "Squirrel");
    EXPECT_EQ(ork->Type(), "Ork");
}

TEST(NPCTest, Coordinates) {
    auto npc = std::make_shared<Druid>("Test", 42, 24);
    EXPECT_EQ(npc->getX(), 42);
    EXPECT_EQ(npc->getY(), 24);
}

TEST(NPCTest, DieMethod) {
    auto npc = std::make_shared<Squirrel>("Test", 0, 0);
    EXPECT_TRUE(npc->isAlive());
    npc->die();
    EXPECT_FALSE(npc->isAlive());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}