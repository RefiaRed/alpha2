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
    this->healButton.defineAll(1280.0/3*2+100, 720.0/3*2-150, 200, 50, "Heal", font, false);
    this->quitButton.defineAll(1280.0/3*2+100, 720.0/3*3-300, 200, 50, "Quit", font, true);
}

BattleState::~BattleState(){

}

//Functions


void BattleState::update() {

    this->player.update();

    this->attackButton.update(*mousePosView);
    this->healButton.update(*mousePosView);
    this->quitButton.update(*mousePosView);

    if(attackButton.isClicked()){

    }
    if(healButton.isClicked()){
        quit();
    }
    if(quitButton.isClicked()){
        quit();
    }

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

    std::cout <<"Ending BattleState" <<std::endl;
}

void BattleState::initTextures() {

    if(!this->textures["PLAYER"].loadFromFile("assets/placeholder.png"))
        std::printf("ERROR PLAYER TEXTURE NOT LOADED IN!\n");

}

void BattleState::initEntities() {
    this->player.createSprite(&textures["PLAYER"], 0.7);
    this->player.setPosition(500,175);

    this->enemy.createSprite(&textures["PLAYER"], 0.7);
    this->enemy.setPosition(100,175);
}

