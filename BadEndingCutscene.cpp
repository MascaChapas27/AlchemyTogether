#include "BadEndingCutscene.hpp"
#include <SFML/Graphics.hpp>
#include "Utilities.hpp"
#include "ResourceHolder.hpp"
#include "Animation.hpp"
#include "MusicPlayer.hpp"

void BadEndingCutscene::play(){

    mainWindow.setFramerateLimit(CUTSCENE_FPS);

    // Rectangle that covers everything
    sf::RectangleShape rectangleCover(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));
    rectangleCover.setFillColor(sf::Color::Black);

    // Sprites for the cutscene

    sf::Sprite deadHeroes;
    deadHeroes.setTexture(TextureHolder::getTextureInstance()->get(TextureID::dead_heroes));
    deadHeroes.setPosition(CUTSCENE1_BACKGROUND_POSITION);
    deadHeroes.scale(2,2);

    // Sound for the breaking earth
    sf::Sound breakingEarthSound;
    breakingEarthSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::breaking_earth));

    bool nextScene = false;

    while(rectangleCover.getFillColor().a>0){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                mainWindow.close();
                exit(EXIT_SUCCESS);
            } else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) || event.type == sf::Event::JoystickButtonPressed){
                nextScene = true;
            }
        }

        sf::Color newColor = rectangleCover.getFillColor();
        newColor.a-=5;
        rectangleCover.setFillColor(newColor);

        mainWindow.clear();
        mainWindow.draw(deadHeroes);
        mainWindow.draw(rectangleCover);
        mainWindow.display();
    }

    rectangleCover.setFillColor(sf::Color::Transparent);

    nextScene = false;

    // Final message for the current character
    std::string finalText;

    // Text and sfx of the current speaking character
    sf::Sound talkingSound;
    talkingSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::boss_voice));
    sf::Sound advanceConversationSound;
    advanceConversationSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::advance_conversation));
    sf::Text talkingText;
    talkingText.setPosition(MAIN_WINDOW_WIDTH/8,5*MAIN_WINDOW_HEIGHT/6+30);
    talkingText.setFont(FontHolder::getFontInstance()->get(FontID::WizardFont));
    talkingText.setFillColor(sf::Color::Blue);
    talkingText.setCharacterSize(20);
    advanceConversationSound.play();
    if(SPANISH) finalText = "Lo suponía";
    else finalText = "Just as I thought";
    unsigned int currentText = 0;
    int wait = 0;

    // Indicates the current letter for the speaking character
    unsigned int currentLetter = 0;

    while(rectangleCover.getFillColor() != sf::Color::White){

        if(currentLetter<finalText.size()){
            if(wait > 0) wait--;
            else {
                if(finalText[currentLetter] == '.') wait = TEXT_WAIT;
                talkingText.setString(talkingText.getString()+finalText[currentLetter]);
                currentLetter++;
                talkingSound.setPitch((5+rand()%10)/10.0);
                talkingSound.play();
            }
        }

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                mainWindow.close();
                exit(EXIT_SUCCESS);
            }
            if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) || event.type == sf::Event::JoystickButtonPressed){
                switch(currentText){
                case 0:
                    advanceConversationSound.play();
                    talkingText.setString("");
                    if(SPANISH) finalText = "No érais más que un par de INÚTILES";
                    else finalText = "You were just a couple of LOSERS";
                    currentLetter = 0;
                    currentText++;
                    break;
                case 1:
                    advanceConversationSound.play();
                    talkingText.setString("");
                    if(SPANISH) finalText = "Ahora NADIE me impedirá DESTRUIR ESTE PLANETA";
                    else finalText = "NOBODY will stop me from DESTROYING THIS PLANET";
                    currentLetter = 0;
                    currentText++;
                    break;
                case 2:
                    nextScene = true;
                    talkingText.setString("");
                    finalText = "";
                    currentLetter = 0;
                    rectangleCover.setFillColor(sf::Color(255,255,255,0));
                    breakingEarthSound.play();
                    currentText++;
                    break;
                }
            }
        }

        if(nextScene){
            sf::Color newColor = rectangleCover.getFillColor();
            newColor.a+=5;
            rectangleCover.setFillColor(newColor);
        }

        mainWindow.clear();
        mainWindow.draw(talkingText);
        mainWindow.draw(deadHeroes);
        mainWindow.draw(rectangleCover);
        mainWindow.display();
    }

    sf::sleep(sf::seconds(1));

    while(rectangleCover.getFillColor() != sf::Color(255,255,255,0)){
        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                mainWindow.close();
                exit(EXIT_SUCCESS);
            }
        }

        sf::Color newColor = rectangleCover.getFillColor();
        newColor.a--;
        rectangleCover.setFillColor(newColor);

        MusicPlayer::getInstance()->alterVolume(-0.4);

        mainWindow.clear();
        mainWindow.draw(rectangleCover);
        mainWindow.display();
    }

    mainWindow.close();
    exit(EXIT_FAILURE);
}
