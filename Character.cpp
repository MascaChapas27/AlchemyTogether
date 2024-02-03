#include "Character.hpp"
#include "Utilities.hpp"
#include <iostream>

Character::Character(){
    invincibilityCounter = -1;
}

void Character::setAnimation(Animation animation)
{
    this->animation = animation;
}

void Character::setSpeed(double speed)
{
    this->speed = speed;
}

void Character::setKeys(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey)
{
    this->leftKey = leftKey;
    this->rightKey = rightKey;
}

void Character::update(std::list<FallingItem> fallingItems)
{
    // First, move the character
    bool moved = false;
    sf::Vector2f newPosition = animation.getPosition();
    if(sf::Keyboard::isKeyPressed(leftKey)){
        moved = true;
        newPosition.x -= speed;
    } else if(sf::Keyboard::isKeyPressed(rightKey)){
        moved = true;
        newPosition.x += speed;
    }

    if(newPosition.x + animation.getWidth()*2 > MAIN_WINDOW_WIDTH){
        newPosition.x = MAIN_WINDOW_WIDTH - animation.getWidth()*2;
    } else if (animation.getPosition().x < 0){
        newPosition.x = 0;
    }

    animation.setPosition(newPosition.x,newPosition.y);

    if(moved) animation.update();
    else animation.resetToStart();

    // Second, check for collisions
    for(FallingItem& fallingItem : fallingItems){
        sf::IntRect rect1 = fallingItem.getHitbox();
        sf::IntRect rect2 = animation.getHitbox();

        if(rect1.left < rect2.left+rect2.width &&
           rect1.left+rect1.width > rect2.left &&
           rect1.top > rect2.top+rect2.height &&
           rect1.top+rect1.height < rect2.top){

               invincibilityCounter = 0;
           }
    }

    // Third, update the animation
    if(invincibilityCounter >= 0  && invincibilityCounter <= INVINCIBILITY_FRAMES){
        hitSprite.setPosition(animation.getPosition());
        invincibilityCounter++;
    } else if (invincibilityCounter == INVINCIBILITY_FRAMES) invincibilityCounter = -1;
}

void Character::setHitSprite(sf::Sprite hitSprite){
    this->hitSprite = hitSprite;
}

void Character::draw(sf::RenderTarget& r, sf::RenderStates s) const{
    if(invincibilityCounter == -1) r.draw(animation,s);
    else if (invincibilityCounter%2==0){
        if(invincibilityCounter < 30) r.draw(hitSprite,s);
        else r.draw(animation,s);
    }
}

void Character::setName(std::string name){
    this->name = name;
}
