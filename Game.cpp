#include "Game.hpp"
#include "Utilities.hpp"

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
    alchemist.setSpeed(2);
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

    int difficulty = 100;

    while(true){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                mainWindow.close();
                exit(0);
            }
        }

        if(rand()%difficulty==0){
            sf::Vector2f position = fallingBook.getPosition();
            position.y = -fallingBook.getHitbox().height;
            position.x = rand()%(MAIN_WINDOW_HEIGHT-fallingBook.getHitbox().width);
            fallingBook.setPosition(position);
            fallingItems.insert(fallingItems.begin(),fallingBook);
        }

        wizard.update(fallingItems);
        alchemist.update(fallingItems);

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
        mainWindow.draw(wizard);
        mainWindow.draw(alchemist);
        for(FallingItem fallingItem : fallingItems){
            mainWindow.draw(fallingItem);
        }

        mainWindow.display();
    }
}
