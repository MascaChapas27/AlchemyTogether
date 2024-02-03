#include "FallingItem.hpp"
#include "Utilities.hpp"

FallingItem::FallingItem(){
    currentSpeed = 0;
}

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
    currentSpeed+=gravity;
    animation.setPosition(animation.getPosition().x,animation.getPosition().y+currentSpeed);
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

bool FallingItem::isOut(){
    return animation.getPosition().y > MAIN_WINDOW_HEIGHT;
}

void FallingItem::setType(std::string type){
    this->type = type;
}

std::string FallingItem::getType(){
    return this->type;
}
