#include <stdio.h>
#include <string.h>
#include "member.h"
#include "Function.h"
#include "heap.h"
#include "heap2.h"

member memList[MAX_SIZE];
int memCnt = 0;
heap* maxHeap;

extern void cmain();

int main()
{
	
	load();
	makeHeap();

	printf("\n #잘나가는 GYM\n\n\n");
	printf("운동 달성률 가장 높은 사람 : %s\n\n", memList[maxAchivePerson()].name);

	trainers trList1;
	trList1.init(10);
	
	for (int i = 0; i < memCnt; i++) {
		if (strcmp(memList[i].trainer, "-") != 0)
			trList1.insert(memList[i]);
	}

	heap2 theap1;
	theap1.init(trList1.trCnt + 1);
	for (int i = 1; trList1.isEmpty() == 0; i++) {
		theap1.push1(trList1.pop());
	}

	trainers trList2;
	trList2.init(10);

	for (int i = 0; i < memCnt; i++) {
		if (strcmp(memList[i].trainer, "-") != 0)
			trList2.insert(memList[i]);
	}

	heap2 theap2;
	theap2.init(trList2.trCnt + 1);
	for (int i = 1; trList2.isEmpty() == 0; i++) {
		theap2.push2(trList2.pop());
	}
	
	printf("\n학생 수 많은 순서\n");
	while (!theap1.isEmpty()) {
		theap1.pop1();
	}

	printf("\n학생들의 목표 달성률이 높은 순서\n");
	while (!theap2.isEmpty()) {
		theap2.pop2();
	}

	element temp;

	
	printf("\n\n추천 등수\n");
	for (int i = 0; i < 94; i++)
	{
		temp = maxHeap->Pop();
		printf("%3d등 : %s\t횟수 : %d\n", i + 1, temp.mName, temp.rCnt);
	}
	
	PT_but_noLocker(); 

	least_PT_age(); 

	cmain(); 
}
