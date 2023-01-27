#include "battlestate.hpp"

//Con-/Destructors
BattleState::BattleState(sf::Font* font, sf::Vector2f* mousePosView, std::stack<State*>* states)
    : State(font, mousePosView, states){
    this->font = font;
    this->mousePosView = mousePosView;
    this->states = states;

    std::cout <<"BattleState Here" <<std::endl;

    initTextures();
    initEntities();

    if(!this->bgTexture.loadFromFile("assets/prototype_background_big.png"))
        std::printf("ERROR BG TEXTURE NOT LOADED IN MENU!\n");

    this->bg.setTexture(this->bgTexture);
    this->bg.setScale(sf::Vector2f(0.5,0.5));
    this->bg.setPosition(sf::Vector2f(-200,0));

    this->attackButton.defineAll(1280.0/3*2+100, 720.0/3, 200, 50, "Attack", font, true);
    this->healButton.defineAll(1280.0/3*2+100, 720.0/3*2-150, 200, 50, "Heal", font, true);
    this->quitButton.defineAll(1280.0/3*2+100, 720.0/3*3-300, 200, 50, "Quit", font, true);
}

BattleState::~BattleState()= default;

//Functions


void BattleState::update() {
    //Update Mouse Position
    this->attackButton.update(*mousePosView);
    this->healButton.update(*mousePosView);
    this->quitButton.update(*mousePosView);


    this->battle();


}

void BattleState::render(sf::RenderWindow& renderWindow) {
    renderWindow.draw(this->bg);
    attackButton.render(renderWindow);
    healButton.render(renderWindow);
    quitButton.render(renderWindow);
    this->player.render(renderWindow);
    this->enemy.render(renderWindow);
}

void BattleState::endState() {
    // LATER: add score to list here
    std::cout <<"Ending BattleState" <<std::endl;
}

void BattleState::initTextures() {

    if(!this->textures["PLAYER"].loadFromFile("assets/placeholder.png"))
        std::printf("ERROR PLAYER TEXTURE NOT LOADED IN!\n");

}

void BattleState::initEntities() {
    this->player.createSprite(&textures["PLAYER"], 0.7);
    this->player.setPosition(500,175);
    this->player.createStatsComponent(1, rd);

    this->spawnEnemy();
    std::cout << "PLAYER" << std::endl;
    this->player.update();
    std::cout << "ENEMY" << std::endl;
    this->enemy.update();

    this->setInitiative();


}

void BattleState::spawnEnemy() {
    this->enemy.createSprite(&textures["PLAYER"], 0.7);
    this->enemy.setPosition(100,175);
    this->enemy.createStatsComponent(1, rd);
}

void BattleState::battle() {

    if(this->player.statsComponent->hasTurn){
        this->playerTurn();
    }
    else
        this->enemyTurn();


}

//Test This!
void BattleState::setInitiative() {
    if(this->player.statsComponent->speed >= this->enemy.statsComponent->speed ) {
        player.statsComponent->hasTurn = true;
        std::cout << "PLAYER starts" << std::endl;

    }
    else{
        enemy.statsComponent->hasTurn = true;
        std::cout << "ENEMY starts" << std::endl;
    }


}

//Test this!
void BattleState::playerTurn(){
    //sequence works until here
    //std::cout << "PLAYER engages" << std::endl;

            //Attack
            if (attackButton.isClicked()) {
                std::cout << "Player attacks" << std::endl;
                this->player.statsComponent->attack(&enemy);

                if(this->enemy.statsComponent->hp <= 0)
                    this->battleWon();

                else {
                    this->player.statsComponent->hasTurn = false;
                    this->enemy.statsComponent->hasTurn = true;
                }

                this->player.update();
                this->enemy.update();

            }
            //Heal
            if (healButton.isClicked()) {
                std::cout << "Player heals" << std::endl;
                if(this->player.statsComponent->hp < this->player.statsComponent->hpMax
                   && this->player.statsComponent->heals > 0){

                    this->player.statsComponent->heal();

                    this->player.statsComponent->hasTurn = false;
                    this->enemy.statsComponent->hasTurn = true;
                }
                this->player.update();
                this->enemy.update();
            }
            //Quit
            if (quitButton.isClicked()) {

                quit();
            }


}

//Test this!
void BattleState::enemyTurn(){
    std::uniform_int_distribution<int> distLow(0,2);
    std::cout << "ENEMY approaches" << std::endl;
    if(this->enemy.statsComponent->hasTurn){

        switch(distLow(rd)) {
            case PASS:
                std::cout << "ENEMY passes" << std::endl;
                this->player.statsComponent->hasTurn = false;
                this->enemy.statsComponent->hasTurn = true;
                break;

            case HEAL:
                std::cout << "ENEMY heals" << std::endl;
                if (this->enemy.statsComponent->hp < this->enemy.statsComponent->hpMax
                    && this->enemy.statsComponent->heals > 0) {
                    this->enemy.statsComponent->heal();
                }
                this->enemy.statsComponent->hasTurn = false;
                this->player.statsComponent->hasTurn = true;
                break;

            case ATTACK:
                std::cout << "Enemy attacks" << std::endl;
                this->player.statsComponent->attack(&player);

                if (this->player.statsComponent->hp <= 0)
                    this->battleLost();

                else{
                    this->enemy.statsComponent->hasTurn = false;
                    this->player.statsComponent->hasTurn = true;
                }
                break;
    }


    }

    this->player.update();
    this->enemy.update();
    }


void BattleState::battleLost() {
    std::cout << "PLAYER LOST" << std::endl;
    this->quit();
}

void BattleState::battleWon() {
    std::cout << "PLAYER WON" << std::endl;
    this->enemy.respawn(this->player.statsComponent->level, rd , &player);
}

