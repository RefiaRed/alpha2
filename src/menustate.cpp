#include "menustate.hpp"

//Con-/Destructors

MenuState::MenuState(sf::Font* font, sf::Vector2f* mousePosView, std::stack<State*>* states)
: State(font, mousePosView, states){
    std::cout <<"MenuState Here" <<std::endl;
    this->states = states;
    this->font = font;

    initBackground();

    this->startButton.defineAll(bg.getSize().x/2, bg.getSize().y/3, 200, 50, "Start", font, true);
    this->eraseButton.defineAll(bg.getSize().x/2, bg.getSize().y/3*2-150, 200, 50, "Erase Score", font, false);
    this->quitButton.defineAll(bg.getSize().x/2, bg.getSize().y/3*3-300, 200, 50, "Quit", font, true);



}


MenuState::~MenuState() {

}

//Functions
void MenuState::update() {

    this->startButton.update(*mousePosView);
    this->eraseButton.update(*mousePosView);
    this->quitButton.update(*mousePosView);

    if(startButton.isClicked()){
        this->states->push(new BattleState(this->font, this->mousePosView, this->states));
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

//Inits
void MenuState::initBackground() {

    if(!this->bgTexture.loadFromFile("assets/prototype_background_big.png"))
        std::printf("ERROR BG TEXTURE NOT LOADED IN MENU!\n");

    this->bg.setTexture(&this->bgTexture);
    this->bg.setSize(sf::Vector2f(1280, 720));
}



