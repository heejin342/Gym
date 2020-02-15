#pragma once 

#define MAX_SIZE 500

typedef struct _element
{
	char mName[10];
	int rCnt;
}element;

class heap
{
private:
	element recoList[MAX_SIZE];
	int recoCnt;
	
	void swap(element& e1, element& e2);
public:
	heap();
	void heapify_bottomUp(int idx);
	void heapify_topDown(int idx);
	void Insert(const char* name);

	element Pop();
	element Top() const;
};
