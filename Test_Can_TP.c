#include "Test.h"

void Test_CanTp_Init(enum CanTp_StateType, enum expected)
{
	if(expected == CanTp_StateType)
	{
		printf("n\%s Passed");
	}
	else
	{
		printf("n\%s FAILED expected: %d CanTp_StateType: %d", expected, CanTp_StateType);
	}
	
}

void Test_CanTp_Shutdown(enum CanTp_StateType, enum expected)
{
	if(expected == CanTp_StateType)
	{
		printf("n\%s Passed");
	}
	else
	{
		printf("n\%s FAILED expected: %d CanTp_StateType: %d", expected, CanTp_StateType);
	}
	
}

void test(void)
{

test_CanTp_Init(CANTP_ON, CanTp_Init(const CanTpConfig *CfgPtr));   
test_CanTp_Shutdown(CANTP_OFF,CanTp_Shutdown(void));       
}

void all_tests(void)
{
  test();   
}


int main()
{
	test();
}