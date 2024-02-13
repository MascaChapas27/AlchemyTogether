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
    load(TextureID::controls_background,"sprites/controls-background.png");
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
    load(TextureID::press_enter,"sprites/press-enter.png");
    load(TextureID::press_escape,"sprites/press-escape.png");
    load(TextureID::time_frame,"sprites/time-frame.png");
    load(TextureID::alchemist_arrow,"sprites/alchemist-arrow.png");
    load(TextureID::wizard_arrow,"sprites/wizard-arrow.png");
    load(TextureID::alchemist_corpse,"sprites/alchemist-corpse.png");
    load(TextureID::wizard_corpse,"sprites/wizard-corpse.png");

    load(TextureID::death0,"sprites/death0.png");
    load(TextureID::death1,"sprites/death1.png");
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
}

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::loadAllFonts()
{
    load(FontID::AlchemistFont,"fonts/gabriela.ttf");
    load(FontID::WizardFont,"fonts/daniela.ttf");
    load(FontID::BossFont,"fonts/father.ttf");
}
