#include "FallingItem.hpp"
#include "Utilities.hpp"

FallingItem::FallingItem(){
    currentSpeed = sf::Vector2f(0,0);
    trailCounter = 0;
    lying = false;
    currentlyLying = false;
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

    if(currentlyLying){
        r.draw(this->lyingItem,s);
    } else {
        for(Animation anim : trail){
            r.draw(anim,s);
        }
        r.draw(this->animation,s);
    }
}

sf::IntRect FallingItem::getHitbox(){
    return animation.getHitbox();
}

void FallingItem::update(){

    trailCounter++;

    if(trailCounter == FALLING_TRAIL_MAX_COUNTER){
        trailCounter=0;
        trail.insert(trail.begin(),animation);
        if(trail.size() > FALLING_TRAIL_MAX_LENGTH) trail.erase(prev(trail.end()));

        for(Animation& anim : trail){
            anim.addTransparency();
        }
    }

    animation.addRotation(rotationSpeed);

    currentSpeed.y+=gravity;
    if((animation.getPosition().x+currentSpeed.x < animation.getHitbox().width && currentSpeed.x < 0) ||
       (animation.getPosition().x+currentSpeed.x > MAIN_WINDOW_WIDTH-animation.getHitbox().width && currentSpeed.x > 0)) currentSpeed.x*=-1;

    if(!currentlyLying && lying && animation.getPosition().y > MAIN_WINDOW_HEIGHT){
        lyingItem.setPosition(sf::Vector2f(animation.getPosition().x,MAIN_WINDOW_HEIGHT-lyingItem.getTextureRect().height));
        currentlyLying = true;
        gravity = 0;
        currentSpeed.y = 0;
    }

    if(currentlyLying){
        currentSpeed.x/=1.05;
        lyingItem.setPosition(lyingItem.getPosition().x+currentSpeed.x,lyingItem.getPosition().y);
    }

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

void FallingItem::setLyingItemTexture(sf::Texture& texture)
{
    lyingItem.setTexture(texture);
    lyingItem.scale(2,2);
    lyingItem.setOrigin(lyingItem.getTextureRect().width/2,lyingItem.getTextureRect().height/2);
    lying = true;
}

void FallingItem::setPosition(double x, double y){
    animation.setPosition(x,y);
}

bool FallingItem::isOut(){
    return animation.getPosition().y > MAIN_WINDOW_HEIGHT+animation.getHitbox().height;
}

void FallingItem::setType(std::string type){
    this->type = type;
}

void FallingItem::setCurrentSpeed(sf::Vector2f currentSpeed)
{
    this->currentSpeed = currentSpeed;
}

void FallingItem::setRotationSpeed(double rotationSpeed)
{
    this->rotationSpeed = rotationSpeed;
}

std::string FallingItem::getType(){
    return this->type;
}
