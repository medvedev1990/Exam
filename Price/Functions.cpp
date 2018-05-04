#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include"Prototips.h"

int i, j;
FILE *file;
char adress_Price_List()
{
	printf("������� ������ � pprice.csv ����� ����� ���� ����� ������ �� ���������: ");
	char *addres = NULL;
	addres = (char*)calloc(128, sizeof(char));
	scanf("%s", &addres);
	return *addres;
}

int menu1_User(int *menu1)
{
	printf("\n1-������ �������\n2-������ ������� � ������������ ���������\n3-���������� � �������\n4-������ ����������� �������\n�������� ��������: ");
	scanf("%d", menu1);
	return *menu1;
}
int chek_Mass()
{
	int schet = 0;
	Price search;
	Price *List = NULL;
	if ((file = fopen("pprice21.csv", "r")) != NULL)
	{
		//������� ����������� �����
		while (!feof(file))
		{
			fgets(search.buffer, 200, file);
			schet++;
		}
		rewind(file);
	}
	fclose(file);
	return schet;
}
void price_List(Price *List)
{
	if ((file = fopen("pprice21.csv", "r")) != NULL)
	{
		int index = 0;
		int start = 0;
		int chek = 0;
		int end = 0;
		int index2;
		while (!feof(file))
		{
			chek = 0;
			fgets((List + index)->buffer, 200, file);

			for (i = 0;i < strlen((List + index)->buffer);i++)
			{
				if ((List + index)->buffer[i] == ';')
				{
					chek++;
					if (chek == 1)
						start = i + 1;
					//������ ������ id
					else if (chek == 2)
					{
						index2 = 0;
						end = i;
						for (j = start;j < end;j++)
						{
							char a = List[index].buffer[j];
							List[index].id[index2] = a;
							index2++;
						}
						(List + index)->id[index2] = '\0';
					}
					//������ ������ ������������ ������
					else if (chek == 3)
					{
						start = end + 1;
						end = i;
						index2 = 0;
						for (j = start;j < end;j++)
						{
							(List + index)->name[index2] = (List + index)->buffer[j];
							index2++;
						}
						(List + index)->name[index2] = '\0';
					}
					//������ ������ ��������� � ������� ����
					else if (chek == 4)
					{
						start = end + 1;
						end = i;
						index2 = 0;
						for (j = start;j < end;j++)
						{
							(List + index)->sale_Roz[index2] = (List + index)->buffer[j];
							index2++;
						}
						(List + index)->sale_Roz[index2] = '\0';

						start = end + 1;
						end = strlen((List + index)->buffer) - 1;
						index2 = 0;
						for (j = start;j < end;j++)
						{
							(List + index)->sale_Opt[index2] = (List + index)->buffer[j];
							index2++;
						}
						(List + index)->sale_Opt[index2] = '\0';
					}
				}
			}
			index++;
		}
		fclose(file);
	}
	else
		printf("NOT OPEN FILE\n");
}
void adress_Save()
{
	char buffer[100];
	printf("������� ����� ���� ��������� ����: ");
	scanf("%s", buffer);
}
void print_Price_List(Price *List, int chek)
{
	chek = chek_Mass();
	printf("|---------------------------------------------------------Price List--------------------------------------------------------------------|\n");
	printf("|  id     |  Name                                                                                                   | Sale opt| Sale roz|\n");
	printf("|---------------------------------------------------------------------------------------------------------------------------------------|\n");
	printf("|         |                                                                                                         |         |         |\n");
	for (int index = 0;index < chek;index++)
	{
		printf("|%9s|%105s|%9s|%9s|\n", (List + index)->id, (List + index)->name, (List + index)->sale_Opt, (List + index)->sale_Roz);
	}
	printf("|---------------------------------------------------------------------------------------------------------------------------------------|\n");
}
void zapp_Basket(Price *List, int chek) //����� ������
{
	Price *Sale = NULL;
	Sale = (Price*)calloc(1, sizeof(Price));
	if (Sale != NULL)
	{
		int contined;
		int row = 1;
		int index = 0;
		char id_Product[10];
		do
		{
			printf("������� id ������ ��� ���������� � �������: ");
			scanf("%s", id_Product);
			for (i = 0;i < chek;i++)
			{
				if (strcmp((List + i)->id, id_Product))
				{
					strcpy((Sale + index)->id, (List + i)->id);
					strcpy((Sale + index)->name, (List + i)->name);
					strcpy((Sale + index)->sale_Opt, (List + i)->sale_Opt);
					strcpy((Sale + index)->sale_Roz, (List + i)->sale_Roz);
					break;
				}
			}
			index++;
			printf("�� ������ ���������� ����������� ������� 1-Yes 2-No: ");
			scanf("%d", &contined);
			if (contined == 1)
			{
				row++;
				Sale = (Price*)realloc(Sale, row * sizeof(Price));
			}
		} while (contined == 1);
		if ((file = fopen("basket_of_goods.txt", "w")) != NULL)
		{
			fprintf(file, "|---------------------------------------------------------Price List--------------------------------------------------------------------|\n");
			fprintf(file, "|  id     |  Name                                                                                                   | Sale opt| Sale roz|\n");
			fprintf(file, "|---------------------------------------------------------------------------------------------------------------------------------------|\n");
			fprintf(file, "|         |                                                                                                         |         |         |\n");
			for (i = 0;i < index;i++)
			{
				fprintf(file, "|%9s|%105s|%9s|%9s|\n", (Sale + i)->id, (Sale + i)->name, (Sale + i)->sale_Opt, (Sale + i)->sale_Roz);
			}
			fprintf(file, "|---------------------------------------------------------------------------------------------------------------------------------------|\n");
		}
		fclose(file);
		free(Sale);
	}

}
int product_Categories()
{
	int menu;
	printf("�������� ��������� ������\n");
	printf(" 1-�������� (Notebook)\n2-��������(Tablet, Pad)\n3-���������, ����������(Smartphone, GPS)\n4-���������, �������(All - In - One PC)\n5-������������ ���������� Eco(Personal Computer)\n6-������������ ���������� Standard(Personal Computer)\n7-������������ ���������� Advanced(Personal Computer)\n8-������������ ���������� Extreme(Personal Computer)\n9-��������� ��������� � ����������(Server)\n10-����������(CPU)\n11-������ ��� �����������(Cooler for CPU)\n12-������, ������� ���������� � ����������(Cooler accessories)\n13-����������� ����� ASUS(Motherboard ASUS)\n14-����������� �����(Motherboard)\n15-������ ����������� ������(RAM)\n16-���������� ASUS(Videocard ASUS)\n17-����������(Videocard)\n18-������� �����(HDD)\n19-������������� ����������(SSD)\n20-������� ������� �����(External HDD)\n21-������� �������� ������ Asus(NAS)\n22-���������� ��� ������� ������(HDD / SSD accessories)\n23-���������� �������(CD, DVD, BD)\n24-�������� �����(Soundcard)\n25-������������ �������(Speakers)\n26-��������(Headphones)\n27-���������(Headset)\n28-���������(Microphone)\n29-������(Modem)\n30-������� � ������������ �����, ����������(LAN card, WiFi)\n31-������� � ������������ ��������������(Router, WiFi)\n32-������� ������, ����� �������(LAN switch, access point)\n33-������� ������, ����������(LAN cable)\n34-����������� SATA, SCSI, IDE, USB, FireWire, IrDA, COM, LPT\n35-������, �����������(DVB - T, DVB - S, FM)\n36-USB ��������, ����(BT, IrDA, RS232, LPT)\n37-USB ������� � ����������(USB power)\n38-����������(Cardreader)\n39-����� ���� ������(CF, MMC, SD, xD, SM, MS)\n40-USB ������(USB Flash)\n41-��������(Monitor)\n42-��������, ���(Printer)\n43-�������(Scanner)\n44-��������� ���������(Cartridge, Toner, Paper)\n45-�������� ��������(Cleaners)\n46-�������� ����������(CD, DVD, FD)\n47-����������� MP3 / MP4 ������ � ����������(Portable MP3 / MP4)\n48-����������� �����, ������� ���������(EBook)\n49-���������(Webcam)\n50-�����������������, ��������������(Digital Video Recorder, Car accessories)\n51-����������(Fax, Copier, Shredder)\n52-������������� �������, �������������(UPS)\n53-������� �������, ����������(Surge)\n54-������ � �����������(Cable, converter)\n55-�������(Case)\n56-����� ������� ATX(Power supply)\n57-����������, ����������(Keyboard, accessories)\n58-����, �������(Mouse, Pad)\n59-���������(Joystick)\n60-�����������, ������ ����������(Digitizer, remote)\n61-������������, ���������, ��������, �������(Battery, accu)\n62-�����, ������� ��� CD(CD bags, boxes)\n63-����������� �����������(Software)\n64-���������� ��� ���������, ���������, ����������(Mobile accessories)\n65-����� ��� ���������(Notebook bag)\n66-���������, �������� ��� ���������(Notebook stand)\n");
	scanf("%d", &menu);
	return menu;
}
char user_01(Price *List, int chek)
{
	char ReplayUser;
	int section;
	do {
		system("cls");
		printf("*************����� ���������� User******************\n");
		printf("----------------------------------------------------\n");
		printf("������� ����:\n");
		printf("1-������� ����� ����\n");
		printf("2-��������� �������\n");
		printf("3-�������� � �������\n");
		printf("4-�������� �����\n");
		printf("5-��������� �����\n");
		printf("6-������� �����������\n");
		scanf("%d", &section);
		switch (section)
		{
		case 1:
		{
			system("cls");
			print_Price_List(List, chek);
			system("pause");
			return 'y';
		}
		break;
		case 2:
		{
			product_Categories();
			printf("�������� ��������� ������: ");
			int kategotiya;
			scanf("%d", &kategotiya);
			switch (kategotiya)
			{
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case 11:
				break;
			case 12:
				break;
			case 13:
				break;
			case 14:
				break;
			case 15:
				break;
			case 16:
				break;
			case 17:
				break;
			case 18:
				break;
			case 19:
				break;
			case 20:
				break;
			case 21:
				break;
			case 22:
				break;
			case 23:
				break;
			case 24:
				break;
			case 25:
				break;
			case 26:
				break;
			case 27:
				break;
			case 28:
				break;
			case 29:
				break;
			case 30:
				break;
			case 31:
				break;
			case 32:
				break;
			case 33:
				break;
			case 34:
				break;
			case 35:
				break;
			case 36:
				break;
			case 37:
				break;
			case 38:
				break;
			case 39:
				break;
			case 40:
				break;
			case 41:
				break;
			case 42:
				break;
			case 43:
				break;
			case 44:
				break;
			case 45:
				break;
			case 46:
				break;
			case 47:
				break;
			case 48:
				break;
			case 49:
				break;
			case 50:
				break;
			case 51:
				break;
			case 52:
				break;
			case 53:
				break;
			case 54:
				break;
			case 55:
				break;
			case 56:
				break;
			case 57:
				break;
			case 58:
				break;
			case 59:
				break;
			case 60:
				break;
			case 61:
				break;
			case 62:
				break;
			case 63:
				break;
			case 64:
				break;
			case 65:
				break;
			default:
				break;
			}
			return 1;
		}
		break;
		case 3:
		{
			system("cls");
			zapp_Basket(List, chek);
			system("pause");
			return 1;
		}
		break;
		case 4:
		{
			order_�lacement(List);
		}
		break;
		case 5:
			return 'y';
			break;
		case 6:
			exit(0);
			break;
		default:
		{
			system("cls");
			printf("�� ��������� ������:\"�� ����� ������ ������\"\n");
			printf("----------------------------------------------\n");
			printf("������ ����� ����������� \"y\"-��\n");
			printf("�� ������������ � ������ ����� ������� \"ENTER\"\n");
			scanf("%c", &ReplayUser);
		}
		}
	} while (ReplayUser == 'y');
	return 0;
}
void order_�lacement(Price *List)
{
	system("cls");
	int i = 0;
	Price *Sale;
	if ((file = fopen("basket_of_goods.txt", "r")) != NULL)
	{
		rewind(file);
		printf("|---------------------------------------------------------Price List--------------------------------------------------------------------|\n");
		printf("|  id     |  Name                                                                                                   | Sale opt| Sale roz|\n");
		printf("|---------------------------------------------------------------------------------------------------------------------------------------|\n");
		printf("|         |                                                                                                         |         |         |\n");
		while (!feof(file))
		{
			//����� �� �����
		}

		printf("|---------------------------------------------------------------------------------------------------------------------------------------|\n");
	}
	fclose(file);
	free(Sale);
	printf("�� ������������ ����������� ������? 1-�� 2-���\n");
	int order;
	scanf("%d", &order);
	if (order == 1)
	{

	}
	else
		exit(0);
}
char admin_01(Price *List, int chek)
{
	if ((file = fopen("pprice21.csv", "w")) != NULL)
	{
		char ReplayAdmin;
		int section;
		do {
			system("cls");
			printf("*************����� ���������� �����******************\n");
			printf("-----------------------------------------------------\n");
			printf("������� ���� ������:\n");
			printf("1-��������\n");
			printf("2-��������\n");
			printf("3-���������\n");
			printf("4-��������� �����\n");
			printf("5-������� �����������\n");
			scanf("%d", &section);
			switch (section)
			{
			case 1:
			{
				List = (Price*)realloc(List, sizeof(Price)*(chek + 1));
				char new_id[10];
				char new_name[200];
				char new_roz_sale[10];
				char new_opt_sale[10];
				printf("������� id ������ ");
				scanf("%s", new_id);
				printf("������� ������������ ������ ");
				scanf("%s", new_name);
				printf("������� ��������� ���� ");
				scanf("%s", new_roz_sale);
				printf("������� ������� ���� ");
				scanf("%s", new_opt_sale);
				strcpy((List + (chek + 1))->id, new_id);
				strcpy((List + (chek + 1))->name, new_name);
				strcpy((List + (chek + 1))->sale_Opt, new_opt_sale);
				strcpy((List + (chek + 1))->sale_Roz, new_roz_sale);
				printf("���������� ���������� ����� ������������ ���������\n");
				chek++;
			}
			break;
			case 2:
			{
				char id[10];
				printf("������� id ������� ��� ��������");
				scanf("%s", id);
				for (int i = 0;i < chek;i++)
				{
					if (strcmp((List + i)->id, id))
					{
						delete List[i].id;
						delete List[i].name;
						delete List[i].sale_Opt;
						delete List[i].sale_Roz;
					}
					break;
				}
				printf("���������� ���������� ����� ������������ ���������\n");
			}
			break;
			case 3:
			{
				char id[10];
				printf("������� id ������� ��� ���������");
				scanf("%s", id);
				for (int i = 0;i < chek;i++)
				{
					if (strcmp((List + i)->id, id))
					{
						printf("��� ������ ��������?\n");
						printf("1- id ������\n");
						printf("2-H����������� ������\n");
						printf("3-��������� ����\n");
						printf("4-������� ����\n");
						printf("5-�����\n");
						int izminenie;
						switch (izminenie)
						{
						case 1:
						{
							printf("������� ����� id ������");
							char new_id[10];
							scanf("%s", new_id);
							strcpy((List + i)->id, new_id);
						}
						break;
						case 2:
						{
							printf("������� ����� ������������ ������");
							char new_name[200];
							scanf("%s", new_name);
							strcpy((List + i)->name, new_name);
						}
						break;
						case 3:
						{
							printf("������� ����� ��������� ����");
							char new_roz_sale[10];
							scanf("%s", new_roz_sale);
							strcpy((List + i)->sale_Roz, new_roz_sale);
						}
						break;
						case 4:
						{
							printf("������� ����� ������� ����");
							char new_opt_sale[10];
							scanf("%s", new_opt_sale);
							strcpy((List + i)->sale_Opt, new_opt_sale);
						}
						break;
						case 5:
						{
							return 'y';
						}
						break;
						default:
							break;
						}
					}
					break;
				}
				printf("���������� ���������� ����� ������������ ���������\n");
			}
			break;
			case 4:
				return 'y';
				break;
			case 5:
				exit(0);
				break;

			default:
			{system("cls");
			printf("�� ��������� ������:\"�� ����� ������ ������\"\n");
			printf("----------------------------------------------\n");
			printf("������ ����� ����������� \"y\"-��\n");
			printf("�� ������������ � ������ ����� ������� \"ENTER\"\n");
			scanf("%c", &ReplayAdmin);
			}
			}
		} while (ReplayAdmin == 'y');
		return 0;
	}
	for (i = 0;i < chek;i++)
	{
		fprintf(file, " ;%s;%s;%s;%s;", (List + i)->id, (List + i)->name, (List + i)->sale_Roz, (List + i)->sale_Opt);
	}
	fclose(file);
	
}