#include "TitleScreen.hpp"
#include "Animation.hpp"
#include "ResourceHolder.hpp"
#include "MusicPlayer.hpp"
#include <iostream>

int TitleScreen::run(){

    MusicPlayer::getInstance()->play(MusicID::intro_music);

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

    // Sprite for the title
    sf::Sprite titleSprite;
    titleSprite.setTexture(TextureHolder::getTextureInstance()->get(TextureID::title));
    titleSprite.scale(2,2);
    titleSprite.setPosition(TITLE_POSITION);

    // Sprite for the "press enter to start" message
    sf::Sprite pressEnterSprite;
    pressEnterSprite.setTexture(TextureHolder::getTextureInstance()->get(TextureID::press_enter));
    pressEnterSprite.scale(2,2);
    pressEnterSprite.setPosition(MAIN_WINDOW_WIDTH/2-pressEnterSprite.getTextureRect().width,MAIN_WINDOW_HEIGHT-pressEnterSprite.getTextureRect().height*2-20);

    // Sprite for the "press escape to skip" message
    sf::Sprite pressEscapeSprite;
    pressEscapeSprite.setTexture(TextureHolder::getTextureInstance()->get(TextureID::press_escape));
    pressEscapeSprite.scale(2,2);
    pressEscapeSprite.setPosition(MAIN_WINDOW_WIDTH/2-pressEscapeSprite.getTextureRect().width,pressEscapeSprite.getTextureRect().height);
    sf::Color newColor = pressEscapeSprite.getColor();
    newColor.a = 0;
    pressEscapeSprite.setColor(newColor);

    // Rectangle that covers everything
    sf::RectangleShape rectangleCover(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));
    rectangleCover.setFillColor(sf::Color::Black);

    // Animations for cutscene 0
    Animation cutscene0_wizard;
    cutscene0_wizard.setDelay(13);
    cutscene0_wizard.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene0_wizard),2,false);
    cutscene0_wizard.setPosition(CUTSCENE0_WIZARD_POSITION);

    Animation cutscene0_alchemist;
    cutscene0_alchemist.setDelay(15);
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
    sf::Sound advanceConversationSound;
    advanceConversationSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::advance_conversation));
    sf::Text talkingText;
    talkingText.setPosition(MAIN_WINDOW_WIDTH/8,5*MAIN_WINDOW_HEIGHT/6+30);
    talkingText.setCharacterSize(CHARACTER_SIZE);

    // Indicates the current letter for the speaking character
    unsigned int currentLetter = 0;

    bool nextCutscene = false;

    // Show the title and wait for input

    while(!nextCutscene){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape) {MusicPlayer::getInstance()->stop(); return -1;}
                else if(event.key.code == sf::Keyboard::Return) nextCutscene = true;
            } else if (event.type == sf::Event::JoystickButtonPressed){
                MusicPlayer::getInstance()->stop();
                return event.joystickButton.joystickId;
            }
        }

        cutscene0_wizard.update();
        cutscene0_boss.update();
        cutscene0_alchemist.update();

        mainWindow.clear();

        mainWindow.draw(cutscene0_background);
        mainWindow.draw(cutscene0_boss);
        mainWindow.draw(cutscene0_wizard);
        mainWindow.draw(cutscene0_alchemist);
        mainWindow.draw(titleSprite);
        mainWindow.draw(pressEnterSprite);

        mainWindow.display();
    }

    nextCutscene = false;

    // Make the rectangles closer
    while(!nextCutscene){

        titleSprite.move(0,-5);
        pressEnterSprite.move(0,5);

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
            else if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape) {MusicPlayer::getInstance()->stop(); return -1;}
            } else if (event.type == sf::Event::JoystickButtonPressed) {MusicPlayer::getInstance()->stop(); return event.joystickButton.joystickId;}
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
        mainWindow.draw(titleSprite);
        mainWindow.draw(pressEnterSprite);

        mainWindow.display();

        if(correctRectangles == 4) nextCutscene=true;
    }

    nextCutscene = false;

    talkingSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::boss_voice));
    talkingText.setFont(FontHolder::getFontInstance()->get(FontID::WizardFont));
    talkingText.setFillColor(sf::Color::Blue);
    talkingText.setCharacterSize(20);
    advanceConversationSound.play();
    if(SPANISH) finalText = "��SALUDOS insignificantes terr�colas!!";
    else finalText = "GREETINGS you meaningless earthlings!!";
    currentLetter = 0;
    int currentText = 0;
    int wait = 0;

    // CUTSCENE 0: Boss says hi :3

    while(!nextCutscene){

        if(pressEscapeSprite.getColor().a != 255){
            sf::Color newColor = pressEscapeSprite.getColor();
            newColor.a+=5;
            pressEscapeSprite.setColor(newColor);
        }

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
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::JoystickButtonPressed) {MusicPlayer::getInstance()->stop(); return event.joystickButton.joystickId;}
            else if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {MusicPlayer::getInstance()->stop(); return -1;}
                else if(event.key.code == sf::Keyboard::Return){
                    if(wait > 0) continue;
                    advanceConversationSound.play();
                    switch(currentText){
                    case 0:
                        talkingText.setString("");
                        if(SPANISH) finalText = "Me dedico a vagar por el UNIVERSO";
                        else finalText = "It's my mission to wander the UNIVERSE";
                        currentLetter = 0;
                        currentText++;
                        break;
                    case 1:
                        talkingText.setString("");
                        if(SPANISH) finalText = "Buscando planetas que DESTRUIR";
                        else finalText = "Looking for planets to DESTROY";
                        currentLetter = 0;
                        currentText++;
                        break;
                    case 2:
                        talkingText.setString("");
                        if(SPANISH) finalText = "Y el vuestro... parece bastante DESTRUIBLE";
                        else finalText = "And yours... looks very DESTROYABLE";
                        currentLetter = 0;
                        currentText++;
                        break;
                    case 3:
                        talkingText.setString("");
                        if(SPANISH) finalText = "(en mi humilde opini�n)";
                        else finalText = "(in my humble opinion)";
                        currentLetter = 0;
                        currentText++;
                        break;
                    case 4:
                        talkingText.setString("");
                        if(SPANISH) finalText = "��Es por eso que DESTRUIR� este PLANETA!!";
                        else finalText = "That's why i'm going to DESTROY this PLANET!!";
                        currentLetter = 0;
                        currentText++;
                        break;
                    case 5:
                        talkingText.setString("");
                        if(SPANISH) finalText = "A no ser que me lanc�is LIBROS y MAGIA";
                        else finalText = "Unless you throw BOOKS and MAGIC at me";
                        currentLetter = 0;
                        currentText++;
                        break;
                    case 6:
                        talkingText.setString("");
                        if(SPANISH) finalText = "(son mi DEBILIDAD)";
                        else finalText = "(they're my WEAKNESSES)";
                        currentLetter = 0;
                        currentText++;
                        break;
                    case 7:
                        talkingText.setString("");
                        if(SPANISH) finalText = "��Pero conf�o en que eso NO PASAR�!!";
                        else finalText = "But I'm sure that WON'T HAPPEN!!";
                        currentLetter = 0;
                        currentText++;
                        break;
                    default:
                        nextCutscene = true;
                        talkingText.setString("");
                        finalText = "";
                        currentLetter = 0;
                        break;
                    }
                }
            }
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
        mainWindow.draw(pressEscapeSprite);

        mainWindow.display();
    }

    nextCutscene = false;
    rectangleCover.setFillColor(sf::Color(0,0,0,0));

    // Transition between cutscene 0 and 1

    while(!nextCutscene){

        if(pressEscapeSprite.getColor().a != 255){
            sf::Color newColor = pressEscapeSprite.getColor();
            newColor.a+=5;
            pressEscapeSprite.setColor(newColor);
        }

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::JoystickButtonPressed) {MusicPlayer::getInstance()->stop(); return event.joystickButton.joystickId;}
            else if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {MusicPlayer::getInstance()->stop(); return -1;}
                else if(event.key.code == sf::Keyboard::Return){
                    sf::Color currentColor = rectangleCover.getFillColor();
                    currentColor.a=255;
                    rectangleCover.setFillColor(currentColor);
                }
            }
        }

        cutscene0_wizard.update();
        cutscene0_boss.update();
        cutscene0_alchemist.update();
        sf::Color currentColor = rectangleCover.getFillColor();
        if(currentColor.a < 255){
            currentColor.a+=5;
            rectangleCover.setFillColor(currentColor);
        } else {
            nextCutscene = true;
        }

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
        mainWindow.draw(rectangleCover);
        mainWindow.draw(pressEscapeSprite);

        mainWindow.display();
    }

    // Animations for cutscene 1
    Animation cutscene1_wizard;
    cutscene1_wizard.setDelay(13);
    cutscene1_wizard.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene1_wizard),2,false);
    cutscene1_wizard.setPosition(CUTSCENE1_WIZARD_POSITION);

    Animation cutscene1_alchemist;
    cutscene1_alchemist.setDelay(15);
    cutscene1_alchemist.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene1_alchemist),2,false);
    cutscene1_alchemist.setPosition(CUTSCENE1_ALCHEMIST_POSITION);

    sf::Sprite cutscene1_background;
    cutscene1_background.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene1_background));
    cutscene1_background.setPosition(CUTSCENE1_BACKGROUND_POSITION);
    cutscene1_background.setScale(2,2);

    nextCutscene = false;

    // Transition between cutscene 0 and 1

    while(!nextCutscene){

        if(pressEscapeSprite.getColor().a != 255){
            sf::Color newColor = pressEscapeSprite.getColor();
            newColor.a+=5;
            pressEscapeSprite.setColor(newColor);
        }

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {MusicPlayer::getInstance()->stop(); return -1;}
                else if (event.type == sf::Event::JoystickButtonPressed) {MusicPlayer::getInstance()->stop(); return event.joystickButton.joystickId;}
                else if(event.key.code == sf::Keyboard::Return){
                    sf::Color currentColor = rectangleCover.getFillColor();
                    currentColor.a=0;
                    rectangleCover.setFillColor(currentColor);
                }
            }
        }

        cutscene1_wizard.update();
        cutscene1_alchemist.update();
        sf::Color currentColor = rectangleCover.getFillColor();
        if(currentColor.a > 0){
            currentColor.a-=5;
            rectangleCover.setFillColor(currentColor);
        } else {
            nextCutscene = true;
        }

        mainWindow.clear();

        mainWindow.draw(cutscene1_background);
        mainWindow.draw(cutscene1_wizard);
        mainWindow.draw(cutscene1_alchemist);
        mainWindow.draw(rectangleDown);
        mainWindow.draw(rectangleLeft);
        mainWindow.draw(rectangleRight);
        mainWindow.draw(rectangleUp);
        mainWindow.draw(talkingText);
        mainWindow.draw(rectangleCover);
        mainWindow.draw(pressEscapeSprite);

        mainWindow.display();
    }

    nextCutscene = false;

    // CUTSCENE 1: alchemist discusses the chances of raining books and magic (clueless)

    talkingSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::wizard_voice));
    talkingText.setFont(FontHolder::getFontInstance()->get(FontID::WizardFont));
    talkingText.setFillColor(sf::Color::Yellow);
    talkingText.setCharacterSize(20);
    advanceConversationSound.play();
    if(SPANISH) finalText = "Tenemos que encontrar libros y magia como sea!! :(";
    else finalText = "We need to find books and magic no matter what!! :(";
    currentLetter = 0;
    currentText = 0;

    while(!nextCutscene){

        if(pressEscapeSprite.getColor().a != 255){
            sf::Color newColor = pressEscapeSprite.getColor();
            newColor.a+=5;
            pressEscapeSprite.setColor(newColor);
        }

        if(currentLetter<finalText.size()){
            talkingText.setString(talkingText.getString()+finalText[currentLetter]);
            currentLetter++;
            talkingSound.setPitch((5+rand()%10)/10.0);
            talkingSound.play();
        } else if (currentText == 3) nextCutscene = true;

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::JoystickButtonPressed) {MusicPlayer::getInstance()->stop(); return event.joystickButton.joystickId;}
            else if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {MusicPlayer::getInstance()->stop(); return -1;}
                else if(event.key.code == sf::Keyboard::Return){

                    advanceConversationSound.play();
                    switch(currentText){
                    case 0:
                        talkingText.setString("");
                        talkingSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::alchemist_voice));
                        talkingText.setFont(FontHolder::getFontInstance()->get(FontID::AlchemistFont));
                        talkingText.setFillColor(sf::Color::White);
                        talkingText.setCharacterSize(30);
                        talkingText.move(0,-8);
                        if(SPANISH) finalText = "y como se supone que vamos a encontrar de eso";
                        else finalText = "and how are we supposed to find that";
                        currentLetter = 0;
                        currentText++;
                        break;
                    case 1:
                        talkingText.setString("");
                        if(SPANISH) finalText = "estamos en mitad de ningun sitio";
                        else finalText = "we are in the middle of nowhere";
                        currentLetter = 0;
                        currentText++;
                        break;
                    case 2:
                        talkingText.setString("");
                        if(SPANISH) finalText = "ni que los libros y la magia cayeran del cielo";
                        else finalText = "books and magic dont just fall from the sky";
                        currentLetter = 0;
                        currentText++;
                        break;
                    default:
                        nextCutscene = true;
                    }
                }
            }
        }

        cutscene1_wizard.update();
        cutscene1_alchemist.update();

        mainWindow.clear();

        mainWindow.draw(cutscene1_background);
        mainWindow.draw(cutscene1_wizard);
        mainWindow.draw(cutscene1_alchemist);
        mainWindow.draw(rectangleDown);
        mainWindow.draw(rectangleLeft);
        mainWindow.draw(rectangleRight);
        mainWindow.draw(rectangleUp);
        mainWindow.draw(talkingText);
        mainWindow.draw(pressEscapeSprite);

        mainWindow.display();
    }

    if(SPANISH) talkingText.setString("ni que los libros y la magia cayeran del cielo");
    else talkingText.setString("books and magic dont just fall from the sky");

    nextCutscene = false;

    // CUTSCENE 2: oh goodness gracious the books are plentiful

    // Sprites for cutscene 2
    sf::Sprite cutscene2_wizard;
    cutscene2_wizard.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene2_wizard));
    cutscene2_wizard.scale(2,2);
    cutscene2_wizard.setPosition(CUTSCENE1_WIZARD_POSITION);

    sf::Sprite cutscene2_alchemist;
    cutscene2_alchemist.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene2_alchemist));
    cutscene2_alchemist.scale(2,2);
    cutscene2_alchemist.setPosition(CUTSCENE2_ALCHEMIST_POSITION);

    sf::Sprite cutscene2_background;
    cutscene2_background.setTexture(TextureHolder::getTextureInstance()->get(TextureID::cutscene2_background));
    cutscene2_background.setPosition(CUTSCENE1_BACKGROUND_POSITION);
    cutscene2_background.setScale(2,2);

    MusicPlayer::getInstance()->stop();

    sf::Sound hitSound;
    hitSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::alchemist_damage));
    hitSound.play();

    int windowMove = WINDOW_SHAKE_FREQUENCY*30;

    wait = 0;

    int opacity = 0;

    while(!nextCutscene){

        if(pressEscapeSprite.getColor().a != 255){
            sf::Color newColor = pressEscapeSprite.getColor();
            newColor.a+=5;
            pressEscapeSprite.setColor(newColor);
        }

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {MusicPlayer::getInstance()->stop(); return -1;}
                else if (event.type == sf::Event::JoystickButtonPressed) {MusicPlayer::getInstance()->stop(); return event.joystickButton.joystickId;}
                else if(event.key.code == sf::Keyboard::Return) nextCutscene = true;
            }
        }

        if(windowMove%WINDOW_SHAKE_FREQUENCY == 0 && windowMove != -1){
            sf::Vector2i newPosition = mainWindow.getPosition();
            newPosition.y += windowMove/WINDOW_SHAKE_FREQUENCY * ((windowMove/WINDOW_SHAKE_FREQUENCY)%2 ? -1 : 1);
            mainWindow.setPosition(newPosition);
        }

        if(windowMove > -1){
            windowMove--;
        } else if(wait < CUTSCENE2_WAIT){
            wait++;
        } else if(opacity < 255){
            opacity+=5;
        } else {
            nextCutscene = true;
        }

        sf::Color rectangleCoverColor = rectangleCover.getFillColor();
        rectangleCoverColor.a = opacity;
        rectangleCover.setFillColor(rectangleCoverColor);

        mainWindow.clear();

        mainWindow.draw(cutscene2_background);
        mainWindow.draw(cutscene2_wizard);
        mainWindow.draw(cutscene2_alchemist);
        mainWindow.draw(rectangleDown);
        mainWindow.draw(rectangleLeft);
        mainWindow.draw(rectangleRight);
        mainWindow.draw(rectangleUp);
        mainWindow.draw(talkingText);
        mainWindow.draw(pressEscapeSprite);
        mainWindow.draw(rectangleCover);

        mainWindow.display();
    }

    MusicPlayer::getInstance()->stop();
    return -1;
}
