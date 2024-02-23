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

        // Super cool movement for the window i could have done in a different class
        // but fuck it i dont want to dedicate a lot of time to this silly thingy
        int windowMovement;
        bool windowGoingDown;

    public:
        Game();
        void run(int alchemistController, int wizardController);

};

#endif // __GAME_HPP__
