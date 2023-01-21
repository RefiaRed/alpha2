#include "menustate.hpp"

//Con-/Destructors

MenuState::MenuState()
: State(){
    std::cout <<"MenuState Here" <<std::endl;
    this->bg.setSize(sf::Vector2f(1280, 720));
    this->bg.setFillColor(sf::Color::Cyan);
}


MenuState::~MenuState() {

}

//Functions
void MenuState::update() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        std::cout << "MenuState update" << std::endl;

    this->updateKeybinds();
}

void MenuState::render(sf::RenderWindow &renderWindow) {
    renderWindow.draw(this->bg);
}

void MenuState::endState() {
    std::cout <<"Ending MenuState" <<std::endl;
}

void MenuState::updateKeybinds() {
    this->checkQuit();
}


