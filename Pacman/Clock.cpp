#include "Clock.h"

Clock::Clock() {

	this->time = 0.f;
	this->length = 0.f;

}

Clock::~Clock() {
}

void Clock::SetAnimationLength(float& aTime) {

	this->length = aTime;

}

void Clock::IncrementTime(float& aTime) {

	this->time += aTime;

}

void Clock::ResetTime() {

	this->time = 0.f;

}

bool Clock::Compare() {
	return time >= length;
}