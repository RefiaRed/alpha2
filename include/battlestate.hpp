#pragma once

#include "state.hpp"



class BattleState :
        public State {
private:
    Entity player;

public:
    //Con-/Destructors
    BattleState();
    virtual ~BattleState();

    //Functions
    void update() override;
    void render(sf::RenderWindow& renderWindow) override;
    void endState() override;

    void updateKeybinds() override;

};



