#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <list>
#include "Character.hpp"
#include "FallingItem.hpp"
#include <SFML/Graphics.hpp>

class Game {
    private:
        // Characters
        Character alchemist;
        Character wizard;

        // List of falling items
        std::list<FallingItem> fallingItems;

        // Background
        sf::Sprite background;

    public:
        void run();

};

#endif // __GAME_HPP__
