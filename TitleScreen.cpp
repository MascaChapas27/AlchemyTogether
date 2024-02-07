#include "TitleScreen.hpp"
#include "Animation.hpp"
#include "ResourceHolder.hpp"
#include "MusicPlayer.hpp"

void TitleScreen::run(){

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

    talkingSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::boss_voice));
    talkingText.setFont(FontHolder::getFontInstance()->get(FontID::BossFont));
    talkingText.setFillColor(sf::Color::Blue);
    advanceConversationSound.play();
    finalText = "¡¡SALUDOS insignificantes terrícolas!!";
    currentLetter = 0;
    int currentText = 0;

    // CUTSCENE 0: Boss says hi :3

    while(!nextCutscene){

        if(currentLetter<finalText.size()){
            talkingText.setString(talkingText.getString()+finalText[currentLetter]);
            currentLetter++;
            talkingSound.setPitch((5+rand()%10)/10.0);
            talkingSound.play();
        }

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::KeyPressed) {
                advanceConversationSound.play();
                switch(currentText){
                case 0:
                    talkingText.setString("");
                    finalText = "En un principio vine a este planeta en son de PAZ";
                    currentLetter = 0;
                    currentText++;
                    break;
                case 1:
                    talkingText.setString("");
                    finalText = "Pero me encontré con un grupo de INFORMÁTICOS";
                    currentLetter = 0;
                    currentText++;
                    break;
                case 2:
                    talkingText.setString("");
                    finalText = "Uno de ellos se ha puesto a HABLARME de LOL";
                    currentLetter = 0;
                    currentText++;
                    break;
                case 3:
                    talkingText.setString("");
                    finalText = "(olía a AJO)";
                    currentLetter = 0;
                    currentText++;
                    break;
                case 4:
                    talkingText.setString("");
                    finalText = "¡¡Es por eso que DESTRUIRÉ este PLANETA!!";
                    currentLetter = 0;
                    currentText++;
                    break;
                case 5:
                    talkingText.setString("");
                    finalText = "A no ser que me lancéis LIBROS y MAGIA";
                    currentLetter = 0;
                    currentText++;
                    break;
                case 6:
                    talkingText.setString("");
                    finalText = "(son mi DEBILIDAD)";
                    currentLetter = 0;
                    currentText++;
                    break;
                case 7:
                    talkingText.setString("");
                    finalText = "¡¡Pero eso NO va a PASAR!!";
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

    nextCutscene = false;
    rectangleCover.setFillColor(sf::Color(0,0,0,0));

    // Transition between cutscene 0 and 1

    while(!nextCutscene){

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::KeyPressed) {
                sf::Color currentColor = rectangleCover.getFillColor();
                currentColor.a=255;
                rectangleCover.setFillColor(currentColor);
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

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::KeyPressed) {
                sf::Color currentColor = rectangleCover.getFillColor();
                currentColor.a=0;
                rectangleCover.setFillColor(currentColor);
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

        mainWindow.display();
    }

    nextCutscene = false;

    // CUTSCENE 1: alchemist discusses the chances of raining books and magic (clueless)

    talkingSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::wizard_voice));
    talkingText.setFont(FontHolder::getFontInstance()->get(FontID::WizardFont));
    talkingText.setFillColor(sf::Color::Yellow);
    talkingText.setCharacterSize(20);
    advanceConversationSound.play();
    finalText = "Tenemos que encontrar libros y magia como sea!! :(";
    currentLetter = 0;
    currentText = 0;

    while(!nextCutscene){

        if(currentLetter<finalText.size()){
            talkingText.setString(talkingText.getString()+finalText[currentLetter]);
            currentLetter++;
            talkingSound.setPitch((5+rand()%10)/10.0);
            talkingSound.play();
        } else if (currentText == 3) nextCutscene = true;

        sf::Event event;
        while(mainWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed) exit(EXIT_SUCCESS);
            else if (event.type == sf::Event::KeyPressed) {
                advanceConversationSound.play();
                switch(currentText){
                case 0:
                    talkingText.setString("");
                    talkingSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::alchemist_voice));
                    talkingText.setFont(FontHolder::getFontInstance()->get(FontID::AlchemistFont));
                    talkingText.setFillColor(sf::Color::White);
                    talkingText.setCharacterSize(30);
                    talkingText.move(0,-8);
                    finalText = "y como se supone que vamos a encontrar de eso";
                    currentLetter = 0;
                    currentText++;
                    break;
                case 1:
                    talkingText.setString("");
                    finalText = "estamos en mitad de ningun sitio";
                    currentLetter = 0;
                    currentText++;
                    break;
                case 2:
                    talkingText.setString("");
                    finalText = "ni que los libros y la magia cayeran del cielo";
                    currentLetter = 0;
                    currentText++;
                    break;
                default:
                    nextCutscene = true;
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

        mainWindow.display();
    }


    MusicPlayer::getInstance()->stop();
}
