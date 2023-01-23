#pragma once

#include "state.hpp"



class BattleState :
        public State {
private:
    sf::Sprite bg;
    sf::Texture bgTexture;

    Entity player;
    Entity enemy;

    Button attackButton;
    Button healButton;
    Button quitButton;

    void initTextures();
    void initEntities();
public:
    //Con-/Destructors
    BattleState(sf::Font* font, sf::Vector2f* mousePosView, std::stack<State*>* states);
    ~BattleState() override;

    //Functions
    void update() override;
    void render(sf::RenderWindow& renderWindow) override;
    void endState() override;


};



