#ifndef __FALLING_ITEM_HPP__
#define __FALLING_ITEM_HPP__

#include <SFML/Graphics.hpp>
#include "Animation.hpp"

class FallingItem : public sf::Drawable {
    private:

        // Type of the falling item
        std::string type;

        // Animation for the falling item
        Animation animation;

        // Gravity that pulls the item down
        double gravity;

        // Current speed of the item
        double currentSpeed;

    public:
        FallingItem();

        void setType(std::string type);
        void setAnimation(Animation animation);
        void setGravity(double gravity);
        sf::IntRect getHitbox();
        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f position);
        void update();
        bool isOut();
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;

};

#endif // __FALLING_ITEM_HPP__
