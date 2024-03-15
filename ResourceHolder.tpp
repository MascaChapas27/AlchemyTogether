#include <assert.h>

// Singleton static variables are initialized as null
template <class Resource, class Identifier>
TextureHolder * ResourceHolder<Resource,Identifier>::textureHolder = nullptr;

template <class Resource, class Identifier>
SoundHolder * ResourceHolder<Resource,Identifier>::soundHolder = nullptr;

template <class Resource, class Identifier>
FontHolder * ResourceHolder<Resource,Identifier>::fontHolder = nullptr;

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::load(Identifier id, const std::string& fileName){
    // Unique pointers are better because they delete themselves when
    // they go out of scope
    std::unique_ptr<Resource> resource(new Resource());

    // We try to load the resource. If there is an error, we die horribly
    if(!resource->loadFromFile(fileName)){
        exit(EXIT_FAILURE);
    }

    // It's important to std::move the pointer so that it's not destroyed
    // as soon as the function ends.
    resourceMap.insert(std::make_pair(id,std::move(resource)));
}

template <class Resource, class Identifier>
Resource& ResourceHolder<Resource,Identifier>::get(Identifier id){
    // First we find the element in the map (auto means that the
    // type is automatically infered from the context)
    auto found = resourceMap.find(id);

    // Once we have the element, which is a pair, we return
    // the texture, which is the second element
    return *(found -> second);
}

template <class Resource, class Identifier>
TextureHolder * ResourceHolder<Resource,Identifier>::getTextureInstance()
{
    if(textureHolder == nullptr)
        textureHolder = new TextureHolder;
    return textureHolder;
}

template <class Resource, class Identifier>
SoundHolder * ResourceHolder<Resource,Identifier>::getSoundInstance()
{
    if(soundHolder == nullptr)
        soundHolder = new SoundHolder;
    return soundHolder;
}

template <class Resource, class Identifier>
FontHolder * ResourceHolder<Resource,Identifier>::getFontInstance()
{
    if(fontHolder == nullptr)
        fontHolder = new FontHolder;
    return fontHolder;
}

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::loadAllTextures()
{
    load(TextureID::alchemist_dance,"sprites/alchemist-dance.png");
    load(TextureID::alchemist_hit,"sprites/alchemist-hit.png");
    load(TextureID::alchemist_shoot,"sprites/alchemist-shoot.png");
    load(TextureID::alchemist_side,"sprites/alchemist-side.png");
    load(TextureID::alchemist_hold,"sprites/alchemist-hold.png");
    load(TextureID::alchemist_walk,"sprites/alchemist-walk.png");
    load(TextureID::title,"sprites/title.png");
    load(TextureID::background,"sprites/background.png");
    load(TextureID::book,"sprites/book.png");
    load(TextureID::magic,"sprites/magic.png");
    load(TextureID::fire,"sprites/fire.png");
    load(TextureID::boss,"sprites/boss.png");
    load(TextureID::boss_hit,"sprites/boss-hit.png");
    load(TextureID::cutscene0_background,"sprites/cutscene0-background.png");
    load(TextureID::cutscene0_boss,"sprites/cutscene0-boss.png");
    load(TextureID::cutscene0_wizard,"sprites/cutscene0-wizard.png");
    load(TextureID::cutscene0_alchemist,"sprites/cutscene0-alchemist.png");
    load(TextureID::cutscene1_background,"sprites/cutscene1-background.png");
    load(TextureID::cutscene1_alchemist,"sprites/cutscene1-alchemist.png");
    load(TextureID::cutscene1_wizard,"sprites/cutscene1-wizard.png");
    load(TextureID::cutscene2_alchemist,"sprites/cutscene2-alchemist.png");
    load(TextureID::cutscene2_wizard,"sprites/cutscene2-wizard.png");
    load(TextureID::cutscene2_background,"sprites/cutscene2-background.png");
    load(TextureID::wizard_dance,"sprites/wizard-dance.png");
    load(TextureID::wizard_hit,"sprites/wizard-hit.png");
    load(TextureID::wizard_shoot,"sprites/wizard-shoot.png");
    load(TextureID::wizard_side,"sprites/wizard-side.png");
    load(TextureID::wizard_hold,"sprites/wizard-hold.png");
    load(TextureID::wizard_walk,"sprites/wizard-walk.png");
    load(TextureID::press_enter,RECREATIVA ? "sprites/press-enter-recreativa.png" : SPANISH ? "sprites/press-enter-es.png" : "sprites/press-enter-en.png");
    load(TextureID::press_escape,RECREATIVA ? "sprites/press-escape-recreativa.png" : SPANISH ? "sprites/press-escape-es.png" : "sprites/press-escape-en.png");
    load(TextureID::time_frame,"sprites/time-frame.png");
    load(TextureID::alchemist_arrow,"sprites/alchemist-arrow.png");
    load(TextureID::wizard_arrow,"sprites/wizard-arrow.png");
    load(TextureID::alchemist_corpse,"sprites/alchemist-corpse.png");
    load(TextureID::wizard_corpse,"sprites/wizard-corpse.png");

    load(TextureID::alchemist_inventory,SPANISH || RECREATIVA ? "sprites/alchemist-inventory-es.png" : "sprites/alchemist-inventory-en.png");
    load(TextureID::wizard_inventory,SPANISH || RECREATIVA ? "sprites/wizard-inventory-es.png" : "sprites/wizard-inventory-en.png");
    load(TextureID::alchemist_revive,SPANISH || RECREATIVA ? "sprites/alchemist-revive-es.png" : "sprites/alchemist-revive-en.png");
    load(TextureID::wizard_revive,SPANISH || RECREATIVA ? "sprites/wizard-revive-es.png" : "sprites/wizard-revive-en.png");
    load(TextureID::boss_health,SPANISH || RECREATIVA ? "sprites/boss-health-es.png" : "sprites/boss-health-en.png");

    load(TextureID::alchemist_plus1,"sprites/alchemist-plus1.png");
    load(TextureID::wizard_plus1,"sprites/wizard-plus1.png");
    load(TextureID::boss_minus1,"sprites/boss-minus1.png");
    load(TextureID::boss_corpse,"sprites/boss-corpse.png");
    load(TextureID::joystick_choose_alchemist,SPANISH || RECREATIVA ? "sprites/joystick-choose-alchemist-es.png" : "sprites/joystick-choose-alchemist-en.png");
    load(TextureID::joystick_choose_wizard,SPANISH || RECREATIVA ? "sprites/joystick-choose-wizard-es.png" : "sprites/joystick-choose-wizard-en.png");
    load(TextureID::controls_background_keyboard_keyboard,RECREATIVA ? "sprites/controls-background-recreativa.png" : SPANISH ? "sprites/controls-background-keyboard-keyboard-es.png" : "sprites/controls-background-keyboard-keyboard-en.png");
    load(TextureID::controls_background_keyboard_joystick,SPANISH ? "sprites/controls-background-keyboard-joystick-es.png" : "sprites/controls-background-keyboard-joystick-en.png");
    load(TextureID::controls_background_joystick_keyboard,SPANISH ? "sprites/controls-background-joystick-keyboard-es.png" : "sprites/controls-background-joystick-keyboard-en.png");
    load(TextureID::controls_background_joystick_joystick,SPANISH ? "sprites/controls-background-joystick-joystick-es.png" : "sprites/controls-background-joystick-joystick-en.png");

    load(TextureID::dead_heroes,"sprites/dead-heroes.png");
    load(TextureID::defeated_boss,"sprites/defeated-boss.png");
}

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::loadAllSounds()
{
    load(SoundID::boss_voice,"sounds/boss-voice.wav");
    load(SoundID::alchemist_voice,"sounds/alchemist-voice.wav");
    load(SoundID::wizard_voice,"sounds/wizard-voice.wav");
    load(SoundID::advance_conversation,"sounds/advance-conversation.wav");
    load(SoundID::alchemist_damage,"sounds/alchemist-damage.wav");
    load(SoundID::alchemist_collect,"sounds/alchemist-collect.wav");
    load(SoundID::alchemist_shoot,"sounds/alchemist-shoot.wav");
    load(SoundID::wizard_damage,"sounds/wizard-damage.wav");
    load(SoundID::wizard_collect,"sounds/wizard-collect.wav");
    load(SoundID::wizard_shoot,"sounds/wizard-shoot.wav");
    load(SoundID::boss_damage,"sounds/boss-damage.wav");
    load(SoundID::boss_shoot,"sounds/boss-shoot.wav");
    load(SoundID::boss_disappear,"sounds/boss-disappear.wav");
    load(SoundID::boss_appear,"sounds/boss-appear.wav");
    load(SoundID::breaking_earth,"sounds/breaking-earth.wav");
    load(SoundID::alchemist_revive,"sounds/alchemist-revive.wav");
    load(SoundID::wizard_revive,"sounds/wizard-revive.wav");
    load(SoundID::alchemist_fall,"sounds/alchemist-fall.wav");
    load(SoundID::wizard_fall,"sounds/wizard-fall.wav");
    load(SoundID::boss_fall,"sounds/boss-fall.wav");
}

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::loadAllFonts()
{
    load(FontID::AlchemistFont,"fonts/gabriela.ttf");
    load(FontID::WizardFont,"fonts/daniela.ttf");
}
