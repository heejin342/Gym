#include <stdio.h>
#include <string.h>
#include "heap.h"
#include "member.h"

heap::heap() : recoCnt(1)
{
}

void heap::swap(element& e1, element& e2)
{
	element temp;
	temp = e1;
	e1 = e2;
	e2 = temp;
}

void heap::heapify_bottomUp(int idx)
{
	if (idx == 1)
		return;

	if (recoList[idx].rCnt > recoList[idx / 2].rCnt)
	{
		swap(recoList[idx], recoList[idx / 2]);
		heapify_bottomUp(idx / 2);
	}
	return;
}

void heap::heapify_topDown(int idx)
{
	if (2 * idx > recoCnt -1)
		return;

	if (2 * idx == recoCnt -1)
	{
		if (recoList[idx].rCnt < recoList[idx * 2].rCnt)
		{
			swap(recoList[idx], recoList[idx * 2]);
			return;
		}
	}

	if (recoList[idx].rCnt < recoList[idx * 2].rCnt && recoList[idx * 2].rCnt >= recoList[idx * 2 + 1].rCnt)
	{
		swap(recoList[idx], recoList[2 * idx]);
		heapify_topDown(2 * idx);

		return;
	}
	else if (recoList[idx].rCnt < recoList[idx * 2 + 1].rCnt && recoList[idx * 2 + 1].rCnt >= recoList[idx * 2].rCnt)
	{
		swap(recoList[idx * 2 + 1], recoList[idx]);
		heapify_topDown(2 * idx + 1);

		return;
	}
	else
	{
		return;
	}
}

void heap::Insert(const char* name)
{
	for (int i = 1; i < recoCnt; i++)
	{
		if (!strcmp(name, recoList[i].mName))
		{
			recoList[i].rCnt++;
			heapify_bottomUp(i);
			return;
		}
	}

	recoList[recoCnt].rCnt = 1;
	strcpy(recoList[recoCnt].mName, name);
	recoCnt++;
}
element heap::Pop()
{	
	element rpos = recoList[1];
	recoList[1] = recoList[recoCnt - 1];
	recoCnt--;
	heapify_topDown(1);
	return rpos;
}
element heap::Top() const
{
	return recoList[1];
}


