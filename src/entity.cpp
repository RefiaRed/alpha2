#include "entity.hpp"

//Con-/Destructors
Entity::Entity() {
    this->shape.setSize(sf::Vector2f(50,50));
    this->shape.setFillColor(sf::Color::White);
}

Entity::~Entity() {

}

void Entity::update() {

}

void Entity::render(sf::RenderWindow &renderWindow) {
    renderWindow.draw(this->shape);
}
