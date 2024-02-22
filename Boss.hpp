#ifndef __BOSS_HPP__
#define __BOSS_HPP__

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include <list>
#include "FallingItem.hpp"
#include <SFML/Audio.hpp>
#include "Utilities.hpp"

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

        // Indicates if the boss should shoot
        bool activated;

        // Sounds
        sf::Sound appearingSound;
        sf::Sound disappearingSound;
        sf::Sound damageSound;
        sf::Sound shootSound;

        // Type of attack currently happening
        AttackType attack;

        // Helper variable to know where to shoot depending on the attack
        int attackAux;

        // Sprite for the sign that contains the health bar
        sf::Sprite healthSprite;

    private:
        void attackCircles(std::list<FallingItem>& fallingItems);
        void attackUniformRain(std::list<FallingItem>& fallingItems);
        void attackRainWithHoles(std::list<FallingItem>& fallingItems);
        void attackRainLeftToRight(std::list<FallingItem>& fallingItems);
        void attackRandomRain(std::list<FallingItem>& fallingItems);

    public:
        Boss();
        void setAnimation(Animation animation);
        void setHitSprite(sf::Sprite hitSprite);
        int getCurrentHealth();
        sf::Vector2f getPosition();
        void setActivated(bool activated);
        void setHealthTexture(sf::Texture& healthTexture);
        void setSoundBuffers(sf::SoundBuffer& appearing, sf::SoundBuffer& disappearing,
                             sf::SoundBuffer& damage, sf::SoundBuffer& shoot);
        void update(std::list<FallingItem>& fallingItems);
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;
};

#endif // __BOSS_HPP__
