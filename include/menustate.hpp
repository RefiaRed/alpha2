#pragma once

#include "state.hpp"

class MenuState :
        public State {
private:

public:
    //Con-/Destructors

    MenuState();
    virtual ~MenuState();

    //Functions

    void update() override;
    void render() override;
    void endState() override;

    void updateKeybinds() override;

};