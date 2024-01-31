#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>  // Include this for open and O_RDONLY


typedef struct {
    long points_inside;
    long points_total;
    int num_restart;
} YourStruct;

int main() {
    YourStruct s;

    int file_descriptor = open("../build/backup_file", O_RDONLY);
    if (file_descriptor == -1) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    // Read the long values
    read(file_descriptor, &(s.points_inside), sizeof(long));
    read(file_descriptor, &(s.points_total), sizeof(long));

    // Read the int value
    read(file_descriptor, &(s.num_restart), sizeof(int));

    // Close the file
    close(file_descriptor);

    // Process the read data as needed
    printf("points_inside: %ld\n", s.points_inside);
    printf("points_total: %ld\n", s.points_total);
    printf("num_restart: %d\n", s.num_restart);

    return 0;
}

