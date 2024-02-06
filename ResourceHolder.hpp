#ifndef __RESOURCE_HOLDER__
#define __RESOURCE_HOLDER__

#include "Utilities.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <map>

/*
    The ResourceHolder is a class that is in charge of resources.
    Instead of loading resources inside of other classes, all resources
    are loaded from the first moment in this class. This ensures that all
    resources are available at all times. This is a generic class, so it can
    be used for textures, fonts and sound buffers without a problem
*/

// First we declare the class
template <class Resource, class Identifier>
class ResourceHolder;

// Then we declare typedefs for the different types
// of resource holders
typedef ResourceHolder<sf::Texture,TextureID> TextureHolder;
typedef ResourceHolder<sf::SoundBuffer,SoundID> SoundHolder;
typedef ResourceHolder<sf::Font,FontID> FontHolder;

// Now we can use the typedefs!
template <class Resource, class Identifier>
class ResourceHolder
{
    protected:
        ResourceHolder(){}
        ~ResourceHolder(){}

        static TextureHolder * textureHolder;
        static SoundHolder * soundHolder;
        static FontHolder * fontHolder;

    private:
        // A map that contains a resource for each identifier
        std::map<Identifier, std::unique_ptr<Resource>> resourceMap;

    public:
        // Loads a resource given its ID and its path
        void load(Identifier id, const std::string& filename);

        // Gets a resource given its ID
        Resource& get(Identifier id);

        // Loads all resources (implementation-specific)
        void loadAllTextures();
        void loadAllSounds();
        void loadAllFonts();

        // NEVER CLONE A SINGLETON
        ResourceHolder(ResourceHolder &other) = delete;

        // NEVER ASSIGN A SINGLETON
        void operator=(const ResourceHolder &) = delete;

        // Singleton-specific methods to get the one and only instance
        static TextureHolder * getTextureInstance();
        static SoundHolder * getSoundInstance();
        static FontHolder * getFontInstance();

};

// Because we used templates, it's impossible to include ResourceHolder.hpp in
// the ResourceHolder.cpp file, so it's necessary to do it the other way around.
// Also, we change the .cpp extension to .tpp because Code::Blocks automatically
// compiles all files with .cpp extension, and ResourceHolder.tpp should not
// be compiled individually

#include "ResourceHolder.tpp"

#endif // __TEXTURE_HOLDER__
