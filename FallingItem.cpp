#include "FallingItem.hpp"
#include "Utilities.hpp"

FallingItem::FallingItem(){
    currentSpeed = sf::Vector2f(0,0);
}

// Definition of static members (default constructor called)
FallingItem FallingItem::fallingBook;
FallingItem FallingItem::fallingMagic;
FallingItem FallingItem::fallingFire;

void FallingItem::setAnimation(Animation animation){
    this->animation = animation;
}

void FallingItem::setGravity(double gravity){
    this->gravity = gravity;
}

void FallingItem::draw(sf::RenderTarget& r, sf::RenderStates s) const{
    r.draw(this->animation,s);
}

sf::IntRect FallingItem::getHitbox(){
    return animation.getHitbox();
}

void FallingItem::update(){
    currentSpeed.y+=gravity;
    animation.setPosition(animation.getPosition().x+currentSpeed.x,animation.getPosition().y+currentSpeed.y);
    animation.update();
}

sf::Vector2f FallingItem::getPosition()
{
    return animation.getPosition();
}

void FallingItem::setPosition(sf::Vector2f position)
{
    animation.setPosition(position.x,position.y);
}

void FallingItem::setPosition(double x, double y){
    animation.setPosition(x,y);
}

bool FallingItem::isOut(){
    return animation.getPosition().y > MAIN_WINDOW_HEIGHT;
}

void FallingItem::setType(std::string type){
    this->type = type;
}

void FallingItem::setCurrentSpeed(sf::Vector2f currentSpeed)
{
    this->currentSpeed = currentSpeed;
}

std::string FallingItem::getType(){
    return this->type;
}
