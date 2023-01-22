#include "game.hpp"
//inits
void Game::initWindow() {
    window.create(sf::VideoMode(1280, 720), "Alpha2 Project", sf::Style::Close);
}

void Game::initFont() {
    if(!font.loadFromFile("assets/rainyhearts.ttf"))
        std::cout << "ERROR: COULDN'T LOAD FONT!" << std::endl;
}

void Game::initStates() {
    this->states.push(new BattleState(&font, &mousePosView));
    this->states.push(new MenuState(&font, &mousePosView));
}



//Con-/Destructors
Game::Game() {
    initWindow();
    initFont();
    initStates();
}

Game::~Game() {
    while (!this->states.empty()){
        delete this->states.top();
        this->states.pop();
    }

}

//Functions
void Game::update() {

    this->updateEvents();

    if(!this->states.empty()) {
        this->states.top()->update();
        this->updateMousePos();

        //std::printf("Mouse Pos: %f, %f \n", mousePosView.x, mousePosView.y);

        if(this->states.top()->getQuit()){
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else{
        this->window.close();
    }
}

void Game::updateEvents() {

    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();
    }

}

void Game::updateDt() {
    //updating deltaTime based on updating and rendering 1 frame
    this->dt = this->dtClock.restart().asSeconds();

    //std::cout << this->dt << "\n";
}

void Game::updateMousePos() {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(this->window);
    this->mousePosView = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));
}

void Game::render() {
    window.clear();
    if(!this->states.empty())
        this->states.top()->render(window);

    window.display();
}

void Game::run() {
    while(this->window.isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}










