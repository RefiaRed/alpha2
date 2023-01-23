#pragma onceonce

#include "button.hpp"


class Entity{

private:

protected:
    sf::Texture* spriteTexture;
    sf::Sprite sprite;

public:
    //Con-/Destructors
    Entity();
    virtual ~Entity();

    void createSprite(sf::Texture* texture, float scale);

    //Functions
    virtual void update();
    virtual void render(sf::RenderWindow& window);

    void setPosition( float x, float y);
};
