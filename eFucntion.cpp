#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include "member.h"
#include "Function.h"
#include "heap.h"

extern member memList[MAX_SIZE];
extern int memCnt;
extern heap* maxHeap;

void removeRest(char* buf, char* buf2)
{
	int i = 0, j = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == ',')
		{
			i++;
			buf2[j++] = ' ';
			continue;
		}
		while (buf[i] != ',' && buf[i] != '\0')
		{
			if (buf[i] == ' ')
			{
				i++;
				continue;
			}

			buf2[j++] = buf[i++];
		}
	}
	buf2[j] = '\0';
}

void load()
{
	FILE* fp = fopen("data.csv", "r+t");
	char buf[200];
	char buf2[200];
	int i = 0;
	fgets(buf, 200, fp);

	while (!feof(fp))
	{
		fgets(buf, 200, fp);
		removeRest(buf, buf2);
		sscanf(buf2, "%d %s %s %s %s %s %s %c %s %lf %lf %lf %s %s %d %d %s %s",
			&memList[i].memNum, memList[i].name, memList[i].dong, memList[i].phoneNum,
			memList[i].chuName, memList[i].birth, memList[i].product, &memList[i].PT,
			memList[i].trainer, &memList[i].firstBMI, &memList[i].nowBMI, &memList[i].goalBMI,
			memList[i].loc, memList[i].firstReg, &memList[i].useNum, &memList[i].usePT,
			memList[i].lastVisit, memList[i].endDay);
	
		// ����ó�� : ó���� ��ǥ�� �������
		if (memList[i].firstBMI == memList[i].goalBMI) {
			memList[i].gr = 1.0;
		}
		// �컩���� ȸ�� �� ��ǥ���� �� �� ȸ��
		else if (memList[i].firstBMI > memList[i].goalBMI && memList[i].nowBMI <= memList[i].goalBMI) {
			memList[i].gr = 1.0;
		}
		// ������� ȸ�� �� ��ǥ���� �� �� ȸ��
		else if (memList[i].firstBMI < memList[i].goalBMI && memList[i].nowBMI >= memList[i].goalBMI) {
			memList[i].gr = 1.0;
		}
		// �컩���� ȸ�� �� ó������ ���� ȸ��
		else if (memList[i].firstBMI > memList[i].goalBMI && memList[i].nowBMI >= memList[i].firstBMI) {
			memList[i].gr = 0.0;
		}
		// ������� ȸ�� �� ó������ ���� ȸ��
		else if (memList[i].firstBMI < memList[i].goalBMI && memList[i].nowBMI <= memList[i].firstBMI) {
			memList[i].gr = 0.0;
		}
		// ������ ȸ����
		else {
			memList[i].gr = (memList[i].firstBMI - memList[i].nowBMI) /
				(memList[i].firstBMI - memList[i].goalBMI);
		}
		//printf("%3d %6s %s %s %6s %s %8s %c %7s %.1f %.1f %.1f %3s %s %3d %3d %s %s",
		//	memList[i].memNum, memList[i].name, memList[i].dong, memList[i].phoneNum,
		//	memList[i].chuName, memList[i].birth, memList[i].product, memList[i].PT,
		//	memList[i].trainer, memList[i].firstBMI, memList[i].nowBMI, memList[i].goalBMI,
		//	memList[i].loc, memList[i].firstReg, memList[i].useNum, memList[i].usePT,
		//	memList[i].lastVisit, memList[i].endDay);
		//printf(" %.1lf\n", memList[i].gr);
		i++;
		memCnt++;
	}
}

void makeHeap()
{
	maxHeap = new heap;
	for (int i = 0; i < memCnt; i++)
	{
		if (memList[i].chuName[0] != '-')
			maxHeap->Insert(memList[i].chuName);
	}
}

void PT_but_noLocker() 
{
	int pt_noLoc = 0;
	int pt_loc = 0;
	
	printf("\n\nPT�� ������ ��Ŀ�� ���»����\n");
	printf("ȸ����ȣ\t�̸� \t \t PTȽ��\n");
	for (int i = 0; i < memCnt; i++)
	{
		if (memList[i].PT == 'Y')
		{
			if (memList[i].loc[0] == '-')
			{
				pt_noLoc++;
				printf("%3d\t\t%s\t\t %d\n",
					memList[i].memNum, memList[i].name, 
						  memList[i].usePT);
			}
		}
	}
	printf("PT�ް� ��Ŀ���� ��� �� : %d\n", pt_noLoc);
}

int maxAchivePerson()
{
	int maxIdx;
	double maxAchive;

	maxAchive = (memList[0].nowBMI - memList[0].firstBMI) / (memList[0].goalBMI - memList[0].firstBMI);


	for (int i = 1; i < memCnt; i++)
	{
		if (memList[i].firstBMI == memList[i].goalBMI)
		{
			continue;
		}

		if (maxAchive < (memList[i].nowBMI - memList[i].firstBMI) / (memList[i].goalBMI - memList[i].firstBMI))
		{
			maxIdx = i;
			maxAchive = (memList[i].nowBMI - memList[i].firstBMI) / (memList[i].goalBMI - memList[i].firstBMI);
		}
	}

	return maxIdx;
}

void least_PT_age() {

	SYSTEMTIME st;
	GetLocalTime(&st);

	int most_PT_age = 0;
	int least_PT_age = 0;
	int age[10] = { 0 };   //���ɴ�迭- age[1] = 0��~9��  ->  age[2] = 10��~19��
	char *ptr;
	int ageint = 0;

	for (int i = 0; i < memCnt; i++) {
		if (memList[i].PT == 'Y') {
			ptr = strtok(memList[i].birth, ".");
			//printf("%s\n\n", memList[i].birth);
			int num = atoi(memList[i].birth);
			if (0 <= num && num <= st.wYear / 100) {  // ����(ex, 00 , 03) �� 0����ũ�� ����⵵ /100 ���� ������� 
				ageint = st.wYear / 100 - num;
				age[ageint / 10]++;
			}
			else {
				ageint = st.wYear - (num + 1900);
				age[ageint / 10]++;
			}
		}
	}

	int max = 0; int min = 9999;
	int maxIdx = 0;   int minIdx = 0;

	for (int i = 0; i < 10; i++) {
		if (age[i] < min && age[i] != 0) {
			min = age[i];
			minIdx = i;
		}
		if (age[i] > max && age[i] != 0) {
			max = age[i];
			maxIdx = i;
		}
	}

	if (minIdx == 0) {
		printf("\n\nPT�� ���� ���� �̿��ϴ� ���ɴ�� �� %d���� '%d��', PT�� ���� ���� �̿��ϴ� ���ɴ�� �� %d���� '10�� �̸� ��' �Դϴ�.\n\n", age[maxIdx], maxIdx * 10, age[minIdx]);
	}
	else if (maxIdx == 0) {
		printf("\n\nPT�� ���� ���� �̿��ϴ� ���ɴ�� �� %d���� '10�� �̸� ��', PT�� ���� ���� �̿��ϴ� ���ɴ�� �� %d���� '%d��' �Դϴ�.\n\n", age[maxIdx], age[minIdx], minIdx * 10);

	}
	printf("\n\nPT�� ���� ���� �̿��ϴ� ���ɴ�� �� %d���� '%d��', PT�� ���� ���� �̿��ϴ� ���ɴ�� �� %d���� '%d��' �Դϴ�.\n\n", age[maxIdx], maxIdx * 10, age[minIdx], minIdx * 10);

	printf("���ɴ뺰 ��� ��\n");
	for (int i = 0; i < 10; i++) {
		(i * 10 > 0) ? printf("%d�� : %d\n", i * 10, age[i]) : printf("0~10�� : %d\n", age[i]);
	}
}