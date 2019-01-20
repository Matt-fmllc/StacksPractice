#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Stacks/TStack.h"
using namespace StackTemplate;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackUnitTests
{		

	const int iTestRuns = 10000;

	void HitStack(TStack<int>* Stack)
	{
		std::srand(7654321);
		int iTestVals[iTestRuns] = { 0 };

		for (int x = 0; x < iTestRuns; x++) {
			iTestVals[x] = std::rand();
			Stack->Push(iTestVals[x]);
		}

		int iVal;
		for (int x = 0; x < iTestRuns; x++) {
			Stack->Pop(iVal);
			// with 3 random sources, no guarantee
			// that anything that was put in is still
			// there or in any order
			//Assert::AreEqual(iVal, iTestVals[(iTestRuns - 1) - x]);
		}
	}

	TEST_CLASS(StacksTemplateUnitTests)
	{
	public:
		
		TEST_METHOD(PushPopTest_FixedMem)
		{
			TStack<int> Stack(TStack<int>::eAT_FixedMem, iTestRuns+1);
			std::srand(7654321);
			int iTestVals[iTestRuns] = { 0 };

			for (int x = 0; x < iTestRuns; x++) {
				iTestVals[x] = std::rand();
				Stack.Push(iTestVals[x]);
			}

			int iVal;
			for (int x = 0; x < iTestRuns; x++) {
				Stack.Pop(iVal);
				Assert::AreEqual(iVal, iTestVals[(iTestRuns-1) - x]);
			}

		}
		TEST_METHOD(PushPopTest_DynMem)
		{
			TStack<int> Stack(TStack<int>::eAT_DynamicMem, 1024);
			std::srand(7654321);
			int iTestVals[iTestRuns] = { 0 };

			for (int x = 0; x < iTestRuns; x++) {
				iTestVals[x] = std::rand();
				Stack.Push(iTestVals[x]);
			}

			int iVal;
			for (int x = 0; x < iTestRuns; x++) {
				Stack.Pop(iVal);
				Assert::AreEqual(iVal, iTestVals[(iTestRuns-1) - x]);
			}
		}
		TEST_METHOD(PushPopClearPopTest_FixedMem)
		{
			TStack<int> Stack(TStack<int>::eAT_FixedMem, iTestRuns+1);
			std::srand(7654321);
			int iTestVals[iTestRuns] = { 0 };

			for (int x = 0; x < iTestRuns; x++) {
				iTestVals[x] = std::rand();
				Stack.Push(iTestVals[x]);
			}

			int iVal;
			for (int x = 0; x < iTestRuns; x++) {
				Stack.Pop(iVal);
				Assert::AreEqual(iVal, iTestVals[(iTestRuns-1) - x]);
			}
		}
		TEST_METHOD(PushPopClearPopTest_DynMem)
		{
			TStack<int> Stack(TStack<int>::eAT_DynamicMem, 1024);
			std::srand(7654321);
			int iTestVals[iTestRuns] = { 0 };

			for (int x = 0; x < iTestRuns; x++) {
				iTestVals[x] = std::rand();
				Stack.Push(iTestVals[x]);
			}

			int iVal;
			for (int x = 0; x < iTestRuns; x++) {
				Stack.Pop(iVal);
				Assert::AreEqual(iVal, iTestVals[(iTestRuns-1) - x]);
			}

		}
		TEST_METHOD(PushPop_MultiThread_FixedMem)
		{
			TStack<int> Stack(TStack<int>::eAT_FixedMem, iTestRuns + 1);

			std::thread T1(HitStack, &Stack);
			std::thread T2(HitStack, &Stack);
			std::thread T3(HitStack, &Stack);

			T1.join();
			T2.join();
			T3.join();
		}
		TEST_METHOD(PushPop_MultiThread_DynMem)
		{
			TStack<int> Stack(TStack<int>::eAT_DynamicMem, 1024);

			std::thread T1(HitStack, &Stack);
			std::thread T2(HitStack, &Stack);
			std::thread T3(HitStack, &Stack);

			T1.join();
			T2.join();
			T3.join();
		}
		TEST_METHOD(PushPopClear_MultiThread_FixedMem)
		{

		}
		TEST_METHOD(PushPopClear_MultiThread_DynMem)
		{

		}

	};
}