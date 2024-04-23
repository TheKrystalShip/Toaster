#pragma once

namespace Toaster
{
    class FpsLimiter
    {
    public:
        FpsLimiter();
        void init(float targetFps);

        void setMaxFps(float targetFps);

        void begin();
        float end();

    private:
        void calculateFps();

        float _fps;
        float _maxFps;
        float _frameTime;
        unsigned int _startTicks;
    };
}
