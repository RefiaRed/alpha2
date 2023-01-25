#pragma once

#include "headers.hpp"

#include "state.hpp"

class State;
class Entity;



class BattleState :
        public State {
private:
    sf::Sprite bg;
    sf::Texture bgTexture;

    Entity player;
    Entity enemy;

    Button attackButton;
    Button healButton;
    Button quitButton;

    enum EnemyAction { PASS, HEAL, ATTACK};






    void initTextures();
    void initEntities();
public:

    std::random_device rd;

    //Con-/Destructors
    BattleState(sf::Font* font, sf::Vector2f* mousePosView, std::stack<State*>* states);
    ~BattleState() override;

    //Functions
    virtual void update() override;
    virtual void render(sf::RenderWindow& renderWindow) override;
    virtual void endState() override;

    void spawnEnemy();


    void setInitiative();
    void battle();

    void playerTurn();
    void enemyTurn();
    void battleLost();
    void battleWon();


};



