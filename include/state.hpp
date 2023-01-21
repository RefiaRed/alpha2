#pragma once

#include "entity.hpp"


class State{
private:

    bool callsQuit{};

public:
    //Con-/Destructors
    State();
    virtual ~State();

   //Functions
    virtual void update() = 0;

    virtual void render(sf::RenderWindow& renderWindow) = 0;
    virtual void endState() = 0;

    virtual void checkQuit();
    const bool& getQuit() const;

    virtual void updateKeybinds() =0;
};

