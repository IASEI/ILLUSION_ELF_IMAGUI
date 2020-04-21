#ifndef __PLUGIN_H__
#define __PLUGIN_H__
/*
*�������
*/

#include<iostream>
namespace ASE
{
	class PlugIn
	{
	public:
		enum ASE_PLUGIN_TYPE { ASE_PLUGIN_GLOBAL,ASE_PLUGIN_COMMAND};
	public:
		PlugIn();
		virtual bool	Run();		//��ʱ����������
		virtual bool    Render();	//ͼ����Ⱦ���
		virtual bool    Compute();	//�����������
		std::string		GetName();
		ASE_PLUGIN_TYPE GetType();
		bool			GetStatus();
		~PlugIn();
	protected:
		bool			isRun;	//�Ƿ�����
		std::string		mName;	//�������
		ASE_PLUGIN_TYPE mType;	//�������
		
	};
}
#endif // !__PLUGIN_H__


