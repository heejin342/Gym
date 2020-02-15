#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <time.h>
#include"WhoWillCancel.h"
#include "Member.h"


#define MAX_MEM 350
#pragma warning(disable : 4996)

extern member memList[MAX_SIZE];
extern int memCnt;

cancel* cancelList;
cancel* lowAchieve;
cancel* highAttend;
cancel* findList;
find* cFind;  //cFind에 각 index는 cancel class의 index
int cancelCnt;

int totalDays(int year, int month, int day)
{
	int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int i = 0;
	int total = 0L;
	total = (year - 1) * 365L + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;

	if (!(year % 4) && year % 100 || !(year % 400))
		months[i]++;

	for (i = 0; i < month - 1; i++)
		total += months[i];

	total += day;

	return total;
}

int now() {

	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);
	
	return totalDays(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
}

int atoiDay(char*string) {
	//토큰 분리
	char strSeparate[] = "년월일";
	char* strPos = string;
	char ymday[5][5];
	int r = 0;
	int c = 0;
	int i = 0;

	while (i < 14) {
		if (i != 4 && i != 5 && i != 8 && i != 9 && i != 12 && i != 13)
			ymday[r][c++] = string[i++];

		else {
			if (i != 5 && i != 9 && i != 13) {
				ymday[r][c] = '\0';
				r++;
			}
			c = 0;
			i++;
		}
	}
	
	return totalDays(atoi(ymday[0]), atoi(ymday[1]), atoi(ymday[2]));
}

void cancelLoad() {

	int nowDay = now();
	int endDay;
	int ingday;
	int resDay;
	int j = 0;

	cancelList = (cancel*)malloc(sizeof(cancel) * 350);

	for (int i = 0; i < MAX_MEM; i++) { //i는 0부터
		endDay = atoiDay(memList[i].endDay);
		resDay = endDay - nowDay;
		ingday = atoiDay(memList[i].lastVisit) - atoiDay(memList[i].firstReg);
		if (atoi(memList[i].product) * 15 > resDay && resDay >= 0 && ingday >= 0) {
			strcpy(cancelList[j].cName, memList[i].name);
			cancelList[j].index = j;
			cancelList[j].cNum = memList[i].memNum;
			cancelList[j].achieve = (double)(memList[i].firstBMI - memList[i].nowBMI) / (double)(memList[i].firstBMI - memList[i].goalBMI);
			cancelList[j].ingDay = ingday;
			cancelList[j].realDay = (double)cancelList[j].ingDay / (double)memList[i].useNum;
			cancelList[j++].resDay = resDay;

		}

	}

	cancelCnt = j;
}

void cancelPrint(int cnt, cancel*cArr) {
	printf("      회원번호 회원이름 목표달성율 운동경과일 운동간격 잔여일\n");
	for (int i = 0; i < cnt; i++)
		printf("%-4d  %-8d %-8s %-10.3lf %-10d %-8.2lf %-6d\n", cArr[i].index, cArr[i].cNum, cArr[i].cName, cArr[i].achieve, cArr[i].ingDay, cArr[i].realDay, cArr[i].resDay);
}


int aCompare(const void* m, const void* n)
{
	cancel* a, *b;
	a = (cancel*)m;
	b = (cancel*)n;


	if (a->achieve < b->achieve) return -1;
	else if (a->achieve > b->achieve) return 1;
	else return 0;
}

int hCompare(const void* m, const void* n)
{
	cancel* a, *b;
	a = (cancel*)m;
	b = (cancel*)n;


	if (a->realDay < b->realDay) return -1;
	else if (a->realDay > b->realDay) return 1;
	else return 0;
}

int fCompare(const void* m, const void* n)
{
	find* a, *b;
	a = (find*)m;
	b = (find*)n;

	if (a->sum < b->sum) return -1;
	else if (a->sum >= b->sum) return 1;
	else return 0;
}


void cancelFind() { //low achieve, high attend

	cFind = (find*)malloc(sizeof(find) * 181);

	for (int i = 0; i < cancelCnt; i++) {
		cFind[i].originIndex = i; //원래 cancel index 저장
		cFind[lowAchieve[i].index].sum = i; //종속 조건으로 볼 총 sum값 저장
	}

	printf("\n");

	for (int i = 0; i < cancelCnt; i++)
		cFind[highAttend[i].index].sum += i; // 더함 =>결국 이 sum이 가장 작은 사람이 출석율 높고 달성율 낮은 사람


	qsort(cFind, cancelCnt, sizeof(find), fCompare);

	findList = (cancel*)malloc(sizeof(cancel) * 350);

	for (int i = 0; i < cancelCnt; i++)
		findList[i] = cancelList[cFind[i].originIndex];

}

void cancelFast() {

	lowAchieve = (cancel*)malloc(sizeof(cancel) * 350);
	highAttend = (cancel*)malloc(sizeof(cancel) * 350);

	for (int i = 0; i < cancelCnt; i++)
		lowAchieve[i] = cancelList[i];

	for (int i = 0; i < cancelCnt; i++)
		highAttend[i] = cancelList[i];

	qsort(lowAchieve, cancelCnt, sizeof(cancel), aCompare); //목표달성율 낮음(작음)
	qsort(highAttend, cancelCnt, sizeof(cancel), hCompare); //운동간격 빠름(작음)
	printf("\n\n< 목표 달성율 낮은 순서 >\n");
	cancelPrint(cancelCnt, lowAchieve);
	printf("\n\n< 운동 간격 좁은 순서 >\n");
	cancelPrint(cancelCnt, highAttend);
	cancelFind();

}

void cmain() {

	cancelLoad();
	//cancelPrint(cancelCnt,cancelList); //잔여일 기준으로 걸러짐
	cancelFast();
	cancelPrint(cancelCnt, findList); //순위 정렬
}