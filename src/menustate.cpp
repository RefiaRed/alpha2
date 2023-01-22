#include "menustate.hpp"

//Con-/Destructors

MenuState::MenuState(sf::Font* font, sf::Vector2f* mousePosView)
: State(font, mousePosView){
    std::cout <<"MenuState Here" <<std::endl;
    this->bg.setSize(sf::Vector2f(1280, 720));
    this->bg.setFillColor(sf::Color::Cyan);
    this->font = font;

    this->startButton.defineAll(bg.getSize().x/2, 200, 200, 50, "Start", font, true);
    this->eraseButton.defineAll(bg.getSize().x/2, 500, 200, 50, "Erase Score", font, false);
    this->quitButton.defineAll(bg.getSize().x/2, 700, 200, 50, "Quit", font, true);



}


MenuState::~MenuState() {

}

//Functions
void MenuState::update() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        std::cout << "MenuState update" << std::endl;

    this->startButton.update(*mousePosView);
    this->eraseButton.update(*mousePosView);
    this->quitButton.update(*mousePosView);
    if(startButton.isClicked()){

    }
    if(startButton.isClicked()){
        quit();
    }
    if(eraseButton.isClicked()){
        quit();
    }
    if(quitButton.isClicked()){
        quit();
    }


}

void MenuState::render(sf::RenderWindow &renderWindow) {
    renderWindow.draw(this->bg);
    startButton.render(renderWindow);
    eraseButton.render(renderWindow);
    quitButton.render(renderWindow);

}

void MenuState::endState() {
    std::cout <<"Ending MenuState" <<std::endl;
}



