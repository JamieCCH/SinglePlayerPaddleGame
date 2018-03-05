//
//  Paddle.cpp
//  Assignment1_JH
//
//  Created by Jamie on 12/02/2018.
//  Copyright © 2018 Jamie. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "Include/Bat.hpp"

Bat::Bat():
    batShape(),batSpeed(450.f),position()
{
    batShape.setSize(sf::Vector2f(100.f, 10.f));
    batShape.setFillColor(sf::Color(255,255,180));
    batShape.setPosition(450.f, 750.f);
}

sf::RectangleShape& Bat::getShape()
{
    batShape = Bat::batShape;
    return batShape;
}

void Bat::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(batShape,states);
}

sf::Vector2f Bat::getPosition()
{
    position = batShape.getPosition();
    return position;
}

void Bat::moveRight()
{
    position.x = batSpeed;
//    position.x *= batSpeed;   //(batSpeed = 1.5f)
}

void Bat::moveLeft()
{
    position.x = -batSpeed;
//    position.x *= -batSpeed; //will eased to stop when approching to 0 (batSpeed = 1.5f)
}

void Bat::update(sf::Time dt)
{
    batShape.move(position.x * dt.asSeconds(),0.f);
}

