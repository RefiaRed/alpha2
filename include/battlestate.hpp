#pragma once

#include "state.hpp"



class BattleState :
        public State {
private:
    Entity player;

public:
    //Con-/Destructors
    BattleState(sf::Font* font, sf::Vector2f* mousePosView);
    ~BattleState() override;

    //Functions
    void update() override;
    void render(sf::RenderWindow& renderWindow) override;
    void endState() override;


};



