#include <stdio.h>
#include <time.h>

void main1(void)
{
// clock()	This function is used to get current system time
// time()	This function is used to get current system time as structure
// difftime()	This function is used to get the difference between two given times
// mktime()	This function interprets tm structure as calendar time
// ctime()	This function is used to return string that contains date and time informations
// asctime()	Tm structure contents are interpreted by this function as calendar time. This time is converted into string.	
}

void wait(int duration)
{
	clock_t end_wait;
	end_wait = clock() + duration * CLK_TCK;

	while(clock()<end_wait){}
}

int main(void)
{
	time_t mytime = time(NULL);
	printf(ctime(&mytime));

	printf("Enter seconds to wait: ");
	int wait_time;
	scanf("%d", &wait_time);

	printf("Start the Wait!\n");
	wait(wait_time); // Fix the overhead that happen when var is used
	printf("End Wait!\n");


	mytime = time(NULL);
	printf(ctime(&mytime));

	return 0;
}