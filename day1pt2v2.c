#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void *a, const void *b) 
{
    return (*(int *)a - *(int *)b);
}

int similarityScore(int left_array[], int right_array[], int len) //two sorted ascending arrays 
{
    //two pointer approach oh yea
    int left_pointer = 0, right_pointer = 0;
    int similarity_score = 0, appearances = 0;
    int matching_number;

    while(left_pointer < len && right_pointer < len) {
        //move along arrays until matching numbers are found
        if (left_array[left_pointer] < right_array[right_pointer]) {
            printf("%d %d\n", left_array[left_pointer], right_array[right_pointer]);
            left_pointer++;
        }

        if (left_array[left_pointer] > right_array[right_pointer]) {
            printf("%d %d\n", left_array[left_pointer], right_array[right_pointer]);
            right_pointer++;
        }
        
        if (left_array[left_pointer] == right_array[right_pointer]) {
            printf("match found\n");
            appearances = 0;
            matching_number = left_array[left_pointer];
            while (left_array[left_pointer] == matching_number) {
                appearances++;
                left_pointer++;
            }
            printf("appearances in left array: %d", appearances);

            while(right_array[right_pointer] == matching_number) {
                printf("add to score\n");
                similarity_score += appearances * matching_number;
                right_pointer++;
            }
            
        }
        
    }
    
    return similarity_score;
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

    printf("%d\n", similarityScore(left_array, right_array, lines_in_file));

   fclose(file_ptr);
    return 0;
}
