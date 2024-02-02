#include <cstdlib>
#include "Utilities.hpp"
#include "ControlsWindow.hpp"
#include "Game.hpp"

// Global variable in Utilities.hpp
sf::RenderWindow mainWindow;

int main(){

    // Configure the main window
    mainWindow.create(sf::VideoMode(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT),MAIN_WINDOW_NAME);
    mainWindow.setFramerateLimit(MAX_FPS);

    // Show initial window with controls and stuff
    ControlsWindow controlsWindow;
    controlsWindow.run();

    // Game
    Game game;
    game.run();

    // The end
    return EXIT_SUCCESS;
}
