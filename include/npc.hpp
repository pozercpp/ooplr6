#pragma once

#include <iostream>
#include <memory>
#include <vector>

struct Squirrel;
struct Druid;
struct Ork;

struct IFightObserver {
  virtual void on_fight(const std::shared_ptr<struct NPC> &attacker, const std::shared_ptr<struct NPC> &defender, bool win) = 0;
  virtual ~IFightObserver() = default;
};

struct NPC : public std::enable_shared_from_this<NPC> {
  std::string name, type;
  int x{0};
  int y{0};
  std::vector<std::shared_ptr<IFightObserver>> observers;
  NPC() = default;
  NPC(const std::string &name_, int x_, int y_);
  ~NPC() noexcept = default;
  void subscribe(std::shared_ptr<IFightObserver> observer);
  void fight_notify(const std::shared_ptr<NPC>& defender, bool win);
  bool is_close(const std::shared_ptr<NPC>& other, size_t distance) const;
  virtual bool accept(const std::shared_ptr<NPC>& attacker) = 0;
  virtual bool visit_squirrel(const std::shared_ptr<Squirrel>& defender) = 0;
  virtual bool visit_druid(const std::shared_ptr<Druid>& defender) = 0;
  virtual bool visit_ork(const std::shared_ptr<Ork>& defender) = 0;
  virtual void print() const = 0;
  virtual void save(std::ostream& os) const;
  friend std::ostream &operator<<(std::ostream& os, const NPC& npc);
};