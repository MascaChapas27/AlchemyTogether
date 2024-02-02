#include "Animation.hpp"
#include <iostream>

Animation::Animation(){
    currentPhotogram = 0;
    pingPong = false;
    goingDown = false;
    delay = 1;
    currentDelay = 0;
}

void Animation::setNumPhotograms(int numPhotograms){
    this->numPhotograms = numPhotograms;
}

void Animation::setTexture(sf::Texture& texture, int width){
    this->sprite.setTexture(texture);
    this->sprite.scale(2.f,2.f);
    sf::IntRect textureRectangle = this->sprite.getTextureRect();
    textureRectangle.width = width;
    this->sprite.setTextureRect(textureRectangle);
}

void Animation::setPingPong(bool pingPong){
    this->pingPong = pingPong;
}

void Animation::setPosition(int x, int y){
    this->sprite.setPosition(x,y);
}

void Animation::update(){

    if(numPhotograms == 0) return;

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

void Animation::setDelay(int delay){
    this->delay = delay;
}
