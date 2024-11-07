#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <ctype.h>

extern char*lineptr[];
#define MAX_LINES 1000
#define MAX_LEN 1000
typedef enum{	// (enumerator: define list of constants with certain value)
	NUMBERED = 1,//righttmost bit
	EXCEPT = 1 << 1,//second rightmost bit
	SORTED = 1 << 2,//third bit
	REVERSED = 1 << 3,//fourth bit
	MATCHED = 1 << 4,//fifth bit
	CASE = 1 << 5,//sixth bit
	FIRST = 1 << 6,//seventh bit
	PARTIAL = 1 << 7,//eigth bit
}flags;
char* strstr_w_option(char* haystack, char* needle, flags option);
void quicksort(char*str[], int left, int right);

void partial(char* line, char* pattern, flags option);
void to_lower(char* input);
char *strstr_fully_matched(char *haystack, char *needle);
char* strstr_fully_matched_with_flags(char* haystack, char* needle, flags option);

