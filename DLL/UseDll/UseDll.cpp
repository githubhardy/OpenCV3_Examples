// UseDll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Dll.h"
#include <iostream>
int main()
{
	//类
	CDLL a(333);
	a.show();
	//函数
	std::cout << fnDLL() << std::endl;
	//变量
	std::cout << nDLL << std::endl;

	system("pause");
    return 0;
}


