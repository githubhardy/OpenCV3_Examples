// UseDll.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Dll.h"
#include <iostream>
int main()
{
	//��
	CDLL a(333);
	a.show();
	//����
	std::cout << fnDLL() << std::endl;
	//����
	std::cout << nDLL << std::endl;

	system("pause");
    return 0;
}


