#include "battlestate.hpp"

//Con-/Destructors
BattleState::BattleState()
    : State(){
    std::cout <<"BattleState Here" <<std::endl;
}

BattleState::~BattleState(){

}

//Functions
void BattleState::update() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        std::cout << "BattleState update" << std::endl;

    this->updateKeybinds();

}

void BattleState::render() {

}

void BattleState::endState() {

    std::cout <<"Ending BattleState" <<std::endl;
}

void BattleState::updateKeybinds() {
    this->checkQuit();
}

