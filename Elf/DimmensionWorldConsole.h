#ifndef __DIMMENSIONWORLDCONSOLE_H__
#define __DIMMENSIONWORLDCONSOLE_H__

#include "PurpleDreamElf.h"
#include "PlugInContainer.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

#define SystemActionShadow		mOrdinary[0][0]			
#define SystemActionBone		mOrdinary[0][1]			
#define SystemActionShape		mOrdinary[0][2]			
#define SystemLightLocation		mSunlight[0]			
#define SystemLightDirection	mSunlight[1]			
#define SystemLightAmbient		mEnvironment[0]			
#define SystemLightDiffuse		mEnvironment[1]
#define SystemLightSpecular		mEnvironment[2]

class SystemAttribute
{
public:
	SystemAttribute();
	bool operator ==(SystemAttribute &msys);
	~SystemAttribute();
public:
	glm::mat4 mOrdinary;
	glm::mat4 mSunlight;
	glm::mat4 mEnvironment;
	glm::mat4 mSpace;				//�ռ��С����������mikuģ��Ϊ��׼
	glm::mat4 mLightProjection;		//���տռ�
	glm::mat4 mLightView;			//���տռ�
	
};

class DimmensionWorldConsole
{
public:
	static DimmensionWorldConsole *create(std::string classname);

	DimmensionWorldConsole();
	int Main();
	inline virtual void InitSystem();
	inline virtual void ImGuiRenderSystem();
	//������Ⱦ��������
	inline virtual void SwapBuffersSystem();
	//ˢ����Ļ
	inline virtual void Clear();
	inline virtual void NewImgGuiFrame();
	//��Ⱦ����
	inline virtual void Render();
	inline virtual void RenderBasis();
	inline virtual void RenderImgUI();
	inline virtual void StartSystemThread();
	//��ʼ����ͨ����
	inline virtual void InitBasic();
	inline virtual void Init();
	inline virtual void End();

	void SetSystemAttribute(unsigned int id);
	void SetShadowOrthoWidth(float width);
	void SetShadowOrthoNear(float mNear);
	void SetShadowOrthoFar(float mFar);
	void SetShadowShadowLookAtEyes(glm::vec3 eyes);
	void SetShadowLookAtDirction(glm::vec3 direction);
	void Exit();
	~DimmensionWorldConsole();
protected:
	bool					mExit;
	float					mScreenWidth;
	float					mScreenHeight;
	float mShadowOrthoWidth;
	float mShadowOrthoNear;
	float mShadowOrthoFar;
	glm::vec3 mShadowLookAtEyes;
	glm::vec3 mShadowLookAtDirection;
	unsigned int			*mSystemAttribute_ssao;
	std::string				mName;
	glm::vec4				mClearColor;
	GLFWwindow				*mWindow;
	shader					*mShader;
	shader					*mShadow;
	ASE::PlugInContainer	*mPlugIn;
	SystemAttribute			*mSys;
	SystemAttribute			mSysCopy;
	float i = 0;
};

#endif

