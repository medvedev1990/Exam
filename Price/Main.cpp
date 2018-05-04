#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include"Prototips.h"


void main()
{
#define key 123456789

	setlocale(LC_ALL, "rus");
	char Replay;//Проверка повтора цикла
	int chek = chek_Mass();
	Price *List = NULL;
	//создаем массив структур размером по колличеству строк;
	List = (Price*)calloc(chek, sizeof(Price));
	if (List != NULL)
	{
		price_List(List);
	}
	else
		printf("NO MEMMORY\n");

	int section; //выбор раздела
	char folder[100]; //Место нахождения папки Усера
	do {
		system("cls");
		printf("*************Добро Пожаловать******************\n");
		printf("------------------------------------------------\n");
		printf("Главное меню\n");
		printf("1-Админ\n");
		printf("2-Пользователь\n");
		printf("3-выйти\n");
		printf("Введите свой уровень доступа:");
		scanf("%d", &section);

		switch (section)
		{
		case 1:
		{
			int key_admin;
			system("cls");
			printf("Подсказка\"Пароль 1234\"\n");
			printf("Введите пароль:");
			scanf("%d", &key_admin);
			if (key_admin == key)
				Replay = admin_01(List,chek);
			else {
				printf("Пароль введен не верно\n");
				Replay = 'y';
			}
		}
		break;

		case 2:
		{
			system("cls");
			int Pass;
			printf("Введите пароль:");
			scanf("%d", &Pass);
			if (Pass == key)
				Replay = user_01(List,chek);
			else {
				printf("Пароль введен не верно\n");
				Replay = 'y';
			}
		}
		break;

		case 3:
		{
			exit(0);
		}
		break;

		default:
		{system("cls");
		printf("Вы совершили ошибку:\"не верно введен формат\"\n");
		printf("----------------------------------------------\n");
		printf("Хотите снова попробовать y-да\n");
		printf("Вы разачерованы и хотите выйти нажмите \"ENTER\"\n");
		scanf("%c", &Replay);
		}
		}
	} while (Replay == 'y');
	free(List);
}