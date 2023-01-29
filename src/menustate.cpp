#include "menustate.hpp"

//Con-/Destructors

MenuState::MenuState(sf::Font* font, sf::Vector2f* mousePosView, std::stack<State*>* states, ScoreManager* scoreManager)
: State(font, mousePosView, states, scoreManager){

    this->states = states;
    this->font = font;
    this->scoreManager = scoreManager;
    this->scoreManager->getScores();

    initBackground();
    initUI();

}


MenuState::~MenuState() = default;

//Functions
void MenuState::update() {

    this->startButton.update(*mousePosView);
    this->eraseButton.update(*mousePosView);
    this->quitButton.update(*mousePosView);
    this->scoreText.setString(scoreManager->readHighScores());

    if(startButton.isClicked()){
        this->states->push(new BattleState(this->font, this->mousePosView, this->states, this->scoreManager));
    }
    if(eraseButton.isClicked()){
        scoreManager->resetScores();
        this->scoreText.setString(scoreManager->readHighScores());
    }
    if(quitButton.isClicked()){
        quit();
    }


}

void MenuState::render(sf::RenderWindow &renderWindow) {
    renderWindow.draw(this->bg);
    renderWindow.draw(this->scoreBg);
    startButton.render(renderWindow);
    eraseButton.render(renderWindow);
    quitButton.render(renderWindow);
    renderWindow.draw(scoreText);

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
    this->scoreBg.setFillColor(sf::Color(0,0,0,200));
    this->scoreBg.setSize(sf::Vector2f(1280.0 / 3, 720));

}

void MenuState::initUI() {
    this->startButton.defineAll(bg.getSize().x/2 - 100, bg.getSize().y/3, 200, 50, "Start", font, true);
    this->eraseButton.defineAll(bg.getSize().x/2 - 100, bg.getSize().y/3*2-150, 200, 50, "Erase Score", font, true);
    this->quitButton.defineAll(bg.getSize().x/2 - 100, bg.getSize().y/3*3-300, 200, 50, "Quit", font, true);

    this->scoreText.setFont(*this->font);
    this->scoreText.setCharacterSize(45);
    this->scoreText.setPosition( 100, bg.getSize().y/3);
}




