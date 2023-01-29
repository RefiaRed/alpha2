#pragma once

#include "headers.hpp"

class Button {
private:
    sf::RectangleShape btnShape;
    sf::Text btnText;

    sf::Color idleColor = sf::Color(92, 37, 186, 255);
    sf::Color hoverColor = sf::Color(158, 118, 227, 255);

    bool isSetActive{};
    bool hovering{};
public:
    //Con-/Destructors
    Button();
    virtual ~Button();

    //Functions
    void update(sf::Vector2f mousePos);
    void render(sf::RenderWindow& renderWindow);

    void defineAll(float x, float y, float width, float height,
                std::string text, sf::Font* btnFont, bool activity);

    //Button Modes

    bool isClicked() const;
    void setActivity(bool activity);
};

