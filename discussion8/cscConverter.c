#include <stdio.h>
#include <stdlib.h>

#define CELL_WIDTH 25

void convertCSV()
{
    int number;
    int delimiter;

    // Read integer + convert to scientific notation
    while (scanf("%d%c", &number, &delimiter) == 2)
    {
        // Print scientific notation w. left-alignment and padding
        printf("%-25e", (double)number);

        // If delimiter a new line, start new row
        if(delimiter == '\n')
        {
            printf("\n");
        }
        else if (delimiter != ',')
        {
            // Unexpected delimiter
            fprintf(stderr, "Unexpected delimiter: %c\n", delimiter);
            exit(1);
        }
        else
        {
            // If delimiter a comma, print tab
            printf("\t");
        }
        
    }
}

int main()
{
    printf("Enter a table of integers in CSV format:\n");
    convertCSV();
    return 0;
}