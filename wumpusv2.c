/* 
  WumpusV2
  Author: Sami Abu Shamat
*/

#include <ctype.h>
#include <stdbool.h> // for bool
#include <stdio.h>
#include <stdlib.h> // for srand

//--------------------------------------------------------------------------------
//function that displays the cave to the player
void displayCave() {
  printf("\n       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
}

// struct for game info
struct gameData {
  int movePosition;
  int moveCounter;
  int pit1Position;
  int pit2Position;
  int wumpusPosition;
  int playerPosition;
  int bats1Position;
  int bats2Position;
  int arrowPosition;
};

//--------------------------------------------------------------------------------
//function that displays the instructions
void displayInstructions() {
    displayCave();
    printf( "Hunt the Wumpus:                                             \n"
    		"The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
    		"room has 3 tunnels leading to other rooms.                   \n"
    		"                                                             \n"
    		"Hazards:                                                     \n"
        	"1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
        	"2. Two other rooms have super-bats.  If you go there, the bats grab you and     \n"
        	"   fly you to some random room, which could be troublesome.  Then those bats go \n"
        	"   to a new room different from where they came from and from the other bats.   \n"
    		"3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and    \n"
        	"   is too heavy for bats to lift.  Usually he is asleep.  Two things wake       \n"
        	"    him up: Anytime you shoot an arrow, or you entering his room.  The Wumpus   \n"
        	"    will move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
        	"    When you move into the Wumpus' room, then he wakes and moves if he is in an \n"
        	"    odd-numbered room, but stays still otherwise.  After that, if he is in your \n"
        	"    room, he snaps your neck and you die!                                       \n"
        	"                                                                                \n"
        	"Moves:                                                                          \n"
        	"On each move you can do the following, where input can be upper or lower-case:  \n"
        	"1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
        	"   then a room number.                                                          \n"
        	"2. Shoot your guided arrow through a list of up to three adjacent rooms, which  \n"
        	"   you specify.  Your arrow ends up in the final room.                          \n"
        	"   To shoot enter 'S' followed by the number of rooms (1..3), and then the      \n"
        	"   list of the desired number (up to 3) of adjacent room numbers, separated     \n"
        	"   by spaces. If an arrow can't go a direction because there is no connecting   \n"
        	"   tunnel, it ricochets and moves to the lowest-numbered adjacent room and      \n"
        	"   continues doing this until it has traveled the designated number of rooms.   \n"
        	"   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
        	"   automatically pick up the arrow if you go through a room with the arrow in   \n"
        	"   it.                                                                          \n"
        	"3. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
        	"4. Enter 'C' to cheat and display current board positions.                      \n"
        	"5. Enter 'D' to display this set of instructions.                               \n"
        	"6. Enter 'P' to print the maze room layout.                                     \n"
        	"7. Enter 'X' to exit the game.                                                  \n"
        	"                                                                                \n"
        	"Good luck!                                                                      \n"
        	" \n\n");
}//end displayInstructions()

//--------------------------------------------------------------------------------
//function that tells the user all of the game datas position for 'C' input
void displayGameItems(struct gameData game) {
  printf("Cheating! Game elements are in the following rooms: \n"
         "Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
         "%4d %5d %6d %5d %5d %5d %5d \n\n",
         game.playerPosition, game.wumpusPosition, game.pit1Position,
         game.pit2Position, game.bats1Position, game.bats2Position,
         game.arrowPosition);
}

//--------------------------------------------------------------------------------
// function that takes in user input and changes the positions of the game items
void resetPositions(struct gameData *game) {
  // vars for user input
  int pit1, pit2, wumpus, player, bats1, bats2, arrow = 0;
  //prompting for user input
  printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n\n");
  scanf("%d %d %d %d %d %d %d", &player, &wumpus, &pit1, &pit2, &bats1, &bats2,
        &arrow);
  ;
  //setting the struct data to the users data
  game->pit1Position = pit1;
  game->pit2Position = pit2;
  game->wumpusPosition = wumpus;
  game->playerPosition = player;
  game->bats1Position = bats1;
  game->bats2Position = bats2;
  game->arrowPosition = arrow;
}

//--------------------------------------------------------------------------------
// user guesses the wumpus's position if correct win if incorrect lose
void userGuess(struct gameData game) {
  // vars
  int userGuess = 0;
  //prompting user
  printf("Enter room (1..20) you think Wumpus is in: ");
  scanf(" %d", &userGuess);
  //if guess is correct you win
  if (userGuess == game.wumpusPosition) {
    printf("You won!\n");
    printf("\nExiting Program ...\n"); 
  } else {  // guess wrong you lose
    printf("You lost.\n");
    printf("\nExiting Program ...\n");
  }
}

//--------------------------------------------------------------------------------
// function to check if  two rooms are adjacent to each other
bool adjacentCheck(int **rooms,  // rooms array
                   int currentPos, // player room
                    int newPos) // user new room
{
  //checking all three adjacent rooms to the current pos
  if (rooms[currentPos][0] == newPos || rooms[currentPos][1] == newPos ||
      rooms[currentPos][2] == newPos) {
    return true;
  } else {
    return false;
  }
  //returning false if none are adjacent
}

//--------------------------------------------------------------------------------
int alreadyFound(int randomValue,      // New number we're checking
                 int *randomNumbers,  // Set of numbers previously found
                 int limit)            // How many numbers previously found
{
    int returnValue = false;
    
    // compare random value against all previously found values
    for( int i = 0; i<limit; i++) {
        if( randomValue == randomNumbers[i]) {
            returnValue = true;   // It is already there
            break;
        }
    }
    
    return returnValue;
} 

//--------------------------------------------------------------------------------
// function that checks if a random number exsist in a 
bool existCheck(int *randomNumbers, int randomNumber, int size) {
  for (int i = 0; i < size; i++) {
    if (randomNumbers[i] == randomNumber) {
      return false;
    }
  }
  return true;
}
//----------------------------------------------------------------------
// function that gets sets unique values
void setUniqueValues(int *randomNumbers,   // Array of random numbers
                     int size)              // Size of random numbers array
{
    int randomValue = -1;
    
    for( int i = 0; i<size; i++) {
        do {
            randomValue = rand() % 20 + 1;   // random number 1..20
        } while (alreadyFound(randomValue, randomNumbers, i));
        randomNumbers[i] = randomValue;
    }
} 

//-------------------------------------------------------------------------------------
//function that retrieves 7 unique random integers to assign the positions for each game item
void initializeGame(struct gameData *game) {

  int *randomNumbers = malloc(7*sizeof(int));
  setUniqueValues(randomNumbers,7);
  //setting struct variables to random numbers
  game->playerPosition = randomNumbers[0];
  game->wumpusPosition = randomNumbers[1];
  game->pit1Position = randomNumbers[2];
  game->pit2Position = randomNumbers[3];
  game->bats1Position = randomNumbers[4];
  game->bats2Position = randomNumbers[5];
  game->arrowPosition = randomNumbers[6];
  // counter = 1
  game->moveCounter = 1;
  //freeing memory
  free(randomNumbers);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//Helper function that updates an array with the current position of all the game items, for looping and checking certain situations
void updateGameItems(int *gameItems,struct gameData game) {
  gameItems[0] = game.playerPosition;
  gameItems[1] = game.wumpusPosition;
  gameItems[2] = game.pit1Position;
  gameItems[3] = game.pit2Position;
  gameItems[4] = game.bats1Position;
  gameItems[5] = game.bats2Position;
  gameItems[6] = game.arrowPosition;
}

//------------------------------------------------------------------------------------------------------
void checkAdjHazards(struct gameData *game, int **rooms,int playerMove) {
  //checking if user walks over the arrow
  if(game->playerPosition == game->arrowPosition) {
    printf("Congratulations, you found the arrow and can once again shoot.\n");
    game->arrowPosition = -1;
  }
  //prompting the room
  printf("You are in room %d. ", playerMove);
  //setting vars equal to adjacent rooms for checking
  int room1 = rooms[playerMove][0];
  int room2 = rooms[playerMove][1];
  int room3 = rooms[playerMove][2];
  // if adjacent rooms contain the wumpus
  if (room1 == game->wumpusPosition||room2 == game->wumpusPosition|| room3 == game->wumpusPosition) {
    printf("You smell a stench.");
  } 
  // if adjacent rooms contain either pit
  if (room1 == game->pit1Position ||room2 == game->pit1Position||room3 == game->pit1Position||
      room1 == game->pit1Position ||room2 == game->pit1Position||room3 == game->pit1Position) {
    printf("You feel a draft.");
    }
  // if adjacent rooms contain either bats
  if (room1 == game->bats1Position ||room2 == game->bats1Position||room3 == game->bats1Position||
      room1 == game->bats2Position ||room2 == game->bats2Position||room3 == game->bats2Position) {
    printf(" You hear rustling of bat wings.");
  }
  printf("\n\n");
}

//------------------------------------------------------------------------------------------
//function that finds two new random numbers that are not equal to bats1 bats2 player or new player
void batTransporation(struct gameData *game,int *randomNumbers,int *gameItems) {
  int randomValue = rand() % 20 +1;
  //loops twice through
  for(int i = 0; i <2;i++)
    {
    // while the random value is equal to bats1 bats2 player or newplayer positions
    while(randomValue == gameItems[0]||randomValue == gameItems[4]||randomValue == gameItems[5]||randomValue ==randomNumbers[i-1])
    {
      randomValue = rand() % 20 + 1;
    }
    // adding positions to array
    randomNumbers[i] = randomValue;
  }
}

//-----------------------------------------------------------------------------------
// function that checks deadly or movement encounters
void checkHazards(struct gameData *game, int **rooms, int *gameItems) {
  int playerPos = game->playerPosition;
  int *randomNumbers = malloc(2*sizeof(int*));
  //player encounters wumpus in odd room
  if (playerPos == game->wumpusPosition &&
      game->wumpusPosition % 2 == 1) {
    game->wumpusPosition = rooms[game->wumpusPosition][0];
    printf("You hear a slithering sound, as the Wumpus slips away. \n"
           "Whew, that was close! \n");
  }
  // player encounters wumpus in even room
  if (playerPos == game->wumpusPosition) {
    printf("You briefly feel a slimy tentacled arm as your neck is snapped.\n"
           "It is over.\n");
    printf("\nExiting Program ...\n");
    exit(0);
  } 
  //player encounters a pit1 or pit2
  if (playerPos == game->pit1Position ||playerPos == game->pit2Position) {
    printf("Aaaaaaaaahhhhhh....   \n");
    printf("    You fall into a pit and die. \n");
    printf("\nExiting Program ...\n");
    exit(0);
    }
  // if player encounters bats1
  if (playerPos == game->bats1Position) {
    batTransporation(&game,randomNumbers,gameItems);
    game->playerPosition = randomNumbers[0];
    game->bats1Position = randomNumbers[1];
    printf("Woah... you're flying! \n");
    printf("You've just been transported by bats to room %d.\n",game->playerPosition); 
  }
  // if player encounters bat2
  if(playerPos == game->bats2Position) {
    batTransporation(&game,randomNumbers,gameItems);
    game->playerPosition = randomNumbers[0];
    game->bats2Position = randomNumbers[1];
    printf("Woah... you're flying!\n");
    printf("You've just been transported by bats to room %d.\n",game->playerPosition); 
  }
  free(randomNumbers);
}

//-----------------------------------------------------------------------------------
// function for user shooting arrow
int userArrow(struct gameData *game,int **rooms) {
  //array to hold all of the users requested rooms to guide the arrow

  int *arrowRooms = malloc(3*sizeof(int*));
  //incrementing the move counter
  game->moveCounter = game->moveCounter + 1;
  // variable for the number of requested cannot be greater than 3 
  int numberOfRooms = 0;
  // int i for while loop
  int i = 0;
  //user does not have the arrow;
  if(game->arrowPosition != -1)
  {
    printf("Sorry, you can't shoot an arrow you don't have. Go find it.\n");
    fflush(stdin);
    return 0;
  }
  //prompting user for input
  printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
  scanf("%d",&numberOfRooms);
  // if the user input a number greater than 3 prompt user and change the number to 3
  if(numberOfRooms > 3) {
    printf("Sorry, the max number of rooms is 3.  Setting that value to 3.");
    numberOfRooms = 3;
  }
  //taking in input and adding it to an array
  while(i < numberOfRooms && scanf("%d", &arrowRooms[i]) == 1) {
    i++;
   }
   fflush(stdin);
  game->arrowPosition = game->playerPosition;
  int arrowPos = game->arrowPosition;
  bool ricochetValue = false;
  //checks if the rooms selected are adjacent or not
  for(int i = 0; i<numberOfRooms;i++) {
    if(adjacentCheck(rooms,arrowPos,arrowRooms[i])) {
      arrowPos = arrowRooms[i];
    } else { // if not adjacent the arrow ricochets
      printf("Room %d is not adjacent.  Arrow ricochets...\n", arrowRooms[i]);
      ricochetValue = true;
      arrowPos = rooms[arrowPos][0];
    }
  }
  //updates positon
  game->arrowPosition = arrowPos;
  //arrow hits player and ricochets
  if(game->arrowPosition == game->playerPosition&& ricochetValue == true) {
    printf( "You just shot yourself, and are dying.\n"
            "It didn't take long, you're dead.\n");
    printf("\nExiting Program ...\n");
    exit(0);
  }
  //arrow hits wumpus and ricochet
  else if(game->arrowPosition == game->wumpusPosition&& ricochetValue == true) {
  	printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
            "Accidental victory, but still you win!\n");
    printf("\nExiting Program ...\n");
    exit(0);
  }
  // arrow hits player
  if(game->arrowPosition == game->playerPosition) {
    printf( "You just shot yourself.  \n"
      "Maybe Darwin was right.  You're dead.\n");
     printf("\nExiting Program ...\n");
     exit(0);
  }
  // arrow hits wumpus
  if(game->arrowPosition == game->wumpusPosition) {
    printf( "Wumpus has just been pierced by your deadly arrow! \n"
            "Congratulations on your victory, you awesome hunter you.\n");
    printf("\nExiting Program ...\n");
    exit(0);
  }
  //wumpus moves to lowest adjacent room if not killed
  game->wumpusPosition = rooms[game->wumpusPosition][0];
  free(arrowRooms);
}

//--------------------------------------------------------------------------------
int main(void) {
  int **rooms = malloc(21 * sizeof(int*));
  for(int i = 0; i < 21;i++) {
    rooms[i] =(int*)malloc(sizeof(int)*3);
  }

  rooms[0][0] = 0;
  rooms[0][1] = 0;
  rooms[0][2] = 0;
  //room 1
  rooms[1][0] = 2;
  rooms[1][1] = 5;
  rooms[1][2] = 8;
  //room 2
  rooms[2][0] = 1;
  rooms[2][1] = 3;
  rooms[2][2] = 10;
  //room 3
  rooms[3][0] = 2;
  rooms[3][1] = 4;
  rooms[3][2] = 12;
  //room 4
  rooms[4][0] = 3;
  rooms[4][1] = 5;
  rooms[4][2] = 14;
  //room 5
  rooms[5][0] = 1;
  rooms[5][1] = 4;
  rooms[5][2] = 6;
  //room 6
  rooms[6][0] = 5;
  rooms[6][1] = 7;
  rooms[6][2] = 15;
  //room 7
  rooms[7][0] = 6;
  rooms[7][1] = 8;
  rooms[7][2] = 17;
  //room 8
  rooms[8][0] = 1;
  rooms[8][1] = 7;
  rooms[8][2] = 9;
  //room 9
  rooms[9][0] = 8;
  rooms[9][1] = 10;
  rooms[9][2] = 18;
  //room 10
  rooms[10][0] = 2;
  rooms[10][1] = 9;
  rooms[10][2] = 11;
  //room 11
  rooms[11][0] = 10;
  rooms[11][1] = 12;
  rooms[11][2] = 19;
  //room 12
  rooms[12][0] = 3;
  rooms[12][1] = 11;
  rooms[12][2] = 13;
  // room 13
  rooms[13][0] = 12;
  rooms[13][1] = 14;
  rooms[13][2] = 20;
  //room 14
  rooms[14][0] = 4;
  rooms[14][1] = 13;
  rooms[14][2] = 15;
  //room 15
  rooms[15][0] = 6;
  rooms[15][1] = 14;
  rooms[15][2] = 16;
  //room 16
  rooms[16][0] = 15;
  rooms[16][1] = 17;
  rooms[16][2] = 20;
  //room 17
  rooms[17][0] = 7;
  rooms[17][1] = 16;
  rooms[17][2] = 18;
  //room 18
  rooms[18][0] = 9;
  rooms[18][1] = 17;
  rooms[18][2] = 19;
  //room 19
  rooms[19][0] = 11;
  rooms[19][1] = 18;
  rooms[19][2] = 20;
  //room 20
  rooms[20][0] = 13;
  rooms[20][1] = 16;
  rooms[20][2] = 19;
  srand(1);
  struct gameData game;
  char userInput;
  initializeGame(&game);
  int *gameItems = malloc(sizeof(int*)*7);
  //while loop for game
  while (1) {
    // checks adjacent hazard
    checkAdjHazards(&game, rooms,game.playerPosition);
    //prompts move
    printf("%d. Enter your move (or 'D' for directions): ", game.moveCounter);
    //update game items
    updateGameItems(gameItems,game);
    scanf(" %c", &userInput);
    //sets user input to capital
    userInput = toupper(userInput);
    // user wants to exit
    if (userInput == 'X')  {
      printf("\nExiting Program ...\n");
      exit(0);
     }  else if (userInput == 'P') { //user wants to display  cave
      displayCave();
     }  else if (userInput == 'D') { //user wants to display instructions
      displayInstructions();
     }  else if (userInput == 'M') { //user wants to move
      int playerMove = 0;
      scanf(" %d", &playerMove);
      // if user input is adjacent
      if (adjacentCheck(rooms, game.playerPosition, playerMove)) {
        //update positon and check hazards, and update move counter 
        game.playerPosition = playerMove;
        checkHazards(&game,rooms,gameItems);
        game.moveCounter = game.moveCounter + 1;
      } else {
        printf("Invalid move.  Please retry. \n");
        continue;
       }
     } else if(userInput == 'S') { //users wants to shoot
        userArrow(&game,rooms);
      } else if (userInput == 'C')  {//user wants to see game elements
      displayGameItems(game);
      }  else if (userInput == 'R') { //user wants to reset positions
      resetPositions(&game);
      }  else if (userInput == 'G') { //user guess wants to guess where the wumpus is
      userGuess(game);
      exit(0);
    } else {
      printf("Invalid move.  Please retry. \n");
     }
  }

  //freeing memory
  free(rooms);
  return 0;
}