#ifndef __FALLING_ITEM_HPP__
#define __FALLING_ITEM_HPP__

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include <list>
#include <SFML/Audio.hpp>

class FallingItem : public sf::Drawable {
    private:

        // Type of the falling item
        std::string type;

        // Animation for the falling item
        Animation animation;

        // Sprite for the lying item
        sf::Sprite lyingItem;

        // Tells if the falling item will lie on the floor after falling
        bool lying;

        // Tells if the falling item is currently lying on the floor what the fuck
        // these names are horrible i swear to god what am i doing here
        bool currentlyLying;

        // Gravity that pulls the item down
        double gravity;

        // Current speed of the item
        sf::Vector2f currentSpeed;

        // Rotation speed for the animation
        double rotationSpeed;

        // Trail for a super cool speed effect
        std::list<Animation> trail;

        // Counter to avoid trail effects from being too close
        int trailCounter;

        // Sound that plays when the item falls and lies on the floor
        sf::Sound lyingSound;

    public:
        FallingItem();

        static FallingItem fallingBook;
        static FallingItem fallingMagic;
        static FallingItem fallingFire;

        void setType(std::string type);
        void setAnimation(Animation animation);
        void setGravity(double gravity);
        sf::IntRect getHitbox() const;
        sf::Vector2f getPosition() const;
        void setPosition(sf::Vector2f position);
        void setPosition(double x, double y);
        void update();
        void setLyingItemTexture(sf::Texture& texture);
        void setCurrentSpeed(sf::Vector2f currentSpeed);
        void setLyingBuffer(sf::SoundBuffer& lyingBuffer);
        bool isOut();
        bool isCurrentlyLying() const;
        void reset();
        void setRotationSpeed(double rotationSpeed);
        std::string getType();
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;

};

#endif // __FALLING_ITEM_HPP__
