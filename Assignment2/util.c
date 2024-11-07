#include"find.h"

//this function finds an occurrence of needle in haystack
//needle must be matched with a whole word in haystack...
char *strstr_fully_matched(char *haystack, char *needle) {
  char *rv;
  char padded_needle[strlen(needle) + 3];
  padded_needle[0] = ' ';
  strcpy(padded_needle + 1, needle);
  padded_needle[strlen(needle) + 1] = ' ';
  padded_needle[strlen(needle) + 2] = '\0';//pad the needle w/ spaces before and after
  if(!strcmp(needle, haystack))
	  return haystack;// needle matches the whole haystack
  if (!strncmp(haystack, padded_needle + 1, strlen(needle) + 1)) {
    return haystack; // needle is at the beginning of haystack
  }
  if ((rv = strstr(haystack, padded_needle)) != NULL) {
    return rv + 1; // needle is at the middle of haystack.
  }
  padded_needle[strlen(needle) + 1] = '\0';//remove the last space
  if ((rv = strstr(haystack, padded_needle)) != NULL &&
      rv[strlen(padded_needle)] == '\0') {
    return rv + 1; // needle is at the end of haystack.
  }
  return NULL;
}
//
// New wrapper function
char* strstr_fully_matched_with_flags(char* haystack, char* needle, flags option) {
    // If CASE is set, you might want to convert both strings to lowercase
    if (option & CASE) {
        // Use to_lower if you have implemented it or handle it inline here
        // Example: to_lower(haystack); to_lower(needle);
    }
    
    return strstr_fully_matched(haystack, needle); // Call the original function
}
//
//lowers the case of each character in its input string
void to_lower(char* input){
	for(int i = 0;i < strlen(input);i++)
		input[i] = tolower(input[i]);
}
//this function finds an occurrence of needle in haystack
//option specify case-sensitivity of search and whether needle should match a whole word
char* strstr_w_option(char* haystack, char* needle, flags option){
	if(option & CASE){
		to_lower(haystack = strdup(haystack));
		to_lower(needle = strdup(needle));
		if(option & MATCHED)
			return strstr_fully_matched(haystack, needle);
		else
			return strstr(haystack, needle);
	}else if(option & MATCHED)
		return strstr_fully_matched(haystack, needle);
	else
		return strstr(haystack, needle);
}
//subroutine used in qsort
static void swap(char** v, int i, int j){ // void**
  char* temp = v[i]; // void*
  v[i] = v[j];
  v[j] = temp;
}
//quick sort on array of strings
void quicksort(char*str[], int left, int right){
  int i, last;
  if(left >= right)
    return;
  swap(str, left, left + (right-left)/2);
  last = left;
  for(i = left + 1; i <= right;i++)
    if(strcmp(str[i],str[left]) < 0)
      swap(str, ++last, i);
  swap(str, left, last);
  quicksort(str, left, last-1);
  quicksort(str, last+1, right);
}

void reverse(char* lineptr[], int nlines) {
    for (int i = 0, j = nlines - 1; i < j; i++, j--) {
        char* temp = lineptr[i];
        lineptr[i] = lineptr[j];
        lineptr[j] = temp;
    }
}


void partial(char* line, char* pattern, flags option)
 {
    int line_len = strlen(line);
    int pattern_len = strlen(pattern);
    char* occurrence;

    // If no occurrence is found, just print the line normally
    if (!occurrence) {
        printf("%s\n", line);
        return;
    }

    int start_index = occurrence - line;
    int end_index = start_index + pattern_len;

    // Condition 1: Length of line is not greater than pattern length + 15
    if (line_len <= pattern_len + 15) {
        printf("%s\n", line);
        return;
    }

    // Condition 2: Print first 10 characters of the line, followed by ellipsis if necessary
    if (start_index > 10) {
        printf("%.10s...", line); // Print first 10 characters with ellipsis
    } else {
        printf("%.*s", start_index, line); // Print up to the match (no ellipsis)
    }

    // Condition 3: Print the pattern
    printf("%s", pattern);

    // Condition 4: Print last five characters of the line, followed by ellipsis if necessary
    if (line_len - end_index > 5) {
        printf("...%.5s\n", line + line_len - 5); // Print last 5 characters with ellipsis
    } else {
        printf("%s\n", line + end_index); // Print remaining characters
    }
}


