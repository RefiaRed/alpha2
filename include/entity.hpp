#pragma once

#include "headers.hpp"
#include "statscomponent.hpp"


class StatsComponent;

class Entity{

private:

protected:
    sf::Texture* spriteTexture;
    sf::Sprite sprite;


public:
    StatsComponent* statsComponent;

    //Con-/Destructors
    Entity();
    virtual ~Entity();

    void createSprite(sf::Texture* texture, float scaleX, float scaleY);
    void createStatsComponent(int level, std::random_device& rd);

    //Functions
    virtual void update();
    virtual void render(sf::RenderWindow& window);


    void setPosition( float x, float y);

    void respawn(int lv, std::random_device& rd, Entity* target);


};
