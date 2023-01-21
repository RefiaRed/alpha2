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

    //inits
    void initWindow();
    void initStates();

public:
    //Con-/Destructors
    Game();
    virtual ~Game();

    //Functions
    void update();
    void updateEvents();
    void updateDt();

    void render();
    void run();


};


