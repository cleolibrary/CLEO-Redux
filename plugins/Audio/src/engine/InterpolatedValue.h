#pragma once

namespace audio
{
    // CLEO5's CInterpolatedValue, plus reset() for stream reuse.
    class CInterpolatedValue
    {
      public:
        CInterpolatedValue(float value) : currValue(value), targetValue(value) {}

        float value() const { return currValue; }
        float target() const { return targetValue; }

        void setValue(float target, float transitionTime)
        {
            targetValue = target;

            if (transitionTime <= 0.0f)
            {
                currValue = target;
                step      = 0.0f;
                return;
            }

            step = (targetValue - currValue) / transitionTime;
        }

        void update(float elapsedTime)
        {
            if (currValue == targetValue) return;

            currValue += step * elapsedTime;

            float remaining = targetValue - currValue;
            remaining *= (step > 0.0f) ? 1.0f : -1.0f;
            if (remaining <= 0.0f) // overshoot
                currValue = targetValue;
        }

        void finish() { currValue = targetValue; }

        bool transitioning() const { return currValue != targetValue; }

        void reset(float value)
        {
            currValue   = value;
            targetValue = value;
            step        = 0.0f;
        }

      private:
        float currValue   = 0.0f;
        float targetValue = 0.0f;
        float step        = 0.0f;
    };
} // namespace audio
