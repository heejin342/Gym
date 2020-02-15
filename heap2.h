
#include "trainer.h"

class heap2 {
public:
	trainer* hlist;
	int hCnt;
	int hN;

	void init(int n);
	int isEmpty();
	void swap(trainer* a, trainer* b);
	void heapify_topdown1(int idx);
	void heapify_topdown2(int idx);
	void heapify_bottomup1(int idx);
	void heapify_bottomup2(int idx);
	void push1(trainer ndata);
	void push2(trainer ndata);
	trainer pop1();
	trainer pop2();
};

