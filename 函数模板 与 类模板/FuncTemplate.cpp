#include "FuncTemplate.h"


int main()
{
	AluPrint(42);      // int特化模板
	AluPrint(3.14f); //float特化模板

	AluPrint("xx"); // 通用模板

	return 0;
}