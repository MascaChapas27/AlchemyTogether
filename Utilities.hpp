#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

enum class TextureID{
    alchemist_dance,alchemist_hit,alchemist_side,alchemist_walk,
    background,book,magic,fire,boss,boss_hit,controls_background,
    cutscene0_boss,cutscene0_wizard,cutscene0_alchemist,cutscene0_background,
    cutscene1_background,cutscene1_alchemist,cutscene1_wizard,
    wizard_dance,wizard_hit,wizard_shoot,wizard_walk
};

enum class SoundID {
    boss_voice, alchemist_voice
};

enum class FontID {
    AlchemistFont, WizardFont, BossFont
};

extern sf::RenderWindow mainWindow;
extern sf::RenderWindow auxWindow;
extern sf::Texture hitWizardTexture;
extern sf::Texture hitAlchemistTexture;

const bool DEBUG = true;

const int MAIN_WINDOW_WIDTH = 800;
const int MAIN_WINDOW_HEIGHT = 600;

const sf::Vector2f CUTSCENE0_BOSS_POSITION(240,104);
const sf::Vector2f CUTSCENE0_WIZARD_POSITION(0,MAIN_WINDOW_HEIGHT-123*2);
const sf::Vector2f CUTSCENE0_ALCHEMIST_POSITION(MAIN_WINDOW_WIDTH-166*2,MAIN_WINDOW_HEIGHT-138*2);

const int SPEAKING_LATENCY = 5;

const int AUX_WINDOW_WIDTH = 109*2;
const int AUX_WINDOW_HEIGHT = 104*2;

const int WIZARD_DANCE_WIDTH = 30;
const int ALCHEMIST_DANCE_WIDTH = 32;

const int CUTSCENE_FPS = 30;
const int MAX_FPS = 100;
const std::string MAIN_WINDOW_NAME = "Alchemy Together";
const std::string AUX_WINDOW_NAME = "Help";

const int INVINCIBILITY_FRAMES = 200;
const int INVINCINILITY_FLICKER = 2;
const int BOSS_INVINCIBILITY_FRAMES = 30;

const int WIZARD_INITIAL_X = 590;
const int WIZARD_INITIAL_Y = 548;
const int ALCHEMIST_INITIAL_X = 210;
const int ALCHEMIST_INITIAL_Y = 540;
const int BOSS_X = 650;
const int BOSS_INITIAL_Y = 150;
const int BOSS_FINAL_Y = 350;
const int BOSS_INITIAL_HEALTH = 50;

const double BOSS_SPEED = 0.05;
const double BOSS_MAX_SPEED = 2;

const int WIZARD_GAME_WIDTH = 30;
const int ALCHEMIST_GAME_WIDTH = 31;

const std::string WIZARD_NAME = "Daniela";
const std::string ALCHEMIST_NAME = "Gabriela";

const std::string BOOK_TYPE = "Book";
const std::string MAGIC_TYPE = "Magic";
const std::string FIRE_TYPE = "Fire";

const int INITIAL_SHOOTING_ANGLE = 0;
const int FINAL_SHOOTING_ANGLE = 90;
const int MAX_SHOOTING_COOLDOWN = 30;

const int GATHER_TIME = 10;
const int BOSS_TIME = 15;

const double PI = 3.14159265;

const int ALCHEMIST_STRENGTH = 7;
const int WIZARD_STRENGTH = 5;

const int FALLING_TRAIL_MAX_LENGTH = 2;
const int FALLING_TRAIL_MAX_COUNTER = 5;

const double GRAVITY = 0.05;

#endif // __UTILITIES_HPP__
