#include "menustate.hpp"

//Con-/Destructors

MenuState::MenuState()
: State(){
    std::cout <<"MenuState Here" <<std::endl;
}


MenuState::~MenuState() {

}

//Functions
void MenuState::update() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        std::cout << "MenuState update" << std::endl;

    this->updateKeybinds();
}

void MenuState::render() {

}

void MenuState::endState() {
    std::cout <<"Ending MenuState" <<std::endl;
}

void MenuState::updateKeybinds() {
    this->checkQuit();
}
