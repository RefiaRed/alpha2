#pragma once

#include "entity.hpp"


class State{
private:

    bool callsQuit;

protected:
    sf::Font* font;
    sf::Vector2f* mousePosView;

public:
    //Con-/Destructors
    State(sf::Font* font,sf::Vector2f* mousePosView);
    virtual ~State();

   //Functions
    virtual void update() = 0;

    virtual void render(sf::RenderWindow& renderWindow) = 0;
    virtual void endState() = 0;

    virtual void quit();
    const bool& getQuit() const;

};

