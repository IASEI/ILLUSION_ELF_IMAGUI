#ifndef __PLUGINCONTAINER_H__
#define __PLUGINCONTAINER_H__

/*
*�������
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<comutil.h>
#include<io.h>
#include<direct.h>
#include<windows.h>
#include"PlugIn.h"

#pragma comment(lib, "comsuppw.lib")

namespace ASE
{
	class PlugInContainer:public PlugIn
	{
	public:
		PlugInContainer();
		bool Run();
		bool Init(std::string path="../plug/");//���ز��
		void Destory();//�ͷŲ��
		~PlugInContainer();

	private:
		std::vector<PlugIn*> mPlug;//���
		std::vector<HINSTANCE> modules;//������dll���

	};
}
#endif // !__PLUGINCONTAINER_H__


