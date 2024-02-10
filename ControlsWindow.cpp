#include "ControlsWindow.hpp"
#include "Animation.hpp"
#include "Utilities.hpp"
#include "MusicPlayer.hpp"

void ControlsWindow::run(){

    // Ok first we have to get the background
    sf::Sprite background;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("sprites/controls-background.png");
    background.setTexture(backgroundTexture);
    background.scale(2.f,2.f);

    // Now the animations for both characters
    Animation wizardAnimation;
    wizardAnimation.setDelay(25);
    wizardAnimation.setPingPong(false);

    sf::Texture wizardTexture;
    wizardTexture.loadFromFile("sprites/wizard-dance.png");
    wizardAnimation.setTexture(wizardTexture,4);
    wizardAnimation.setPosition(WIZARD_INITIAL_X,WIZARD_INITIAL_Y);

    Animation alchemistAnimation;
    alchemistAnimation.setPingPong(true);
    alchemistAnimation.setDelay(15);
    alchemistAnimation.setPingPong(true);
    alchemistAnimation.setPosition(ALCHEMIST_INITIAL_X,ALCHEMIST_INITIAL_Y);

    sf::Texture alchemistTexture;
    alchemistTexture.loadFromFile("sprites/alchemist-dance.png");
    alchemistAnimation.setTexture(alchemistTexture,6);

    // Now let's make it work

    while(true){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == event.Closed){
                exit(EXIT_SUCCESS);
            } else if (event.type == event.KeyPressed){
                return;
            }
        }

        wizardAnimation.update();
        alchemistAnimation.update();

        mainWindow.clear();

        mainWindow.draw(background);
        mainWindow.draw(wizardAnimation);
        mainWindow.draw(alchemistAnimation);

        mainWindow.display();
    }
}
