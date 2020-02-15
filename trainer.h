#pragma once

#include "member.h"

class trainer {
public:
	char tname[10];
	int NOM;
	double perf;
};

class trainers {
public:
	trainer* tlist;
	int trCnt;
	int trN;

	void init(int n);
	int isEmpty();
	void set(member key);
	void insert(member key);
	trainer pop();
};