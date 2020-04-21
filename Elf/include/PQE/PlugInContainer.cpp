#include "PlugInContainer.h"

namespace ASE
{
	PlugInContainer::PlugInContainer()
	{
		this->isRun = true;
	}

	bool PlugInContainer::Init(std::string path)
	{
		if (_access(path.c_str(), 0) == -1)_mkdir(path.c_str());
		_bstr_t t = path.c_str();
		wchar_t* pwchar = (wchar_t*)t;
		std::wstring wpath = pwchar;
		// ��pluginsĿ¼�в���dll�ļ������ļ���Ϣ������fileData��
		WIN32_FIND_DATA fileData;
		HANDLE fileHandle = FindFirstFile((wpath +L"*.dll").c_str(), &fileData);
		if (fileHandle == (void*)ERROR_INVALID_HANDLE ||fileHandle == (void*)ERROR_FILE_NOT_FOUND||fileHandle== INVALID_HANDLE_VALUE)
		{
			// û���ҵ��κ�dll�ļ�
			std::cout << "not dll" << std::endl;
			return false;
		}

		//ѭ������pluginsĿ¼�е�����dll�ļ�
		do {
			typedef PlugIn* (__cdecl *ObjProc)(void);
			typedef const char* (__cdecl *NameProc)(void);

			// ��dll���ص���ǰ���̵ĵ�ַ�ռ���
			HINSTANCE mod = LoadLibrary((wpath + std::wstring(fileData.cFileName)).c_str());

			if (!mod) 
			{
				// ����dllʧ�ܣ����ͷ������Ѽ���dll
				for (HINSTANCE hInst : modules)
					FreeLibrary(hInst);
				printf("not load successfully\n");
				return false;
			}
			// ��dll����л�ȡgetObj��getName�ĺ�����ַ
			ObjProc objFunc = (ObjProc)GetProcAddress(mod, "GetObj");
			NameProc nameFunc = (NameProc)GetProcAddress(mod, "GetName");

			if (!objFunc || !nameFunc)
				printf("Invalid Plugin DLL: both 'getObj' and 'getName' must be defined.\n");
			printf("%s\n", path.c_str());

			mPlug.push_back(objFunc());  // ����objFunc����getObj�����ɵĶ���ָ��
			modules.push_back(mod);		 // ����dll���

			std::clog << nameFunc() << " loaded!\n";
		} while (FindNextFile(fileHandle, &fileData));
		std::clog << std::endl;
		// �ر��ļ����
		FindClose(fileHandle);
		return true;
	}

	bool PlugInContainer::Run()
	{
		std::vector<std::string> deleteName;
		if (!this->isRun)return false;
		for (auto &p : this->mPlug)
		{
			p->Run();
			bool status=p->GetStatus();
			switch (p->GetType())
			{
			case ASE::PlugIn::ASE_PLUGIN_GLOBAL:
				break;
			case ASE::PlugIn::ASE_PLUGIN_COMMAND:
				if (!status)
					deleteName.push_back(p->GetName());
				break;
			default:
				break;
			}
		}
		for (auto &d : deleteName)
		{
			std::vector<PlugIn*>::iterator it = std::find_if(this->mPlug.begin(), this->mPlug.end(), [&](PlugIn *obj) {return obj->GetName() == d;});
			if (it != mPlug.end())
			{
				delete mPlug[it - mPlug.begin()];
				mPlug[it - mPlug.begin()] = NULL;
				mPlug.erase(it);
			}
		}

		return true;
	}

	void PlugInContainer::Destory()
	{
		for (auto &p : this->mPlug)
		{
			delete p;p = NULL;
		}

		for (HINSTANCE hInst : this->modules)
			FreeLibrary(hInst);
	}

	PlugInContainer::~PlugInContainer()
	{
		this->Destory();
	}
}
