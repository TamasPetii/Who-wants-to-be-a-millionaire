#include "Time.h"

std::string Time::To_String() {
	int hour = secundum / 3600;
	int min = secundum % 3600 / 60;
	int sec = secundum % 3600 % 60;
	return (hour < 10 ? "0" : "") + std::to_string(hour) + ":" + (min < 10 ? "0" : "") + std::to_string(min) + ":" + (sec < 10 ? "0" : "") + std::to_string(sec);
}