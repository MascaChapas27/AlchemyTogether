#include "MusicPlayer.hpp"

MusicPlayer * MusicPlayer::musicPlayer = nullptr;

MusicPlayer * MusicPlayer::getInstance()
{
    if(musicPlayer==nullptr)
        musicPlayer = new MusicPlayer();
    return musicPlayer;
}

void MusicPlayer::load(MusicID identifier, const std::string path)
{
    filenames[identifier] = path;
}

void MusicPlayer::play(MusicID theme)
{
    std::string filename = filenames[theme];

    currentMusic.openFromFile(filename);

    currentMusic.setLoop(true);
    currentMusic.play();
}

void MusicPlayer::stop()
{
    currentMusic.stop();
}

float MusicPlayer::getVolume()
{
    return currentMusic.getVolume();
}

void MusicPlayer::alterVolume(float change)
{
    currentMusic.setVolume(currentMusic.getVolume()+change);
}

void MusicPlayer::loadAllMusic()
{
    load(MusicID::intro_music,"music/intro.wav");
    load(MusicID::battle_music,"music/battle.wav");
}
