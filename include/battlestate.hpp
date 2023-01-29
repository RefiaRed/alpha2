#pragma once

#include "headers.hpp"

#include "state.hpp"

class State;
class Entity;
class Button;



class BattleState :
        public State {
private:
    sf::Sprite bg;
    sf::Texture bgTexture;

    sf::RectangleShape overlayBg;
    sf::RectangleShape pauseBg;

    Entity player;
    Entity enemy;
    int scoreCount = 0;
    int roundCount = 1;

    //inBattle
    Button attackButton;
    Button healButton;
    Button quitButton;
    //isPaused
    Button continueButton;
    Button exitButton;

    enum EnemyAction { PASS, HEAL, ATTACK};
    /*-------Battle Info-----------------*/
    sf::Text infoText;
    sf::Text scoreText;
    std::stringstream scoreStream;

    sf::Text wonText;

    sf::Text roundText;
    std::stringstream roundStream;
    //Stats
    std::stringstream pStats;
    std::stringstream eStats;

    sf::Text statInfoP;
    sf::Text statInfoE;







    void initTextures();
    void initEntities();
public:
    bool isPaused = true;
    std::random_device rd;


    //Con-/Destructors
    BattleState(sf::Font* font, sf::Vector2f* mousePosView, std::stack<State*>* states, ScoreManager* scoreManager);
    ~BattleState() override;

    //Functions
    void update() override;
    void render(sf::RenderWindow& renderWindow) override;
    void endState() override;

    void spawnEnemy();


    void setInitiative();
    void battle();

    void playerTurn();
    void enemyTurn();
    void battleLost();
    void battleWon();

    void initStatInfo();
    void updateStatInfo();
    void updateUI();


};



