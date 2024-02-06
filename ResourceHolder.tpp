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
    load(TextureID::alchemist_side,"sprites/alchemist-side.png");
    load(TextureID::alchemist_walk,"sprites/alchemist-walk.png");
    load(TextureID::background,"sprites/background.png");
    load(TextureID::book,"sprites/book.png");
    load(TextureID::magic,"sprites/magic.png");
    load(TextureID::fire,"sprites/fire.png");
    load(TextureID::boss,"sprites/boss.png");
    load(TextureID::boss_hit,"sprites/boss-hit.png");
    load(TextureID::controls_background,"sprites/controls-background.png");
    load(TextureID::cutscene0_boss,"sprites/cutscene0-boss.png");
    load(TextureID::cutscene0_wizard,"sprites/cutscene0-wizard.png");
    load(TextureID::cutscene0_alchemist,"sprites/cutscene0-alchemist.png");
    load(TextureID::cutscene1_background,"sprites/cutscene1-background.png");
    load(TextureID::cutscene1_alchemist,"sprites/cutscene1-alchemist.png");
    load(TextureID::cutscene1_wizard,"sprites/cutscene1-wizard.png");
    load(TextureID::wizard_dance,"sprites/wizard-dance.png");
    load(TextureID::wizard_hit,"sprites/wizard-hit.png");
    load(TextureID::wizard_shoot,"sprites/wizard-shoot.png");
    load(TextureID::wizard_walk,"sprites/wizard-walk.png");
}

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::loadAllSounds()
{

}

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::loadAllFonts()
{
    load(FontID::AlchemistFont,"fonts/gabriela.ttf");
    load(FontID::WizardFont,"fonts/daniela.ttf");
    load(FontID::BossFont,"fonts/father.ttf");
}
