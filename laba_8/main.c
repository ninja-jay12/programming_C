
#include <stdio.h> // определение символических констант 
#define MAXLINE 1000  
void process_line(char buffer[]);
int main(void)
{
	char line[MAXLINE];
	gets_s(line);
	process_line(line);
	puts(line);
	return 0;
}
void process_line(char buffer[])
{
	char c;  // текущий символ  
	int prev_c;  // предыдущий символ  
	char *in_ptr;
	char *out_ptr;
	// начальные присваивания (инициализация)  
	prev_c = ' ';
	in_ptr = buffer;
	out_ptr = buffer;
	// цикл чтения символов из строки  
	do
	{
		c = *in_ptr; // взять текущий символ из буфера  
		if (c == ' ' && prev_c == ' ')
		{
		}
		else
		{
			*out_ptr++ = *in_ptr;
		}
		prev_c = c;
		in_ptr++;
	} while (c != '\0');
}
