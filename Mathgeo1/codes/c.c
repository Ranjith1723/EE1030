#include <stdio.h>

int main() {
    // Define the coordinates for points A, O, and C
    float x1 = 1.0, y1 = 2.0;  // Point A(1, 2)
    float x2 = 0.0, y2 = 0.0;  // Point O(0, 0)
    float y3 = 6.0;            // y-coordinate of point C (a, 6)
    
    // Open file to write
    FILE *file = fopen("coordinates.dat", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write the coordinates to the file in the format: x1 y1 x2 y2 a y3
    // Here, 'a' is left as a placeholder for Python to solve
    fprintf(file, "%f %f %f %f a %f\n", x1, y1, x2, y2, y3);

    // Close the file
    fclose(file);

    printf("Coordinates saved to coordinates.dat\n");
    return 0;
}

