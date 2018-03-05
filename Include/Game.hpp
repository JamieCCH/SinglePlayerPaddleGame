//
//  Game.hpp
//  Assignment1_JH
//
//  Created by Jamie on 24/02/2018.
//  Copyright © 2018 Jamie. All rights reserved.
//
#ifndef Game_h
#define Game_h

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Ball.hpp"
#include "Bat.hpp"

class Game : private sf::NonCopyable
{
public:
            Game();
    void    run();
    
private:
    void    processEvents();
    void    update(sf::Time elapsedTime);
    void    render();
    void    updateStatistics(sf::Time elapsedTime);
    void    handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    
private:
    sf::RenderWindow       mWindow;
    sf::Font               mFont;
    sf::Image              mIcon;
    sf::Text               mText;
    sf::Music              mMusic;
    sf::Music              mSound;
    int           lives;
    int           score;
    int         mWindowHeight;
    int         mWindowWidth;
    
    static const float      PlayerSpeed;
    static const sf::Time   TimePerFrame;
    sf::Text                mStatisticsText;
    sf::Time                mStatisticsUpdateTime;
    std::size_t             mStatisticsNumFrames;
    
    Bat        mBat;
    Ball       mBall;
    
    bool      mIsMovingRight;
    bool      mIsMovingLeft;
    
    sf::Text    endText;

};

#endif /* Game_h */
