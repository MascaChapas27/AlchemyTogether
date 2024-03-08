#include "GoodEndingCutscene.hpp"
#include <SFML/Graphics.hpp>
#include "Utilities.hpp"
#include "ResourceHolder.hpp"
#include "Animation.hpp"
#include "MusicPlayer.hpp"

void GoodEndingCutscene::play(){

    mainWindow.setFramerateLimit(CUTSCENE_FPS);

    // Rectangle that covers everything
    sf::RectangleShape rectangleCover(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));
    rectangleCover.setFillColor(sf::Color::Black);

    // Sprites for the cutscene

    sf::Sprite defeatedBoss;
    defeatedBoss.setTexture(TextureHolder::getTextureInstance()->get(TextureID::defeated_boss));
    defeatedBoss.setPosition(CUTSCENE1_BACKGROUND_POSITION);
    defeatedBoss.scale(2,2);

    bool nextScene = false;

    while(rectangleCover.getFillColor().a>0){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(!RECREATIVA){
                if(event.type == sf::Event::KeyPressed){
                    if(event.key.code == sf::Keyboard::Num6) exit(EXIT_SUCCESS);
                    else if(event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::A) nextScene = true;
                }
            }
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
        mainWindow.draw(defeatedBoss);
        mainWindow.draw(rectangleCover);
        mainWindow.display();
    }

    rectangleCover.setFillColor(sf::Color::Transparent);

    nextScene = false;

    // Final message for the current character
    std::wstring finalText;

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
    if(RECREATIVA || SPANISH) finalText = L"AaaaAaAaaaa mi espaldaaa";
    else finalText = L"AaaAAaArrgAGhh my baaack";
    unsigned int currentText = 0;

    // Indicates the current letter for the speaking character
    unsigned int currentLetter = 0;

    while(rectangleCover.getFillColor() != sf::Color::Black){

        if(currentLetter<finalText.size()){
            talkingText.setString(talkingText.getString()+finalText[currentLetter]);
            currentLetter++;
            talkingSound.setPitch((5+rand()%10)/10.0);
            talkingSound.play();
        }

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if((RECREATIVA && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6) ||
               (!RECREATIVA && event.type == sf::Event::Closed)){
                mainWindow.close();
                exit(EXIT_SUCCESS);
            }
            if((RECREATIVA && event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::A)) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) || event.type == sf::Event::JoystickButtonPressed){
                switch(currentText){
                case 0:
                    advanceConversationSound.play();

                    talkingText.setString(L"");
                    if(RECREATIVA || SPANISH) finalText = L"Está bien... no destruiré la Tierra...";
                    else finalText = L"Alright... I won't destroy the Earth...";

                    currentLetter = 0;
                    currentText++;
                    break;
                case 1:
                    advanceConversationSound.play();

                    talkingText.setString(L"");
                    if(RECREATIVA || SPANISH) finalText = L"Por favor llevadme a un hospital";
                    else finalText = L"Take me to a hospital please";

                    currentLetter = 0;
                    currentText++;
                    break;
                case 2:
                    nextScene = true;
                    talkingText.setString(L"");
                    finalText = L"";
                    currentLetter = 0;
                    rectangleCover.setFillColor(sf::Color(0,0,0,0));
                    currentText++;
                    break;
                }
            }
        }

        if(nextScene){
            sf::Color newColor = rectangleCover.getFillColor();
            newColor.a+=5;
            rectangleCover.setFillColor(newColor);
            MusicPlayer::getInstance()->alterVolume(-1);
        }

        mainWindow.clear();
        mainWindow.draw(talkingText);
        mainWindow.draw(defeatedBoss);
        mainWindow.draw(rectangleCover);
        mainWindow.display();
    }

    mainWindow.close();
    exit(EXIT_SUCCESS);
}
