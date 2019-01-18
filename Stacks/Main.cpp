

#include "pch.h"
#include <iostream>

#include "Stacks.h"
#include "TStack.h"
using namespace StackTemplate;


void PracticeStackTemplates()
{
	printf("\nTemplate Stack Practice");
	printf("\n--Fixed Mem--");

	TStack<int> Stack(TStack<int>::eAT_FixedMem, 1024);

	int Data[] = { 0, 1, 2, 3, 4, 5 };
	int DataSize = (sizeof(Data) / sizeof(int));

	for (int x = 0; x < DataSize; x++) {
		Stack.Push(Data[x]);
	}
	for (int x = 0; x < DataSize; x++) {
		int data;
		Stack.Pop(data);
		printf("\n %d", data);
	}
	// test "Popping" from an empty stack
	int temp;
	Stack.Pop(temp);
	for (int x = DataSize - 1; x >= 0; x--) {
		Stack.Push(Data[x]);
	}
	printf("\n");
	for (int x = 0; x < DataSize; x++) {
		int data;
		Stack.Pop(data);
		printf("\n %d", data);
	}

	printf("\n--Dynamic Memory--");
	TStack<float> Stack2(TStack<float>::eAT_DynamicMem, 1024);

	float Dataf[] = { 0.f, 1.1f, 2.2f, 3.3f, 4.f, 5.f };
	int DataSizef = (sizeof(Dataf) / sizeof(int));

	for (int x = 0; x < DataSizef; x++) {
		Stack2.Push(Dataf[x]);
	}
	for (int x = 0; x < DataSizef; x++) {
		float data;
		Stack2.Pop(data);
		printf("\n %f", data);
	}
	// test "Popping" from an empty stack
	float tempf;
	Stack2.Pop(tempf);
	for (int x = DataSizef - 1; x >= 0; x--) {
		Stack2.Push(Dataf[x]);
	}
	printf("\n");
	for (int x = 0; x < DataSizef; x++) {
		float data;
		Stack2.Pop(data);
		printf("\n %f", data);
	}

}


void PracticeStackFixed()
{
	FixedStack Stack(100);

	printf("\nFixed Stack Practice");

	int Data[] = { 0, 1, 2, 3, 4, 5 };
	int DataSize = (sizeof(Data) / sizeof(int));

	for (int x = 0; x < DataSize; x++) {
		Stack.Push(Data[x]);
	}
	for (int x = 0; x < DataSize; x++) {
		printf("\n %d", Stack.Pop());
	}
}

int main()
{
	PracticeStackTemplates();
	PracticeStackFixed();
}
