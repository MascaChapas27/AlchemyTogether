#include "ControlsWindow.hpp"
#include "Animation.hpp"
#include "Utilities.hpp"

void ControlsWindow::run(){
    // Ok first we have to get the background
    sf::Sprite background;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("sprites/controls-background.png");
    background.setTexture(backgroundTexture);
    background.scale(2.f,2.f);

    // Now the animations for both characters
    Animation wizardAnimation;
    wizardAnimation.setNumPhotograms(4);
    wizardAnimation.setDelay(25);
    wizardAnimation.setPingPong(false);

    sf::Texture wizardTexture;
    wizardTexture.loadFromFile("sprites/wizard-dance.png");
    wizardAnimation.setTexture(wizardTexture,WIZARD_DANCE_WIDTH);
    wizardAnimation.setPosition(562,496);

    Animation alchemistAnimation;
    alchemistAnimation.setNumPhotograms(6);
    alchemistAnimation.setPingPong(true);
    alchemistAnimation.setDelay(15);
    alchemistAnimation.setPingPong(true);
    alchemistAnimation.setPosition(180,480);

    sf::Texture alchemistTexture;
    alchemistTexture.loadFromFile("sprites/alchemist-dance.png");
    alchemistAnimation.setTexture(alchemistTexture,ALCHEMIST_DANCE_WIDTH);

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
