// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#include<iostream>

// �����Ǵ� DLL.dll ������
class DLL_API CDLL {
public:
	CDLL(int b = 66) :a(b) {};
	// TODO:  �ڴ�������ķ�����
	void show(void) { std::cout << a << std::endl; }
private:
	int a;
};

extern DLL_API int nDLL;

DLL_API int fnDLL(void);
