#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <list>
#include "Character.hpp"
#include "FallingItem.hpp"
#include <SFML/Graphics.hpp>
#include "Boss.hpp"

class Game {
    private:
        // Characters
        Character alchemist;
        Character wizard;

        // Boss
        Boss boss;

        // List of falling items
        std::list<FallingItem> fallingItems;

        // Background
        sf::Sprite background;

    public:
        void run(int alchemistController, int wizardController);

};

#endif // __GAME_HPP__
