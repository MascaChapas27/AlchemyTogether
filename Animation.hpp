#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

#include <SFML/Graphics.hpp>

class Animation : public sf::Drawable{
    private:
        // Number of photograms
        int numPhotograms;

        // Current photogram
        int currentPhotogram;

        // Sprite for the animation
        sf::Sprite sprite;

        // If set to true, after reaching the end it will
        // go back and then forward (1-2-3-4-3-2-1)
        // If set to false, will immediately start
        // from the beginning (1-2-3-4-1-2-3-4)
        bool pingPong;

        // If set to true, we are advancing the photograms in reverse order
        // (only makes sense with pingPong set to true)
        bool goingDown;

        // How many frames will it take to move the animation from one
        // rectangle to another
        int delay;

        // The delay attribute acts as a limit for the delay so this attribute
        // tries to get to that value and when it arrives then the update happens
        // and the current delay is reset
        int currentDelay;

    public:
        Animation();
        void setTexture(sf::Texture& texture, int numPhotograms, bool centerOrigin=true);
        void setPingPong(bool pingPong);
        void setPosition(double x, double y);
        void setPosition(sf::Vector2f position);
        void setDelay(int delay);
        sf::Vector2f getPosition() const;
        sf::IntRect getHitbox() const;
        void resetToStart();
        void addTransparency();
        sf::Color getColor();
        void setColor(sf::Color color);
        void addRotation(double rotation);
        double getWidth();
        void update();
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;
};

#endif // __ANIMATION_HPP__
