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
    alchemistText.setPosition(20,20);
    alchemistText.setString("Books needed: 1");

    sf::Font wizardFont;
    wizardFont.loadFromFile("fonts/daniela.ttf");
    sf::Text wizardText;
    wizardText.setFont(wizardFont);
    wizardText.setFillColor(sf::Color::Yellow);
    wizardText.setCharacterSize(20);
    wizardText.setPosition(20,60);
    wizardText.setString("Magic needed: 1");

    sf::Font goldFont;
    goldFont.loadFromFile("fonts/father.ttf");
    sf::Text goldText;
    goldText.setFont(goldFont);
    goldText.setFillColor(sf::Color(255,255,200));
    goldText.setCharacterSize(22);
    goldText.setPosition(20,100);
    goldText.setString("Gold made: 0");

    int difficulty = 120;

    int goldMade = 0;

    while(true){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                mainWindow.close();
                exit(0);
            }
        }

        if(rand()%difficulty==0){
            if(rand()%2){
                sf::Vector2f position = fallingBook.getPosition();
                position.y = -fallingBook.getHitbox().height;
                position.x = rand()%(MAIN_WINDOW_HEIGHT-fallingBook.getHitbox().width);
                fallingBook.setPosition(position);
                fallingBook.setCurrentSpeed(sf::Vector2f(0,0));
                fallingBook.setGravity(10.0/difficulty);
                fallingItems.insert(fallingItems.begin(),fallingBook);
            } else {
                sf::Vector2f position = fallingMagic.getPosition();
                position.y = -fallingMagic.getHitbox().height;
                position.x = rand()%(MAIN_WINDOW_HEIGHT-fallingMagic.getHitbox().width);
                fallingMagic.setPosition(position);
                fallingMagic.setCurrentSpeed(sf::Vector2f(0,0));
                fallingMagic.setGravity(10.0/difficulty);
                fallingItems.insert(fallingItems.begin(),fallingMagic);
            }
        }

        // Check if wizard got hit and lost magic
        int wizardLostItems = wizard.update(fallingItems);

        if(wizardLostItems > 0){
            for(int i=0;i<wizardLostItems;i++){
                fallingMagic.setPosition(wizard.getPosition());
                fallingMagic.setCurrentSpeed(sf::Vector2f(-1+rand()%3,-8+rand()%3));
                fallingMagic.setGravity(10.0/difficulty);
                fallingItems.insert(fallingItems.begin(),fallingMagic);
            }
        }

        // Check if alchemist got hit and lost books
        int alchemistLostItems = alchemist.update(fallingItems);

        if(alchemistLostItems > 0){
            for(int i=0;i<alchemistLostItems;i++){
                fallingBook.setPosition(alchemist.getPosition());
                fallingBook.setCurrentSpeed(sf::Vector2f(-1+rand()%3,-8+rand()%3));
                fallingBook.setGravity(10.0/difficulty);
                fallingItems.insert(fallingItems.begin(),fallingBook);
            }
        }

        // Check if the characters have enough items
        if(wizard.getCurrentItems() == goldMade+1 && alchemist.getCurrentItems() == goldMade+1){
            goldMade++;
            wizard.setCurrentItems(0);
            wizard.setMaxItems(goldMade+1);
            alchemist.setCurrentItems(0);
            alchemist.setMaxItems(goldMade+1);
            difficulty-=5;
        }

        // Update the texts
        char wizardString[20];
        sprintf(wizardString,"Magic needed: %d",(wizard.getMaxItems()-wizard.getCurrentItems()));
        wizardText.setString(wizardString);

        char alchemistString[20];
        sprintf(alchemistString,"Books needed: %d",(alchemist.getMaxItems()-alchemist.getCurrentItems()));
        alchemistText.setString(alchemistString);


        char goldString[20];
        sprintf(goldString,"Gold made: %d",goldMade);
        goldText.setString(goldString);

        auto iter = fallingItems.begin();
        while(iter != fallingItems.end()){
            if(iter->isOut()) iter=fallingItems.erase(iter);
            else {
                iter->update();
                iter++;
            }
        }

        mainWindow.clear();

        mainWindow.draw(background);
        mainWindow.draw(alchemistText);
        mainWindow.draw(wizardText);
        mainWindow.draw(goldText);
        mainWindow.draw(wizard);
        mainWindow.draw(alchemist);
        for(FallingItem fallingItem : fallingItems){
            mainWindow.draw(fallingItem);
        }

        mainWindow.display();
    }
}
