#pragma once

#include "headers.hpp"

#include "state.hpp"

class State;
class Entity;
class Button;

class BattleState :
        public State {
private:
    bool isPaused = true;
    int scoreCount = 0;
    int roundCount = 1;

    std::random_device rd;

    sf::Sprite bg;
    sf::Texture bgTexture;
    sf::RectangleShape overlayBg;
    sf::RectangleShape pauseBg;

    Entity player;
    Entity enemy;

    /*-------------Actions--------------*/
    //inBattle
    enum EnemyAction { PASS, HEAL, ATTACK};
    Button attackButton;
    Button healButton;
    Button quitButton;
    //isPaused
    Button continueButton;
    Button exitButton;

    /*-------Battle Info-----------------*/
    sf::Text infoText;
    sf::Text scoreText;
    std::stringstream scoreStream;
    sf::Text wonText;
    sf::Text roundText;
    std::stringstream roundStream;
    //Stats
    std::stringstream pStats;
    sf::Text statInfoP;
    std::stringstream eStats;
    sf::Text statInfoE;

    //Inits
    void initText();
    void initUI();
    void initStatInfo();
    void initTextures();
    void initEntities();

public:
    //Con-/Destructors
    BattleState(sf::Font* font, sf::Vector2f* mousePosView, std::stack<State*>* states, ScoreManager* scoreManager);
    ~BattleState() override;

    /*---------Functions---------------*/
    void render(sf::RenderWindow& renderWindow) override;
    void endState() override;
    void spawnEnemy();
    //Battle
    void setInitiative();
    void battle();
    void playerTurn();
    void enemyTurn();
    void battleLost();
    void battleWon();
    //Updates
    void update() override;
    void updateUI();
    void updateStatInfo();






};



