#include "Game.hpp"
#include "Utilities.hpp"
#include <iostream>

void Game::run(){

    // Prepare the wizard
    Animation walkingWizard;
    walkingWizard.setDelay(20);
    walkingWizard.setNumPhotograms(2);
    walkingWizard.setPosition(WIZARD_INITIAL_X,WIZARD_INITIAL_Y);

    sf::Texture walkingWizardTexture;
    walkingWizardTexture.loadFromFile("sprites/wizard-walk.png");
    walkingWizard.setTexture(walkingWizardTexture,WIZARD_GAME_WIDTH);

    wizard.setAnimation(walkingWizard);

    sf::Sprite hitWizard;
    sf::Texture hitWizardTexture;
    hitWizardTexture.loadFromFile("sprites/wizard-hit.png");
    hitWizard.setTexture(hitWizardTexture);
    hitWizard.scale(2.f,2.f);

    wizard.setHitSprite(hitWizard);

    wizard.setKeys(sf::Keyboard::J, sf::Keyboard::L);
    wizard.setSpeed(3);
    wizard.setName(WIZARD_NAME);

    // Prepare the alchemist

    Animation walkingAlchemist;
    walkingAlchemist.setDelay(25);
    walkingAlchemist.setNumPhotograms(2);
    walkingAlchemist.setPosition(ALCHEMIST_INITIAL_X,ALCHEMIST_INITIAL_Y);

    sf::Texture walkingAlchemistTexture;
    walkingAlchemistTexture.loadFromFile("sprites/alchemist-walk.png");
    walkingAlchemist.setTexture(walkingAlchemistTexture,ALCHEMIST_GAME_WIDTH);

    alchemist.setAnimation(walkingAlchemist);

    sf::Sprite hitAlchemist;
    sf::Texture hitAlchemistTexture;
    hitAlchemistTexture.loadFromFile("sprites/alchemist-hit.png");
    hitAlchemist.setTexture(hitAlchemistTexture);
    hitAlchemist.scale(2.f,2.f);

    alchemist.setHitSprite(hitAlchemist);

    alchemist.setKeys(sf::Keyboard::A, sf::Keyboard::D);
    alchemist.setSpeed(3);
    alchemist.setName(ALCHEMIST_NAME);

    // Prepare the boss
    Animation flyingBoss;
    flyingBoss.setDelay(15);
    flyingBoss.setNumPhotograms(3);

    sf::Texture flyingBossTexture;
    flyingBossTexture.loadFromFile("sprites/boss.png");

    flyingBoss.setTexture(flyingBossTexture,67);
    flyingBoss.setPosition(BOSS_X,-flyingBoss.getHitbox().height*2);

    boss.setAnimation(flyingBoss);

    sf::Sprite hitBoss;
    sf::Texture hitBossTexture;
    hitBossTexture.loadFromFile("sprites/boss-hit.png");
    hitBoss.setTexture(hitBossTexture);
    hitBoss.scale(2.f,2.f);

    boss.setHitSprite(hitBoss);

    // Prepare the background

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("sprites/background.png");
    background.setTexture(backgroundTexture);
    background.scale(2.f,2.f);

    // Prepare the animations for the falling stuff
    Animation fallingBookAnimation;
    sf::Texture fallingBookTexture;
    fallingBookTexture.loadFromFile("sprites/book.png");
    fallingBookAnimation.setTexture(fallingBookTexture,24);
    fallingBookAnimation.setDelay(1);
    fallingBookAnimation.setNumPhotograms(2);

    FallingItem fallingBook;
    fallingBook.setAnimation(fallingBookAnimation);
    fallingBook.setGravity(0.05);
    fallingBook.setType(BOOK_TYPE);

    Animation fallingMagicAnimation;
    sf::Texture fallingMagicTexture;
    fallingMagicTexture.loadFromFile("sprites/magic.png");
    fallingMagicAnimation.setTexture(fallingMagicTexture,24);
    fallingMagicAnimation.setDelay(10);
    fallingMagicAnimation.setNumPhotograms(2);

    FallingItem fallingMagic;
    fallingMagic.setAnimation(fallingMagicAnimation);
    fallingMagic.setGravity(0.05);
    fallingMagic.setType(MAGIC_TYPE);

    // Prepare the fonts to draw stuff
    sf::Font alchemistFont;
    alchemistFont.loadFromFile("fonts/gabriela.ttf");
    sf::Text alchemistText;
    alchemistText.setFont(alchemistFont);
    alchemistText.setFillColor(sf::Color::White);
    alchemistText.setCharacterSize(20);
    alchemistText.setString("Books needed: 1");

    sf::Font wizardFont;
    wizardFont.loadFromFile("fonts/daniela.ttf");
    sf::Text wizardText;
    wizardText.setFont(wizardFont);
    wizardText.setFillColor(sf::Color::Yellow);
    wizardText.setCharacterSize(20);
    wizardText.setString("Magic needed: 1");

    sf::Font clockFont;
    clockFont.loadFromFile("fonts/father.ttf");
    sf::Text clockText;
    clockText.setFont(clockFont);
    clockText.setFillColor(sf::Color::Blue);
    clockText.setCharacterSize(22);
    clockText.setPosition(20,20);
    clockText.setString("Time left: ");

    int difficulty = 40;

    sf::Clock clock;

    bool bossHere = false;

    while(true){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                mainWindow.close();
                exit(0);
            }
        }

        // Spawn books or magic or the boss
        if(rand()%difficulty==0){
            if(!bossHere){
                if(rand()%2){
                    sf::Vector2f position = fallingBook.getPosition();
                    position.y = -fallingBook.getHitbox().height;
                    position.x = rand()%(MAIN_WINDOW_HEIGHT-fallingBook.getHitbox().width);
                    fallingBook.setPosition(position);
                    fallingBook.setCurrentSpeed(sf::Vector2f(0,0));
                    fallingItems.insert(fallingItems.begin(),fallingBook);
                } else {
                    sf::Vector2f position = fallingMagic.getPosition();
                    position.y = -fallingMagic.getHitbox().height;
                    position.x = rand()%(MAIN_WINDOW_HEIGHT-fallingMagic.getHitbox().width);
                    fallingMagic.setPosition(position);
                    fallingMagic.setCurrentSpeed(sf::Vector2f(0,0));
                    fallingItems.insert(fallingItems.begin(),fallingMagic);
                }
            }
        }

        // Check if wizard got hit and lost magic
        int wizardLostItems = wizard.update(fallingItems);

        if(wizardLostItems > 0){
            for(int i=0;i<wizardLostItems;i++){
                fallingMagic.setPosition(wizard.getPosition());
                fallingMagic.setCurrentSpeed(sf::Vector2f((-10+rand()%30)/10.0,(-80+rand()%30)/10.0));
                fallingItems.insert(fallingItems.begin(),fallingMagic);
            }
        }

        // Check if alchemist got hit and lost books
        int alchemistLostItems = alchemist.update(fallingItems);

        if(alchemistLostItems > 0){
            for(int i=0;i<alchemistLostItems;i++){
                fallingBook.setPosition(alchemist.getPosition());
                fallingBook.setCurrentSpeed(sf::Vector2f((-10+rand()%30)/10.0,(-80+rand()%30)/10.0));
                fallingItems.insert(fallingItems.begin(),fallingBook);
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
            }
        } else if (bossHere){
            if(clock.getElapsedTime().asSeconds() >= BOSS_TIME){
                clock.restart();
                bossHere=false;
                boss.setActivated(false);
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

        mainWindow.draw(background);
        mainWindow.draw(clockText);
        mainWindow.draw(wizard);
        mainWindow.draw(alchemist);
        mainWindow.draw(boss);
        for(FallingItem fallingItem : fallingItems){
            mainWindow.draw(fallingItem);
        }

        mainWindow.display();
    }
}
