#include "FallingItem.hpp"

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
