#pragma once

#include "state.hpp"




class Game{
private:
    sf::RenderWindow window;
    sf::Event event;

    sf::Clock dtClock;
    float dt;

    //inits
    void initWindow();

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


