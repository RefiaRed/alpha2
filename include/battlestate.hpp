#pragma once

#include "state.hpp"

class BattleState :
        public State {
private:

public:
    //Con-/Destructors
    BattleState();
    virtual ~BattleState();

    //Functions
    void update() override;
    void render() override;
    void endState() override;

    void updateKeybinds() override;

};



