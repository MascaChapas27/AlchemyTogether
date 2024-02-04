#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <SFML/Graphics.hpp>
#include <list>
#include "FallingItem.hpp"

class Character : public sf::Drawable {
    private:

        // Name of the character
        std::string name;

        // Animation for the character when it walks
        Animation walkingAnimation;

        // Animation for the character when it shoots
        Animation shootingAnimation;

        // Indicates if the character is shooting or walking
        bool shooting;

        // Indicates the shooting angle
        int shootingAngle;

        // Indicates if the shooting angle is moving up or down
        bool shootingAngleGoingDown;

        // Cooldown until you can shoot again
        int shootingCooldown;

        // Sprite for getting hit
        sf::Sprite hitSprite;

        // Counter for the invincibility frames after getting hit
        int invincibilityCounter;

        // Speed for the character
        double speed;

        // Keys for moving left and right
        sf::Keyboard::Key leftKey;
        sf::Keyboard::Key rightKey;

        // Key for shooting
        sf::Keyboard::Key shootingKey;

        // Current and max amount of items the character has
        int currentItems;
        int maxItems;

        // Indicates if the character is dead
        bool dead;

    public:
        Character();
        void setName(std::string name);
        void setWalkingAnimation(Animation animation);
        void setShootingAnimation(Animation animation);
        void setHitSprite(sf::Sprite hitSprite);
        void setSpeed(double speed);
        void setKeys(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key shootingKey);
        void setCurrentItems(int currentItems);
        void setMaxItems(int maxItems);
        int getCurrentItems();
        int getMaxItems();
        void setShooting(bool shooting);
        sf::Vector2f getPosition();
        int update(std::list<FallingItem>& fallingItems);
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;
};

#endif // __CHARACTER_HPP__
