
#include"stdafx.h"


#ifdef _DEBUG
#include "OperatorNewCountInfo.h"

#include <fstream>
#include <ios>
using std::hex;
using std::dec;





COperatorNewCountInfo  g_objNewCountInfo;
log_pre           g_log_pre;




COperatorNewCountInfo::COperatorNewCountInfo(void)
{
	stc_log_info  objTmp;
	memset(&objTmp,0,sizeof(objTmp));
	m_vInfo.resize(128);
	m_vInfo.clear();
	int temp = (m_vInfo.begin() == m_vInfo.end());

	_NewCount =0;
	_DeleteCount =0;
}


void  COperatorNewCountInfo::WriteLog(const stc_log_info & obj)
{	//new ����������������Ϣ
	if(true != obj.isdelete)
	{
		m_vInfo.push_back(obj);
		_NewCount ++;
		return ;
	}
	stc_log_info  objTmp;
	memset(&objTmp,0,sizeof(objTmp));


	//delete�������ȱ���ԭ����Ϣ��  д�룬  Ȼ����ԭ�в��ָ���
	for(vector<stc_log_info>::iterator it = m_vInfo.begin(); it<m_vInfo.end();it++ )
	{
		
		if(it->p == obj.p && !it->isdelete)
		{
			//����new��Ϣ
			memcpy(objTmp.new_filename,it->new_filename, sizeof(it->new_filename));
			memcpy(objTmp.new_function,it->new_function, sizeof(it->new_function));
			objTmp.new_line = it->new_line;
			
			//д��delete��Ϣ
			*it=obj;

			//д��new��Ϣ
			memcpy(it->new_filename,objTmp.new_filename, sizeof(objTmp.new_filename));
			memcpy(it->new_function,objTmp.new_function, sizeof(objTmp.new_function));
			it->new_line = objTmp.new_line;


			_DeleteCount ++;
			break;
		}

				
	}


}


COperatorNewCountInfo::~COperatorNewCountInfo(void)
{
	remove("mem_log.txt");
	//д���ļ�
	ofstream ofs("mem_log.txt",ofstream::out);
	
	ofs<<*this;

	ofs.close();
	//����
	vector<stc_log_info> v;
	m_vInfo.swap(v);
}


int COperatorNewCountInfo::GetNewCount()
{
	return _NewCount;
}
int COperatorNewCountInfo::GetDeleteCount()
{
	return _DeleteCount;
}


ofstream&  operator <<(ofstream &ofs, COperatorNewCountInfo & obj)
{
	int temp = obj.GetDeleteCount() - obj.GetNewCount(), index =0;
	ofs<<"---------------------------------------------------"<<std::endl;
	ofs<<"ͳ�Ƶ�new"<<obj.GetNewCount()<<"��"<<"delete"<<obj.GetDeleteCount()<<"��."<<endl;
	if(temp)
		ofs<<"й©�ڴ�"<<temp<<"��"<<std::endl;
	
	for(vector<stc_log_info>::iterator it = obj.m_vInfo.begin(); it<obj.m_vInfo.end();it++ )
	{
		if(it->isdelete == false)
		{
		ofs<<"  "<<dec<<index++<<endl;
		ofs<<"Դ�ļ�:\t\t"<<it->new_filename<<endl;
		ofs<<"�к�  :\t\t"<<it->new_line<<endl;
		ofs<<"������:\t\t"<<it->new_function<<endl;
		ofs<<"�ڴ��ַ:\t"<<hex<<it->p<<endl;
		ofs<<endl<<endl;
		}
	}
	
	ofs<<"ллʹ��!"<<endl;

	return ofs;
}






#endif