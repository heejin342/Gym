#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap2.h"


void heap2::init(int n)
{
	this->hN = n;
	this->hCnt = 0;
	this->hlist = (trainer*)malloc(this->hCnt * sizeof(trainer));
}

int heap2::isEmpty()
{
	if (this->hCnt == 0)
		return 1;
	return 0;
}

void heap2::swap(trainer* a, trainer* b)
{
	trainer temp = *a;
	*a = *b;
	*b = temp;
}


void heap2::heapify_topdown1(int idx) // recursive
{
	// leaf node에 도착하면 끝
	if (2 * idx > this->hCnt)
		return;
	if (2 * idx == this->hCnt) {
		if (this->hlist[idx].NOM < this->hlist[2 * idx].NOM)
			swap(&this->hlist[idx], &this->hlist[2 * idx]);
		return;
	}
	// lchild가 rchild보다 크고 lchild가 parent보다 클때
	if (this->hlist[2 * idx].NOM > this->hlist[2 * idx + 1].NOM && this->hlist[2 * idx].NOM > this->hlist[idx].NOM) {
		swap(&this->hlist[idx], &this->hlist[2 * idx]);
		heapify_topdown1(2 * idx);
	}
	// rchild가 lchild보다 크고 lchild가 parent보다 클때
	else if (this->hlist[2 * idx + 1].NOM > this->hlist[2 * idx].NOM && this->hlist[2 * idx + 1].NOM > this->hlist[idx].NOM) {
		swap(&this->hlist[idx], &this->hlist[2 * idx + 1]);
		heapify_topdown1(2 * idx + 1);
	}
}

void heap2::heapify_topdown2(int idx) // recursive
{
	// leaf node에 도착하면 끝
	if (2 * idx > this->hCnt)
		return;
	if (2 * idx == this->hCnt) {
		if (this->hlist[idx].perf < this->hlist[2 * idx].perf)
			swap(&this->hlist[idx], &this->hlist[2 * idx]);
		return;
	}
	// lchild가 rchild보다 크고 lchild가 parent보다 클때
	if (this->hlist[2 * idx].perf > this->hlist[2 * idx + 1].perf && this->hlist[2 * idx].perf > this->hlist[idx].perf) {
		swap(&this->hlist[idx], &this->hlist[2 * idx]);
		heapify_topdown2(2 * idx);
	}
	// rchild가 lchild보다 크고 lchild가 parent보다 클때
	else if (this->hlist[2 * idx + 1].perf > this->hlist[2 * idx].perf && this->hlist[2 * idx + 1].perf > this->hlist[idx].perf) {
		swap(&this->hlist[idx], &this->hlist[2 * idx + 1]);
		heapify_topdown2(2 * idx + 1);
	}
}

void heap2::heapify_bottomup1(int idx) // recursive
{
	// root node에 도착하면 끝
	if (idx == 1)
		return;
	// 부모가 자식보다 작다면
	if (this->hlist[idx / 2].NOM < this->hlist[idx].NOM) {
		swap(&this->hlist[idx / 2], &this->hlist[idx]);
		heapify_bottomup1(idx / 2);
	}
}

void heap2::heapify_bottomup2(int idx) // recursive
{
	// root node에 도착하면 끝
	if (idx == 1)
		return;
	// 부모가 자식보다 작다면
	if (this->hlist[idx / 2].perf < this->hlist[idx].perf) {
		swap(&this->hlist[idx / 2], &this->hlist[idx]);
		heapify_bottomup2(idx / 2);
	}
}

void heap2::push1(trainer ndata)
{
	this->hCnt++;
	strcpy(this->hlist[this->hCnt].tname, ndata.tname);
	this->hlist[this->hCnt].NOM = ndata.NOM;
	this->hlist[this->hCnt].perf = ndata.perf;
	heapify_bottomup1(this->hCnt);
}

void heap2::push2(trainer ndata)
{
	this->hCnt++;
	strcpy(this->hlist[this->hCnt].tname, ndata.tname);
	this->hlist[this->hCnt].NOM = ndata.NOM;
	this->hlist[this->hCnt].perf = ndata.perf;
	heapify_bottomup2(this->hCnt);
}

trainer heap2::pop1()
{
	//   node temp = heap[1];
	trainer temp;
	strcpy(temp.tname, this->hlist[1].tname);
	temp.NOM = this->hlist[1].NOM;
	temp.perf = this->hlist[1].perf;
	//   heap[1] = heap[cnt];
	strcpy(this->hlist[1].tname, this->hlist[this->hCnt].tname);
	this->hlist[1].NOM = this->hlist[this->hCnt].NOM;
	this->hlist[1].perf = this->hlist[this->hCnt].perf;

	this->hCnt--;
	heapify_topdown1(1);

	printf("%s: %2d명 %.2lf\n", temp.tname, temp.NOM, temp.perf);
	return temp;
}

trainer heap2::pop2()
{
	//   node temp = heap[1];
	trainer temp;
	strcpy(temp.tname, this->hlist[1].tname);
	temp.NOM = this->hlist[1].NOM;
	temp.perf = this->hlist[1].perf;
	//   heap[1] = heap[cnt];
	strcpy(this->hlist[1].tname, this->hlist[this->hCnt].tname);
	this->hlist[1].NOM = this->hlist[this->hCnt].NOM;
	this->hlist[1].perf = this->hlist[this->hCnt].perf;

	this->hCnt--;
	heapify_topdown2(1);

	printf("%s: %2d명 %.2lf\n", temp.tname, temp.NOM, temp.perf);
	return temp;
}