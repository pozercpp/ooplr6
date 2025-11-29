#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <npc.hpp>
#include <squirrel.hpp>
#include <druid.hpp>
#include <ork.hpp>

TEST(NPCBasic, Creation) {
    Squirrel s("Nutty", 10, 20);
    EXPECT_EQ(s.getName(), "Nutty");
    EXPECT_EQ(s.getX(), 10);
    EXPECT_EQ(s.getY(), 20);
    EXPECT_TRUE(s.isAlive());
    EXPECT_EQ(s.getType(), SquirrelType);
}


TEST(NPCDistance, DistanceCalculation) {
    auto a = std::make_shared<Druid>("Merlin", 0, 0);
    auto b = std::make_shared<Squirrel>("Fluffy", 3, 4);
    double dist = a->distanceTo(b);
    EXPECT_NEAR(dist, 5.0, 0.0001);
}

TEST(NPCFight, KillRules) {
    auto ork = std::make_shared<Ork>("Thrall", 100, 100);
    auto druid = std::make_shared<Druid>("Malfurion", 105, 100);
    EXPECT_TRUE(druid->isAlive());
    EXPECT_TRUE(ork->isAlive());
    auto druid2  = std::make_shared<Druid>("Cenarius", 50, 50);
    auto squirrel = std::make_shared<Squirrel>("Chip", 51, 50);
    druid2->fight(squirrel);
    EXPECT_FALSE(squirrel->isAlive());
    EXPECT_TRUE(druid2->isAlive());
    auto squirrel2 = std::make_shared<Squirrel>("Dale", 10, 10);
    auto ork2 = std::make_shared<Ork>("Garrosh", 15, 10);
    squirrel2->fight(ork2);
    EXPECT_TRUE(ork2->isAlive());
    EXPECT_TRUE(squirrel2->isAlive());
}

TEST(NPCFight, MutualKill) {
    auto ork = std::make_shared<Ork>("Grom", 100, 100);
    auto druid = std::make_shared<Druid>("Hamul", 100, 100);
    ork->fight(druid);
    druid->fight(ork);
    EXPECT_FALSE(druid->isAlive());
    EXPECT_TRUE(ork->isAlive());
}

TEST(NPCSave, SaveToStream) {
    auto npc = std::make_shared<Squirrel>("Acorn", 30, 40);

    std::ostringstream oss;
    npc->save(oss);
    std::string expected = "1 Acorn 30 40\n";
    EXPECT_EQ(oss.str(), expected);
}

TEST(NPCDeath, DieOnce) {
    auto s = std::make_shared<Squirrel>("Victim", 0, 0);
    auto d = std::make_shared<Druid>("Killer", 5, 0);
    d->fight(s);
    EXPECT_FALSE(s->isAlive());
    d->fight(s);
    EXPECT_FALSE(s->isAlive());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}