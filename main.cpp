#include <cstdlib>
#include "Utilities.hpp"
#include "ControlsWindow.hpp"
#include "Game.hpp"
#include "TitleScreen.hpp"
#include "ResourceHolder.hpp"
#include "MusicPlayer.hpp"

// Global variables in Utilities.hpp
sf::RenderWindow mainWindow;
sf::Texture hitWizardTexture;
sf::Texture hitAlchemistTexture;

int main(){

    // Load resources
    TextureHolder::getTextureInstance()->loadAllTextures();
    FontHolder::getFontInstance()->loadAllFonts();
    SoundHolder::getSoundInstance()->loadAllSounds();
    MusicPlayer::getInstance()->loadAllMusic();

    // Configure the main window
    mainWindow.create(sf::VideoMode(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT),MAIN_WINDOW_NAME,sf::Style::Close);
    mainWindow.setFramerateLimit(CUTSCENE_FPS);

    // Show title screen and initial cutscene
    TitleScreen titleScreen;
    int joystickID = titleScreen.run();
    mainWindow.setFramerateLimit(MAX_FPS);

    // Show initial window with controls and stuff
    ControlsWindow controlsWindow;
    std::pair<int,int> controllers = controlsWindow.run(joystickID);

    // Game
    Game game;
    game.run(controllers.first, controllers.second);

    // The end
    return EXIT_SUCCESS;
}
