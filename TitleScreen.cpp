#include "TitleScreen.hpp"
#include "Animation.hpp"
#include "ResourceHolder.hpp"

void TitleScreen::run(){

    // Rectangles that enclose the cutscenes
    sf::RectangleShape rectangleUp(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT/6));
    rectangleUp.setFillColor(sf::Color::Black);
    sf::Vector2f finalUpPosition(0,0);
    rectangleUp.setPosition(0,-rectangleUp.getSize().y);

    sf::RectangleShape rectangleLeft(sf::Vector2f(MAIN_WINDOW_WIDTH/4,MAIN_WINDOW_HEIGHT));
    rectangleLeft.setFillColor(sf::Color::Black);
    sf::Vector2f finalLeftPosition(0,0);
    rectangleLeft.setPosition(-rectangleLeft.getSize().x,0);

    sf::RectangleShape rectangleRight(sf::Vector2f(MAIN_WINDOW_WIDTH/4,MAIN_WINDOW_HEIGHT));
    rectangleRight.setFillColor(sf::Color::Black);
    sf::Vector2f finalRightPosition(6*MAIN_WINDOW_WIDTH/8,0);
    rectangleRight.setPosition(MAIN_WINDOW_WIDTH+rectangleRight.getSize().x,0);

    sf::RectangleShape rectangleDown(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT/3));
    rectangleDown.setFillColor(sf::Color::Black);
    sf::Vector2f finalDownPosition(0,4*MAIN_WINDOW_HEIGHT/6);
    rectangleDown.setPosition(0,MAIN_WINDOW_HEIGHT+rectangleDown.getSize().y);

    // Rectangle that covers everything
    sf::RectangleShape rectangleCover(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));
    rectangleCover.setFillColor(sf::Color::Black);

    // Animations for cutscene 0
    Animation cutscene0_wizard;
    cutscene0_wizard.setDelay(30);
    cutscene0_wizard.setNumPhotograms(2);
    cutscene0_wizard.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene0_wizard));
    cutscene0_wizard.setPosition(0,400);

    Animation cutscene0_boss;
    cutscene0_boss.setDelay(50);
    cutscene0_boss.setNumPhotograms(2);
    cutscene0_boss.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene0_boss));
    cutscene0_boss.setPosition(200,200);

    // Show the title and wait for input

    bool nextCutscene = false;

    while(!nextCutscene){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::KeyPressed) nextCutscene = true;
        }

        cutscene0_wizard.update();
        cutscene0_boss.update();

        mainWindow.clear();

        mainWindow.draw(cutscene0_boss);
        mainWindow.draw(cutscene0_wizard);

        mainWindow.display();
    }
}
