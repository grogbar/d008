#include "stdafx.h"
#include "CppUnitTest.h"
#include "../d008/action.h"
#include "../d008/FunClass.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsProc
{
	TEST_CLASS(UnitTest)
	{
	public:
		TEST_METHOD(Proc__constructor)
		{
			// Just a simple constructor test
			FunClass foo4;
			
			//std::string s = obj.command;
			std::string sValid = "";
			//Assert::AreEqual(sValid, obj.get_command());
		}
	};
}