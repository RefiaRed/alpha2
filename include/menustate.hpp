#pragma once

#include "state.hpp"


class MenuState :
        public State {
private:
    sf::RectangleShape bg;
    Button startButton;
    Button eraseButton;
    Button quitButton;

public:
    //Con-/Destructors
    MenuState(sf::Font* font,sf::Vector2f* mousePosView);
    ~MenuState() override;

    //Functions

    void update() override;
    void render(sf::RenderWindow& renderWindow) override;
    void endState() override;


};