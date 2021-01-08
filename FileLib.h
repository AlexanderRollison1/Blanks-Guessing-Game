//Alexander Rollison 1001681800
#ifndef FileLib_H
#define FileLib_H
FILE * OpenFile(int argc,char *argv[], char mode[]);
int ReadFileIntoArray(FILE * FH, GLS Phrases[]);
void NewFile(FILE * FH, GLS Phrases[], int SC);
void CLP(char *argv[], char name[], char filename[]);
#endif
