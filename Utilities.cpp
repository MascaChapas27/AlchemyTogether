#include "Utilities.hpp"
#include <iostream>

bool is_any_button_pressed(int joystick){
    int numButtons = sf::Joystick::getButtonCount(joystick);

    for(int i=0;i<numButtons;i++){
        if(sf::Joystick::isButtonPressed(joystick,i)) return true;
    }

    return false;
}

bool joystick_moving_left(int joystick){
    if(sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::PovX) < -JOYSTICK_THRESHOLD) return true;
    if(sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::X) < -JOYSTICK_THRESHOLD) return true;
    if(sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::U) < -JOYSTICK_THRESHOLD) return true;
    return false;
}

bool joystick_moving_right(int joystick){
    if(sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::PovX) > JOYSTICK_THRESHOLD) return true;
    if(sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::X) > JOYSTICK_THRESHOLD) return true;
    if(sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::U) > JOYSTICK_THRESHOLD) return true;
    return false;
}

void buttons_debug(int joystick){
    while(true){

        sf::Event event;
        while(mainWindow.pollEvent(event));

        std::cout << "X: " << sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::X) << std::endl;
        std::cout << "Y: " << sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::Y) << std::endl;
        std::cout << "Z: " << sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::Z) << std::endl;
        std::cout << "R: " << sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::R) << std::endl;
        std::cout << "U: " << sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::U) << std::endl;
        std::cout << "V: " << sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::V) << std::endl;
        std::cout << "PovX: " << sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::PovX) << std::endl;
        std::cout << "PovY: " << sf::Joystick::getAxisPosition(joystick,sf::Joystick::Axis::PovY) << std::endl;

        sf::sleep(sf::seconds(0.5));
    }
}
