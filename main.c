//Totalistic Cellular Automaton 
//Elvin Garcia CS 211 project 1 
#include <stdio.h>
#include <stdbool.h>

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    int localSum; // total sum of local cells, [left] + [me] + [right]: possible values are 0-6
    int status;   // this cell's current status: 0, 1, or 2
    int count;    // running accumulated count of this cell's active status for all generations
} cell;


bool setValArray(int valArray[7], int rule) {
    if (rule < 0 || rule > 2186) {  // Validates the rule number is between 0 and 2186
        return false; 
    }
    // Convert rule number to base 3 and store each number in the valArray
    for (int i = 0; i < 7; ++i) { 
        valArray[i] = rule % 3;  // get the remainder / base 3 number
        rule = rule / 3;  // Move to the next ternary digit by dividing by 3
    }         
    return true;   
}
       

void EvolutionSteps(int valArray[7]) {
printf("Local Sum:   6       5       4       3       2       1       0      \n"); //display local sum and states - are always the same so just out put 
printf("States:    |+++|   |++-|   |++ |   |+- |   |-- |   |-  |   |   |    \n"); // the lines this exact way 
printf("                   |+-+|   |+ +|   |+ -|   |- -|   | - |            \n");   
printf("                   |-++|   | ++|   |-+ |   | --|   |  -|            \n");           
printf("                           |+--|   | +-|   |+  |                    \n");                   
printf("                           |-+-|   |- +|   | + |                    \n");                                   
printf("                           |--+|   | -+|   |  +|                    \n");                                  
printf("                                   |---|                            \n");    

printf("New Status: ");  // new status depends on rule number user enters so use a for l00P through the possiblities depending on users input;
for (int i = 6; i >= 0; --i) {
    switch(valArray[i]) {
        case 0:
        printf("| |     ");
    break;

case 1:
    printf("|-|     ");
    break;

case 2:
    printf("|+|     ");
    break;
  }
}
printf("\n\n");
}


void setSums(cell world[WORLD_SIZE]) { //  setsums function will bascially update array cells through calculating there local sum
    for(int i = 0; i < WORLD_SIZE; i++){ // fournloop to iterate through each cell size  WORLD_SIZE in array
       
       if (i == 0) { 
         world[i].localSum = world[WORLD_SIZE - 1].status + world[i].status + world[i + 1].status;
       } // first if statment is just for the first cell as its neighbor would be the last array cell so local sum is found through adding last ceel,current, and second cell

       else if (i == WORLD_SIZE - 1) {
        world[i].localSum =  world[i - 1].status + world[i].status + world[0].status;
       }  //else if is for the last cell where right neighnor is the first celll and the left is the second to last 

       else {
         world[i].localSum = world[i - 1].status + world[i].status + world[i + 1].status;
       } //else is for the rest as each cell local sum will be the sum of the left and right neighbors ontop of itself
   }
}

// validation function whhich requests user to enter valid number for gens inbetween 1 - 49
int ValidateGenerate() {
    int numgens; 
    while (1) { //while loop that makes sures user enters a valid input
         printf("Enter the number of generations (1-49): \n");
         scanf("%d", &numgens);
         if (numgens >= 1 && numgens <= 49) {
            return numgens; // retuen correct value 
         }
    }
}
// also a validation function for initial stat of 1 - 2
int ValidateInitialStatus() {
    int initStatus;
    while (1){ // another while loop to ensure they enter a correct value 
        printf("Enter the value (1 or 2) for the initial active cell: \n"); 
        scanf("%d", &initStatus); 
        if (initStatus == 1 || initStatus == 2){
            return initStatus;
        }
    }
}


void initalWORLD(cell world[WORLD_SIZE], int initStatus){ // initialize world with ceels set to zero and the special mid case 32
    for (int i = 0; i < WORLD_SIZE; ++i) {  //loop to make initialize alll cells to zero
        world[i].status = 0;
        world[i].count = 0;
    }
   int MID = WORLD_SIZE / 2;  // special middle cell case

   world[MID].status = initStatus;  // sets the middle status to users provided initial status 
   world[MID].count = initStatus ;  // sets the count of middle cell to user provided inital status to keep track of its activity

   setSums(world);  // goes through to update all cels local sum
}

void worldPrinted(cell world[WORLD_SIZE], int Sum){
    // simple for loop that goes through all cells in world size to print out the stauus of each cell
    for(int i = 0; i < WORLD_SIZE; ++i) {
        if(world[i].status == 2) {
            printf("+"); // healthy cell represetned by + 
        }
        else if (world[i].status == 1) {
            printf("-"); // at risk cells -
        }
        else {
            printf(" ");
        }
    }
    printf(" %d \n", Sum); // print sum of status values for generation
}

int evolveWorld(cell world[WORLD_SIZE], int ruleValArray[7]) {
      int Sum = 0; // track sum of status values
      int Nextstatus; // temp variable store the next values status for cells

      for (int i = 0; i < WORLD_SIZE; ++i) {
        Nextstatus = ruleValArray[world[i].localSum]; // get next status for cells depending on local sum and rukle arry
      
      world[i].count +=  Nextstatus; // count activity 
      world[i].status = Nextstatus; // update cell status to the next status 

      Sum += Nextstatus;   // add next status to total sum

    }
    setSums(world); // update local sums with new statuses
    
return Sum; // return the total sum after the evolve world happens 
}


void PrintGens(cell world[WORLD_SIZE], int valArray[7], int numGens) {
    int Sum; 
// loop through generations and evolve the world while getting sum of status values for generation
    for (int gen = 0; gen < numGens - 1; ++gen) { 
        Sum = evolveWorld(world, valArray);
        worldPrinted(world, Sum); // print the world  for generation
    }

    for (int i = 0; i < WORLD_SIZE; ++i) {
      printf("_");
    }
    // print __ line under the world that is the size width of world
    printf("\n");

    for (int i = 0; i < WORLD_SIZE; ++i) {
        if(world[i].count < 10) { // print space when count is less than 10
            printf(" ");
        }
        else {
            printf("%d",world[i].count / 10); //else print tens digit 
        }
    }

    printf("\n");
    
    // Print the ones digit of the count for each cell
    for (int i = 0; i < WORLD_SIZE; ++i) {
        if ( world[i].count == 0) {
            printf(" ");
        }
        else if (world[i].count != 0) {
            printf("%d", world[i].count % 10);
        }
    }
    printf("\n");
}

int main() { // main function
    cell world[WORLD_SIZE]; // array represent our WORLDDDDD
    int Rule, valArray[7], numGens, initStatus;  // declarations in main - 
    bool check = false; 
    
    printf("Welcome to the Totalistic Cellular Automaton!\n"); // WELCOME!

   // check if user Enters the rule # (0-2186)
   while(!check) {
    printf("Enter the rule # (0-2186): \n");
    scanf("%d", &Rule );
    check = setValArray(valArray, Rule); // if setValArray is true then check is true 
    }
    
    printf("\nThe value array for rule #%d is ", Rule);
    
    for (int i = 6; i >= 0; i--) { // i starts a 6 since valarray has 7 digits starting from zero goes through i greater than 0 to get all 
                                  // values in array , and decrement to put in reverse order.
        printf("%d", valArray[i]); //print each digit 
    }
    printf("\n\n");

    printf("The evolution of all possible states are as follows:\n");
    EvolutionSteps(valArray); // calls void function to print out states and then hoiw they evolve with based on rule 
    
    numGens = ValidateGenerate(); //ask and make sure user enters valid genteration 1 - 49 for the world call
    
    initStatus = ValidateInitialStatus(); // ask and ensure the user enters valid inital status 1 -2 call

    printf("\nInitializing world & evolving...\n"); 
    initalWORLD(world, initStatus); // initalize world call numGen set all cells to zero except the mid which holds users entered status 


    worldPrinted(world, initStatus); // print world before evolve 
    PrintGens(world, valArray, numGens); // evolve and print world for user entered generations 

    return 0;
}
