#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include"Prototips.h"


void main()
{
#define key 123456789

	setlocale(LC_ALL, "rus");
	char Replay;//�������� ������� �����
	int chek = chek_Mass();
	Price *List = NULL;
	//������� ������ �������� �������� �� ����������� �����;
	List = (Price*)calloc(chek, sizeof(Price));
	if (List != NULL)
	{
		price_List(List);
	}
	else
		printf("NO MEMMORY\n");

	int section; //����� �������
	char folder[100]; //����� ���������� ����� �����
	do {
		system("cls");
		printf("*************����� ����������******************\n");
		printf("------------------------------------------------\n");
		printf("������� ����\n");
		printf("1-�����\n");
		printf("2-������������\n");
		printf("3-�����\n");
		printf("������� ���� ������� �������:");
		scanf("%d", &section);

		switch (section)
		{
		case 1:
		{
			int key_admin;
			system("cls");
			printf("���������\"������ 1234\"\n");
			printf("������� ������:");
			scanf("%d", &key_admin);
			if (key_admin == key)
				Replay = admin_01(List,chek);
			else {
				printf("������ ������ �� �����\n");
				Replay = 'y';
			}
		}
		break;

		case 2:
		{
			system("cls");
			int Pass;
			printf("������� ������:");
			scanf("%d", &Pass);
			if (Pass == key)
				Replay = user_01(List,chek);
			else {
				printf("������ ������ �� �����\n");
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
		printf("�� ��������� ������:\"�� ����� ������ ������\"\n");
		printf("----------------------------------------------\n");
		printf("������ ����� ����������� y-��\n");
		printf("�� ������������ � ������ ����� ������� \"ENTER\"\n");
		scanf("%c", &Replay);
		}
		}
	} while (Replay == 'y');
	free(List);
}