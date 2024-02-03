#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

extern sf::RenderWindow mainWindow;

const int MAIN_WINDOW_WIDTH = 800;
const int MAIN_WINDOW_HEIGHT = 600;

const int WIZARD_DANCE_WIDTH = 30;
const int ALCHEMIST_DANCE_WIDTH = 32;

const int MAX_FPS = 100;
const std::string MAIN_WINDOW_NAME = "Alchemy Together";

const int INVINCIBILITY_FRAMES = 200;
const int INVINCINILITY_FLICKER = 2;
const int BOSS_INVINCIBILITY_FRAMES = 30;

const int WIZARD_INITIAL_X = 562;
const int WIZARD_INITIAL_Y = 496;
const int ALCHEMIST_INITIAL_X = 180;
const int ALCHEMIST_INITIAL_Y = 480;
const int BOSS_X = 600;
const int BOSS_INITIAL_Y = 100;
const int BOSS_FINAL_Y = 300;
const int BOSS_INITIAL_HEALTH = 100;

const double BOSS_SPEED = 0.05;
const double BOSS_MAX_SPEED = 2;

const int WIZARD_GAME_WIDTH = 30;
const int ALCHEMIST_GAME_WIDTH = 31;

const std::string WIZARD_NAME = "Daniela";
const std::string ALCHEMIST_NAME = "Gabriela";

const std::string BOOK_TYPE = "Book";
const std::string MAGIC_TYPE = "Magic";

const int GATHER_TIME = 10;
const int BOSS_TIME = 30;

#endif // __UTILITIES_HPP__
