#include "TitleScreen.hpp"
#include "Animation.hpp"
#include "ResourceHolder.hpp"

void TitleScreen::run(){

    // Rectangles that enclose the cutscenes
    sf::RectangleShape rectangleUp(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT/6));
    rectangleUp.setFillColor(sf::Color::Black);
    sf::Vector2f finalUpPosition(0,0);
    rectangleUp.setPosition(0,-rectangleUp.getSize().y);

    sf::RectangleShape rectangleLeft(sf::Vector2f(MAIN_WINDOW_WIDTH/8,MAIN_WINDOW_HEIGHT));
    rectangleLeft.setFillColor(sf::Color::Black);
    sf::Vector2f finalLeftPosition(0,0);
    rectangleLeft.setPosition(-rectangleLeft.getSize().x,0);

    sf::RectangleShape rectangleRight(sf::Vector2f(MAIN_WINDOW_WIDTH/8,MAIN_WINDOW_HEIGHT));
    rectangleRight.setFillColor(sf::Color::Black);
    sf::Vector2f finalRightPosition(7*MAIN_WINDOW_WIDTH/8,0);
    rectangleRight.setPosition(MAIN_WINDOW_WIDTH,0);

    sf::RectangleShape rectangleDown(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT/6));
    rectangleDown.setFillColor(sf::Color::Black);
    sf::Vector2f finalDownPosition(0,5*MAIN_WINDOW_HEIGHT/6);
    rectangleDown.setPosition(0,MAIN_WINDOW_HEIGHT);

    // Rectangle that covers everything
    sf::RectangleShape rectangleCover(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));
    rectangleCover.setFillColor(sf::Color::Black);

    // Animations for cutscene 0
    Animation cutscene0_wizard;
    cutscene0_wizard.setDelay(10);
    cutscene0_wizard.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene0_wizard),2,false);
    cutscene0_wizard.setPosition(CUTSCENE0_WIZARD_POSITION);

    Animation cutscene0_alchemist;
    cutscene0_alchemist.setDelay(12);
    cutscene0_alchemist.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene0_alchemist),2,false);
    cutscene0_alchemist.setPosition(CUTSCENE0_ALCHEMIST_POSITION);

    Animation cutscene0_boss;
    cutscene0_boss.setDelay(15);
    cutscene0_boss.setPingPong(true);
    cutscene0_boss.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene0_boss),3,false);
    cutscene0_boss.setPosition(CUTSCENE0_BOSS_POSITION);

    sf::Sprite cutscene0_background;
    cutscene0_background.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene0_background));
    cutscene0_background.setScale(2,2);

    // Final message for the current character
    std::string finalText;

    // Text and sfx of the current speaking character
    sf::Sound talkingSound;
    sf::Text talkingText;
    talkingText.setPosition(MAIN_WINDOW_WIDTH/8,5*MAIN_WINDOW_HEIGHT/6);

    // Indicates the current letter for the speaking character
    unsigned int currentLetter = 0;

    bool nextCutscene = false;

    // Show the title and wait for input

    while(!nextCutscene){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::KeyPressed) nextCutscene = true;
        }

        cutscene0_wizard.update();
        cutscene0_boss.update();
        cutscene0_alchemist.update();

        mainWindow.clear();

        mainWindow.draw(cutscene0_background);
        mainWindow.draw(cutscene0_boss);
        mainWindow.draw(cutscene0_wizard);
        mainWindow.draw(cutscene0_alchemist);

        mainWindow.display();
    }

    nextCutscene = false;

    // Make the rectangles closer
    while(!nextCutscene){

        int correctRectangles = 0;

        if(rectangleUp.getPosition().y != finalUpPosition.y){
            rectangleUp.move(0,5);
        } else {
            correctRectangles++;
        }

        if(rectangleLeft.getPosition().x != finalLeftPosition.x){
            rectangleLeft.move(5,0);
        } else {
            correctRectangles++;
        }

        if(rectangleRight.getPosition().x != finalRightPosition.x){
            rectangleRight.move(-5,0);
        } else {
            correctRectangles++;
        }

        if(rectangleDown.getPosition().y != finalDownPosition.y){
            rectangleDown.move(0,-5);
        } else {
            correctRectangles++;
        }

        // Code repetition ehehe
        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::KeyPressed) nextCutscene = true;
        }

        cutscene0_wizard.update();
        cutscene0_boss.update();
        cutscene0_alchemist.update();

        mainWindow.clear();

        mainWindow.draw(cutscene0_background);
        mainWindow.draw(cutscene0_boss);
        mainWindow.draw(cutscene0_wizard);
        mainWindow.draw(cutscene0_alchemist);
        mainWindow.draw(rectangleDown);
        mainWindow.draw(rectangleLeft);
        mainWindow.draw(rectangleRight);
        mainWindow.draw(rectangleUp);

        mainWindow.display();

        if(correctRectangles == 4) nextCutscene=true;
    }

    nextCutscene = false;

    talkingText.setFont(FontHolder::getFontInstance()->get(FontID::BossFont));
    talkingText.setFillColor(sf::Color::Blue);
    finalText = "¡¡SALUDOS insignificantes mortales!!";
    currentLetter = 0;

    // CUTSCENE 0: Boss says hi :3

    while(!nextCutscene){

        if(currentLetter<finalText.size()){
            talkingText.setString(talkingText.getString()+finalText[currentLetter]);
            currentLetter++;
            talkingSound.setPitch((5+rand()%10)/10.0);
            talkingSound.play();
        }

        // Code repetition ehehe
        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::KeyPressed) nextCutscene = true;
        }

        cutscene0_wizard.update();
        cutscene0_boss.update();
        cutscene0_alchemist.update();

        mainWindow.clear();

        mainWindow.draw(cutscene0_background);
        mainWindow.draw(cutscene0_boss);
        mainWindow.draw(cutscene0_wizard);
        mainWindow.draw(cutscene0_alchemist);
        mainWindow.draw(rectangleDown);
        mainWindow.draw(rectangleLeft);
        mainWindow.draw(rectangleRight);
        mainWindow.draw(rectangleUp);
        mainWindow.draw(talkingText);

        mainWindow.display();
    }



}
