#include "AccelStepper.hpp"

AccelStepper::AccelStepper(uint8_t pulPin, uint8_t dirPin, uint8_t enPin, Tc* timerCounter):
    pins{pulPin, dirPin, enPin},
    tc(timerCounter)
{}

AccelStepper::~AccelStepper() {

}

void AccelStepper::setPinsInverted(bool pulInvert, bool dirInvert, bool enInvert) {
    pinsInverted[0] = pulInvert;
    pinsInverted[1] = dirInvert;
    pinsInverted[2] = enInvert;
}

void AccelStepper::enableOutput() {
    pinMode(pins[0], OUTPUT);
    pinMode(pins[1], OUTPUT);
    pinMode(pins[2], OUTPUT);
    digitalWrite(pins[2], HIGH ^ pinsInverted[2]);
}

void AccelStepper::disableOutput() {
    digitalWrite(pins[2], LOW ^ pinsInverted[2]);
}

void AccelStepper::setOrigin() {
    currentPosition = 0;
}

void AccelStepper::setDisplacement(int32_t x) {
    targetPosition = x;
}

void AccelStepper::setVelocity(float v) {
    speed = fabs(v);
    direction = (bool)(v >= 0);
}

void AccelStepper::setAcceleration(float a) {
    acceleration = a;
    sqrtTwoAcceleration = sqrt(2.0 * fabs(a));
}

int32_t AccelStepper::getDisplacement() {
    return currentPosition;
}

float AccelStepper::getVelocity() {
    return (direction ? speed : -speed);
}

void AccelStepper::run() {
    
}

void AccelStepper::stop() {
    
}

// assume initial speed is not zero
float AccelStepper::computeNewSpeed() {
    if (acceleration == 0.0)
        return speed;

    if (direction == (acceleration > 0))
        return speed + fabs(acceleration) / speed;
    else
        return max(sqrtTwoAcceleration, speed - fabs(acceleration) / speed);
}