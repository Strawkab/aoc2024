#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void *a, const void *b) 
{
    return (*(int *)a - *(int *)b);
}

int main (int argc, char** argv) 
{
    FILE *file_ptr;
    char ch;
    int lines_in_file = 0; //hardcoded oops

    file_ptr = fopen(argv[1], "r");

    if (NULL == file_ptr) {
        printf("file can't be opened \n");

        return EXIT_FAILURE;
    }

    for (ch = getc(file_ptr); ch != EOF; ch = getc(file_ptr)) {
        if (ch == '\n') {
            lines_in_file++;
        }
    }
    rewind(file_ptr);

    printf("%d\n", lines_in_file);

    int left_array[lines_in_file], right_array[lines_in_file];
    int left_int, right_int;
    int counter = 0;

    while (fscanf(file_ptr, "%d   %d", &left_int, &right_int) != EOF) {
        printf("%d %d\n", left_int, right_int);
        left_array[counter] = left_int;
        right_array[counter] = right_int;
        counter++;
    }

    qsort(left_array, lines_in_file, sizeof(int), comp);
    qsort(right_array, lines_in_file, sizeof(int), comp);
    for (counter = 0; counter < lines_in_file; counter++) {
        printf("%d %d\n", left_array[counter], right_array[counter]);
    }

    int difference;
    int sum_of_differences;
    for (counter = 0; counter < lines_in_file; counter++) {
        difference = abs(left_array[counter] - right_array[counter]);
        printf("abs(%d - %d) = %d\n", left_array[counter], right_array[counter], difference);
        sum_of_differences += difference;
    }

    printf("%d\n", sum_of_differences);

    fclose(file_ptr);
    return 0;
}
