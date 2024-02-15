#include "Utilities.hpp"

bool is_any_button_pressed(int joystick){
    int numButtons = sf::Joystick::getButtonCount(joystick);

    for(int i=0;i<numButtons;i++){
        if(sf::Joystick::isButtonPressed(joystick,i)) return true;
    }

    return false;
}
