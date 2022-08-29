//----INCLUDES----//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


//----MAIN----//
int main(int argc, char const *argv[])
{
	//---------IF ARGUMENTS ARE GIVEN-----------//
	if (argc > 1)
	{
		//----IF FIRST ARGUMENT IS ADD----//
		if (!strcmp(argv[1], "add"))
		{
			FILE* file;
			file = fopen(strcat(getenv("HOME"), "/.TODO") , "a");
			for (int i = 2; i < argc; ++i)
			{
				fprintf(file, "%s\n", argv[i]);
			}
			fclose(file);
		}

		//----IF FIRST ARGUMENT IS HELP"----//
		else if (!strcmp(argv[1], "help"))
			printf("list - lists tasks\nadd - adds task\nrm - removes task\nclear/clean - clears all tasks\n");

		//----IF FIRST ARGUMENT IS LIST----//
		else if (!strcmp(argv[1], "list"))
		{
			char c;
			FILE* file;
			file = fopen(strcat(getenv("HOME"), "/.TODO"), "a+");

			c = fgetc(file);
			int num = 0;
			printf("0 ");
			while (c != EOF)
			{
				if(c != '\n')
					printf("%c", c);
				else
					printf("\n%d ", ++num);
				c = fgetc(file);
			}
			printf("\b\b");

			fclose(file);
		}

		//----IF FIRST ARGUMENT IS RM----//
		else if (!strcmp(argv[1], "rm"))
		{
			int lno = atoi(argv[2]), ctr = 0;
			char ch;
			FILE *fptr1, *fptr2;
			char* fname = strcat(getenv("HOME"), "/.TODO");
			char str[256], temp[] = "temp.txt";
			fptr1 = fopen(fname, "r");
			fptr2 = fopen(temp, "w");
			lno++;
			while (!feof(fptr1)) 
			{
				strcpy(str, "\0");
				fgets(str, 256, fptr1);
				if (!feof(fptr1)) 
				{
					ctr++;
					if (ctr != lno) 
					{
						fprintf(fptr2, "%s", str);
					}
				}
			}
			fclose(fptr1);
			fclose(fptr2);
			remove(fname);
			rename(temp, fname);
		}

		//----IF FIRST ARGUMENT IS CLEAR/CLEAN----//
		else if ((!strcmp(argv[1], "clear")) || (!strcmp(argv[1], "clean")))
			remove(strcat(getenv("HOME"), "/.TODO"));

		//----IF FIRST ARGUMENT IS NOT SOME OF THE ABOVE, ADD IT TO TODO FILE----//
		else
		{
			FILE* file;
			file = fopen(strcat(getenv("HOME"), "/.TODO") , "a");
			for (int i = 1; i < argc; ++i)
			{
				fprintf(file, "%s\n", argv[i]);
			}
			fclose(file);
		} 
	}

	//----IF NO ARGUMENTS GIVEN----//
	else
		printf("run todo help for list of commands\n");

	return 0;
}
