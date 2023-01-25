#include "entity.hpp"

//Con-/Destructors
Entity::Entity() {
    this->spriteTexture = nullptr;
    this->sprite.setPosition(sf::Vector2f(50,50));

}

Entity::~Entity() {
    delete this->statsComponent;
}


void Entity::update() {
    std::cout << this->statsComponent->debugPrint();
    //this->statsComponent->gainExp(1);
}

void Entity::render(sf::RenderWindow& window) {

    window.draw(this->sprite);
}

void Entity::createSprite(sf::Texture* texture, float scale) {
    this->spriteTexture = texture;
    this->sprite.setTexture(*this->spriteTexture);
    this->sprite.setTextureRect(sf::IntRect (0,0,222, 480));
    this->sprite.setScale(sf::Vector2f(scale,scale));
}

void Entity::setPosition(float x, float y) {
    this->sprite.setPosition(x,y);

}

void Entity::createStatsComponent(int level, std::random_device& rd) {
    this->statsComponent = new StatsComponent(level, rd);
}


