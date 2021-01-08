//Alexander Rollison 1001681800

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "GameLib.h"
#include "FileLib.h"

FILE * OpenFile(int argc,char *argv[], char mode[])
{
	
	
	char filename[100] = {};
	FILE * FH;
	CLP(argv, "FILENAME=", filename);
	
	do
	{
		FH = fopen(filename, mode);
		if(FH == NULL)
		{
			printf("Could not open file named %s\n", filename);
			perror("PARAMETERS MUST BE: xxxxxxxxxx.e FILENAME=xxxxxxxx.xxxx");
			printf("Enter an existing filename at the prompt: ");
			scanf("%s",filename);
			FH = fopen(filename, mode);
		}
	}
	while(FH == NULL);		
	return FH;
	
	/*
	FILE *FH;
	char filename[100] = {};
	if(argc == 1)
	{
		printf("\nYou forgot the filename.Enter it here: ");
		scanf("%s",filename);
		FH = fopen(filename,mode);
	}
	else
	{
		strcpy(filename, argv[1]);
		FH = fopen(filename,mode);
	}
	while(FH == NULL)
	{
		printf("\nFile couldn't open, Enter a new filename\n");
		scanf("%s",filename);
		FH = fopen(filename,mode);
	}
	return FH;
	*/
}
int ReadFileIntoArray(FILE * FH, GLS Phrases[])
{
	char index[100];
	char *token = NULL;
	int count = 0;
	
	while(fgets(index, sizeof(index)-1,FH) && count < MAX_ENTRIES)
	{
		if(index[0] == ' ')
		{
			continue;
		}
		
		if(index[strlen(index)-1] == '\n')
		{
			index[strlen(index)-1] = '\0';
		}
		token = strtok(index,"|");
		Phrases[count].name = malloc(strlen(token)*sizeof(char)+1);
		strcpy(Phrases[count].name, token);
		///
		token = strtok(NULL,"|");
		Phrases[count].genre = malloc(strlen(token)*sizeof(char)+1);
		strcpy(Phrases[count].genre, token);
		///
		token = strtok(NULL,"|");
		strcpy(Phrases[count].year, token);
		///
		token = strtok(NULL,"|");
		Phrases[count].developer = malloc(strlen(token)*sizeof(char)+1);
		strcpy(Phrases[count].developer, token);
		if(Phrases[count].developer[strlen(Phrases[count].developer)-1] == '\n')
		{
			Phrases[count].developer[strlen(Phrases[count].developer)-1] = '\0';
		}
		count++;
	}
	return count;
}
void NewFile(FILE * FH, GLS Phrases[], int SC)
{
	Phrases[SC].name = NULL;
	fseek(FH,0,SEEK_END); // End of file
	int End = ftell(FH);  // Recording End of File
	int i = 1;
	fseek(FH,0,SEEK_SET); // Moving Pointer to Beginning of File
	
	while(Phrases[i-1].genre != NULL)
	{
		if(i != (SC+1))// If it isn't the user chosen Phrase, print
		{
			fprintf(FH, "%s|%s|%s|%s\n",Phrases[i-1].name,Phrases[i-1].genre,Phrases[i-1].year, Phrases[i-1].developer);
			i++;
		}
		else
		{
			
			i++;
		}
	}
	//fprintf(FH,"\n");
	int Now = ftell(FH); // get the current position of the pointer
	int HowMany = abs(End - Now);//two positions being subtracted to see how many more spaces to print.
	
	int j;
	for(j = 0; j < HowMany; j++)
	{
		fprintf(FH," ");
	}

//// Cleaning up
	int f;
	for(f = 0; f < MAX_ENTRIES; f++)
	{
		free(Phrases[f].name);
		free(Phrases[f].genre);
		free(Phrases[f].developer);
	}
	
	fclose(FH);
}


void CLP(char *argv[], char name[], char filename[])
{
	int i= 1; 
	while (argv[i] != NULL)
	{
		if (!strncmp(argv[i], name, strlen(name)))
		{
			strcpy(filename, strchr(argv[i], '=') + 1);
		}
		i++;
	}
}
