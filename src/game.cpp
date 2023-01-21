#include "game.hpp"
//inits
void Game::initWindow() {
    window.create(sf::VideoMode(1280, 720), "Alpha2 Project", sf::Style::Close);
}

void Game::initStates() {
    this->states.push(new BattleState);
    this->states.push(new MenuState);
}
//Con-/Destructors
Game::Game() {
    initWindow();
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






