#include "Game.hpp"
#include "Utilities.hpp"
#include <iostream>
#include "ResourceHolder.hpp"

void Game::run(){

    TextureHolder * textureHolder = TextureHolder::getTextureInstance();

    // Prepare the wizard
    Animation walkingWizard;
    walkingWizard.setDelay(10);
    walkingWizard.setTexture(textureHolder->get(TextureID::wizard_walk),2);
    walkingWizard.setPosition(WIZARD_INITIAL_X,MAIN_WINDOW_HEIGHT-walkingWizard.getHitbox().height);
    wizard.setWalkingAnimation(walkingWizard);

    Animation shootingWizard;
    shootingWizard.setDelay(10);
    shootingWizard.setTexture(textureHolder->get(TextureID::wizard_shoot),2);
    wizard.setShootingAnimation(shootingWizard);

    Animation holdingWizard;
    holdingWizard.setDelay(10);
    holdingWizard.setTexture(textureHolder->get(TextureID::wizard_hold),2);
    wizard.setHoldingAnimation(holdingWizard);

    Animation sideWizard;
    sideWizard.setDelay(10);
    sideWizard.setTexture(textureHolder->get(TextureID::wizard_side),2);
    wizard.setSideAnimation(sideWizard);

    sf::Sprite hitWizard;
    hitWizard.setTexture(textureHolder->get(TextureID::wizard_hit),1);
    hitWizard.scale(2.f,2.f);
    wizard.setHitSprite(hitWizard);

    wizard.setKeys(sf::Keyboard::J, sf::Keyboard::L, sf::Keyboard::I);
    wizard.setSpeed(3);
    wizard.setName(WIZARD_NAME);

    // Prepare the alchemist
    Animation walkingAlchemist;
    walkingAlchemist.setDelay(15);
    walkingAlchemist.setTexture(textureHolder->get(TextureID::alchemist_walk),2);
    walkingAlchemist.setPosition(ALCHEMIST_INITIAL_X,MAIN_WINDOW_HEIGHT-walkingAlchemist.getHitbox().height);
    alchemist.setWalkingAnimation(walkingAlchemist);

    Animation shootingAlchemist;
    shootingAlchemist.setDelay(15);
    shootingAlchemist.setTexture(textureHolder->get(TextureID::alchemist_shoot),2);
    alchemist.setShootingAnimation(shootingAlchemist);

    Animation sideAlchemist;
    sideAlchemist.setDelay(15);
    sideAlchemist.setTexture(textureHolder->get(TextureID::alchemist_side),2);
    alchemist.setSideAnimation(sideAlchemist);

    Animation holdingAlchemist;
    holdingAlchemist.setDelay(15);
    holdingAlchemist.setTexture(textureHolder->get(TextureID::alchemist_hold),2);
    alchemist.setHoldingAnimation(holdingAlchemist);

    sf::Sprite hitAlchemist;
    hitAlchemist.setTexture(textureHolder->get(TextureID::alchemist_hit));
    hitAlchemist.scale(2.f,2.f);
    alchemist.setHitSprite(hitAlchemist);

    alchemist.setKeys(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W);
    alchemist.setSpeed(3);
    alchemist.setName(ALCHEMIST_NAME);

    // Prepare the boss
    Animation flyingBoss;
    flyingBoss.setDelay(15);

    sf::Texture flyingBossTexture;
    flyingBossTexture.loadFromFile("sprites/boss.png");

    flyingBoss.setTexture(flyingBossTexture,3);
    flyingBoss.setPosition(BOSS_X,-flyingBoss.getHitbox().height*2);

    boss.setAnimation(flyingBoss);

    sf::Sprite hitBoss;
    sf::Texture hitBossTexture;
    hitBossTexture.loadFromFile("sprites/boss-hit.png");
    hitBoss.setTexture(hitBossTexture);
    hitBoss.scale(2.f,2.f);

    boss.setHitSprite(hitBoss);

    // Prepare the backgrounds
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("sprites/background.png");
    background.setTexture(backgroundTexture);
    background.scale(2.f,2.f);

    sf::Texture walkingBackgroundTexture;
    walkingBackgroundTexture.loadFromFile("sprites/walking-background.png");
    sf::Sprite walkingBackground;
    walkingBackground.setTexture(walkingBackgroundTexture);
    walkingBackground.scale(2.f,2.f);

    sf::Texture shootingBackgroundTexture;
    shootingBackgroundTexture.loadFromFile("sprites/shooting-background.png");
    sf::Sprite shootingBackground;
    shootingBackground.setTexture(shootingBackgroundTexture);
    shootingBackground.scale(2.f,2.f);

    // Prepare the animations for the falling stuff
    Animation fallingBookAnimation;
    sf::Texture fallingBookTexture;
    fallingBookAnimation.setDelay(1);
    fallingBookAnimation.setTexture(TextureHolder::getTextureInstance()->get(TextureID::book),2);

    FallingItem::fallingBook.setAnimation(fallingBookAnimation);
    FallingItem::fallingBook.setGravity(GRAVITY);
    FallingItem::fallingBook.setType(BOOK_TYPE);

    Animation fallingMagicAnimation;
    sf::Texture fallingMagicTexture;
    fallingMagicTexture.loadFromFile("sprites/magic.png");
    fallingMagicAnimation.setTexture(fallingMagicTexture,2);
    fallingMagicAnimation.setDelay(10);

    FallingItem::fallingMagic.setAnimation(fallingMagicAnimation);
    FallingItem::fallingMagic.setGravity(GRAVITY);
    FallingItem::fallingMagic.setType(MAGIC_TYPE);

    Animation fallingFireAnimation;
    sf::Texture fallingFireTexture;
    fallingFireTexture.loadFromFile("sprites/fire.png");
    fallingFireAnimation.setTexture(fallingFireTexture,2);
    fallingFireAnimation.setDelay(10);

    FallingItem::fallingFire.setAnimation(fallingFireAnimation);
    FallingItem::fallingFire.setGravity(GRAVITY);
    FallingItem::fallingFire.setType(FIRE_TYPE);

    // Prepare the font to write the time
    sf::Font clockFont;
    clockFont.loadFromFile("fonts/father.ttf");
    sf::Text clockText;
    clockText.setFont(clockFont);
    clockText.setFillColor(sf::Color::Blue);
    clockText.setCharacterSize(22);
    clockText.setPosition(26,24);
    clockText.setString("Time left: ");

    int difficulty = 20;

    sf::Clock clock;

    bool bossHere = false;

    while(boss.getCurrentHealth()>0){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                mainWindow.close();
                auxWindow.close();
                exit(0);
            }
        }

        while(auxWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                mainWindow.close();
                auxWindow.close();
                exit(0);
            }
        }

        // Spawn books or magic or the boss
        if(rand()%difficulty==0){
            if(!bossHere){
                if(rand()%2){
                    sf::Vector2f position;
                    position.y = -FallingItem::fallingBook.getHitbox().height;
                    position.x = rand()%(MAIN_WINDOW_HEIGHT-FallingItem::fallingBook.getHitbox().width);
                    FallingItem::fallingBook.setPosition(position);
                    FallingItem::fallingBook.setCurrentSpeed(sf::Vector2f(0,0));
                    FallingItem::fallingBook.setRotationSpeed((-10+rand()%21)/10.0);
                    fallingItems.insert(fallingItems.begin(),FallingItem::fallingBook);
                } else {
                    sf::Vector2f position;
                    position.y = -FallingItem::fallingMagic.getHitbox().height;
                    position.x = rand()%(MAIN_WINDOW_HEIGHT-FallingItem::fallingMagic.getHitbox().width);
                    FallingItem::fallingMagic.setPosition(position);
                    FallingItem::fallingMagic.setCurrentSpeed(sf::Vector2f(0,0));
                    FallingItem::fallingMagic.setRotationSpeed((-10+rand()%21)/10.0);
                    fallingItems.insert(fallingItems.begin(),FallingItem::fallingMagic);
                }
            } else {
                FallingItem::fallingFire.setPosition(boss.getPosition());
                FallingItem::fallingFire.setCurrentSpeed(sf::Vector2f((-40+rand()%45)/10.0,(-40+rand()%20)/10.0));
                FallingItem::fallingFire.setRotationSpeed((-10+rand()%21)/10.0);
                fallingItems.insert(fallingItems.begin(),FallingItem::fallingFire);
            }
        }

        // Check if wizard got hit and lost magic
        int wizardLostItems = wizard.update(fallingItems);

        if(wizardLostItems > 0){
            for(int i=0;i<wizardLostItems;i++){
                FallingItem::fallingMagic.setPosition(wizard.getPosition());
                FallingItem::fallingMagic.setCurrentSpeed(sf::Vector2f((-10+rand()%30)/10.0,(-80+rand()%30)/10.0));
                FallingItem::fallingMagic.setRotationSpeed((-10+rand()%21)/10.0);
                fallingItems.insert(fallingItems.begin(),FallingItem::fallingMagic);
            }
        }

        // Check if alchemist got hit and lost books
        int alchemistLostItems = alchemist.update(fallingItems);

        if(alchemistLostItems > 0){
            for(int i=0;i<alchemistLostItems;i++){
                FallingItem::fallingBook.setPosition(alchemist.getPosition());
                FallingItem::fallingBook.setCurrentSpeed(sf::Vector2f((-10+rand()%30)/10.0,(-80+rand()%30)/10.0));
                FallingItem::fallingBook.setRotationSpeed((-10+rand()%21)/10.0);
                fallingItems.insert(fallingItems.begin(),FallingItem::fallingBook);
            }
        }

        // Update the boss
        boss.update(fallingItems);

        // Check the clocks
        if(!bossHere){
            if(clock.getElapsedTime().asSeconds() >= GATHER_TIME){
                clock.restart();
                bossHere=true;
                boss.setActivated(true);
                wizard.setShooting(true);
                alchemist.setShooting(true);
            }
        } else if (bossHere){
            if(clock.getElapsedTime().asSeconds() >= BOSS_TIME){
                clock.restart();
                bossHere=false;
                boss.setActivated(false);
                wizard.setShooting(false);
                alchemist.setShooting(false);
            }
        }

        // Update the texts
        char clockString[20];
        sprintf(clockString,"Time left: 00:%02d",(bossHere ? BOSS_TIME : GATHER_TIME) - (int)clock.getElapsedTime().asSeconds());
        clockText.setString(clockString);

        auto iter = fallingItems.begin();
        while(iter != fallingItems.end()){
            if(iter->isOut()) iter=fallingItems.erase(iter);
            else {
                iter->update();
                iter++;
            }
        }

        flyingBoss.update();

        mainWindow.clear();
        auxWindow.clear();

        mainWindow.draw(background);
        if(!bossHere) auxWindow.draw(walkingBackground);
        else auxWindow.draw(shootingBackground);
        auxWindow.draw(clockText);
        mainWindow.draw(wizard);
        mainWindow.draw(alchemist);
        mainWindow.draw(boss);
        for(FallingItem fallingItem : fallingItems){
            mainWindow.draw(fallingItem);
        }

        mainWindow.display();
        auxWindow.display();
    }
}
