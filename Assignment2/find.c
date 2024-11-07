#include"find.h"
char*lineptr[MAX_LINES];
int readlines(){ // read lines from input and store in data structure
	int len, nlines;
	char*p, line[MAX_LEN];
	nlines = 0;
	while(fgets(line, MAX_LEN, stdin)){
		len = strlen(line);
		if(nlines >= MAX_LINES || (p = malloc(len + 1)) == NULL)
			return -1;
		else{
			if(line[len - 1] == '\n')//droping the newline at the end...
				line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}
void error(int error_code){
	printf("find: fatal error - Illegal usage. Error code: %d. Usage: \"%s\"\n",
	error_code, "find [-n] [-x] [-s] [-r] [-m] [-c] [-f] [-p] pattern");
	exit(error_code);
}
flags set_flags(int argc, char** argv){
	flags option = 0;//By default, all flags are down!
	for(int i = 1; i < argc - 1;i++){
		if(argv[i][0] != '-')//if argument doesn't start with -
			error(2);
		for(int j = 1; argv[i][j] != '\0';j++)
			switch(argv[i][j]){ // |= or equal 
				case 'n':case 'N':
				option |= NUMBERED;
				break;
				case 'x':case 'X':
				option |= EXCEPT;
				break;
				case 's':case 'S':
				option |= SORTED;
				break;
				case 'r':case 'R':
				option |= REVERSED;
				break;
				case 'm':case 'M':
				option |= MATCHED;
				break;
				case 'c':case 'C':
				option |= CASE;
				break;
				case 'f':case 'F':
				option |= FIRST;
				break;
				case 'p':case 'P':
				option |= PARTIAL;
				break;
				default: 
				error(3);
			}
	}
	return option;
}
/*
* Program find is used to find the occurrences of a given pattern in stdin
* Assumption is that stdin is made of multiple lines (no more than 1000)
* Program tries finding the pattern in each line.
* The pattern is given to the program as the last command-line argument
* There are multiple options for running this program, all passed in CLAs
* Usage: find [-n] [-x] [-s] [-r] [-m] [-c] [-f] [-p] pattern
* -n: prints the line number in the output
* -x: prints out the lines that don't have the pattern
* -s: prints out the lines in alphabetical order
* -r: prints out the lines in reverse order (LIFO)
* -m: finds the pattern only if it matches a whole word in stdin
* -c ignore the case when finding the pattern string
* -f: prints out the index of first occurrence of pattern found in each line
* -p: partially prints out the input lines. Uses ellipsis to shorten lines.
******e.g. if we look for "apple" in "my favorite dessert is apple pie with coffee"
****** then the output is "my favorit...apple...offee"
*/


int main(int argc, char** argv) // argc represents how many arguments, argv is list of all arguments
{
	if(argc < 2) // must have at least one command argument
		error(1); // void error ^
	char* pattern = strdup(argv[argc - 1]);// the last CommandLineAargument is considered to be the pattern
	flags option = set_flags(argc, argv); // flags (In find.h) (enumerator: define list of constants with certain value)
	if((option & REVERSED) && (option & SORTED)) // r and s cannot be used together
		error(4);//cannot print the output using both sorted and reversed options...

	if((option & FIRST) && (option & EXCEPT)) // f and x cannot be used together
		error(4); 
	
	if((option & PARTIAL) && (option & EXCEPT)) // p and x cannot be used together
		error(4);

int nlines = readlines(lineptr);  // readlines() returns the number of lines // **Maybe erase lineptr**
/*
	if(option & REVERSED)
	{
		reverse(lineptr, nlines);
		for (int i=0; i < nlines; i++)
		{
			print_line(lineptr[i], option);
		}
		return 0;
	}
*/

	if(option & SORTED)
	{
		quicksort(lineptr, 0, nlines - 1);
	}

	char initial[10] = "";
	for(int i = 0; i < nlines;i++)
	{//first in first out
		if(option & NUMBERED)
		{
			sprintf(initial, "%d. ", i + 1);
		}

		//search for pattern in current line
		char* first_occurrence = strstr_w_option(lineptr[i], pattern, option);	

		if (option & FIRST) 
		{
            if (first_occurrence != NULL) {
                int index = first_occurrence - lineptr[i];  // Calculate the index of the first occurrence
                printf("%s%d: %s\n", initial, index, lineptr[i]);  // Print the line with the index
            }
			continue;
		}

		if (option & MATCHED)
		{
			if (!strstr_fully_matched_with_flags(lineptr[i], pattern, option)) 
			{
        		continue; // Skip this line if it doesn't fully match
   			}
		}
		

		
		char line_copy[MAX_LEN];	
		if (option & CASE) 
		{
			strcpy(line_copy, lineptr[i]);
			to_lower(line_copy);
            if (strstr_w_option(lineptr[i], pattern, option)) {
                if (option & PARTIAL) {
                    partial(lineptr[i], pattern, option);  // Handle partial print if -p flag is set
                } else {
                    printf("%s%s\n", initial, lineptr[i]);  // Print the full line with optional numbering
                }
            }
        } else {
            // If CASE is not set and there's a match, print line based on EXCEPT flag
            if (first_occurrence != NULL) 
			{
				if (option & PARTIAL)
				{
					 partial(lineptr[i], pattern, option);  // Handle partial print if -p flag is set
				}else{
                    printf("%s%s\n", initial, lineptr[i]);  // Print the full line with optional numbering
				}
			} else if (option & EXCEPT){
				// Print line if EXCEPT is set and pattern is not found
				printf("%s%s\n", initial, lineptr[i]);  // Print line if it does not contain the pattern
			}

                // Handle EXCEPT flag
                if ((option & EXCEPT) == 0) {
                    // Print the line normally if EXCEPT is not set
                    
                }
		}
	}

		//if except flag is up and pattern cannot be found in current line
		//or if except flag is down and pattern can be found in the current line

	free(pattern); // clean allocated memory
    return 0;
}