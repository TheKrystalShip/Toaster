#include "Timing.h"

#include <SDL2/SDL.h>

namespace Toaster
{
    FpsLimiter::FpsLimiter()
    {
    }

    void FpsLimiter::init(float maxFps)
    {
        setMaxFps(maxFps);
    }

    void FpsLimiter::setMaxFps(float maxFps)
    {
        _maxFps = maxFps;
    }

    void FpsLimiter::begin()
    {
        _startTicks = SDL_GetTicks();
    }

    float FpsLimiter::end()
    {
        calculateFps();

        float frameTicks = SDL_GetTicks() - _startTicks;
        // Limit FPS to _maxFps
        if (1000.0f / _maxFps > frameTicks)
        {
            SDL_Delay((1000.0f / _maxFps) - frameTicks);
        }

        return _fps;
    }

    void FpsLimiter::calculateFps()
    {
        static const int NUM_SAMPLES = 10;
        static float frameTimes[NUM_SAMPLES];
        static int currentFrame = 0;

        static float previousTicks = SDL_GetTicks();

        float currentTicks;

        currentTicks = SDL_GetTicks();

        _frameTime = currentTicks - previousTicks;
        frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

        previousTicks = currentTicks;

        int count;

        currentFrame++;
        if (currentFrame < NUM_SAMPLES)
        {
            count = currentFrame;
        }
        else
        {
            count = NUM_SAMPLES;
        }

        float frameTimeAverage = 0;

        for (int i = 0; i < count; i++)
        {
            frameTimeAverage += frameTimes[i];
        }

        // Average frame times
        frameTimeAverage /= count;

        if (frameTimeAverage > 0)
        {
            _fps = 1000.0f / frameTimeAverage;
        }
        else
        {
            _fps = 60;
        }
    }
}
