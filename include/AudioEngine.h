#pragma once

#include <SDL2/SDL_mixer.h>

#include <map>
#include <string>

namespace Toaster
{
    class SoundEffect
    {
    public:
        friend class AudioEngine;
        void play(int loops = 0);

    private:
        Mix_Chunk *_chunk = nullptr;
    };

    class Music
    {
    public:
        friend class AudioEngine;

        /// @brief Plays the music file
        /// @param loops 1 to play once, -1 for infinite loop
        void play(int loops = -1);
        void pause();
        void stop();
        void resume();

    private:
        Mix_Music *_music = nullptr;
    };

    class AudioEngine
    {
    public:
        AudioEngine();
        ~AudioEngine();

        void init();
        void destroy();

        SoundEffect loadSoundEffect(const std::string &filePath);
        Music loadMusic(const std::string &filePath);

    private:
        std::map<std::string, Mix_Chunk *> _effectMap;
        std::map<std::string, Mix_Music *> _musicMap;
        bool _isInitialized = false;
    };
}
