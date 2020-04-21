/*!
@file
@author		Albert Semenov
@date		08/2008
*/

#ifndef __DIMENSIONWORLD_H__
#define __DIMENSIONWORLD_H__

#include "fantastic.h"
#include "include/pde/PurpleDreamElf.h"
#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
#	include <windows.h>
#	include <winuser.h>
#endif

namespace DW
{

	class DimensionWorld 
	{
	public://����

		
		DimensionWorld();
		void			_windowResized();
		virtual			~DimensionWorld();
		virtual void	prepare();
		int				getWidth();
		int				getHeight();

	public://ϵͳ
		static DimensionWorld * Create(const TCHAR * class_name);	/**< �������� */
		bool			create(const TCHAR * window_title, const TCHAR * class_name, bool fullscreen, HINSTANCE h_instance, LPVOID lpParam);
		bool			ChangeScreenSetting();
		void			reshapeGL();
		void			run();
		virtual void	draw() {}
		void			quit();
		void			setWindowCaption(const std::wstring& _text);
	private:
		void			updateFPS();
		void			drawOneFrame();
		void			drawSkyBox();

	public://��ʼ��
		bool			initSystem();
		bool			initGlewAndOther();
		bool			createGui();
		virtual void	createScene() { }
		virtual bool	init() = 0;


	private://ж��
		void			destroyAll();
		virtual void	destroyScene() { }
		void			destroyWindow();
		//void destroyRender();

	public://��ϵͳ
		friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
		int				Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

		/** ��Ϣ����ص����� */
		friend LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT			Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		float getMouseX()
		{
			return mouse_x;
		}

		float getMouseY()
		{
			return mouse_y;
		}

		
		HWND getHwnd()
		{
			return hWnd;
		}
	private:

		TCHAR* m_ClassName;
		bool	m_IsFullScreen;
		int		m_WindowPosX;												/**< ���ڵ����Ͻǵ�Xλ�� */
		int		m_WindowPosY;												/**< ���ڵ����Ͻǵ�Yλ�� */
		int		m_WindowWidth;												/**< ���ڵĿ�� */
		int		m_WindowHeight;												/**< ���ڵĸ߶� */
		int		m_ScreenWidth;												/**< ȫ���Ŀ�� */
		int		m_ScreenHeight;												/**< ȫ���ĸ߶� */
		int		m_BitsPerPixel;

		

		HWND hWnd;
		HDC hDC;
		HGLRC hRC;
		HINSTANCE hInstance;

		bool mExit;
		bool isEnableSkyBox;
		bool isEnableUI;

		float mouse_x, mouse_y;

		std::string mRootMedia;
		std::string mResourceFileName;



	};

} // namespace base

#endif // __BASE_MANAGER_H__
