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
    //std::cout << this->statsComponent->debugPrint();

}

void Entity::render(sf::RenderWindow& window) {

    window.draw(this->sprite);
}

void Entity::createSprite(sf::Texture* texture, float scaleX, float scaleY ) {
    this->spriteTexture = texture;
    this->sprite.setTexture(*this->spriteTexture);
    this->sprite.setTextureRect(sf::IntRect (0,0,222, 480));
    this->sprite.setScale(sf::Vector2f(scaleX,scaleY));
}

void Entity::setPosition(float x, float y) {
    this->sprite.setPosition(x,y);

}

void Entity::createStatsComponent(int level, std::random_device& rd) {
    this->statsComponent = new StatsComponent(level, rd);
}

void Entity::respawn(int lv, std::random_device& rd, Entity* target) {
    int xP = (this->statsComponent->health + this->statsComponent->strength) / 2 ;
    delete this->statsComponent;
    target->statsComponent->gainExp(xP);
    this->createStatsComponent(lv, rd);
    this->statsComponent->gainExp(xP);
    this->statsComponent->hp = this->statsComponent->hpMax;
}


