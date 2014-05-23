/*=====================================================================================
模块名  ：
文件名  ：String_eager.h
相关文件：
实现功能：实现string类，eager版本
作者    ：包增辉(bao.z.h.2008@gmail.com)
版权    ：
---------------------------------------------------------------------------------------
修改记录：
日期        版本    修改人      走读人      修改记录
2014/1/4    V1.0    包增辉                    创建
========================================================================================*/


#ifndef STRING_EAGER_H
#define STRING_EAGER_H


#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "new_handler_support.h"
#include "type_def.h"



/*==============================================================================
类名    ：String
功能    ：
主要接口：
备注    ：
--------------------------------------------------------------------------------
修改记录：
日  期        版本        修改人            走读人            修改记录
2014/1/26     V1.0        包增辉
==============================================================================*/
class String : public NewHandlerSupport<String>
{
public:
	String() : m_pcszData(new s8[1])
	{
		*m_pcszData = '\0';
		SetCurrHandler(OutOfMem);     //设置new失败时要调用的new handler.
	}

	String(const s8* str)
	{
		if (str)
		{
			m_pcszData = new s8[strlen(str) + 1];
			strcpy(m_pcszData, str);
		}
		SetCurrHandler(OutOfMem);     //设置new失败时要调用的new handler.
	}

	String(const String& rhs) : m_pcszData(new s8[rhs.size() + 1])
	{
		strcpy(m_pcszData, rhs.c_str());
		SetCurrHandler(OutOfMem);    //设置new失败时要调用的new handler.
	}

	~String()
	{
        delete[] m_pcszData;
        m_pcszData = NULL;
	}

	String& operator=(const String& rhs)
	{
		if (&rhs != this)
        {
			String strTemp(rhs);
			std::swap(m_pcszData, strTemp.m_pcszData);
		}

		return *this;
	}

	String& operator=(const s8* str)
	{
		if (str != m_pcszData)
        {
			String strTemp(str);
			std::swap(m_pcszData, strTemp.m_pcszData);
		}

		return *this;
	}

	size_t size() const
	{
		return strlen(m_pcszData);
	}

	const s8* c_str() const
	{
		return m_pcszData;
	}

	const s8* begin() const
	{
		return m_pcszData;
	}

	const s8* end() const
	{
		s8* pchTemp = m_pcszData;

		while ( *pchTemp != '\0')
		{
			pchTemp++;
		}

		return pchTemp;
	}

	//empty()
	BOOL32 empty() const
	{
		return strlen(m_pcszData) == 0;
	}

	//重载==,>,<    要同时处理const char *, string两种对象
	BOOL32 operator==(const String& rhs) const
	{
		return strcmp(m_pcszData, rhs.m_pcszData) == 0;
	}

	BOOL32 operator==(const s8* str) const
	{
		if (str)
			return strcmp(m_pcszData, str) == 0;
        else
            return FALSE;
	}

	BOOL32 operator<(const String& rhs) const
	{
		return strcmp(m_pcszData, rhs.m_pcszData) < 0;
	}

	BOOL32 operator<(const s8* str) const
	{
		if (str)
			return strcmp(m_pcszData, str) < 0;
	}

	BOOL32 operator>(const String& rhs) const
	{
		return strcmp(m_pcszData, rhs.m_pcszData) > 0;
	}

	BOOL32 operator>(const s8* str) const
	{
		if (str)
			return strcmp(m_pcszData, str) > 0;
	}

	//重载+=,+
	String operator+(const String& rhs)
	{
	    String strTemp(*this);
        strTemp.operator+=(rhs);

        return strTemp;
	}


    //有问题，不应该修改自己缓冲区的值！！！
	String operator+(const s8* str)
	{
		if (str)
		{
            String strRhs(str);

            String strTemp(*this);
            strTemp.operator+=(strRhs);

            return strTemp;
		}
	}

	String& operator+=(const String& rhs)
	{
		s8* pchTemp = new s8[strlen(m_pcszData) + strlen(rhs.m_pcszData) + 1];
		strcpy(pchTemp, m_pcszData);
		strcat(pchTemp, rhs.m_pcszData);

		delete[] m_pcszData;
		m_pcszData = pchTemp;

		return *this;
	}

	String& operator+=(const s8* str)
	{
		if (str)
		{
			s8* pchTemp = new s8[strlen(m_pcszData) + strlen(str) + 1];
			strcpy(pchTemp, m_pcszData);
			strcat(pchTemp, str);

			delete[] m_pcszData;
			m_pcszData = pchTemp;
		}

		return *this;
	}

	operator const char*() const
	{
		return m_pcszData;
	}

	//重载[]
    const s8& operator[](u8 pos) const
	{
		if ( pos < size())
			return  m_pcszData[pos];

		return *m_pcszData;
	}


	s8& operator[](u8 pos)
	{
		if ( pos < size())
			return  m_pcszData[pos];

		return *m_pcszData;
	}



	void swap(String& rhs)
	{
		if (&rhs != this)
		{
			std::swap(m_pcszData, rhs.m_pcszData);
		}
	}

	//定义string new 失败时要调用的new-handler.
	static void OutOfMem()
	{
		printf("alloc string error.Unable to satisfy request for memory.\n");
		abort();
	};

private:
	s8* m_pcszData;
};

std::ostream& operator<<(std::ostream &out,const String &str);



#endif

