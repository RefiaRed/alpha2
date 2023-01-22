#include "battlestate.hpp"

//Con-/Destructors
BattleState::BattleState(sf::Font* font, sf::Vector2f* mousePosView)
    : State(font, mousePosView){
    this->font = font;
    this->mousePosView = mousePosView;
    std::cout <<"BattleState Here" <<std::endl;
}

BattleState::~BattleState(){

}

//Functions
void BattleState::update() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        std::cout << "BattleState update" << std::endl;


    this->player.update();

}

void BattleState::render(sf::RenderWindow& renderWindow) {
    this->player.render(renderWindow);
}

void BattleState::endState() {

    std::cout <<"Ending BattleState" <<std::endl;
}

