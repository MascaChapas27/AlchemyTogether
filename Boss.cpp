#include "Boss.hpp"
#include "Utilities.hpp"
#include <iostream>

Boss::Boss(){
    invincibilityCounter = -1;
    currentSpeed = 0;
    goingDown = true;
    health = BOSS_INITIAL_HEALTH;
}

void Boss::setAnimation(Animation animation){
    this->animation = animation;
    initialY = -animation.getHitbox().height*3;
    finalY = -animation.getHitbox().height*3;
}

void Boss::setHitSprite(sf::Sprite hitSprite){
    this->hitSprite = hitSprite;
}

int Boss::getCurrentHealth(){
    return health;
}

sf::Vector2f Boss::getPosition(){
    return animation.getPosition();
}

void Boss::setActivated(bool activated){
    if(activated){
        initialY = BOSS_INITIAL_Y;
        finalY = BOSS_FINAL_Y;
        goingDown = true;
    } else {
        initialY = -animation.getHitbox().height*3;
        finalY = -animation.getHitbox().height*3;
        goingDown = false;
    }
}

void Boss::update(std::list<FallingItem>& fallingItems){

    // First, move the boss
    sf::Vector2f newPosition = animation.getPosition();
    currentSpeed = currentSpeed + (goingDown ? BOSS_SPEED : -BOSS_SPEED);
    if(currentSpeed > BOSS_MAX_SPEED) currentSpeed = BOSS_MAX_SPEED;
    if(currentSpeed < -BOSS_MAX_SPEED) currentSpeed = -BOSS_MAX_SPEED;
    newPosition.y+=currentSpeed;

    animation.setPosition(newPosition.x,newPosition.y);

    animation.update();

    // Second, change direction
    int currentY = animation.getPosition().y;
    if(goingDown && currentY>finalY){
        goingDown = false;
    } else if (!goingDown && currentY < initialY){
        goingDown = true;
    }

    // Third, check for collisions

    auto iter = fallingItems.begin();
    while(iter != fallingItems.end() && (invincibilityCounter>=10 || invincibilityCounter==-1)){
        sf::IntRect rect1 = iter->getHitbox();
        sf::IntRect rect2 = animation.getHitbox();

        if((rect1.left < (rect2.left+rect2.width)) &&
           ((rect1.left+rect1.width) > rect2.left) &&
           (rect1.top < (rect2.top+rect2.height) &&
           ((rect1.top+rect1.height) > rect2.top))){

            if(iter->getType() == BOOK_TYPE || iter->getType() == MAGIC_TYPE){
                health-=10;
                iter=fallingItems.erase(iter);
                invincibilityCounter=0;
            } else {
                iter++;
            }
        } else {
            iter++;
        }
    }

    // Fourth, update the animation
    if(invincibilityCounter >= 0  && invincibilityCounter < BOSS_INVINCIBILITY_FRAMES){
        hitSprite.setPosition(animation.getPosition());
        invincibilityCounter++;
    } else if (invincibilityCounter == BOSS_INVINCIBILITY_FRAMES) invincibilityCounter = -1;
}

void Boss::draw(sf::RenderTarget& r, sf::RenderStates s) const{
    if(invincibilityCounter == -1) r.draw(animation,s);
    else if (invincibilityCounter%2==0){
        if(invincibilityCounter < 10) r.draw(hitSprite,s);
        else r.draw(animation,s);
    }

    sf::RectangleShape backgroundRectangle(sf::Vector2f(animation.getHitbox().width*2,10));
    backgroundRectangle.setFillColor(sf::Color(0,0,100));
    backgroundRectangle.setPosition(animation.getPosition().x,animation.getPosition().y-10);
    r.draw(backgroundRectangle,s);

    sf::RectangleShape rectangle(sf::Vector2f(((double)health/BOSS_INITIAL_HEALTH)*animation.getHitbox().width*2,10));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(animation.getPosition().x,animation.getPosition().y-10);
    r.draw(rectangle,s);
}
