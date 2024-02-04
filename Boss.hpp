#ifndef __BOSS_HPP__
#define __BOSS_HPP__

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include <list>
#include "FallingItem.hpp"

class Boss : public sf::Drawable {
    private:
        // Animation for the boss
        Animation animation;

        // Sprite for getting hit
        sf::Sprite hitSprite;

        // Counter for the invincibility frames after getting hit
        int invincibilityCounter;

        // Initial and final positions on the Y axis
        double initialY;
        double finalY;

        // Initial and final positions on the X axis
        double initialX;
        double finalX;

        // Current speed for the boss
        double currentSpeedY;
        double currentSpeedX;

        // Tells if the boss is going up or down, and left of right
        bool goingDown;
        bool goingRight;

        // Health for the boss
        int health;

    public:
        Boss();
        void setAnimation(Animation animation);
        void setHitSprite(sf::Sprite hitSprite);
        int getCurrentHealth();
        sf::Vector2f getPosition();
        void setActivated(bool activated);
        void update(std::list<FallingItem>& fallingItems);
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;
};

#endif // __BOSS_HPP__
