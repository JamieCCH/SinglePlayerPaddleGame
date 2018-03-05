//
//  Ball.hpp
//  Assignment1_JH
//
//  Created by Jamie on 12/02/2018.
//  Copyright © 2018 Jamie. All rights reserved.
//
#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Ball: public sf::Drawable, public sf::Transformable
{
public:
            Ball();
    sf::CircleShape&    getShape();
    sf::Vector2f        getPosition();
    int     getXVelicity();
    int     getYVelicity();
    void    hitBottom();
    void    reboundBatOrTop();
    void    reboundSide();
    void    update(sf::Time);

    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    
private:
    sf::CircleShape     ballShape;
    sf::Vector2f        position;
    int                 xVelocity;
    int                 yVelocity;

};


#endif /* Ball_hpp */
