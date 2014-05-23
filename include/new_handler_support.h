/*=====================================================================================
模块名  ：
文件名  ：new_handler_support.h
相关文件：
实现功能：处理new对象时失败的情况,设置自定义的new-handler.
作者    ：包增辉(bao.z.h.2008@gmail.com)
版权    ：
---------------------------------------------------------------------------------------
修改记录：
日期        版本    修改人      走读人      修改记录
2014/1/25   V1.0    包增辉                    创建
========================================================================================*/

#ifndef NEW_HANDLER_SUPPORT_H
#define NEW_HANDLER_SUPPORT_H


#include <new>


class NewHandlerHolder
{
public:
	explicit NewHandlerHolder(std::new_handler nh) : m_nhHandler(nh) {}

	~NewHandlerHolder()
	{
		std::set_new_handler(m_nhHandler);
	}

private:
	std::new_handler m_nhHandler;
	
	NewHandlerHolder(const NewHandlerHolder&);            //禁用copy ctor, oper assign
	NewHandlerHolder& operator=(const NewHandlerHolder&);

};




/*==============================================================================
类名    ：NewHandlerSupport
功能    ：
主要接口：         
备注    ：接口类，当一个类想自定义new失败时的new-handler时，可继承此类。
          如：class Widget : public NewHandlerSupport<Widget>.
--------------------------------------------------------------------------------
修改记录：
日  期        版本        修改人            走读人            修改记录
2014/1/26     V1.0        包增辉      
==============================================================================*/
template <typename T>
class NewHandlerSupport
{
public:
	static std::new_handler SetCurrHandler(std::new_handler p) throw();
	static void* operator new(std::size_t size) throw(std::bad_alloc);

private:
	static std::new_handler m_nhCurrHandler;    //保存处理new本类对象 失败时要调用的new_handler
};



template<typename T>
std::new_handler NewHandlerSupport<T>::SetCurrHandler(std::new_handler p) throw()
{
	std::new_handler nhOldHander = m_nhCurrHandler;
	m_nhCurrHandler = p;
	return nhOldHander;
}

template<typename T>
void* NewHandlerSupport<T>::operator new(std::size_t size) throw(std::bad_alloc)
{
	NewHandlerHolder nhhHandlerHolder(std::set_new_handler(m_nhCurrHandler));
	return ::operator new(size);
}

template<typename T>
std::new_handler NewHandlerSupport<T>::m_nhCurrHandler = 0;




#endif