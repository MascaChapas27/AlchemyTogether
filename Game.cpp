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
    wizard.setSpeed(2.5);

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

    // Prepare the background

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("sprites/background.png");
    background.setTexture(backgroundTexture);
    background.scale(2.f,2.f);

    while(true){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                mainWindow.close();
                exit(0);
            }
        }

        wizard.update(fallingItems);
        alchemist.update(fallingItems);

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
