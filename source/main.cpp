/*=====================================================================================
模块名  ：
文件名  ：main.cpp
相关文件：
实现功能：
作者    ：包增辉(bao.z.h.2008@gmail.com)
版权    ：
---------------------------------------------------------------------------------------
修改记录：
日期             版本    修改人      走读人      修改记录
2014-02-07      V1.0    包增辉                   创建
========================================================================================*/



#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "string_eager.h"
#include <vector>
#include <map>
#include <algorithm>
#include "type_def.h"


using namespace std;


void foo(String x)
{
}

void bar(const String& x)
{
}

String baz()
{
  String ret("world");
  return ret;
}


void printElem(pair<const String, u32>& elem)
{
	cout << elem.first << "," << elem.second << endl;
}



/*
int main()
{


	String s0;
	String s1("hello");
	String s2(s0);
	String s3(s1);
	s2 = s1;
	s3 = s3;
	s1 = "aewsome";


	foo(s1);
	bar(s1);
	foo("temporary");
	bar("temporary");
	String s4 = baz();
	s4 = baz();

	std::vector<String> svec;
	svec.push_back(s0);
	svec.push_back(s1);
	svec.push_back("good job");


	String str = "baozenghui, hello world!";
	cout<<str<<endl;

	map<String, u32> mapStudent;
	mapStudent["LiMin"] = 90;
	mapStudent["ZiLinMi"] = 79;
	mapStudent["BoB"] = 92;
	mapStudent.insert(make_pair("Bing",99));
	mapStudent.insert(make_pair("Albert",86));

	for_each(mapStudent.begin(), mapStudent.end(), printElem);

    printf("cnt = %d\n", strlen("https://github.com/baozh/documents/downloads"));

	return 0;
}

*/
