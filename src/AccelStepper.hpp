#pragma once
#include <Arduino.h>

class AccelStepper {
    public:
        AccelStepper(uint8_t pulPin, uint8_t dirPin, uint8_t enPin, Tc* timerCounter);
        ~AccelStepper();

        void setPinsInverted(bool pulInvert, bool dirInvert, bool enInvert);
        void enableOutput();
        void disableOutput();

        void setOrigin();
        void setDisplacement(int32_t x);
        void setVelocity(float v);
        void setAcceleration(float a);

        int32_t getDisplacement();
        float getVelocity();

        void run();
        void stop();

    private:
        uint8_t pins[3];
        Tc* tc;
        bool pinsInverted[3] = {false, false, false};

        int32_t currentPosition = 0;
        int32_t targetPosition = 0;
        bool direction = false;
        float speed = 0.0;
        float acceleration = 0.0;

        float sqrtTwoAcceleration = 0.0;

        float computeNewSpeed();
};