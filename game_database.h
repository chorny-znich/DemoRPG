#pragma once
#include <disreality_engine.h>
#include <unordered_map>
#include <memory>

/**
 * @brief 
 */
class GameDatabase
{
private:
  GameDatabase() = default;
public:
  GameDatabase(const GameDatabase&) = delete;
  GameDatabase& operator=(const GameDatabase&) = delete;
  static GameDatabase& instance()
  {
    static GameDatabase database;
    return database;
  }

  void init();
  dr::GameObject* getItem(std::uint16_t id);
  //static Enemy& getEnemy(size_t id);
private:
  std::unordered_map<size_t, std::shared_ptr<dr::GameObject>> mItemDatabase;
  //std::unordered_map<size_t, Enemy> mEnemyDatabase;
};