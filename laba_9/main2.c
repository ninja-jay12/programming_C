#pragma warning(disable : 4996) // чиним fopen
#include <stdio.h> 
#define MAXLINE 1024  
int main(void)
{  // указатели на структуру типа FILE для входной и выходного файлов
	int N;
	int a = 1;
	printf("N - quantity of symbol in line\n");
	printf("enter N please\n");
	scanf_s("%d", &N);
	char line[MAXLINE]; // текущая строка  
	char *ptr;  
 // открыть файл для чтения  
	FILE *fpin = fopen( "test.txt", "r" );
	if (fpin == NULL)
	{
		printf("error: file not found\n"); // если файл с данными отсутствует, выводим ошибку
		return;
	}
	// открыть файл для записи
	FILE* fpout = fopen("result.txt", "a"); // создаем файл с результатом
	
	
		while (!feof(fpin)) // цикл до конца файла  
		{   // чтение строки
			ptr = fgets(line, N, fpin);
			
			if (ptr == NULL)
				break; // файл исчерпан
			while (*ptr != '\0')
			{
				if (a == N)
				{     // достигнута максимальная длина строки  
					
					a = 1;
					a++;
					fprintf(fpout, "\n");
				}
				else
				{
					a++;
				}
				ptr++; // продвигаем указатель по строке
			}
			fputs(line, fpout); // запись строки
		}
		fclose(fpin); // закрыть входной файл  
		fclose(fpout); // закрыть выходной файл 
		return 0;
}
