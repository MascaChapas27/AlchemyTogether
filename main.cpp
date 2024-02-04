#include <cstdlib>
#include "Utilities.hpp"
#include "ControlsWindow.hpp"
#include "Game.hpp"

// Global variables in Utilities.hpp
sf::RenderWindow mainWindow;
sf::RenderWindow auxWindow;

int main(){

    // Configure the main window
    mainWindow.create(sf::VideoMode(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT),MAIN_WINDOW_NAME);
    mainWindow.setFramerateLimit(MAX_FPS);

    // Show initial window with controls and stuff
    ControlsWindow controlsWindow;
    controlsWindow.run();

    // Configure the aux window
    auxWindow.create(sf::VideoMode(AUX_WINDOW_WIDTH,AUX_WINDOW_HEIGHT),AUX_WINDOW_NAME);
    auxWindow.setFramerateLimit(MAX_FPS);
    auxWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x-AUX_WINDOW_WIDTH-20,mainWindow.getPosition().y));

    // Game
    Game game;
    game.run();

    // The end
    return EXIT_SUCCESS;
}
