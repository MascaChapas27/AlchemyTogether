#include "Character.hpp"
#include "Utilities.hpp"
#include <iostream>

Character::Character(){
    invincibilityCounter = -1;
    maxItems = 10;
    currentItems = 0;
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

int Character::update(std::list<FallingItem>& fallingItems)
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

    int lostItems = 0;

    auto iter = fallingItems.begin();
    while(iter != fallingItems.end() && (invincibilityCounter>=30 || invincibilityCounter==-1)){
        sf::IntRect rect1 = iter->getHitbox();
        sf::IntRect rect2 = animation.getHitbox();

        if((rect1.left < (rect2.left+rect2.width)) &&
           ((rect1.left+rect1.width) > rect2.left) &&
           (rect1.top < (rect2.top+rect2.height) &&
           ((rect1.top+rect1.height) > rect2.top))){

            if(((iter->getType() == BOOK_TYPE && name == WIZARD_NAME) ||
               (iter->getType() == MAGIC_TYPE && name == ALCHEMIST_NAME)) &&
                invincibilityCounter == -1){
                lostItems = currentItems;
                currentItems = 0;
                invincibilityCounter = 0;
                iter++;
            } else if((iter->getType() == BOOK_TYPE && name == ALCHEMIST_NAME) ||
               (iter->getType() == MAGIC_TYPE && name == WIZARD_NAME)) {
                iter=fallingItems.erase(iter);
                currentItems = currentItems == maxItems ? maxItems : currentItems+1;
            } else {
                iter++;
            }
        } else {
            iter++;
        }
    }

    // Third, update the animation
    if(invincibilityCounter >= 0  && invincibilityCounter < INVINCIBILITY_FRAMES){
        hitSprite.setPosition(animation.getPosition());
        invincibilityCounter++;
    } else if (invincibilityCounter == INVINCIBILITY_FRAMES) invincibilityCounter = -1;

    return lostItems;
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

    sf::RectangleShape backgroundRectangle(sf::Vector2f(animation.getHitbox().width*2,10));
    backgroundRectangle.setFillColor(name == WIZARD_NAME ? sf::Color(100,100,000) : sf::Color(100,100,100));
    backgroundRectangle.setPosition(animation.getPosition().x,animation.getPosition().y-10);
    r.draw(backgroundRectangle,s);

    sf::RectangleShape rectangle(sf::Vector2f(((double)currentItems/maxItems)*animation.getHitbox().width*2,10));
    rectangle.setFillColor(name == WIZARD_NAME ? sf::Color::Yellow : sf::Color::White);
    rectangle.setPosition(animation.getPosition().x,animation.getPosition().y-10);
    r.draw(rectangle,s);
}

sf::Vector2f Character::getPosition()
{
    return animation.getPosition();
}

void Character::setCurrentItems(int currentItems)
{
    this->currentItems = currentItems;
}

void Character::setMaxItems(int maxItems)
{
    this->maxItems = maxItems;
}

int Character::getCurrentItems()
{
    return currentItems;
}

int Character::getMaxItems()
{
    return maxItems;
}

void Character::setName(std::string name){
    this->name = name;
}
