#pragma once

#include "headers.hpp"

#include "button.hpp"
#include "entity.hpp"
#include "scoremanager.hpp"

class ScoreManager;

class State {
private:

    bool callsQuit;

protected:
    std::stack<State*>* states;
    sf::Font* font;
    ScoreManager* scoreManager;
    sf::Vector2f* mousePosView;

    std::map<std::string, sf::Texture> textures;

public:
    //Con-/Destructors
    State(sf::Font* font,sf::Vector2f* mousePosView, std::stack<State*>* states, ScoreManager* scoreManager);
    virtual ~State();

   //Functions
    virtual void update() = 0;

    virtual void render(sf::RenderWindow& renderWindow) = 0;
    virtual void endState() = 0;

    virtual void quit();
    const bool& getQuit() const;

};

