#include "game.hpp"
//inits
void Game::initWindow() {
    window.create(sf::VideoMode(1280, 720), "Alpha2 Project", sf::Style::Close);
}

//Con-/Destructors
Game::Game() {
    initWindow();
}

Game::~Game() {

}

//Functions
void Game::update() {

    updateEvents();
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




