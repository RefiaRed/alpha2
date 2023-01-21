#pragma once

#include "state.hpp"

class MenuState :
        public State {
private:
    sf::RectangleShape bg;
public:
    //Con-/Destructors

    MenuState();
    virtual ~MenuState();

    //Functions

    void update() override;
    void render(sf::RenderWindow& renderWindow) override;
    void endState() override;

    void updateKeybinds() override;

};