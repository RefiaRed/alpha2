#pragma once

#include <iostream>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"


class AnimationComponent {

private:
    class Animation{
    public:
        sf::Texture& textureSheet;
        float AniSpeed;
        int width;
        int height;
        sf::IntRect startRect;
        sf::IntRect endRect;

        Animation(sf::Texture& textureSheet, float AniSpeed, int start_x, int start_y,int end_x, int end_y,int width, int height )
        : textureSheet(textureSheet), AniSpeed(AniSpeed), width(width), height(height){
            this->startRect = sf::IntRect(start_x, start_y, width, height);
            this->endRect = sf::IntRect(end_x, end_y, width, height);
        }
        //Functions
        void update(){

        }
        void pause(){

        }
        void reset(){

        }


    };

    std::map<std::string, Animation> animations;

public:
    //Con-/Destructors
    AnimationComponent();
    virtual ~AnimationComponent();
    //Functions

};

