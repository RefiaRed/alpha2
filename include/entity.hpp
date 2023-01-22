#pragma onceonce

#include "button.hpp"


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
    virtual void render(sf::RenderWindow& window);
};
