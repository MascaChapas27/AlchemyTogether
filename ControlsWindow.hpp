#ifndef __CONTROLS_WINDOW_HPP__
#define __CONTROLS_WINDOW_HPP
#include <utility>

class ControlsWindow {
    public:
        // Runs the controls window
        std::pair<int,int> run(int joystickID);
};

#endif // __CONTROLS_WINDOW_HPP__
