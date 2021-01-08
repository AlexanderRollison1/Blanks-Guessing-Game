//Alexander Rollison

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GameLib.h"
#include "FileLib.h"

int main(int argc, char *argv[])
{
	GLS Game[MAX_ENTRIES] = {};
	/*
	int d;
	for(d = 0; d < MAX_ENTRIES; d++)
	{
		Game[d].name = {};
		Game[d].genre = {};
		Game[d].year = {};
		Game[d].developer = {};
	}
	*/
	char ChosenPhrase[100];
	FILE *FH;
	char mode[2] = "r+";
	int SC = 0;
/*Creating a file and mode to hold the CLPs and passing them to OpenFile() which will validate the
file and return the file handle which we will use throughout the assignment. */
	if(argc < 1)
	{
		printf("\n\nNeeds 2 command line parameters\n Parameters : Code7.e FILENAME=xxxx.txt\n\nExiting...\n\n");
		exit(0);
	}
	FH = OpenFile(argc, argv, mode);
	
/*We are passing the main struct array and File Handle to the Startgame function which will return
the User Inputted choice (-1 to be used with arrays). This function will also be what Displays the 
array, meaning we will use function ReadFileIntoArray in order to use strtok to put each string 
into its specifiedspot in the struct.*/

		SC = StartGame(FH, Game, ChosenPhrase);
		char UpperPhrase[strlen(ChosenPhrase)];
		//UpperPhrase[strlen(UpperPhrase)] = '\0';
////Uppercasing and putting into UpperPhrase
		int k;
		for(k = 0; k < strlen(ChosenPhrase); k++)
		{
			if(islower(ChosenPhrase[k]) && isalpha(ChosenPhrase[k]))
			{
				UpperPhrase[k] = toupper(ChosenPhrase[k]); 
			}
			else
			{
				UpperPhrase[k] = ChosenPhrase[k];
			}
		}
//// Using DashIt function to replace all of the characters of the array with a dash for the game.
		
		char DashedPhrase[strlen(ChosenPhrase)];		
		DashIt(ChosenPhrase, DashedPhrase);	
		DashedPhrase[strlen(DashedPhrase)] = '\0';
		printf("",ChosenPhrase,strlen(ChosenPhrase),DashedPhrase,strlen(DashedPhrase),UpperPhrase,strlen(UpperPhrase));		
//// From here, the code is just like the past assignment until right after the do while loop.
		int Strike = 0;
		do
		{
			if (GuessALetter(ChosenPhrase, DashedPhrase, UpperPhrase) == 0)
			{
				Strike++;
				printf("Strike %d\n", Strike);
				if(Strike == STRIKES)
				{
					printf("%d STRIKES - YOU'RE OUT!!\n\n", STRIKES);
					printf("Game over");
					exit(0);
				}
			}
		}
		while(strchr(DashedPhrase,'-') != NULL && Strike < STRIKES);

//// Did the player win this time? After this, we will continue the loop until there are 0 phrases.
		if(Strike < STRIKES)
		{
			printf("You figured it out!!\n\n");
			printf("The phrase was\n%s\n\n",Game[SC].genre);
			printf("YOU WIN!!!!\n");
			NewFile(FH, Game,SC);
		}
		else
		{
			printf("%d STRIKES - YOU'RE OUT!!\n\n", STRIKES);
			printf("Game over");
		}
	return 0;
}
