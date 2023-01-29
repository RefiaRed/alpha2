#include "game.hpp"

//Con-/Destructors
Game::Game() {
    initWindow();
    initFont();
    initState();
    scoreManager.initScoreFile();
}

Game::~Game() {
    while (!this->states.empty()){
        delete this->states.top();
        this->states.pop();
    }

}
//inits
void Game::initWindow() {
    window.create(sf::VideoMode(1280, 720), "Alpha2 Project", sf::Style::Close);
}

void Game::initFont() {
    if(!font.loadFromFile("assets/rainyhearts.ttf"))
        std::cout << "ERROR: COULDN'T LOAD FONT!" << std::endl;
}

void Game::initState() {
    this->states.push(new MenuState(&font, &mousePosView, &states, &scoreManager)); // <- &n = sending addresses of n
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

void Game::updateMousePos() {
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
        this->update();
        this->render();
    }
}











