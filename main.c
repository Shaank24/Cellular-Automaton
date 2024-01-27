// Program 1: Elementary Cellular Automaton
// Course: CS 211, Fall 2023, UIC
// System: Advanced zyLab
// Author: Shaan Kohli

#include <stdio.h>
#include <stdbool.h> 

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    bool state[3]; //active status for [left, me, right] cells 
    bool active; //current active status for this cell
} cell;

//convert an 8-bit integer rule (0-255) to array of bits 
//(stored in reverse order). Parameters include the rule number and the 8 digit bit array
//return true if input rule is valid (0-255)
//return false if input rule is invalid
bool setBitArray(bool bitArray[8], int rule) {

        // Makes sure rule is valid and converts to bit array
        if (rule >= 0 && rule <= 255) {
            for (int i = 0; i < 8; i++) {
                bitArray[i] = rule % 2;
                rule /= 2;
            }
            return true;
        }
        return false;
}

//convert a 3-bit state array to its 
//associated index of the rule# bit array and return the index
int stateToIndex(bool state[3]) {
    int idx = 0;

    if (state[0] == 1) {
        idx += 4;
    }

    if (state[1] == 1) {
        idx += 2;
    }
 
    if (state[2] == 1) {
        idx += 1;
    }

    return idx;
}

//update the state array for each cell in the world array based on the
//current status of active for the nearby [left,me,right] cells
//note: world is assumed periodic/cyclic, with front-to-back and back-to-front wrapping
// No return
void setStates(cell world[WORLD_SIZE]) {

    //TODO: Task 5 - write the setStates() function
    for (int i = 1; i < WORLD_SIZE - 1; i++) {
        world[i].state[0] = world[i-1].active;
        world[i].state[1] = world[i].active;
        world[i].state[2] = world[i+1].active;
      
    }

    // Loop from end to beginning
    world[0].state[0] = world[WORLD_SIZE - 1].active;
    world[0].state[1] = world[0].active;
    world[0].state[2] = world[1].active;

    // Loop from end to beginning
    world[WORLD_SIZE - 1].state[0] = world[WORLD_SIZE - 2].active;
    world[WORLD_SIZE - 1].state[1] = world[WORLD_SIZE - 1].active;
    world[WORLD_SIZE - 1].state[2] = world[0].active;
}

//evolve each cell's active status to the next generation using its state array
//ruleBitArray contains the 8-bits for the rule#, stored in reverse order
// No return
void evolveWorld(cell world[WORLD_SIZE], bool ruleBitArray[8]) {

    //TODO: Task 7 - write the evolveWorld() function
    cell tempWorld[WORLD_SIZE];

    for (int i = 0; i < WORLD_SIZE; i++) {
        int index = stateToIndex(world[i].state);

        tempWorld[i].active = ruleBitArray[index];
    }

    for (int i = 0; i < WORLD_SIZE; i++) {
        world[i].active = tempWorld[i].active;
    }

}


int main() {
    cell world[WORLD_SIZE];

    printf("Welcome to the Elementary Cellular Automaton!\n");

    //Reads in a valid rule# and generate the rule's 8-bit rule bit array 
    //print the bit array in correct binary number order
    int rule = -1;
    bool ruleBitArray[8];

    printf("Enter the rule # (0-255): ");
    scanf("%d", &rule);
    while(setBitArray(ruleBitArray, rule) == 0) {
        printf("Enter the rule # (0-255): ");
        scanf("%d\n", &rule);
    }

    printf("\n");
    printf("The bit array for rule #%d is ", rule);
    for (int i = 7; i >= 0; i--) {
        printf("%d", ruleBitArray[i]);
    }
        
    printf("\n\n");

    //Uses the rule bit array to report the evolution step for all possible cell states.
    //checks each number in bit array and prints out '*' or ' '
    printf("The evolution of all possible states are as follows:\n");
    printf("|***|   |** |   |* *|   |*  |   | **|   | * |   |  *|   |   |\n");
    for (int i = 7; i >= 0; i--) {
        if (ruleBitArray[i] == 0) {
            printf(" | |    ");
        } 
        else {
            printf(" |*|    ");
        }
    }
    printf("\n");

    //Reads in the total number of generation evolution steps from the user and initialize the world 
    //with ONLY the middle cell active

    int numGenerations;
    printf("\n");
    printf("Enter the number of generations: ");
    scanf("%d\n", &numGenerations);
    printf("\n");
    printf("Initializing world & evolving...\n");

    for (int i = 0; i < WORLD_SIZE; i++) {
        world[i].active = false;
    }

    // Gets access to middle cell
    int middleCell = WORLD_SIZE / 2;
    world[middleCell].active = true;

    setStates(world);

    // Gets initial state
    for (int i = 0; i < WORLD_SIZE; i++) {
        if (world[i].active) {
            printf("*");
        }
        else {
            printf(" ");
        }
    }
    printf("\n");


    //Evolves the world the user-specified number of generations, printing each active cell as '*' and
    // each non-active cell as ' ' after each evolution step to the next generation
    for (int i = 1; i < numGenerations; i++) {
        setStates(world);
        evolveWorld(world, ruleBitArray);

        for (int j = 0; j < WORLD_SIZE; j++) {
            if (world[j].active) {
                printf("*");
            }
            else {
                printf(" ");
            }
        }

        printf("\n");
    }
    
    return 0;
}
