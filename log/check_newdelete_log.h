//----------------------------------------->
// 1. new    placement new   operator new  ��  ::operator new
// 1. new��������ִ�й���
//        a. ����operator new�����ڴ�
//		  b. ���ù��캯�����������
//        c. ������Ӧָ��
// 2. new�����������޷�������,
//
//
//<-----------------------------------------

#pragma once


#ifdef _DEBUG

#include<new>
#include"OperatorNewCountInfo.h"

extern  void * get_log( char * file,char * function, int line,bool isdelete,void * p);
extern  void   get_log_pre( char * file,char * function, int line);


void *  operator new(std::size_t _Count , char * file,char * function, int line  );
void *  operator new[](std::size_t _Count , char * file,char * function, int line);

void  operator delete(void * object );
void  operator delete[](void * object );









#define new	 new(__FILE__,__FUNCSIG__,__LINE__)

//����delete�Ļ��ƣ� ���صĳɶԵ� new�� delete ֻ����new ���䷢���쳣ʱ��
//delete�Żᱻ���������ã� �Լ��޷����ã�  �ɱ��������ã�  ֻ���ṩ�� ����
// û���� ,�����쳣ʱ���ļ����ܲ��ᱻ������д�롣
#define delete      get_log_pre( __FILE__,__FUNCSIG__,__LINE__);delete





#endif



