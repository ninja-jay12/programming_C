#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#pragma warning(disable : 4996)
typedef struct
{
	int raz;
	char adr[100];
	int dom;
	int itag;
	int kvart;
	int cen;
	char kom[100];
}KV;

void out(FILE* f, KV* mp, int size)
{
	fwrite(&size, sizeof(int), 1, f);
	fwrite(mp, sizeof(KV), size, f);
}

void in(FILE* f, KV* mp, int* size)
{
	fread(size, sizeof(int), 1, f);
	fread(mp, sizeof(KV), *size, f);
}

KV kva() {
	KV mp;
	printf("\nПлощадь(м^2): ");
	scanf("%d", &mp.raz);
	printf("\nУлица: ");
	scanf("%s", &mp.adr);
	printf("\nДом: ");
	scanf("%d", &mp.dom);
	printf("\nЭтаж: ");
	scanf("%d", &mp.itag);
	printf("\nКвартира: ");
	scanf("%d", &mp.kvart);
	printf("\nЦена(руб): ");
	scanf("%d", &mp.cen);
	printf("\nКомментарий: ");
	scanf("%s", &mp.kom);
	return mp;
}

void show(KV* mp, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("\nПлощадь(m^2): %d \nАдрес: \nУлица:%s \nДом: %d \nЭтаж: %d \nКвартира: %d \nЦена: %d \nКомментарий: %s \n", mp[i].raz, mp[i].adr, mp[i].dom, mp[i].itag, mp[i].kvart, mp[i].cen, mp[i].kom);
	}
}

void find(KV* mp, int size)
{
	char adr[100];
	int cen, raz;
	printf("\nПлощадь:");
	scanf("%d", &raz);
	printf("\nЦена(руб):");
	scanf("%d", &cen);
	printf("\nАдрес:");
	scanf("%s", &adr);
	for (int i = 0; i < size; i++)
		if (mp[i].raz == raz || cen == mp[i].cen || strcmp(mp[i].adr, adr) == 0) 
			printf("\nПо вашему запросу найдено: \nПлощадь(m^2): %d \nАдрес: \nУлица: %s \nДом: %d \nЭтаж: %d \nКвартира: %d \nЦена: %d \nКомментарий: %s \n", mp[i].raz, mp[i].adr, mp[i].dom, mp[i].itag, mp[i].kvart, mp[i].cen, mp[i].kom);
}

int adr(const void* f, const void* s)
{
	return strcmp(((KV*)f)->adr, ((KV*)s)->adr) > 0;
}

int cen(const void* f, const void* s)
{
	return (((KV*)f)->cen - ((KV*)s)->cen < 0);
}

int main()
{
	setlocale(LC_ALL, "RU");
	KV mp[100];
	int size = 0, i;
	FILE* f = fopen("file.txt", "rb");
	if (f)
	{
		in(f, mp, &size);
		fclose(f);
	}
	f = fopen("file.txt", "wb");
	char flag_wasNextLine = 0;
	while (1)
	{
		if (!flag_wasNextLine)
		{
			printf("Введите:\n|1| - если хотите добавить квартиру\n");
			printf("|2| - если хотите удалить квартиру\n");
			printf("|3| - если хотите сортировать по адресу\n");
			printf("|4| - если хотите сортировать по цене\n");
			printf("|5| - если хотите отобразить весь список\n");
			printf("|6| - если хотите открыть поиск\n");
			printf("|0| - если хотите выйти\n>");
		}
		char tmpc, prevc = 0;
		i = 0;
		while ((tmpc = getchar()) != '\n')
		{
			i++;
			prevc = prevc * 10 + tmpc;
		}
		if (i == 0)
			flag_wasNextLine = 1;
		else
			flag_wasNextLine = 0;

		i = prevc - '0';
		switch (i)
		{
		case 1:
			mp[size] = kva();
			size++;
			printf("\n");
			break;
		case 2:
			printf("\nУкажите номер квартиры(начиная с нуля) по списку: ");
			scanf("%d", &i);
			--size;
			for (; i < size; i++)
				mp[i] = mp[i + 1];
			printf("\n");
			break;
		case 3:
			qsort(mp, size, sizeof(KV), adr);
			show(mp, size);
			printf("\n");
			break;
		case 4:
			qsort(mp, size, sizeof(KV), cen);
			show(mp, size);
			printf("\n");
			break;
		case 5:
			show(mp, size);
			printf("\n");
			break;
		case 6:
			find(mp, size);
			printf("\n");
			break;
		case 0:
			out(f, mp, size);
			fclose(f);
			return 0;
		default:
		{
			break;
		}
		}
	}
}
