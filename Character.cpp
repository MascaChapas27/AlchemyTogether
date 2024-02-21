#include "Character.hpp"
#include "Utilities.hpp"
#include <iostream>
#include "ResourceHolder.hpp"

Character::Character(){
    invincibilityCounter = -1;
    maxItems = 10;
    currentItems = 0;
    shooting = false;
    shootingAngle = INITIAL_SHOOTING_ANGLE + rand()%(FINAL_SHOOTING_ANGLE-INITIAL_SHOOTING_ANGLE+1);
    shootingAngleGoingDown = false;
    shootingCooldown = 0;
    dead = false;
    controller = -1;
    reviveCounter = 0;
}

void Character::setWalkingAnimation(Animation walkingAnimation)
{
    this->walkingAnimation = walkingAnimation;
    this->position = walkingAnimation.getPosition();
}

void Character::setShootingAnimation(Animation shootingAnimation)
{
    this->shootingAnimation = shootingAnimation;
}

void Character::setHoldingAnimation(Animation animation)
{
    this->holdingAnimation = animation;
}

void Character::setSideAnimation(Animation animation)
{
    this->sideAnimation = animation;
}

void Character::setSpeed(double speed)
{
    this->speed = speed;
}

void Character::setKeys(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key shootingKey)
{
    this->leftKey = leftKey;
    this->rightKey = rightKey;
    this->shootingKey = shootingKey;
}

int Character::getController()
{
    return controller;
}

void Character::setController(int controllerID)
{
    this->controller = controllerID;
}

int Character::update(std::list<FallingItem>& fallingItems, Character& buddy)
{
    if(dead){
        fallingCorpse.update();
        return 0;
    }

    bool moved = false;
    if(controller == -1){
        if(sf::Keyboard::isKeyPressed(leftKey)){
            moved = true;
            position.x -= speed;
        } else if(sf::Keyboard::isKeyPressed(rightKey)){
            moved = true;
            position.x += speed;
        }
    } else {
        if(joystick_moving_left(controller)){
            moved = true;
            position.x -= speed;
        } else if(joystick_moving_right(controller)){
            moved = true;
            position.x += speed;
        }
    }


    if(position.x + walkingAnimation.getWidth() > MAIN_WINDOW_WIDTH){
        position.x = MAIN_WINDOW_WIDTH - walkingAnimation.getWidth();
    } else if (position.x-walkingAnimation.getWidth() < 0){
        position.x = walkingAnimation.getWidth();
    }

    // First, update all animations just in case
    walkingAnimation.setPosition(position);
    holdingAnimation.setPosition(position);
    sideAnimation.setPosition(position);
    shootingAnimation.setPosition(position);

    if(moved) {
        walkingAnimation.update();
        shootingAnimation.update();
        holdingAnimation.update();
        sideAnimation.update();
    }
    else {
        walkingAnimation.resetToStart();
        shootingAnimation.resetToStart();
        holdingAnimation.resetToStart();
        sideAnimation.resetToStart();
    }

    // Second, check for collisions

    int lostItems = 0;

    auto iter = fallingItems.begin();
    while(iter != fallingItems.end() && (invincibilityCounter>=30 || invincibilityCounter==-1)){
        sf::IntRect rect1 = iter->getHitbox();
        sf::IntRect rect2 = walkingAnimation.getHitbox();

        if((rect1.left < (rect2.left+rect2.width)) &&
           ((rect1.left+rect1.width) > rect2.left) &&
           (rect1.top < (rect2.top+rect2.height) &&
           ((rect1.top+rect1.height) > rect2.top))){

            if(((iter->getType() == BOOK_TYPE && name == WIZARD_NAME) ||
               (iter->getType() == MAGIC_TYPE && name == ALCHEMIST_NAME) ||
               (iter->getType() == FIRE_TYPE)) &&
                invincibilityCounter == -1){
                damageSound.play();
                if(currentItems == 0){
                    Animation deadCharacter;
                    deadCharacter.setDelay(1);
                    deadCharacter.setPosition(getPosition());
                    deadCharacter.setTexture(name == WIZARD_NAME ? TextureHolder::getTextureInstance()->get(TextureID::wizard_hit) :
                                             TextureHolder::getTextureInstance()->get(TextureID::alchemist_hit),1);

                    fallingCorpse.setAnimation(deadCharacter);
                    fallingCorpse.setPosition(getPosition());
                    fallingCorpse.setCurrentSpeed(sf::Vector2f((-10+rand()%30)/10.0,(-80+rand()%30)/10.0));
                    fallingCorpse.setGravity(GRAVITY*2);
                    fallingCorpse.setRotationSpeed(name == ALCHEMIST_NAME ? 0.4 : -0.4);
                    fallingCorpse.setType(CORPSE_TYPE);
                    fallingCorpse.setLyingItemTexture(TextureHolder::getTextureInstance()->get(name == ALCHEMIST_NAME ? TextureID::alchemist_corpse : TextureID::wizard_corpse));
                    dead = true;
                    return 0;
                } else {
                    lostItems = currentItems;
                    currentItems = 0;
                    invincibilityCounter = 0;
                    iter++;
                }
            } else if(currentItems < maxItems && ((iter->getType() == BOOK_TYPE && name == ALCHEMIST_NAME) ||
               (iter->getType() == MAGIC_TYPE && name == WIZARD_NAME))) {
                iter=fallingItems.erase(iter);
                currentItems = currentItems == maxItems ? maxItems : currentItems+1;
                collectSound.setPitch(1+currentItems/10.0);
                collectSound.play();

                Animation plus1Animation;
                plus1Animation.setDelay(1);
                plus1Animation.setPosition(getPosition());
                plus1Animation.setTexture(name == WIZARD_NAME ? TextureHolder::getTextureInstance()->get(TextureID::wizard_plus1) :
                                         TextureHolder::getTextureInstance()->get(TextureID::alchemist_plus1),1);

                FallingItem fallingPlus1;
                fallingPlus1.setAnimation(plus1Animation);
                fallingPlus1.setPosition(getPosition());
                fallingPlus1.setCurrentSpeed(sf::Vector2f((-20+rand()%40)/10.0,(-60+rand()%10)/10.0));
                fallingPlus1.setGravity(GRAVITY*3);
                fallingPlus1.setRotationSpeed((-5+rand()%10)/10.0);
                fallingPlus1.setType(PLUS1_TYPE);

                fallingItems.insert(iter,fallingPlus1);

            } else {
                iter++;
            }
        } else {
            iter++;
        }
    }

    // Third, update the hit sprite
    if(invincibilityCounter >= 0  && invincibilityCounter < INVINCIBILITY_FRAMES){
        hitSprite.setPosition(walkingAnimation.getPosition().x-walkingAnimation.getHitbox().width,walkingAnimation.getPosition().y-walkingAnimation.getHitbox().height);
        invincibilityCounter++;
    } else if (invincibilityCounter == INVINCIBILITY_FRAMES) invincibilityCounter = -1;

    // Fourth, change the shooting angle if shooting and update the animations
    if(shooting){
        if(shootingAngleGoingDown){
            shootingAngle--;
            if(shootingAngle <= INITIAL_SHOOTING_ANGLE){
                shootingAngleGoingDown = false;
            }
        } else {
            shootingAngle++;
            if(shootingAngle >= FINAL_SHOOTING_ANGLE){
                shootingAngleGoingDown = true;
            }
        }
    }

    // Five, shoot
    if(shooting){
        if(shootingCooldown == 0 && currentItems > 0 && (controller == -1 ? sf::Keyboard::isKeyPressed(shootingKey) : joystick_pressing_any_button(controller))){
            shootSound.play();
            if(name == ALCHEMIST_NAME){
                FallingItem::fallingBook.setPosition(walkingAnimation.getPosition().x+walkingAnimation.getHitbox().width+10,walkingAnimation.getPosition().y-walkingAnimation.getHitbox().height);
                FallingItem::fallingBook.setCurrentSpeed(sf::Vector2f(cos(shootingAngle*PI/180)*ALCHEMIST_STRENGTH,-sin(shootingAngle*PI/180)*ALCHEMIST_STRENGTH));
                fallingItems.insert(fallingItems.begin(),FallingItem::fallingBook);
            } else {
                FallingItem::fallingMagic.setPosition(walkingAnimation.getPosition().x+walkingAnimation.getHitbox().width+10,walkingAnimation.getPosition().y-walkingAnimation.getHitbox().height);
                FallingItem::fallingMagic.setCurrentSpeed(sf::Vector2f(cos(shootingAngle*PI/180)*WIZARD_STRENGTH,-sin(shootingAngle*PI/180)*WIZARD_STRENGTH));
                fallingItems.insert(fallingItems.begin(),FallingItem::fallingMagic);
            }
            currentItems--;
            shootingCooldown = MAX_SHOOTING_COOLDOWN;

        } else if(shootingCooldown > 0)
            shootingCooldown--;

        shootingArrow.setRotation(-shootingAngle);
        shootingArrow.setPosition(walkingAnimation.getPosition().x+walkingAnimation.getHitbox().width+10,walkingAnimation.getPosition().y-walkingAnimation.getHitbox().height);
    }

    // Six, revive your buddy
    sf::IntRect rect1 = walkingAnimation.getHitbox();
    sf::IntRect rect2 = buddy.getHitbox();

    if(buddy.isDead() && rectangles_collide(rect1,rect2)){

        buddy.tryToRevive();
    }

    return lostItems;
}

void Character::tryToRevive()
{
    if(!dead) return;

    reviveCounter++;

    if(reviveCounter >= POINTS_TO_REVIVE){

        position = sf::Vector2f(fallingCorpse.getPosition().x,name == WIZARD_NAME ? WIZARD_INITIAL_Y : ALCHEMIST_INITIAL_Y);

        walkingAnimation.setPosition(position);
        sideAnimation.setPosition(position);
        shootingAnimation.setPosition(position);
        holdingAnimation.setPosition(position);

        reviveCounter = 0;
        invincibilityCounter = HIT_SPRITE_DURATION;

        fallingCorpse.reset();

        dead=false;

        reviveSound.play();
    }
}

sf::IntRect Character::getHitbox(){
    if(dead) return fallingCorpse.getHitbox();
    else return walkingAnimation.getHitbox();
}

void Character::setHitSprite(sf::Sprite hitSprite){
    this->hitSprite = hitSprite;
}

bool Character::isDead(){
    return this->dead;
}

void Character::setShootingArrowTexture(sf::Texture& texture)
{
    this->shootingArrow.setTexture(texture);
    shootingArrow.scale(2,2);
    shootingArrow.setOrigin(0.f,shootingArrow.getTextureRect().height/2);
}

void Character::setSoundBuffers(sf::SoundBuffer& damageSoundBuffer, sf::SoundBuffer& collectSoundBuffer, sf::SoundBuffer& shootSoundBuffer, sf::SoundBuffer& reviveSoundBuffer)
{
    damageSound.setBuffer(damageSoundBuffer);
    collectSound.setBuffer(collectSoundBuffer);
    shootSound.setBuffer(shootSoundBuffer);
    reviveSound.setBuffer(reviveSoundBuffer);
}

void Character::draw(sf::RenderTarget& r, sf::RenderStates s) const{

    if(dead){
        r.draw(fallingCorpse,s);

        // Draw the revive points
        if(fallingCorpse.isCurrentlyLying()){
            sf::RectangleShape backgroundRectangle(sf::Vector2f(fallingCorpse.getHitbox().width,10));
            backgroundRectangle.setFillColor(name == WIZARD_NAME ? sf::Color(100,100,000) : sf::Color(100,100,100));
            backgroundRectangle.setPosition(fallingCorpse.getPosition().x-fallingCorpse.getHitbox().width/2,fallingCorpse.getPosition().y-fallingCorpse.getHitbox().height-10);
            r.draw(backgroundRectangle,s);

            sf::RectangleShape rectangle(sf::Vector2f(((double)reviveCounter/POINTS_TO_REVIVE)*fallingCorpse.getHitbox().width,10));
            rectangle.setFillColor(name == WIZARD_NAME ? sf::Color::Yellow : sf::Color::White);
            rectangle.setPosition(fallingCorpse.getPosition().x-fallingCorpse.getHitbox().width/2,fallingCorpse.getPosition().y-fallingCorpse.getHitbox().height-10);
            r.draw(rectangle,s);
        }
        return;
    }

    Animation animation;

    if(shooting){
        if(shootingCooldown > MAX_SHOOTING_COOLDOWN/2){
            animation = shootingAnimation;
        } else if (currentItems > 0){
            animation = holdingAnimation;
        } else {
            animation = sideAnimation;
        }
    } else {
        animation = walkingAnimation;
    }

    if(invincibilityCounter == -1) r.draw(animation,s);
    else if (invincibilityCounter%2==0){
        if(invincibilityCounter < HIT_SPRITE_DURATION) r.draw(hitSprite,s);
        else r.draw(animation,s);
    }

    // Draw the amount of items left
    sf::RectangleShape backgroundRectangle(sf::Vector2f(animation.getHitbox().width*2,10));
    backgroundRectangle.setFillColor(name == WIZARD_NAME ? sf::Color(100,100,000) : sf::Color(100,100,100));
    backgroundRectangle.setPosition(animation.getPosition().x-animation.getHitbox().width,animation.getPosition().y-animation.getHitbox().height-10);
    r.draw(backgroundRectangle,s);

    sf::RectangleShape rectangle(sf::Vector2f(((double)currentItems/maxItems)*animation.getHitbox().width*2,10));
    rectangle.setFillColor(name == WIZARD_NAME ? sf::Color::Yellow : sf::Color::White);
    rectangle.setPosition(animation.getPosition().x-animation.getHitbox().width,animation.getPosition().y-animation.getHitbox().height-10);
    r.draw(rectangle,s);

    // Draw the shooting angle
    if(shooting){
        r.draw(shootingArrow,s);
    }

    if(DEBUG){
        sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(animation.getHitbox().width,animation.getHitbox().height));
        rectangle.setPosition(animation.getHitbox().left,animation.getHitbox().top);
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(1);
        rectangle.setFillColor(sf::Color::Transparent);
        r.draw(rectangle,s);
    }
}

sf::Vector2f Character::getPosition()
{
    return this->position;
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

void Character::setShooting(bool shooting){
    this->shooting = shooting;
    if(shooting) {
        holdingAnimation.setPosition(walkingAnimation.getPosition());
        sideAnimation.setPosition(walkingAnimation.getPosition());
        shootingArrow.setPosition(walkingAnimation.getPosition().x+walkingAnimation.getHitbox().width+10,walkingAnimation.getPosition().y-walkingAnimation.getHitbox().height);
    }
    else walkingAnimation.setPosition(sideAnimation.getPosition());
}
