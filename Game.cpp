//
//  Game.cpp
//  Assignment1_JH
//
//  Created by Jamie on 24/02/2018.
//  Copyright © 2018 Jamie. All rights reserved.
//

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Include/Game.hpp"
#include "ResourcePath.hpp"

using namespace std;

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game():
    mWindow(sf::VideoMode(1000, 800), "SFML Assignement 1: Paddle Game, Jamie Huang"),
    mBat(),
    mBall(),
    mFont(),
    mIcon(),
    mText(),
    lives(5),
    score(0),
    mStatisticsText(),
    mIsMovingRight(false),
    mIsMovingLeft(false)
{
    mWindowWidth = mWindow.getSize().x;
    mWindowHeight = mWindow.getSize().y;
    
    if(!mMusic.openFromFile(resourcePath()+"Media/Music/bgm.ogg")) return;
    mMusic.setVolume(50);
    mMusic.setPitch(2);
    mMusic.setPosition(0,1,0);
    mMusic.setAttenuation(100);
    mMusic.setLoop(true);
    mMusic.play();
    
    if(!mSound.openFromFile(resourcePath()+"Media/Music/munchausen.ogg")) return;
    mSound.setVolume(50);
    mSound.setPitch(2);
    mSound.setPosition(0,1,0);
    mSound.setAttenuation(100);
    
    if(!mIcon.loadFromFile(resourcePath()+"Media/Textures/icon.png")) return;
    mWindow.setIcon(mIcon.getSize().x,mIcon.getSize().y,mIcon.getPixelsPtr());

    if (!mFont.loadFromFile(resourcePath()+"Media/Sansation.ttf")) return;
    mText.setFont(mFont);
    mText.setPosition(10.f, 10.f);
    mText.setCharacterSize(30);
    mText.setFillColor(sf::Color::White);
    
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(750.f, 10.f);
    mStatisticsText.setCharacterSize(20);
    mStatisticsText.setFillColor(sf::Color(180,180,180));
    
    endText.setFont(mFont);
    endText.setStyle(sf::Text::Bold);

    endText.setCharacterSize(60);
    endText.setFillColor(sf::Color(220, 100, 20));
}


void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
            sf::Time elapsedTime = clock.restart();
            timeSinceLastUpdate += elapsedTime;
            while (timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;
                processEvents();
                if(lives>0)
                update(TimePerFrame);
            }
            if(lives>0)
            updateStatistics(elapsedTime);

        if(lives==0)
        {
            endText.setString(">> GAME OVER <<" );
            endText.setPosition(mWindowWidth/2-endText.getLocalBounds().width/2, mWindowHeight/2-endText.getLocalBounds().height/2);
            mMusic.stop();
        }
        render();
    }
}


void Game::update(sf::Time elapsedTime)
{
    if (mIsMovingLeft)
    {
        if(mBat.getPosition().x > 0){
            mBat.moveLeft();
            mBat.update(elapsedTime);
        }else{
            mBat.setPosition(0,mBat.getPosition().y);
        }
    }
    if (mIsMovingRight)
    {
        if(mBat.getPosition().x + mBat.getShape().getSize().x < mWindowWidth)
        {
            mBat.moveRight();
            mBat.update(elapsedTime);
        }else{
            mBat.setPosition(mWindowWidth - mBat.getShape().getSize().x, mBat.getPosition().y);
        }
    }
    
//move ball
    //ball touches paddle
    if((mBall.getPosition().y + mBall.getShape().getRadius() >= mBat.getPosition().y && mBall.getPosition().y <= mBat.getPosition().y + mBat.getShape().getSize().y)&&
       (mBall.getPosition().x + mBall.getShape().getRadius() >= mBat.getPosition().x && mBall.getPosition().x <= mBat.getPosition().x + mBat.getShape().getSize().x))
    {
        mBall.reboundBatOrTop();
        score++;
        mSound.play();
    }
    //ball reaches window top
    if(mBall.getPosition().y <= 0)
    {
        mBall.reboundBatOrTop();
    }
    //ball hits window sides
    if(mBall.getPosition().x + mBall.getShape().getRadius() > mWindowWidth ||
       mBall.getPosition().x <= 0)
    {
        mBall.reboundSide();
    }
    
    if(mBall.getPosition().y + mBall.getShape().getRadius() >= mWindowHeight)
    {
        mBall.hitBottom();
        lives--;
    }
    
    mBall.update(elapsedTime);
    mText.setString("Scores: " + to_string(score) + "  Lives: " + to_string(lives) );

}

void Game::render()
{
    mWindow.clear(sf::Color(0, 90, 180));
    mWindow.draw(mBat);
    mWindow.draw(mBall);
    mWindow.draw(mText);
    mWindow.draw(mStatisticsText);
    mWindow.draw(endText);
    mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;
    
    if(mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString(
                                  "Frames / Second = " + to_string(mStatisticsNumFrames) + "\n"+
                                  "Time / Update = " + to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames )+ "us");
        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Left){
        mIsMovingLeft = isPressed;
//        cout<<"X: "<<mBat.getPosition().x<< " / Y: "<<mBat.getPosition().y<<endl;
    }else if (key == sf::Keyboard::Right){
//        cout<<"bat x: "<<mBat.getPosition().x<< "   bat y: "<<mBat.getPosition().y<<endl;
        mIsMovingRight = isPressed;
    }
}

