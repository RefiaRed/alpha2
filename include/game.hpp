#pragma once

#include "headers.hpp"
#include "menustate.hpp"




class Game{
private:
    sf::RenderWindow window;
    sf::Event event{};


    sf::Clock dtClock;
    float dt{};


    std::stack<State*> states;
    ScoreManager scoreManager;
    sf::Font font;

    //inits
    void initWindow();
    void initState();
    void initFont();

    //Mouse position
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





};


