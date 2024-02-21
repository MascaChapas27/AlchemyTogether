#include "Animation.hpp"
#include <iostream>
#include "Utilities.hpp"

Animation::Animation(){
    currentPhotogram = 0;
    pingPong = false;
    goingDown = false;
    delay = 1;
    currentDelay = 0;
}

void Animation::setTexture(sf::Texture& texture, int numPhotograms, bool centerOrigin){
    this->numPhotograms = numPhotograms;
    sprite.setTexture(texture);
    sprite.scale(2.f,2.f);
    sf::IntRect textureRectangle = sprite.getTextureRect();
    textureRectangle.width = textureRectangle.width/numPhotograms;
    sprite.setTextureRect(textureRectangle);
    if(centerOrigin) sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().height/2);
}

void Animation::setPingPong(bool pingPong){
    this->pingPong = pingPong;
}

void Animation::setPosition(double x, double y){
    this->sprite.setPosition(x,y);
}

void Animation::setPosition(sf::Vector2f position){
    this->sprite.setPosition(position);
}

void Animation::update(){

    if(numPhotograms == 0){
        sf::IntRect textureRectangle = this->sprite.getTextureRect();
        textureRectangle.left = 0;
        this->sprite.setTextureRect(textureRectangle);
        return;
    }

    sf::IntRect textureRectangle = this->sprite.getTextureRect();
    textureRectangle.left = currentPhotogram * textureRectangle.width;
    this->sprite.setTextureRect(textureRectangle);

    currentDelay++;
    if(currentDelay == delay){
        if(goingDown) currentPhotogram--;
        else currentPhotogram++;

        currentDelay = 0;
    }

    if(currentPhotogram == numPhotograms){
        if(pingPong){
            goingDown = true;
            currentPhotogram-=2;
        } else {
            currentPhotogram = 0;
        }
    } else if(currentPhotogram == 0){
        goingDown = false;
    }
}

void Animation::draw(sf::RenderTarget& r, sf::RenderStates s) const{
    r.draw(this->sprite,s);
}

void Animation::resetToStart(){
    sf::IntRect textureRectangle = this->sprite.getTextureRect();
    textureRectangle.left = 0;
    this->sprite.setTextureRect(textureRectangle);
}

void Animation::setDelay(int delay){
    this->delay = delay;
}

sf::Color Animation::getColor()
{
    return sprite.getColor();
}

void Animation::setColor(sf::Color color)
{
    sprite.setColor(color);
}

sf::Vector2f Animation::getPosition() const{
    return sprite.getPosition();
}

sf::IntRect Animation::getHitbox() const{
    sf::IntRect hitbox = sprite.getTextureRect();
    bool zeroOrigin = sprite.getOrigin().x == 0 && sprite.getOrigin().y == 0;
    hitbox.left = sprite.getPosition().x+(zeroOrigin ? hitbox.width/2 : -hitbox.width/2);
    hitbox.top = sprite.getPosition().y+(zeroOrigin ? hitbox.height/2 : -hitbox.height/2);
    return hitbox;
}

void Animation::addTransparency()
{
    sf::Color newColor = this->sprite.getColor();
    newColor.a/=3;
    this->sprite.setColor(newColor);
}

void Animation::addRotation(double rotation)
{
    sprite.rotate(rotation);
}

double Animation::getWidth(){
    return sprite.getTextureRect().width;
}
