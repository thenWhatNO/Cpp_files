#include <stdio.h>

int main() {

    char grid[10][20];

    for (int i = 0; i < 10; i++){
        for (int k = 0; k < 20; k++){
            grid[i][k] = ' ';
        }
    }
    
    for(int j = 0; j < 10; j++){
            printf("%s", grid[j]);
    }
    
    //printf("%d\n", grid[0][0]);
    
    return 0;
}

