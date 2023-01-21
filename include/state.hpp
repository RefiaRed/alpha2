#pragma once

#include <iostream>
//#include <ctime>
//#include <cstdlib>
#include <vector>
#include <stack>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class State{
private:
    bool callsQuit;

public:
    //Con-/Destructors
    State();
    virtual ~State();

   //Functions
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void endState() = 0;

    virtual void checkQuit();
    const bool& getQuit() const;

    virtual void updateKeybinds() =0;
};

