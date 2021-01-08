//Alexander Rollison

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GameLib.h"
#include "FileLib.h"

int StartGame(FILE *FH, GLS Phrases[], char ChosenPhrase[])
{
	int GameNumber = ReadFileIntoArray(FH,Phrases);
	int choice;
//// Making sure the game is still able to be played
	
	if (GameNumber == 0)
	{
		printf("\nAll of the games have been played - please reload file\n");
		exit(0);
	}
	printf("Welcome to the 3 STRIKES - YOU'RE OUT - the CSE version\n");
	
//// User input for SC / validation --> returning the User's choice -1

	do
	{
		printf("\nPlease pick a game from the following menu\n");
		
		printf("\n");
		int i = 1;
		while(i<=GameNumber)
		{
			if(i<=GameNumber)
			{
				printf("%d. %s is a game that was released in %s, created by %s's developers \n",i,Phrases[i-1].name,Phrases[i-1].year, Phrases[i-1].developer);
				i++;
			}
		}
		
		scanf("%d",&choice);
		if(choice <= 0 || choice > GameNumber)
		{
			printf("\nPlease enter a valid choice\n");
		}
	}
	while(choice <= 0 || choice > GameNumber);
	
	CheckPhrase(Phrases[choice-1].genre);
	strcpy(ChosenPhrase, Phrases[choice-1].genre);
	ChosenPhrase[strlen(ChosenPhrase)] = '\0';
	
	return choice-1;
}

//// Any phrase with - must be checked for.
void CheckPhrase(char *Phrase)
{
	int position;
	int i;
	if (strchr(Phrase, '-') != NULL)
	{
		for(i = 0; i < strlen(Phrase);i++)
		{
			if(Phrase[i] == '-')
			{
				position = i;
				i = strlen(Phrase);
			}
		}
		printf("\"%s\" contains a dash in position %d!!\n\n",Phrase,position+1);
		printf("You broke the rules. We can't play. BYE!!");
		exit(0);
	}
}

int GuessALetter(char Phrase[],char DashedPhrase[],char UpperPhrase[])
{
	char Guess;
	char *FindGuess = NULL;
	char GuessALetterCopy[strlen(Phrase)+1];
	int FoundALetter = 0;

	strcpy(GuessALetterCopy, UpperPhrase);
	printf("\n%s\n",DashedPhrase);
	printf("Guess a letter : ");
	scanf(" %c", &Guess);
	getchar();
	Guess = toupper(Guess);
	FindGuess = strchr(GuessALetterCopy,Guess);
	while(FindGuess != NULL)
	{
		FoundALetter = 1;
		DashedPhrase[FindGuess - GuessALetterCopy] = Phrase[FindGuess - GuessALetterCopy];
		*FindGuess = '-';
		FindGuess = strchr(GuessALetterCopy,Guess);
	}
	return FoundALetter;
}

void DashIt(char ChosenPhrase[], char DashedPhrase[])
{
	char *char_set = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;
	for(i = 0; i < strlen(ChosenPhrase); i++)
	{
		if(islower(ChosenPhrase[i]) && isalpha(ChosenPhrase[i]))
		{
			DashedPhrase[i] = toupper(ChosenPhrase[i]); 
		}
		else
		{
			DashedPhrase[i] = ChosenPhrase[i];
		}
	}
	DashedPhrase[strlen(DashedPhrase)] = '\0';
	char *Occur = strpbrk(DashedPhrase, char_set);
	while(Occur != NULL)
	{
		*Occur = '-';
		Occur = strpbrk(DashedPhrase, char_set);
	}
}

