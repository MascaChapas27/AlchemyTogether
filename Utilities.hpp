#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

enum class TextureID{

    title,press_enter,press_escape,
    cutscene0_boss,cutscene0_wizard,cutscene0_alchemist,cutscene0_background,
    cutscene1_background,cutscene1_alchemist,cutscene1_wizard,
    cutscene2_alchemist,cutscene2_wizard,cutscene2_background,

    alchemist_dance,wizard_dance,joystick_choose_alchemist,joystick_choose_wizard,
    controls_background_keyboard_keyboard, controls_background_keyboard_joystick, controls_background_joystick_keyboard, controls_background_joystick_joystick,

    alchemist_hit,alchemist_shoot,alchemist_walk,alchemist_hold,alchemist_side,
    wizard_hit,wizard_shoot,wizard_side,wizard_hold,wizard_walk,
    background,book,magic,fire,boss,boss_hit,
    time_frame,alchemist_arrow,wizard_arrow,alchemist_corpse,wizard_corpse,
    wizard_plus1,alchemist_plus1,boss_minus1,boss_corpse,
};

enum class SoundID {
    boss_voice, alchemist_voice, wizard_voice, advance_conversation,
    alchemist_damage,alchemist_collect,alchemist_shoot,
    wizard_damage,wizard_collect,wizard_shoot,
    boss_damage,boss_shoot,boss_appear,boss_disappear
};

enum class FontID {
    AlchemistFont, WizardFont
};

enum class MusicID {
    intro_music, battle_music, death_music
};

enum class AttackType {
    UNIFORM_RAIN, RAIN_WITH_HOLES, CIRCLES, RAIN_LEFT_TO_RIGHT, RANDOM_RAIN
};
const int NUM_BOSS_ATTACKS = 5;
const int NUM_FIRE_CIRCLES = 6;
const int RAIN_LEFT_TO_RIGHT_LATENCY = 20;
const int NUM_FIRE_RAIN_WITH_HOLES = 15;
const int RANDOM_RAIN_FIRE_PER_SECOND = 13;
const int NUM_FIRE_UNIFORM_RAIN = 7;

extern sf::RenderWindow mainWindow;

const float JOYSTICK_THRESHOLD = 0.3;

const bool DEBUG = false;

const int MAIN_WINDOW_WIDTH = 800;
const int MAIN_WINDOW_HEIGHT = 600;

const int CHARACTER_SIZE = 22;

const sf::Vector2f TITLE_POSITION(118,40);

const sf::Vector2f CUTSCENE0_BOSS_POSITION(240,104);
const sf::Vector2f CUTSCENE0_WIZARD_POSITION(0,MAIN_WINDOW_HEIGHT-123*2);
const sf::Vector2f CUTSCENE0_ALCHEMIST_POSITION(MAIN_WINDOW_WIDTH-166*2,MAIN_WINDOW_HEIGHT-138*2);

const sf::Vector2f CUTSCENE1_WIZARD_POSITION(231*2,118*2);
const sf::Vector2f CUTSCENE1_ALCHEMIST_POSITION(79*2,105*2);
const sf::Vector2f CUTSCENE1_BACKGROUND_POSITION(100,100);

const sf::Vector2f CUTSCENE2_ALCHEMIST_POSITION(140,222);
const int CUTSCENE2_WAIT = 50;

const int WINDOW_SHAKE_FREQUENCY = 1;

const int TEXT_WAIT = 20;

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

const int ATTACK = 1;

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
const std::string CORPSE_TYPE = "Corpse";
const std::string PLUS1_TYPE = "Plus1";
const std::string MINUS1_TYPE = "Minus1";

const int INITIAL_SHOOTING_ANGLE = 0;
const int FINAL_SHOOTING_ANGLE = 90;
const int MAX_SHOOTING_COOLDOWN = 30;

const int GATHER_TIME = 10;
const int BOSS_TIME = 15;

const double PI = 3.14159265;

const int ALCHEMIST_STRENGTH = 7;
const int WIZARD_STRENGTH = 7;

const int FALLING_TRAIL_MAX_LENGTH = 2;
const int FALLING_TRAIL_MAX_COUNTER = 5;

const double GRAVITY = 0.05;

bool is_any_button_pressed(int joystick);

#endif // __UTILITIES_HPP__
