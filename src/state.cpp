#include "state.hpp"

//Con-/Destructors
State::State(sf::Font* font, sf::Vector2f* mousePosView, std::stack<State*>* states) {
    this->states = states;
    this->callsQuit = false;
    this->font = font;
    this->mousePosView = mousePosView;
}

State::~State() {

}

void State::quit() {
        this->callsQuit = true;
}

const bool &State::getQuit() const {
    return this->callsQuit;
}

void State::render(sf::RenderWindow& renderWindow) {

}



