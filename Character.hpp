#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <SFML/Graphics.hpp>
#include <list>
#include "FallingItem.hpp"
#include <SFML/Audio.hpp>

class Character : public sf::Drawable {
    private:

        // Name of the character
        std::string name;

        // Animation for the character when it walks
        Animation walkingAnimation;

        // Animation for the character when it shoots
        Animation shootingAnimation;

        // Animation for the character when it holds an item
        Animation holdingAnimation;

        // Animation for the character when it looks to the side
        Animation sideAnimation;

        // Indicates if the character is shooting or walking
        bool shooting;

        // Indicates the shooting angle
        int shootingAngle;

        // Sprite for the arrow that indicates the shooting angle
        sf::Sprite shootingArrow;

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

        // Sound that plays when you get hit
        sf::Sound damageSound;

        // Sound that plays when you collect an item
        sf::Sound collectSound;

        // Sound that plays when you shoot
        sf::Sound shootSound;

        // Current position for the character
        sf::Vector2f position;

        // Controller the character will use (-1 means none)
        int controller;


    public:
        Character();
        void setName(std::string name);
        void setWalkingAnimation(Animation animation);
        void setShootingAnimation(Animation animation);
        void setHoldingAnimation(Animation animation);
        void setSideAnimation(Animation animation);
        void setHitSprite(sf::Sprite hitSprite);
        void setSpeed(double speed);
        void setKeys(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key shootingKey);
        void setShootingArrowTexture(sf::Texture& texture);
        void setCurrentItems(int currentItems);
        void setMaxItems(int maxItems);
        void setSoundBuffers(sf::SoundBuffer& damageSoundBuffer, sf::SoundBuffer& collectSoundBuffer, sf::SoundBuffer& shootSoundBuffer);
        int getCurrentItems();
        bool isDead();
        int getMaxItems();
        int getController();
        void setController(int controllerID);
        void setShooting(bool shooting);
        sf::Vector2f getPosition();
        int update(std::list<FallingItem>& fallingItems);
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;
};

#endif // __CHARACTER_HPP__
