#include "pch.h"
#include "CppUnitTest.h"

#include "Aquarium.h"
#include "FishBeta.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CAquariumTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCAquariumConstruct)
		{
			CAquarium aquarium;
		}

		TEST_METHOD(TestCAquariumHitTest)
		{
			CAquarium aquarium;

			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty aquarium");

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(100, 200);
			aquarium.Add(fish1);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish1,
				L"Testing fish at 100, 200");

			Assert::IsFalse(aquarium.HitTest(10, 210) == fish1,
				L"Testing fish at 10, 210");
			Assert::IsTrue(aquarium.HitTest(10, 210) == nullptr,
				L"Testing fish at 10, 210");
			
			shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(&aquarium);
			fish2->SetLocation(100, 200);
			aquarium.Add(fish2);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish2,
				L"Testing fish at 100, 200");
		}

		//Below is a test for the MoveToEnd function
		//I altered the return for this test to verify that it works
		//TEST_METHOD(TestCAquariumMoveToEndTest) 
		//{
		//	CAquarium aquarium;

		//	shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
		//	fish1->SetLocation(100, 200);
		//	aquarium.Add(fish1);

		//	shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(&aquarium);
		//	fish1->SetLocation(153, 210);
		//	aquarium.Add(fish2);

		//	Assert::IsTrue(aquarium.MoveToEnd(fish1) == fish1);

		//}

	};
}