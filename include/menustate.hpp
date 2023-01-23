#pragma once

#include "state.hpp"
#include "battlestate.hpp"

class MenuState :
        public State {
private:
    sf::RectangleShape bg;
    sf::Texture bgTexture;

    Button startButton;
    Button eraseButton;
    Button quitButton;
    //Inits
    void initBackground();


public:
    //Con-/Destructors
    MenuState(sf::Font* font,sf::Vector2f* mousePosView, std::stack<State*>* states);
    ~MenuState() override;

    //Functions

    void update() override;
    void render(sf::RenderWindow& renderWindow) override;
    void endState() override;


};