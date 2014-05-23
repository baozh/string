/*=====================================================================================
模块名  ：
文件名  ：test.cpp
相关文件：
实现功能：做一些功能测试、边界测试
作者    ：包增辉(bao.z.h.2008@gmail.com)
版权    ：
---------------------------------------------------------------------------------------
修改记录：
日期        版本    修改人      走读人      修改记录
2014/1/25   V1.0    包增辉                    创建
========================================================================================*/







#define BOOST_TEST_MAIN    //定义主测试套件，是测试main函数入口
#ifdef BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#else
#include <boost/test/included/unit_test.hpp>
#endif


#include "string_sso.h"


using namespace boost;



//开始测试套件
BOOST_AUTO_TEST_SUITE(s_string)

//测试用例
BOOST_AUTO_TEST_CASE(testEmptyString)
{
    String_sso s1;
    BOOST_CHECK_EQUAL(s1.empty(), TRUE);
    BOOST_CHECK_EQUAL(s1.size(), 0);
    BOOST_CHECK_EQUAL(s1.begin(), s1.end());
    BOOST_CHECK_EQUAL(strcmp(s1.c_str(), ""), 0);

    String_sso s2(s1);
    BOOST_CHECK_EQUAL(s2.empty(), TRUE);
    BOOST_CHECK_EQUAL(s2.size(), 0);
    BOOST_CHECK_EQUAL(s2.begin(), s1.end());
    BOOST_CHECK_EQUAL(strcmp(s2.c_str(), ""), 0);

    BOOST_CHECK_EQUAL(s2 == "", TRUE);
    BOOST_CHECK_EQUAL(s2 == "a", FALSE);

    BOOST_CHECK_EQUAL(s2 < "a", TRUE);
    BOOST_CHECK_EQUAL(s2 > "a", FALSE);

    String_sso s3 = s2 + "baozenghui";
    BOOST_CHECK_EQUAL(s3 == "baozenghui", TRUE);
    BOOST_CHECK_EQUAL(s3 > "baozenghui", FALSE);
    BOOST_CHECK_EQUAL(s3 > "baozenghuia", FALSE);
    BOOST_CHECK_EQUAL(s3 > "baozenghu", TRUE);

    BOOST_CHECK_EQUAL(s3 < "baozenghui", FALSE);
    BOOST_CHECK_EQUAL(s3 < "baozenghuia", TRUE);
    BOOST_CHECK_EQUAL(s3 < "baozenghu", FALSE);

    BOOST_CHECK_EQUAL(s3[0] ,'b');
    BOOST_CHECK_EQUAL(s3[3] ,'z');
    BOOST_CHECK_EQUAL(s3[9] ,'i');
  }

//测试用例
BOOST_AUTO_TEST_CASE(testCopyAndAssignment)
{
  String_sso empty;
  String_sso s1(empty);
  BOOST_CHECK_EQUAL(s1.empty(), TRUE);
  BOOST_CHECK_EQUAL(s1.size(), 0);
  BOOST_CHECK_EQUAL(s1.begin(), s1.end());
  BOOST_CHECK_EQUAL(strcmp(s1.c_str(), ""), 0);

  String_sso s2("chenshuo");
  BOOST_CHECK_EQUAL(s2.empty(), FALSE);
  BOOST_CHECK_EQUAL(s2.size(), 8);
  BOOST_CHECK_EQUAL(s2.end() - s2.begin(), 8);
  BOOST_CHECK_EQUAL(strcmp(s2.c_str(), "chenshuo"), 0);

  String_sso s3(s2);
  BOOST_CHECK(s2.c_str() != s3.c_str());
  BOOST_CHECK_EQUAL(s3.empty(), FALSE);
  BOOST_CHECK_EQUAL(s3.size(), 8);
  BOOST_CHECK_EQUAL(s3.end() - s3.begin(), 8);
  BOOST_CHECK_EQUAL(strcmp(s3.c_str(), "chenshuo"), 0);

  String_sso s4 = s2;
  BOOST_CHECK(s2.c_str() != s4.c_str());
  BOOST_CHECK_EQUAL(s4.empty(), FALSE);
  BOOST_CHECK_EQUAL(s4.size(), 8);
  BOOST_CHECK_EQUAL(s4.end() - s4.begin(), 8);
  BOOST_CHECK_EQUAL(strcmp(s4.c_str(), "chenshuo"), 0);

  const char* olds3 = s3.c_str();
  s3 = "";
  BOOST_CHECK_EQUAL(s3.c_str(), olds3);
  BOOST_CHECK_EQUAL(s3.empty(), TRUE);
  BOOST_CHECK_EQUAL(s3.size(), 0);
  BOOST_CHECK_EQUAL(s3.end() - s3.begin(), 0);
  BOOST_CHECK_EQUAL(strcmp(s3.c_str(), ""), 0);

  s3 = s2;
  BOOST_CHECK(s2.c_str() != s3.c_str());
  BOOST_CHECK_EQUAL(s3.c_str(), olds3);
  BOOST_CHECK_EQUAL(s3.empty(), FALSE);
  BOOST_CHECK_EQUAL(s3.size(), 8);
  BOOST_CHECK_EQUAL(s3.end() - s3.begin(), 8);
  BOOST_CHECK_EQUAL(strcmp(s3.c_str(), "chenshuo"), 0);

  s3 = s3;
  BOOST_CHECK_EQUAL(s3.c_str(), olds3);
  BOOST_CHECK_EQUAL(s3.empty(), FALSE);
  BOOST_CHECK_EQUAL(s3.size(), 8);
  BOOST_CHECK_EQUAL(s3.end() - s3.begin(), 8);
  BOOST_CHECK_EQUAL(strcmp(s3.c_str(), "chenshuo"), 0);

  s3 = "muduo";
  BOOST_CHECK_EQUAL(s3.empty(), FALSE);
  BOOST_CHECK_EQUAL(s3.size(), 5);
  BOOST_CHECK_EQUAL(s3.end() - s3.begin(), 5);
  BOOST_CHECK_EQUAL(strcmp(s3.c_str(), "muduo"), 0);

  s3 = "chenshuo.com";
  BOOST_CHECK_EQUAL(s3.empty(), FALSE);
  BOOST_CHECK_EQUAL(s3.size(), 12);
  BOOST_CHECK_EQUAL(s3.end() - s3.begin(), 12);
  BOOST_CHECK_EQUAL(strcmp(s3.c_str(), "chenshuo.com"), 0);

  s3 = "https://github.com/baozh/documents/downloads";
  BOOST_CHECK(s3.c_str() != olds3);
  BOOST_CHECK_EQUAL(s3.empty(), FALSE);
  BOOST_CHECK_EQUAL(s3.size(), 44);
  BOOST_CHECK_EQUAL(s3.end() - s3.begin(), 44);
  BOOST_CHECK_EQUAL(strcmp(s3.c_str(), "https://github.com/baozh/documents/downloads"), 0);

  const char* olds4 = s4.c_str();
  s4 = "muduo network library";
  BOOST_CHECK(s4.c_str() != olds4);
  BOOST_CHECK_EQUAL(s4.empty(), FALSE);
  BOOST_CHECK_EQUAL(s4.size(), 21);
  BOOST_CHECK_EQUAL(s4.end() - s4.begin(), 21);
  BOOST_CHECK_EQUAL(strcmp(s4.c_str(), "muduo network library"), 0);

  s3 = s4;
  BOOST_CHECK_EQUAL(s3.empty(), FALSE);
  BOOST_CHECK_EQUAL(s3.size(), 21);
  BOOST_CHECK_EQUAL(s3.end() - s3.begin(), 21);
  BOOST_CHECK_EQUAL(strcmp(s3.c_str(), "muduo network library"), 0);

  s3 = "https://github.com/baozh/documents/downloads/";
  s4 = s3;
  BOOST_CHECK_EQUAL(s4.empty(), FALSE);
  BOOST_CHECK_EQUAL(s4.size(), 45);
  BOOST_CHECK_EQUAL(s4.end() - s4.begin(), 45);
  BOOST_CHECK_EQUAL(strcmp(s4.c_str(), "https://github.com/baozh/documents/downloads/"), 0);
}


BOOST_AUTO_TEST_CASE(testStringStore)
{
  String_sso empty;
  String_sso s1(empty);
  BOOST_CHECK_EQUAL(s1.empty(), TRUE);
  BOOST_CHECK_EQUAL(s1.size(), 0);
  BOOST_CHECK_EQUAL(s1.begin(), s1.end());
  BOOST_CHECK_EQUAL(strcmp(s1.c_str(), ""), 0);

  String_sso s2("chenshuo");
  BOOST_CHECK_EQUAL(s2.empty(), FALSE);
  BOOST_CHECK_EQUAL(s2.size(), 8);
  BOOST_CHECK_EQUAL(s2.end() - s2.begin(), 8);
  BOOST_CHECK_EQUAL(strcmp(s2.c_str(), "chenshuo"), 0);

  String_sso s3("baozenghui");

  String_sso s4 = s3 + "11111";
  BOOST_CHECK_EQUAL(s3.size(), 10);
  BOOST_CHECK_EQUAL(s4.size(), 15);
  BOOST_CHECK_EQUAL(s4 < s3, FALSE);

  String_sso s5 = s4 + "111";
  BOOST_CHECK_EQUAL(s5.size(), 18);
  BOOST_CHECK_EQUAL(s4 < s5, TRUE);

}




//结束测试套件
BOOST_AUTO_TEST_SUITE_END()



