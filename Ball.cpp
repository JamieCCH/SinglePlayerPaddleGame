//
//  Ball.cpp
//  Assignment1_JH
//
//  Created by Jamie on 12/02/2018.
//  Copyright © 2018 Jamie. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "Include/Ball.hpp"
#include <time.h>

Ball::Ball():
    ballShape(),position(),xVelocity(550),yVelocity(350)
{
    srand(time(0));
    ballShape.setRadius(10.0f);
    ballShape.setPosition(rand()%1000, 10.f);
    ballShape.setFillColor(sf::Color(255, 230, 155));
}

sf::CircleShape& Ball::getShape()
{
    ballShape = Ball::ballShape;
    return ballShape;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(ballShape,states);
}

sf::Vector2f Ball::getPosition()
{
    position = ballShape.getPosition();
    return position;
}

int Ball::getXVelicity()
{
    return xVelocity;
}

int Ball::getYVelicity()
{
    return yVelocity;
}

void Ball::hitBottom()
{
    ballShape.setPosition(rand()%1000, 10.f);
}

void Ball::reboundBatOrTop()
{
    yVelocity = -yVelocity;
}

void Ball::reboundSide()
{
    xVelocity = -xVelocity;
}

void Ball::update(sf::Time dt)
{
    ballShape.setPosition(
                          ballShape.getPosition().x + (xVelocity * dt.asSeconds()),
                          ballShape.getPosition().y + (yVelocity * dt.asSeconds()));
}
