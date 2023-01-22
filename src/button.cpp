#include "button.hpp"

//Con-/Destructors

Button::Button() = default;;


Button::~Button() = default;

//Functions

void Button::update(sf::Vector2f mousePos){

    hovering = this->btnShape.getGlobalBounds().contains(mousePos) && isSetActive;

    //Button Feedback
    if (hovering){
        this->btnText.setFillColor(sf::Color::Cyan);
        this->btnShape.setFillColor(hoverColor);
    }
    else{
        this->btnText.setFillColor(sf::Color::White);
        this->btnShape.setFillColor(idleColor);
    }



}

void Button::render(sf::RenderWindow& renderWindow) {
    renderWindow.draw(this->btnShape);
    renderWindow.draw(this->btnText);
}

//Button Mode

bool Button::isHovering() const {
    return hovering;
}

bool Button::isClicked() const {
    return hovering && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Button::setActivity(bool activity) {
    this->isSetActive = activity;
}

void Button::defineAll(float x, float y, float width, float height,
                    std::string text, sf::Font* btnFont, bool activity) {
    hovering = false;
    isSetActive = activity;

    //Box
    this->btnShape.setSize(sf::Vector2f(width, height));
    this->btnShape.setFillColor(idleColor);
    this->btnShape.setPosition(x, y);


    //Button text
    this->btnText.setFont(*btnFont);
    this->btnText.setString(text);
    this->btnText.setCharacterSize(25);
    //Centering button text to the (visual) center
    this->btnText.setPosition(
            this->btnShape.getPosition().x + (this->btnShape.getGlobalBounds().width / 2.f) - this->btnText.getGlobalBounds().width / 2.f,
            this->btnShape.getPosition().y + 5
    );
}
