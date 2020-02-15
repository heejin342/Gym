#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trainer.h"

void trainers::init(int n)
{
	this->trN = n;
	this->trCnt = 0;
	this->tlist = (trainer*)malloc(this->trN * sizeof(trainer));
}

int trainers::isEmpty()
{
	if (this->trCnt == 0)
		return 1;
	return 0;
}

void trainers::set(member key)
{
	strcpy(this->tlist[this->trCnt].tname, key.trainer);
	this->tlist[this->trCnt].NOM = 1;
	this->tlist[this->trCnt].perf = key.gr;
	this->trCnt++;
}

void trainers::insert(member key)
{
	int i;
	if (this->trCnt == 0) {
		this->set(key);
		return;
	}
	else {
		for (i = 0; i < this->trCnt; i++) {
			if (strcmp(this->tlist[i].tname, key.trainer) == 0) {
				this->tlist[i].perf = (this->tlist[i].perf * (double)this->tlist[i].NOM + key.gr)
					/ ((double)this->tlist[i].NOM + (double)1);
				this->tlist[i].NOM++;
				return;
			}
		}
		this->set(key);
		return;
	}
}

trainer trainers::pop()
{
	trainer temp = this->tlist[trCnt - 1];
	this->trCnt--;
	return temp;
}