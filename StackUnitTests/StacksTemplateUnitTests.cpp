#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Stacks/TStack.h"
using namespace StackTemplate;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackUnitTests
{		

	const int iTestRuns = 10000;

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
		TEST_METHOD(PushPop_MultiThread_DynMem)
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
		TEST_METHOD(PushPopClear_MultiThread_FixedMem)
		{

		}
		TEST_METHOD(PushPopClear_MultiThread_DynMem)
		{

		}

	};
}