#include <stdio.h>
#include <time.h>
#include <windows.h>
HANDLE wHnd;  
HANDLE rHnd; 

int checkIfFileExists(const char * filename)
{
    FILE *file;
    if ( (file = fopen(filename, "r")) )
    {
        fclose(file);
        return 1;
    }

    return 0;
}

void changeConsoleInfo()
{
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    
    SetConsoleTitle("Estudando : Nifo18");
    SMALL_RECT windowSize = {0, 0, 13, 2};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    
    COORD bufferSize = {10, 10};
    SetConsoleScreenBufferSize(wHnd, bufferSize);
}

int saveFile(char start[10], char end[10],char relativeTime[10])
{
	time_t rawtime;
	struct tm * timeinfo;
	time( &rawtime );
	
	timeinfo = localtime( &rawtime );
	
	char fileNameUnFormat[] = "%02d.%02d.%02d.txt";
	char fileNameFormated[30];
	
	sprintf(fileNameFormated, fileNameUnFormat,timeinfo->tm_mon+1, timeinfo->tm_mday ,
	 (timeinfo->tm_year - 100) );
	
	//Máximo de 10 arquivos iguais
	for(int i = 0; i < 10; i++)
	{
		if(checkIfFileExists(fileNameFormated))
		{
			char fileNameUnFormat[] = "%02d.%02d.%02d_(%d).txt";
			sprintf(fileNameFormated, fileNameUnFormat, timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_year - 100, (i+2) );
		}
		else
		{
			break;
		}
	}
	
	FILE* file_ptr = fopen(fileNameFormated, "w");
	
	if (file_ptr == NULL)
    {
        printf("Error opening the file");
        return -1;
    }
	
	fprintf(file_ptr, "============================\n");
    fprintf(file_ptr, start);
    fprintf(file_ptr, end);
    fprintf(file_ptr, relativeTime);
	fprintf(file_ptr, "\n============================\n");
	
	fclose(file_ptr);
	return 0;
}

int main()
{
	time_t rawtime;
	struct tm * timeinfo;
	
	char temp;
	
	char startUnFormat[] = "Começou estudar  : %02d:%02d:%02d\n";
	char startFormated[30];
	
	char endUnFormat[] = "Parou de estudar : %02d:%02d:%02d\n";
	char endFormated[30];
	
	char TimeUnFormat[] = "Tempo de estudou : %02d:%02d:%02d";
	char TimeFormated[30];
	
	
	int timeStart[3];
	int timeEnd[3];
	int timeRelative[3];
	
	changeConsoleInfo();
	
	time( &rawtime );
	timeinfo = localtime( &rawtime );
	
	timeStart[0] = timeinfo->tm_hour;
	timeStart[1] = timeinfo->tm_min;
	timeStart[2] = timeinfo->tm_sec;
	
	sprintf(startFormated,startUnFormat,timeStart[0], timeStart[1], timeStart[2]);
	
	printf("Estudando...\n");
	scanf("%c", &temp);
	
	time( &rawtime );
	timeinfo = localtime( &rawtime );
	
	timeEnd[0] = timeinfo->tm_hour;
	timeEnd[1] = timeinfo->tm_min;
	timeEnd[2] = timeinfo->tm_sec;
	
	sprintf(endFormated,endUnFormat,timeEnd[0], timeEnd[1], timeEnd[2]);
	
	timeRelative[0] = timeEnd[0] - timeStart[0];
	timeRelative[1] = timeEnd[1] - timeStart[1];
	timeRelative[2] = timeEnd[2] - timeStart[2];
	
	sprintf(TimeFormated,TimeUnFormat,timeRelative[0], timeRelative[1], timeRelative[2]);

	return saveFile(startFormated, endFormated,TimeFormated);
}

