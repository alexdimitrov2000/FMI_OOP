#include <ctime>
#include "DateHelper.h"

Date DateHelper::getTodaysDate() {
	time_t ttime = time(0);
	struct tm now;
	localtime_s(&now, &ttime);

	Date today(now);

	return today;
}