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

    if(DEBUG){
        sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(getHitbox().width,getHitbox().height));
        rectangle.setOrigin(rectangle.getSize().x/2,rectangle.getSize().y/2);
        rectangle.setPosition(getPosition());
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(1);
        rectangle.setFillColor(sf::Color::Transparent);
        r.draw(rectangle,s);
    }
}

sf::IntRect FallingItem::getHitbox() const{

    if(currentlyLying){
        sf::IntRect rectangle = lyingItem.getTextureRect();
        rectangle.width*=2;
        rectangle.height*=2;
        rectangle.left = lyingItem.getPosition().x-rectangle.width/2;
        rectangle.top = lyingItem.getPosition().y-rectangle.height/2;
        return rectangle;
    } else return animation.getHitbox();
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
        lyingSound.play();
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

sf::Vector2f FallingItem::getPosition() const
{
    return currentlyLying ? lyingItem.getPosition() : animation.getPosition();
}

void FallingItem::setPosition(sf::Vector2f position)
{
    animation.setPosition(position.x,position.y);
}

void FallingItem::setLyingItemTexture(sf::Texture& texture)
{
    lyingItem.setTexture(texture);
    lyingItem.setScale(2,2);
    lyingItem.setOrigin(lyingItem.getTextureRect().width/2,lyingItem.getTextureRect().height/2);
    lying = true;
}

void FallingItem::setLyingBuffer(sf::SoundBuffer& lyingBuffer)
{
    this->lyingSound.setBuffer(lyingBuffer);
}

void FallingItem::reset()
{
    currentSpeed = sf::Vector2f(0,0);
    trailCounter = 0;
    currentlyLying = false;
    trail.clear();
}

void FallingItem::setPosition(double x, double y){
    animation.setPosition(x,y);
}

bool FallingItem::isOut(){
    return animation.getPosition().y > MAIN_WINDOW_HEIGHT+animation.getHitbox().height;
}

bool FallingItem::isCurrentlyLying() const
{
    return currentlyLying;
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
