#include "Boss.hpp"
#include "Utilities.hpp"
#include <iostream>

Boss::Boss(){
    invincibilityCounter = -1;
    currentSpeedX = 0;
    currentSpeedY = 0;
    goingDown = true;
    goingRight = true;
    health = BOSS_INITIAL_HEALTH;
    activated = false;
    attackAux = 0;
}

void Boss::setAnimation(Animation animation){
    this->animation = animation;
    initialY = -animation.getHitbox().height*3;
    finalY = -animation.getHitbox().height*3;
    animation.setColor(sf::Color::Transparent);
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
    this->activated = activated;
    if(activated){
        attackAux = 0;
        appearingSound.play();
        initialY = BOSS_INITIAL_Y;
        finalY = BOSS_FINAL_Y;
        goingDown = true;
        attack = static_cast<AttackType>(rand()%NUM_BOSS_ATTACKS);

    } else {
        disappearingSound.play();
        initialY = -animation.getHitbox().height*3;
        finalY = -animation.getHitbox().height*3;
        goingDown = false;
    }
}

void Boss::update(std::list<FallingItem>& fallingItems){

    // Zero, make the boss transparent if it's deactivated and the opposite
    if(activated){
        sf::Color newColor = animation.getColor();
        if(newColor.a < 255) newColor.a+=1;
        animation.setColor(newColor);
    } else {
        sf::Color newColor = animation.getColor();
        if(newColor.a > 0) newColor.a-=1;
        animation.setColor(newColor);
    }

    // First, move the boss
    sf::Vector2f newPosition = animation.getPosition();
    currentSpeedY = currentSpeedY + (goingDown ? BOSS_SPEED : -BOSS_SPEED);
    if(currentSpeedY > BOSS_MAX_SPEED) currentSpeedY = BOSS_MAX_SPEED;
    if(currentSpeedY < -BOSS_MAX_SPEED) currentSpeedY = -BOSS_MAX_SPEED;
    newPosition.y+=currentSpeedY;

    animation.setPosition(newPosition.x,newPosition.y);

    animation.update();

    // Second, change direction
    int currentY = animation.getPosition().y;
    if(goingDown && currentY>finalY){
        goingDown = false;
    } else if (!goingDown && currentY < initialY){
        goingDown = true;
    }

    // Third, check for collisions if activated
    if(activated){
        auto iter = fallingItems.begin();
        while(iter != fallingItems.end() && (invincibilityCounter>=10 || invincibilityCounter==-1)){
            sf::IntRect rect1 = iter->getHitbox();
            sf::IntRect rect2 = animation.getHitbox();
            rect2.left-=rect2.width/2;

            if((rect1.left < (rect2.left+rect2.width)) &&
               ((rect1.left+rect1.width) > rect2.left) &&
               (rect1.top < (rect2.top+rect2.height) &&
               ((rect1.top+rect1.height) > rect2.top))){

                if(iter->getType() == BOOK_TYPE || iter->getType() == MAGIC_TYPE){
                    damageSound.play();
                    health--;
                    iter=fallingItems.erase(iter);
                    invincibilityCounter=0;
                } else {
                    iter++;
                }
            } else {
                iter++;
            }
        }
    }

    // Fourth, update the animation
    if(invincibilityCounter >= 0  && invincibilityCounter < BOSS_INVINCIBILITY_FRAMES){
        hitSprite.setPosition(animation.getPosition().x-animation.getHitbox().width,animation.getPosition().y-animation.getHitbox().height);
        invincibilityCounter++;
    } else if (invincibilityCounter == BOSS_INVINCIBILITY_FRAMES) invincibilityCounter = -1;

    // Fifth, shoot
    if(activated){
        switch(attack){
        case AttackType::CIRCLES:
            attackCircles(fallingItems);
            break;
        case AttackType::RAIN_LEFT_TO_RIGHT:
            attackRainLeftToRight(fallingItems);
            break;
        case AttackType::RAIN_WITH_HOLES:
            attackRainWithHoles(fallingItems);
            break;
        case AttackType::RANDOM_RAIN:
            attackRandomRain(fallingItems);
            break;
        case AttackType::UNIFORM_RAIN:
            attackUniformRain(fallingItems);
            break;
        }
    }
}

void Boss::attackCircles(std::list<FallingItem>& fallingItems)
{
    if(attackAux == 0){
        shootSound.play();
        double transpos = (rand()%100) / 10.0;
        for(int i=0;i<NUM_FIRE_CIRCLES;i++){
            double angle = transpos + i/((double)NUM_FIRE_CIRCLES) * 2*PI;
            FallingItem::fallingFire.setPosition(getPosition());
            FallingItem::fallingFire.setCurrentSpeed(sf::Vector2f(cos(angle)*3,sin(angle)*3));
            FallingItem::fallingFire.setRotationSpeed((-10+rand()%21)/10.0);
            fallingItems.insert(fallingItems.begin(),FallingItem::fallingFire);
        }
        attackAux = MAX_FPS*2;
    } else
        attackAux--;
}

void Boss::attackRainLeftToRight(std::list<FallingItem>& fallingItems)
{
    if(attackAux < MAX_FPS*2){
        if(attackAux%RAIN_LEFT_TO_RIGHT_LATENCY == 0){
            double positionX = MAIN_WINDOW_WIDTH*((double)attackAux/(MAX_FPS*2));
            FallingItem::fallingFire.setPosition(sf::Vector2f(positionX,-30));
            FallingItem::fallingFire.setCurrentSpeed(sf::Vector2f((-2+rand()%4)/10.0,0));
            FallingItem::fallingFire.setRotationSpeed((-10+rand()%21)/10.0);
            fallingItems.insert(fallingItems.begin(),FallingItem::fallingFire);
        }
        attackAux++;
    } else {
        attackAux = 0;
    }
}

void Boss::attackRainWithHoles(std::list<FallingItem>& fallingItems)
{
    if(attackAux == 0){
        shootSound.play();

        int hole1 = rand()%NUM_FIRE_RAIN_WITH_HOLES;
        int hole2 = (hole1 + NUM_FIRE_RAIN_WITH_HOLES/2) %NUM_FIRE_RAIN_WITH_HOLES;

        for(int i=0;i<NUM_FIRE_RAIN_WITH_HOLES;i++){
            if(i == hole1 || i == hole2) continue;
            double positionX = MAIN_WINDOW_WIDTH*((double)i/NUM_FIRE_RAIN_WITH_HOLES);
            FallingItem::fallingFire.setPosition(sf::Vector2f(positionX,-30));
            FallingItem::fallingFire.setCurrentSpeed(sf::Vector2f(0,0));
            FallingItem::fallingFire.setRotationSpeed((-10+rand()%21)/10.0);
            fallingItems.insert(fallingItems.begin(),FallingItem::fallingFire);
        }
        attackAux = MAX_FPS;
    } else {
        attackAux--;
    }
}

void Boss::attackRandomRain(std::list<FallingItem>& fallingItems)
{
    if(attackAux == 0){
        shootSound.play();
        double positionX = MAIN_WINDOW_WIDTH*(rand()%100/100.0);
        FallingItem::fallingFire.setPosition(sf::Vector2f(positionX,-30));
        FallingItem::fallingFire.setCurrentSpeed(sf::Vector2f(0,0));
        FallingItem::fallingFire.setRotationSpeed((-10+rand()%21)/10.0);
        fallingItems.insert(fallingItems.begin(),FallingItem::fallingFire);
        attackAux = MAX_FPS/RANDOM_RAIN_FIRE_PER_SECOND;
    } else {
        attackAux--;
    }
}

void Boss::attackUniformRain(std::list<FallingItem>& fallingItems)
{
    if(attackAux == 0){
        shootSound.play();

        for(int i=0;i<NUM_FIRE_UNIFORM_RAIN;i++){
            double positionX = MAIN_WINDOW_WIDTH*((double)i/NUM_FIRE_UNIFORM_RAIN);
            FallingItem::fallingFire.setPosition(sf::Vector2f(positionX,-30));
            FallingItem::fallingFire.setCurrentSpeed(sf::Vector2f((-2+rand()%4)/10.0,0));
            FallingItem::fallingFire.setRotationSpeed((-10+rand()%21)/10.0);
            fallingItems.insert(fallingItems.begin(),FallingItem::fallingFire);
        }
        attackAux = MAX_FPS;
    } else {
        attackAux--;
    }
}


void Boss::draw(sf::RenderTarget& r, sf::RenderStates s) const{
    if(invincibilityCounter == -1) r.draw(animation,s);
    else if (invincibilityCounter%2==0){
        if(invincibilityCounter < 10) r.draw(hitSprite,s);
        else r.draw(animation,s);
    }

    sf::RectangleShape backgroundRectangle(sf::Vector2f(animation.getHitbox().width*2,10));
    backgroundRectangle.setFillColor(sf::Color(0,0,100));
    backgroundRectangle.setPosition(animation.getPosition().x-animation.getHitbox().width,animation.getPosition().y-animation.getHitbox().height-10);
    r.draw(backgroundRectangle,s);

    sf::RectangleShape rectangle(sf::Vector2f(((double)health/BOSS_INITIAL_HEALTH)*animation.getHitbox().width*2,10));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(animation.getPosition().x-animation.getHitbox().width,animation.getPosition().y-animation.getHitbox().height-10);
    r.draw(rectangle,s);
}

void Boss::setSoundBuffers(sf::SoundBuffer& appearing, sf::SoundBuffer& disappearing, sf::SoundBuffer& damage, sf::SoundBuffer& shoot)
{
    appearingSound.setBuffer(appearing);
    disappearingSound.setBuffer(disappearing);
    damageSound.setBuffer(damage);
    shootSound.setBuffer(shoot);
}
