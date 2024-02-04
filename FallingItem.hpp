#ifndef __FALLING_ITEM_HPP__
#define __FALLING_ITEM_HPP__

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include <list>

class FallingItem : public sf::Drawable {
    private:

        // Type of the falling item
        std::string type;

        // Animation for the falling item
        Animation animation;

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

    public:
        FallingItem();

        static FallingItem fallingBook;
        static FallingItem fallingMagic;
        static FallingItem fallingFire;

        void setType(std::string type);
        void setAnimation(Animation animation);
        void setGravity(double gravity);
        sf::IntRect getHitbox();
        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f position);
        void setPosition(double x, double y);
        void update();
        void setCurrentSpeed(sf::Vector2f currentSpeed);
        bool isOut();
        void setRotationSpeed(double rotationSpeed);
        std::string getType();
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;

};

#endif // __FALLING_ITEM_HPP__
