#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <SFML/Graphics.hpp>
#include <list>
#include "FallingItem.hpp"

class Character : public sf::Drawable {
    private:

        // Name of the character
        std::string name;

        // Animation for the character
        Animation animation;

        // Sprite for getting hit
        sf::Sprite hitSprite;

        // Counter for the invincibility frames after getting hit
        int invincibilityCounter;

        // Speed for the character
        double speed;

        // Keys for moving left and right
        sf::Keyboard::Key leftKey;
        sf::Keyboard::Key rightKey;

    public:
        Character();
        void setName(std::string name);
        void setAnimation(Animation animation);
        void setHitSprite(sf::Sprite hitSprite);
        void setSpeed(double speed);
        void setKeys(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey);
        void update(std::list<FallingItem> fallingItems);
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;
};

#endif // __CHARACTER_HPP__
