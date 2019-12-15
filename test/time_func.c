#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void main1(void)
{
// clock()	This function is used to get current system time
// time()	This function is used to get current system time as structure
// difftime()	This function is used to get the difference between two given times
// mktime()	This function interprets tm structure as calendar time
// ctime()	This function is used to return string that contains date and time informations
// asctime() Tm structure contents are interpreted by this function as calendar time.This time is converted into string.
}

void AutoUpdate()
{
	time_t mytime;
	clock_t wait_time;
	while(1){
		mytime = time(NULL);
		printf(ctime(&mytime));
		wait_time = clock() + 0.4 * CLK_TCK;
		while(clock()<wait_time){}
		system("cls");
	}
}

int main(int argc, char**argv)
{
	FILE *file;
	file = fopen("error.txt", "a"); // Appends to error log. Creates file when unavailble.
	
	time_t TimeStamp = time(NULL);
	fprintf(stdout, ctime(&TimeStamp));
	fprintf(file, ctime(&TimeStamp));

	system("a.exe");


	return 0;
}