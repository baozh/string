/*=====================================================================================
ģ����  ��
�ļ���  ��new_handler_support.h
����ļ���
ʵ�ֹ��ܣ�����new����ʱʧ�ܵ����,�����Զ����new-handler.
����    ��������(bao.z.h.2008@gmail.com)
��Ȩ    ��
---------------------------------------------------------------------------------------
�޸ļ�¼��
����        �汾    �޸���      �߶���      �޸ļ�¼
2014/1/25   V1.0    ������                    ����
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
	
	NewHandlerHolder(const NewHandlerHolder&);            //����copy ctor, oper assign
	NewHandlerHolder& operator=(const NewHandlerHolder&);

};




/*==============================================================================
����    ��NewHandlerSupport
����    ��
��Ҫ�ӿڣ�         
��ע    ���ӿ��࣬��һ�������Զ���newʧ��ʱ��new-handlerʱ���ɼ̳д��ࡣ
          �磺class Widget : public NewHandlerSupport<Widget>.
--------------------------------------------------------------------------------
�޸ļ�¼��
��  ��        �汾        �޸���            �߶���            �޸ļ�¼
2014/1/26     V1.0        ������      
==============================================================================*/
template <typename T>
class NewHandlerSupport
{
public:
	static std::new_handler SetCurrHandler(std::new_handler p) throw();
	static void* operator new(std::size_t size) throw(std::bad_alloc);

private:
	static std::new_handler m_nhCurrHandler;    //���洦��new������� ʧ��ʱҪ���õ�new_handler
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