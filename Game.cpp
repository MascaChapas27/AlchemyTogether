#include "Game.hpp"
#include "Utilities.hpp"
#include <iostream>
#include "ResourceHolder.hpp"
#include "MusicPlayer.hpp"
#include "BadEndingCutscene.hpp"
#include "GoodEndingCutscene.hpp"

Game::Game(){
    this->windowGoingDown = false;
    this->windowMovement = 0;
}

void Game::run(int alchemistController, int wizardController){

    TextureHolder * textureHolder = TextureHolder::getTextureInstance();
    SoundHolder * soundHolder = SoundHolder::getSoundInstance();

    MusicPlayer::getInstance()->play(MusicID::battle_music);

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

    wizard.setShootingArrowTexture(textureHolder->get(TextureID::wizard_arrow));

    wizard.setKeys(sf::Keyboard::J, sf::Keyboard::L, sf::Keyboard::I);
    wizard.setSpeed(3);
    wizard.setName(WIZARD_NAME);
    wizard.setSoundBuffers(soundHolder->get(SoundID::wizard_damage),soundHolder->get(SoundID::wizard_collect),soundHolder->get(SoundID::wizard_shoot),soundHolder->get(SoundID::wizard_revive));
    wizard.setController(wizardController);
    wizard.setInventoryTexture(textureHolder->get(TextureID::wizard_inventory));
    wizard.setReviveTexture(textureHolder->get(TextureID::wizard_revive));

    // Prepare the alchemist
    Animation walkingAlchemist;
    walkingAlchemist.setDelay(15);
    walkingAlchemist.setTexture(textureHolder->get(TextureID::alchemist_walk),2);
    walkingAlchemist.setPosition(ALCHEMIST_INITIAL_X-2,MAIN_WINDOW_HEIGHT-walkingAlchemist.getHitbox().height);
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

    alchemist.setShootingArrowTexture(textureHolder->get(TextureID::alchemist_arrow));

    alchemist.setKeys(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W);
    alchemist.setSpeed(3);
    alchemist.setName(ALCHEMIST_NAME);
    alchemist.setSoundBuffers(soundHolder->get(SoundID::alchemist_damage),soundHolder->get(SoundID::alchemist_collect),soundHolder->get(SoundID::alchemist_shoot),soundHolder->get(SoundID::alchemist_revive));
    alchemist.setController(alchemistController);
    alchemist.setInventoryTexture(textureHolder->get(TextureID::alchemist_inventory));
    alchemist.setReviveTexture(textureHolder->get(TextureID::alchemist_revive));

    // Prepare the boss
    Animation flyingBoss;
    flyingBoss.setDelay(15);
    flyingBoss.setTexture(textureHolder->get(TextureID::boss),3);
    flyingBoss.setPosition(BOSS_X,-flyingBoss.getHitbox().height*2);

    boss.setAnimation(flyingBoss);
    boss.setSoundBuffers(soundHolder->get(SoundID::boss_appear),
                         soundHolder->get(SoundID::boss_disappear),
                         soundHolder->get(SoundID::boss_damage),
                         soundHolder->get(SoundID::boss_shoot));

    sf::Sprite hitBoss;
    hitBoss.setTexture(textureHolder->get(TextureID::boss_hit));
    hitBoss.scale(2.f,2.f);

    boss.setHitSprite(hitBoss);
    boss.setHealthTexture(textureHolder->get(TextureID::boss_health));

    // Prepare the backgrounds
    background.setTexture(textureHolder->get(TextureID::background));
    background.scale(2.f,2.f);

    sf::Sprite timeFrameSprite;
    timeFrameSprite.setTexture(textureHolder->get(TextureID::time_frame));
    timeFrameSprite.scale(2.f,2.f);
    timeFrameSprite.setPosition(20,20);

    // Prepare the animations for the falling stuff
    Animation fallingBookAnimation;
    sf::Texture fallingBookTexture;
    fallingBookAnimation.setDelay(1);
    fallingBookAnimation.setTexture(TextureHolder::getTextureInstance()->get(TextureID::book),2);

    FallingItem::fallingBook.setAnimation(fallingBookAnimation);
    FallingItem::fallingBook.setGravity(GRAVITY);
    FallingItem::fallingBook.setType(BOOK_TYPE);

    Animation fallingMagicAnimation;
    fallingMagicAnimation.setTexture(textureHolder->get(TextureID::magic),2);
    fallingMagicAnimation.setDelay(10);

    FallingItem::fallingMagic.setAnimation(fallingMagicAnimation);
    FallingItem::fallingMagic.setGravity(GRAVITY);
    FallingItem::fallingMagic.setType(MAGIC_TYPE);

    Animation fallingFireAnimation;
    fallingFireAnimation.setTexture(textureHolder->get(TextureID::fire),2);
    fallingFireAnimation.setDelay(10);

    FallingItem::fallingFire.setAnimation(fallingFireAnimation);
    FallingItem::fallingFire.setGravity(GRAVITY);
    FallingItem::fallingFire.setType(FIRE_TYPE);

    // Prepare the font to write the time
    sf::Text clockText;
    clockText.setFont(FontHolder::getFontInstance()->get(FontID::WizardFont));
    clockText.setCharacterSize(20);
    clockText.setFillColor(sf::Color::Blue);
    clockText.setPosition(SPANISH ? 50 : 63,44);

    int difficulty = 20;

    sf::Clock clock;

    bool bossHere = false;

    while(!(wizard.isDead() && alchemist.isDead()) && boss.getCurrentHealth()>0){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if((RECREATIVA && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6) ||
               (!RECREATIVA && event.type == sf::Event::Closed)){
                mainWindow.close();
                exit(EXIT_SUCCESS);
            }
        }

        if(windowMovement > 0){
            if(windowGoingDown){
                mainWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x,mainWindow.getPosition().y+windowMovement));
            } else {
                mainWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x,mainWindow.getPosition().y-windowMovement));
                windowMovement--;
            }
            windowGoingDown = !windowGoingDown;
        }

        // Spawn books or magic
        if(rand()%difficulty==0){
            if(!bossHere){
                if(rand()%2){
                    sf::Vector2f position;
                    position.y = -FallingItem::fallingBook.getHitbox().height;
                    position.x = FallingItem::fallingBook.getHitbox().width + rand()%(MAIN_WINDOW_WIDTH-FallingItem::fallingBook.getHitbox().width);
                    FallingItem::fallingBook.setPosition(position);
                    FallingItem::fallingBook.setCurrentSpeed(sf::Vector2f(0,0));
                    FallingItem::fallingBook.setRotationSpeed((-10+rand()%21)/10.0);
                    fallingItems.insert(fallingItems.begin(),FallingItem::fallingBook);
                } else {
                    sf::Vector2f position;
                    position.y = -FallingItem::fallingMagic.getHitbox().height;
                    position.x = rand()%(MAIN_WINDOW_WIDTH-FallingItem::fallingMagic.getHitbox().width);
                    FallingItem::fallingMagic.setPosition(position);
                    FallingItem::fallingMagic.setCurrentSpeed(sf::Vector2f(0,0));
                    FallingItem::fallingMagic.setRotationSpeed((-10+rand()%21)/10.0);
                    fallingItems.insert(fallingItems.begin(),FallingItem::fallingMagic);
                }
            }
        }

        // Check if wizard got hit and lost magic
        int wizardLostItems = wizard.update(fallingItems,alchemist);

        if(wizardLostItems != 0){
            windowMovement=WINDOW_SHAKE_HIT;
            for(int i=0;i<wizardLostItems;i++){
                FallingItem::fallingMagic.setPosition(wizard.getPosition());
                FallingItem::fallingMagic.setCurrentSpeed(sf::Vector2f((-10+rand()%30)/10.0,(-80+rand()%30)/10.0));
                FallingItem::fallingMagic.setRotationSpeed((-10+rand()%21)/10.0);
                fallingItems.insert(fallingItems.begin(),FallingItem::fallingMagic);
            }
        }

        // Check if alchemist got hit and lost books
        int alchemistLostItems = alchemist.update(fallingItems, wizard);

        if(alchemistLostItems != 0){
            windowMovement=WINDOW_SHAKE_HIT;
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
        char clockString[30];
        sprintf(clockString,SPANISH ? "Tiempo: 00:%02d" : "Time: 00:%02d",(bossHere ? BOSS_TIME : GATHER_TIME) - (int)clock.getElapsedTime().asSeconds());
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

        mainWindow.draw(background);
        mainWindow.draw(wizard);
        mainWindow.draw(alchemist);
        mainWindow.draw(boss);
        for(FallingItem fallingItem : fallingItems){
            mainWindow.draw(fallingItem);
        }
        mainWindow.draw(timeFrameSprite);
        mainWindow.draw(clockText);

        mainWindow.display();
    }

    wizard.setShowSigns(false);
    alchemist.setShowSigns(false);

    MusicPlayer::getInstance()->stop();

    sf::Clock endClock;
    endClock.restart();

    auto iter = fallingItems.begin();
    while(iter != fallingItems.end()){
        if(iter->getType() != CORPSE_TYPE) iter=fallingItems.erase(iter);
        else iter++;
    }

    if(wizard.isDead() && alchemist.isDead()){

        bool fadeBlack = false;

        sf::RectangleShape foregroundRectangle(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));
        foregroundRectangle.setFillColor(sf::Color(0,0,0,0));

        MusicPlayer::getInstance()->play(MusicID::death_music);

        while(foregroundRectangle.getFillColor().a < 255){
            sf::Event event;
            while(mainWindow.pollEvent(event)){
                if((RECREATIVA && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6) ||
                   (!RECREATIVA && event.type == sf::Event::Closed)){
                    mainWindow.close();
                    exit(EXIT_SUCCESS);
                }
            }

            if(windowMovement > 0){
                if(windowGoingDown){
                    mainWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x,mainWindow.getPosition().y+windowMovement));
                } else {
                    mainWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x,mainWindow.getPosition().y-windowMovement));
                    windowMovement--;
                }
                windowGoingDown = !windowGoingDown;
            }

            if(!fadeBlack && endClock.getElapsedTime().asSeconds() > 3){
                fadeBlack = true;
            }

            if(fadeBlack){
                sf::Color newColor = foregroundRectangle.getFillColor();
                if(newColor.a < 255) newColor.a++;
                foregroundRectangle.setFillColor(newColor);
            }

            wizard.update(fallingItems,alchemist);
            alchemist.update(fallingItems,wizard);

            mainWindow.clear();
            mainWindow.draw(wizard);
            mainWindow.draw(alchemist);
            mainWindow.draw(foregroundRectangle);
            mainWindow.display();
        }

        BadEndingCutscene badEndingCutscene;
        badEndingCutscene.play();

    } else {

        bool dancing = false;
        bool fadeBlack = false;
        Animation wizardAnimation;
        wizardAnimation.setDelay(25);
        wizardAnimation.setPingPong(false);
        wizardAnimation.setTexture(textureHolder->get(TextureID::wizard_dance),4);

        Animation alchemistAnimation;
        alchemistAnimation.setPingPong(true);
        alchemistAnimation.setDelay(15);
        alchemistAnimation.setTexture(textureHolder->get(TextureID::alchemist_dance),6);

        sf::RectangleShape foregroundRectangle(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));
        foregroundRectangle.setFillColor(sf::Color(0,0,0,0));

        while(foregroundRectangle.getFillColor().a < 255){
            sf::Event event;
            while(mainWindow.pollEvent(event)){
                if((RECREATIVA && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6) ||
                   (!RECREATIVA && event.type == sf::Event::Closed)){
                    mainWindow.close();
                    exit(EXIT_SUCCESS);
                }
            }

            if(!dancing && endClock.getElapsedTime().asSeconds() > 3){
                dancing = true;
                wizardAnimation.setPosition(wizard.isDead() ? -300 : wizard.getPosition().x,wizard.isDead() ? -300 : wizard.getPosition().y);
                alchemistAnimation.setPosition(alchemist.isDead() ? -300 : alchemist.getPosition().x,alchemist.isDead() ? -300 : alchemist.getPosition().y);
                MusicPlayer::getInstance()->play(MusicID::good_ending_music);
            }

            if(!fadeBlack && endClock.getElapsedTime().asSeconds() > 5){
                fadeBlack = true;
            }

            if(fadeBlack){
                sf::Color newColor = foregroundRectangle.getFillColor();
                newColor.a++;
                foregroundRectangle.setFillColor(newColor);
            }

            for(FallingItem& fallingItem : fallingItems){
                fallingItem.update();
            }

            if(dancing){
                alchemistAnimation.update();
                wizardAnimation.update();
            }
            wizard.update(fallingItems,alchemist);
            alchemist.update(fallingItems,wizard);

            mainWindow.clear();

            for(FallingItem& fallingItem : fallingItems){
                mainWindow.draw(fallingItem);
            }
            if(dancing){

                if(wizard.isDead()) mainWindow.draw(wizard);
                else mainWindow.draw(wizardAnimation);

                if(alchemist.isDead()) mainWindow.draw(alchemist);
                else mainWindow.draw(alchemistAnimation);

            } else {
                mainWindow.draw(wizard);
                mainWindow.draw(alchemist);
            }

            mainWindow.draw(foregroundRectangle);
            mainWindow.display();
        }

        GoodEndingCutscene goodEndingCutscene;
        goodEndingCutscene.play();
    }
}
