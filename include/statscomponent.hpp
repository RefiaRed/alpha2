#pragma  once

#include "headers.hpp"
#include "entity.hpp"

class Entity;
class StatsComponent {
public:
    int level;
    int exp;
    int expNext;
    int heals;

    //Attributes
    int health;
    int strength;
    int speed;

    bool hasTurn = false;

    //Stats
    int hp;
    int hpMax;
    int atk;
    int def;

    StatsComponent(int level, std::random_device& rd);
    ~StatsComponent();

    void updateStats();
    void calculateExpNext();
    void levelUp();
    void gainExp(int xp);

    std::string debugPrint() const;

    //Actions
    void attack(Entity* target);
    void heal();
    void rollNewStats(std::random_device& rd);


};


