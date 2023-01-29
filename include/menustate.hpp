#pragma once

#include "headers.hpp"
#include "state.hpp"
#include "battlestate.hpp"


class State;
class Button;
class BattleState;

class MenuState :
        public State {
private:
    sf::RectangleShape bg;
    sf::Texture bgTexture;
    sf::RectangleShape scoreBg;

    Button startButton;
    Button eraseButton;
    Button quitButton;

    sf::Text scoreText;
    //Inits
    void initBackground();


public:

    //Con-/Destructors
    MenuState(sf::Font* font,sf::Vector2f* mousePosView, std::stack<State*>* states, ScoreManager* scoreManager);
    ~MenuState() override;

    //Functions

    void update() override;
    void render(sf::RenderWindow& renderWindow) override;
    void endState() override;


};