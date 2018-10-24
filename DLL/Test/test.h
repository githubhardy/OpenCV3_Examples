#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;
/*
试题一
1.C++ class
1.编写一个不带指针成员变量的Test类。
2.要求写构造函数，析构函数，拷贝构造函数，赋值函数。
3.要求写出必要的测试代码。
*/

class Test
{
public:

	Test(int q = 0, int w = 0) :a(q), b(w) {};
	~Test() {};
	Test(const Test& temp)
	{
		a = temp.a;
		b = temp.b;
	}
	Test & operator =(const Test &other);
	void show() { cout << endl << "a = " << a << "  b = " << b << endl; };
private:
	unsigned int a, b;
};

//复制运算
Test& Test::operator =(const Test &other)
{
	if (this == &other)
		return *this;
	a = other.a;
	b = other.b;
	return *this;
}

//试题一 测试
void Test1(void)
{
	Test test1(3, 2); test1.show();
	Test test2;
	test2 = test1; test2.show(); //已经存在的对象	
	Test test3(test1); test3.show();//新的对象
}
/*
试题二
C++ with pointer class
    1.编写一个带指针成员变量的String类
	2.要求编写构造函数，析构函数，拷贝构造函数，赋值函数。
	3.要求写出必要的测试代码。
	*/

class String1
{
public:
	String1(const char *str = NULL);
	String1(const String1 &rhs);
	String1& operator =(const String1 &rhs);
	~String1(void) { delete[]data; };
	void show(void);
private:
	char *data;
};

String1::String1(const char *str)
{
	if (NULL == str)
	{
		data = new char[1];
		*data = '\0';
	}
	else
	{
		data = new char[strlen(str) + 1];
		strcpy(data, str);
	}
}

String1::String1(const String1 &rhs)
{
	//拷贝构造，不需要自赋值检查
	data = new char[strlen(rhs.data) + 1];
	strcpy(data, rhs.data);
}

String1& String1::operator =(const String1 &rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	//经常会忘记删除自己
	delete[]data;
	data = NULL;

	data = new char[strlen(rhs.data) + 1];
	strcpy(data, rhs.data);
	return *this;
}
void String1::show(void)
{
	char * p = data;//每次都需要重新刷新指针
	while (*p != '\0')
	{
		cout << *p;
		++p;
	}
	cout << endl;

	//第二种输出方法
	//printf("%s\n", data);
}

//试题二 测试
void Test2_String(void)
{
	String1 str1("test string");
	str1.show();
	String1 str2(str1);
	str2.show();
	String1 str3;
	str3 = str1;
	str3.show();
}

/*
3.
  vector
    建立一个vector对象，
	增加N个元素，并对vector对象进行遍历。
	删除1个元素，并对vector对象进行遍历。
	*/

void vector_show(const vector<int>& vec)
{
	auto iter_ben = vec.begin();
	auto iter_end = vec.end();
	cout << "vector: " << endl;
	for (; iter_ben != iter_end; iter_ben++)
	{
		cout << *iter_ben << " ";
	}
	cout << endl;
}

void Test3_vector(void)
{
	vector<int> my_vector;
	for (int i = 0; i < 10; i++)
	{
		my_vector.push_back(i);
	}

	vector_show(my_vector);//0-9
	my_vector.pop_back();
	vector_show(my_vector);//0-8



	//vector<int>::iterator iter = my_vector.end(); //十分坑爹，这里的迭代器还是9，但是9上一步已经删掉，软件报容器越界,虽然size()是正确的，但是迭代器是错误的。
	//vector<int>::iterator iter1 = my_vector.begin();
	//my_vector.erase(iter);
	//vector_show(my_vector);

	//最简洁的遍历方式
	for (auto &c : my_vector)
	{
		cout << c << " ";
	}
	cout << endl;
}

/*
list
建立一个list对象，
  增加N个元素，并对list对象进行遍历。
  在list对象的头部，删除1个元素；在尾部，也删除1个元素;并对list对象进行遍历。
  */
void list_show(const list<int>& list1)
{
	auto list_ben = list1.begin();
	auto list_end = list1.end();
	cout << "list: " << endl;
	for (; list_ben != list_end; list_ben++)
	{
		cout << *list_ben << " ";
	}
	cout << endl;
}

void Test4_list(void)
{
	list<int> my_list;
	for (int i = 0; i<10; i++)
	{
		//my_list.insert(list_end, i); //list<int>::iterator list_ben = my_list.begin();
		my_list.push_back(i);
	}
	list_show(my_list);

	my_list.pop_front();
	list_show(my_list);
	my_list.pop_back();
	for (auto &listtemp : my_list)
	{
		cout << listtemp << " ";
	}
	cout << endl;
}


/*
5.
  map
    建立一个map对象，
	增加N个元素，并对map对象进行遍历。
	删除1个元素，并对map对象进行遍历。

	*/

void Test5_map()
{
	map<int, int> my_map;
	for (int i = 0, j = 0; i < 10; i++, j++)
	{
		my_map.insert(pair<int, int>(i, j));
	}
	cout << "map: " << endl;
	for (auto &temp : my_map)
	{
		cout << temp.first << "--" << temp.second << " ";
	}
	cout << endl;
	my_map.erase(1);
	cout << "map: " << endl;
	for (auto &temp : my_map)
	{
		cout << temp.first << "--" << temp.second << " ";
	}
	cout << endl;
}

/*
6.vector扩展题
  关于vector，我们需要做到这样的效果：
  std::vetor vec......;
  ......
  vec[0][2] = 5;
  也就是说，把vector做成可以像二维数组使用的方式，如何实现？
  */

void Test6_doublevect()
{
	int c = 5, r = 5;
	int count = 0;
	vector<vector<int> > doublevect(r, vector<int>(c, 0));//初始化所有值为0

														  //使用数组方法赋值
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < r; j++)
		{
			doublevect[i][j] = count;
			count++;
		}
	}

	/*使用迭代器方式遍历*/
	cout << "double vector show:" << endl;
	for (auto it_vv = doublevect.begin(); it_vv != doublevect.end(); ++it_vv)
	{
		for (auto it_v = it_vv->begin(); it_v != it_vv->end(); it_v++)
		{ //迭代器的使用方法和指针类似
			cout << *it_v << " ";
		}
		cout << " " << endl;
	}
}
/*
7.
新建一个项目，然后执行如下操作：
建立一个BaseClass类（一个抽象类），要求如下：
类中包含以下成员：一个char*类型的成员变量；一个纯虚函数，函数内容可以自定义。
请写出对应的无参构造函数，析构函数，拷贝构造函数，赋值函数。
建立一个SubClass类（一个可以实例化的类），要求如下：
SubClass 继承BaseClass；
类中包含以下成员：一个init*类型的成员变量；
请写出对应的无参构造函数，析构函数，拷贝构造函数，赋值函数。
 
 在main函数中：建立一个vector，vector容器内的类型是BaseClass*；
 在vector中加入N个元素（N的数值可以通过1个变量定义），新加入的元素，是通过动态内存分配的；
 在main退出时，遍历vector容器，做必要的内存释放工作；

 */

class BaseClass {
public:
	virtual void show(void) = 0;//纯虚函数，基类不能实例！注意！
	//无参构造函数(默认构造函数)
	BaseClass()
	{
		data = new char[1];
		*data = '\0';
	};
	//BaseClass(char *temp) :data(temp) {};
	//析构函数
	virtual ~BaseClass();
	//拷贝构造函数 （将会新建对象）
	BaseClass(const BaseClass &temp);
	//赋值函数(已存在在对象)
	BaseClass& operator =(const BaseClass &temp);

private:
	char *data;
};

BaseClass::~BaseClass()
{
	if (NULL != data)
	{
		delete[]data;
		data = NULL;
	}
}

BaseClass::BaseClass(const BaseClass &temp)
{
	data = temp.data;
}


BaseClass& BaseClass::operator =(const BaseClass &temp)
{
	if (this == &temp)
	{
		return *this;
	}

	delete[]data;
	data = NULL;

	data = new char[strlen(temp.data) + 1];
	strcpy(data, temp.data);
	return *this;
}


class SubClass : public BaseClass
{
public:
	SubClass() { sub = 1; };
	~SubClass() {};
	SubClass(const SubClass &temp);
	SubClass& operator =(const SubClass &temp);
	void show(void);
private:
	int sub;
};

SubClass::SubClass(const SubClass &temp) :BaseClass(temp)
{
	sub = temp.sub;
}

SubClass& SubClass::operator =(const SubClass &temp)
{
	if (this == &temp)
	{
		return *this;
	}
	BaseClass::operator=(temp);//调用基类的函数
	sub = temp.sub;
	return *this;
}

void SubClass::show(void)
{
	cout << sub;
}
void Test7()
{
	/*
	在main函数中：建立一个vector，vector容器内的类型是BaseClass*；
	在vector中加入N个元素（N的数值可以通过1个变量定义），新加入的元素，是通过动态内存分配的；
	在main退出时，遍历vector容器，做必要的内存释放工作；
	*/
	vector<BaseClass*> vect_point;
	const int N = 10;

	SubClass sub;

	for (int i = 0; i < N; i++)
	{
		BaseClass * p = new SubClass();
		vect_point.push_back(p);
	}

	for (int i = 0; i < N; i++)
	{
		delete[] vect_point[i];
		vect_point[i] = nullptr;
	}
}

/*
8.
建立一个基于dll的项目，导出一个Class，一个函数，一个变量。
建立一个测试项目，测试此dll项目。
*/



/*
9.
建立一个基于Unicode的项目(exe类型)，实现以下功能
1).char* 到 wchar_t*的转换；wchar_t * 到 char *的转换；
2).CString 到 TCHAR*的转换；TCHAR* 到CString的转换；
3).std::string/ std::wstring 到 TCHAR*的转换；
4).TCHAR* 到std::string/ std::wstring的转换；
5).CStringA 到 CString的转换；CString 到 CStringA的转换；
*/





