#pragma once

#include <iostream>
#include <ctime> //IDK if needed
#include <cstdlib> //IDK if needed
#include <vector>
#include <stack>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Entity{

private:

protected:
    sf::RectangleShape shape;

public:
    //Con-/Destructors
    Entity();
    virtual ~Entity();

    //Functions
    virtual void update();
    virtual void render(sf::RenderWindow& renderWindow);
};
