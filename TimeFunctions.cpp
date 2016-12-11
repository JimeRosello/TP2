#include <ctime>
#include "TimeFunctions.h"

unsigned int getMinutesSinceMidnight() {
	time_t seconds;
	seconds = time(NULL);
	return (((seconds + hoursOffsetFromUTC * 3600) % (24 * 3600)) / 60);
}
