//Alexander Rollison
#ifndef GameLib_H
#define GameLib_H
#define MAX_ENTRIES 5
#define STRIKES 3

typedef struct
{
	char *name;
	char *genre;
	char year[4];
	char *developer;
}GLS;

int StartGame(FILE *FH, GLS Phrases[], char ChosenPhrase[]);
void CheckPhrase(char *Phrase);
int GuessALetter(char Phrase[],char DashedPhrase[],char UpperPhrase[]);
void DashIt(char *Phrase, char DashedPhrase[]);
#endif
