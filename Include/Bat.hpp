//
//  Bat.hpp
//  Assignment1_JH
//
//  Created by Jamie on 12/02/2018.
//  Copyright © 2018 Jamie. All rights reserved.
//

#ifndef Bat_hpp
#define Bat_hpp


#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>

class Bat: public sf::Drawable, public sf::Transformable
{
public:
                  Bat();
    
    sf::RectangleShape& getShape();
    
    sf::Vector2f  getPosition();
    
    void          moveLeft();
    void          moveRight();
    void          update(sf::Time);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    sf::Vector2f        position;
    sf::RectangleShape  batShape;
    float               batSpeed;
    
};

#endif /* Bat_hpp */
