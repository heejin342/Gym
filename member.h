#pragma once 

#define MAX_SIZE 500

typedef struct _member
{
	int memNum;
	char name[10];
	char dong[10];
	char phoneNum[20];
	char chuName[10];
	char birth[20];
	char product[10];
	char PT;
	char trainer[10];
	double firstBMI;
	double nowBMI;
	double goalBMI;
	char loc[5];
	char firstReg[30];
	int useNum;
	int usePT;
	char lastVisit[30];
	char endDay[30];

	double gr;
}member;
