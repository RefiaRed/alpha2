#pragma once

#include <iostream>
//#include <ctime>
//#include <cstdlib>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class State{
private:


public:
    //Con-/Destructors
    State();
    virtual ~State();

   //Functions
    virtual void update() = 0;
    virtual void render() = 0;

};

