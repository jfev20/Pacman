#ifndef CLOCK_H
#define CLOCK_H

class Clock {

private:

	

public:
	Clock();
	~Clock();
	float time = 0.f;
	float length = 0.f;
	void SetAnimationLength(float aTime);
	void IncrementTime(float aTime);
	void ResetTime();
	bool Compare();

};





#endif // CLOCK_H