#include "ControlsWindow.hpp"
#include "Animation.hpp"
#include "Utilities.hpp"
#include "MusicPlayer.hpp"
#include "ResourceHolder.hpp"

std::pair<int,int> ControlsWindow::run(int joystickID){

    TextureHolder * textureHolder = TextureHolder::getTextureInstance();

    // Ok first we have to get the background
    sf::Sprite background;
    background.setTexture(textureHolder->get(TextureID::controls_background_keyboard_keyboard));
    background.scale(2.f,2.f);

    // Now the animations for both characters
    Animation wizardAnimation;
    wizardAnimation.setDelay(25);
    wizardAnimation.setPingPong(false);
    wizardAnimation.setTexture(textureHolder->get(TextureID::wizard_dance),4);
    wizardAnimation.setPosition(WIZARD_INITIAL_X,WIZARD_INITIAL_Y);

    Animation alchemistAnimation;
    alchemistAnimation.setDelay(15);
    alchemistAnimation.setPingPong(true);
    alchemistAnimation.setPosition(ALCHEMIST_INITIAL_X,ALCHEMIST_INITIAL_Y);
    alchemistAnimation.setTexture(textureHolder->get(TextureID::alchemist_dance),6);

    // Now let's make it work

    int wizardJoystick = -1;
    int alchemistJoystick = -1;

    while(true){

        sf::Event event;
        while(mainWindow.pollEvent(event) || joystickID != -1){
            if(event.type == sf::Event::Closed){
                exit(EXIT_SUCCESS);
            } else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) || (event.type == sf::Event::JoystickButtonPressed && ((int)event.joystickButton.joystickId == alchemistJoystick || (int)event.joystickButton.joystickId == wizardJoystick))){
                return std::pair<int,int>(alchemistJoystick,wizardJoystick);
            } else if (event.type == sf::Event::JoystickButtonPressed || joystickID != -1){
                int pressedJoystick = joystickID == -1 ? event.joystickButton.joystickId : joystickID;
                joystickID = -1;
                if(alchemistJoystick==-1 && wizardJoystick==-1){
                    bool moved = false;
                    bool alchemistSelected = true;
                    bool pressed = true;
                    sf::Sprite chooseControllerBackground;
                    chooseControllerBackground.setTexture(TextureHolder::getTextureInstance()->get(TextureID::joystick_choose_alchemist));
                    chooseControllerBackground.scale(2,2);

                    while(alchemistJoystick==-1 && wizardJoystick==-1){
                        while(mainWindow.pollEvent(event)){
                            if(event.type == sf::Event::Closed){
                                mainWindow.close();
                                exit(EXIT_SUCCESS);
                            }
                        }

                        if(!moved && (joystick_moving_left(pressedJoystick) || joystick_moving_right(pressedJoystick))){
                            if(alchemistSelected){
                                chooseControllerBackground.setTexture(TextureHolder::getTextureInstance()->get(TextureID::joystick_choose_wizard));
                                alchemistSelected = false;
                            } else {
                                chooseControllerBackground.setTexture(TextureHolder::getTextureInstance()->get(TextureID::joystick_choose_alchemist));
                                alchemistSelected = true;
                            }
                            moved = true;
                        } else if (moved && !(joystick_moving_left(pressedJoystick) || joystick_moving_right(pressedJoystick)))
                            moved = false;

                        if (!pressed && joystick_pressing_any_button(pressedJoystick)){
                            if(alchemistSelected)
                                alchemistJoystick = pressedJoystick;
                            else
                                wizardJoystick = pressedJoystick;
                        } else if(pressed && !joystick_pressing_any_button(pressedJoystick))
                            pressed = false;

                        mainWindow.clear();
                        mainWindow.draw(chooseControllerBackground);
                        mainWindow.display();
                    }
                } else if (alchemistJoystick != -1){
                    wizardJoystick = pressedJoystick;
                } else {
                    alchemistJoystick = pressedJoystick;
                }

                if(wizardJoystick != -1 && alchemistJoystick != -1)
                    background.setTexture(textureHolder->get(TextureID::controls_background_joystick_joystick));
                else if(wizardJoystick != -1)
                    background.setTexture(textureHolder->get(TextureID::controls_background_keyboard_joystick));
                else
                    background.setTexture(textureHolder->get(TextureID::controls_background_joystick_keyboard));
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
