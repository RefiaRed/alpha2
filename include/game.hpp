#pragma once

#include "battlestate.hpp"
#include "menustate.hpp"




class Game{
private:
    sf::RenderWindow window;
    sf::Event event{};

    sf::Clock dtClock;
    float dt{};

    std::stack<State*> states;

    sf::Font font;

    //inits
    void initWindow();
    void initStates();
    void initFont();

    //Mouse positions
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

public:
    //Con-/Destructors
    Game();
    virtual ~Game();

    //Functions
    void update();
    void updateEvents();
    void updateDt();
    virtual void updateMousePos();

    void render();
    void run();

    sf::Vector2f getMousePosition();


};


