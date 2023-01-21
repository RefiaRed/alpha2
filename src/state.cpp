#include "state.hpp"

//Con-/Destructors
State::State() {
    this->callsQuit = false;
}

State::~State() {

}

void State::checkQuit() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->callsQuit = true;
}

const bool &State::getQuit() const {
    return this->callsQuit;
}

void State::render(sf::RenderWindow& renderWindow) {

}

