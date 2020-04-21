#include "DimensionWorldWin32.h"

namespace DW
{
	ULONG_PTR gdiplusToken;

	/*����*/



	/*����*/
	void DimensionWorld::_windowResized()
	{
		RECT rect = { 0, 0, 0, 0 };
		GetClientRect(hWnd, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		//resizeRender(width, height)
	}

	DimensionWorld::DimensionWorld():
		hWnd(0),
		hDC(0),
		hRC(0),
		mExit(true),
		mResourceFileName("MyGUI_Core.xml"),
		m_ClassName(_T("asf")),
		m_WindowPosX(0),
		m_WindowPosY(0),
		m_IsFullScreen(false),
		m_BitsPerPixel(16),
		isEnableSkyBox(false),
		isEnableUI(true)

	{
		//Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		//Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		m_ScreenWidth = GetSystemMetrics(SM_CXSCREEN);		/**< ��ȡ��ǰ��Ļ�� */
		m_ScreenHeight = GetSystemMetrics(SM_CYSCREEN);		/**< ��ȡ��ǰ��Ļ�� */
		m_WindowWidth = m_ScreenWidth / 2;
		m_WindowHeight = m_ScreenHeight / 2;
	
	}

	DimensionWorld::~DimensionWorld()
	{
		
	}

	void DimensionWorld::prepare()
	{
	}

	int DimensionWorld::getWidth()
	{
		if (m_IsFullScreen == true)
		{
			return m_ScreenWidth;
		}
		else
		{
			return m_WindowWidth;
		}
	}

	int DimensionWorld::getHeight()
	{
		if (m_IsFullScreen == true)
		{
			return m_ScreenHeight;
		}
		else
		{
			return m_WindowHeight;
		}
	}

	void DimensionWorld::destroyWindow()
	{
		if (hWnd != 0)										/**< ���ھ���Ƿ���� */
		{
			if (hDC != 0)										/**< �����豸�������Ƿ���� */
			{
				wglMakeCurrent(hDC, 0);						/**< ���õ�ǰ��OpenGL����Ⱦ����Ϊ��NULL */
				if (hRC != 0)									/**< OpenGL����Ⱦ�������Ƿ���� */
				{
					wglDeleteContext(hRC);					/**< �ͷ�OpenGL����Ⱦ������ */
					hRC = 0;									/**< ����OpenGL����Ⱦ������Ϊ0 */
				}
				ReleaseDC(hWnd, hDC);						/**< �ͷŴ��ڵ��豸������ */
				hDC = 0;										/**< ���ô��ڵ��豸������Ϊ0 */
			}
			DestroyWindow(hWnd);								/**< ɾ������ */
			hWnd = 0;											/**< ���ô��ھ��Ϊ0 */
		}

		if (m_IsFullScreen)										/**< ���Ϊȫ��ģʽ���ڳ�������󣬱任������ģʽ������ʾ��� */
		{
			ChangeDisplaySettings(NULL, 0);						/**< �任������ģʽ */
			ShowCursor(true);									/**< ��ʾ��� */
		}
	}

	

	bool DimensionWorld::create(const TCHAR * window_title, const TCHAR * class_name, bool fullscreen, HINSTANCE h_instance, LPVOID lpParam)
	{
		m_IsFullScreen = fullscreen;
		int nX = 0;
		int nY = 0;
		
		PIXELFORMATDESCRIPTOR pfd =											/**< �������������ṹ */
		{
			sizeof(PIXELFORMATDESCRIPTOR),									/**< ���������ṹ�Ĵ�С */
			1,																/**< �汾�� */
			PFD_DRAW_TO_WINDOW |											/**< �������������ʾ��һ�������� */
			PFD_SUPPORT_OPENGL |											/**< ������֧��OpenGL��ͼ */
			PFD_STEREO |											/**< ��ɫ�����������建�� */
			PFD_DOUBLEBUFFER,												/**< ��ɫ��������˫���� */
			PFD_TYPE_RGBA,													/**< ʹ��RGBA��ɫ��ʽ */
			16,													/**< ��ɫ����������ɫֵ��ռ��λ�� */
			0, 0, 0, 0, 0, 0,												/**< ʹ��Ĭ�ϵ���ɫ���� */
			0,																/**< ��Alpha���� */
			0,																/**< ��ɫ��������alpha�ɷֵ���λ���� */
			0,																/**< ���ۼƻ����� */
			0, 0, 0, 0,														/**< �ۼƻ���������λ */
			32,																/**< 32λ��Ȼ��� */
			0,																/**< ���ɰ滺�� */
			0,																/**< �޸��������� */
			PFD_MAIN_PLANE,													/**< ����ΪPFD_MAIN_PLANE������Ϊ����ͼ�� */
			0,																/**< ��ʾOpenGLʵ����֧�ֵ��ϲ���²�ƽ������� */
			0, 0, 0															/**< ��ʱ���Ѳ���ʹ�� */
		};

		DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX&~WS_MINIMIZE;	/**< �������Ǵ������ͣ�ʹ�ó����趨��ȥ����󻯰�ť�������ܸı䴰���С */
		DWORD windowExtendedStyle = WS_EX_APPWINDOW;
		/// �������Ǵ��ڵĴ�С��ʹ��ͻ����Ĵ�СΪ�������õĴ�С
		if (m_IsFullScreen == true)											/**< ���Ϊȫ��ģʽ������ת��Ϊȫ��ģʽ */
		{
			ShowCursor(true);											/**< ������� */
			windowStyle = WS_POPUP;										/**< ���ô���ģʽΪ���㴰�� */
			windowExtendedStyle |= WS_EX_TOPMOST;
			/// �������Ǵ��ڵĴ�С��ʹ��ͻ����Ĵ�СΪ�������õĴ�С
			
		}
		RECT windowRect = { m_WindowPosX, m_WindowPosY, m_WindowPosX + +getWidth(), m_WindowPosY + getHeight() };

		if (m_IsFullScreen == false)										/**< �ڴ���ģʽ��ʹ�� */
		{
			windowExtendedStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	/**< ʹ���ھ���3D��� */
			nX = (m_ScreenWidth - m_WindowWidth) / 2;                    /**< ���㴰�ھ����� */
			nY = (m_ScreenHeight - m_WindowHeight) / 2;
			/// �������Ǵ��ڵĴ�С��ʹ��ͻ����Ĵ�СΪ�������õĴ�С
			AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExtendedStyle);
			/// �жϴ��ڵ����Ͻ��Ƿ�������������
			if (windowRect.left < 0)										/**< �������X����Ϊ�����ƶ����굽0�������������ڵ�λ�� */
			{
				windowRect.right -= windowRect.left;
				windowRect.left = 0;
			}
			if (windowRect.top < 0)											/**< �������Y����Ϊ�����ƶ����굽0�������������ڵ�λ�� */
			{
				windowRect.bottom -= windowRect.top;
				windowRect.top = 0;
			}
		}

		/// ��������
		hWnd = CreateWindowEx(windowExtendedStyle,						/**< ���ڵ���չ��� */
			class_name,									/**< ���ڵ����� */
			window_title,								/**< ���ڱ��� */
			windowStyle,								/**< ���ڵķ�� */
			nX, nY,                                      /**< ���ڵ����Ͻ�λ�� */
			windowRect.right - windowRect.left,			/**< ���ڵĿ�� */
			windowRect.bottom - windowRect.top,			/**< ���ڵĸ߶� */
			NULL,								/**< ���ڵĸ�����Ϊ���� */
			0,											/**< �޲˵� */
			h_instance,									/**< ���봰�ڵ�ʵ����� */
			lpParam);									/**< ������������ */

		while (hWnd != NULL)													/**< �����Ƿ񴴽��ɹ� */
		{
			hDC = GetDC(hWnd);											/**< ���ش��ڵ��豸������ */
			if (hDC == 0)													/**< ���Ϊ�� */
			{																/**< ʧ�� */
				break;
			}

			GLuint PixelFormat;
			if (!PDE::arbMultisampleSupported)
			{
				PixelFormat = ChoosePixelFormat(hDC, &pfd);				// Find A Compatible Pixel Format
				if (PixelFormat == 0)												// Did We Find A Compatible Format?
				{
					// Failed
					ReleaseDC(hWnd, hDC);							// Release Our Device Context
					hDC = 0;												// Zero The Device Context
					DestroyWindow(hWnd);									// Destroy The Window
					hWnd = 0;												// Zero The Window Handle
					break;												// Return False
				}

			}
			else
			{
				PixelFormat = PDE::arbMultisampleFormat;
			}

			if (SetPixelFormat(hDC, PixelFormat, &pfd) == false)			/**< �������ظ�ʽ */
			{																/**< ʧ�� */
				break;
			}
			hRC = wglCreateContext(hDC);								/**< ����OpenGL����Ⱦ������ */
			if (hRC == 0)													/**< ���Ϊ�� */
			{																/**< ʧ�� */
				break;
			}
			if (wglMakeCurrent(hDC, hRC) == false)						/**< ���õ�ǰ��OpenGL����Ⱦ����Ϊ��ǰ�Ĵ��� */
			{																/**< ʧ�� */
				break;
			}

			if (!PDE::arbMultisampleSupported && CHECK_FOR_MULTISAMPLE)
			{

				if (PDE::initMultisample(h_instance, hWnd, pfd))
				{

					destroyWindow();
					return create(window_title, class_name, fullscreen, h_instance, lpParam);
				}
			}

			ShowWindow(hWnd, SW_NORMAL);									/**< ��ʾ���� */
			reshapeGL();													/**< ����OpenGL�������ڴ�С */
			return true;													/**< �ɹ����� */
		}

		destroyWindow();															/**< �ͷ���Դ */
		return false;														/**< ����ʧ�� */
	}

	bool DimensionWorld::ChangeScreenSetting()
	{
		DEVMODE dmScreenSettings;											/**< �豸ģʽ */	
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));/**< ����ṹ */
		dmScreenSettings.dmSize = sizeof(DEVMODE);					/**< �ṹ��С */
		dmScreenSettings.dmPelsWidth = getWidth();						/**< ���ÿ�� */
		dmScreenSettings.dmPelsHeight = getHeight();						/**< ���ø߶� */
		dmScreenSettings.dmBitsPerPel = m_BitsPerPixel;					/**< ����λ��� */
																		//dmScreenSettings.dmDisplayFrequency = 75;                           /**< ������Ļˢ���� */
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// | DM_DISPLAYFREQUENCY;

																				 /// �ı���ʾģʽ
		if (ChangeDisplaySettings(&dmScreenSettings, 0) != DISP_CHANGE_SUCCESSFUL)
		{
			return false;													/**< ���ʧ�ܣ�����false */
		}

		return true;														/**< �ɹ����� */
	}

	void DimensionWorld::reshapeGL()
	{
		GLsizei width = getWidth();
		GLsizei height = getHeight();
		glViewport(0, 0, width, height);									/**< ���������ӿ� */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void DimensionWorld::run()
	{
		// First we clear the screen and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Then we reset the modelview matrix
		glLoadIdentity();
		drawSkyBox();
		draw();
	}

	void DimensionWorld::setWindowCaption(const std::wstring& _text)
	{
		SetWindowTextW(hWnd, _text.c_str());
	}

	void DimensionWorld::updateFPS()
	{
		
	}

	void DimensionWorld::drawOneFrame()
	{
		
	}

	void DimensionWorld::drawSkyBox()
	{
		if (isEnableSkyBox)
		{
			glTranslatef(0, -25, 0);
			initSkyBox.drawAllEBO();
			glLoadIdentity();
		}
	}

	/*��ʼ��*/

	bool DimensionWorld::initSystem()
	{
		initGlewAndOther();
		createScene();
		_windowResized();
		return true;
	}

	bool DimensionWorld::initGlewAndOther()
	{
		glewInit();
		glEnable(GL_TEXTURE_2D);
		if (isEnableSkyBox)
		{
			initSkyBox.importFile("Elf/magic/skybox/skybox.pde");
			initSkyBox.generationAllEBO();
		}
		
		return true;
	}

	/*ж��*/


	void DimensionWorld::destroyAll()
	{
		destroyScene();

	

		destroyWindow();

		//UnregisterClass(WND_CLASS_NAME, hInstance);
	}
	/*��ϵͳ*/

	/** ��Ϣѭ�� */
	LRESULT DimensionWorld::Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)														/**< ����ͬ��Windows��Ϣ */
		{
		case WM_SYSCOMMAND:												/**< �ػ�ϵͳ���� */
			switch (wParam)
			{
			case SC_SCREENSAVE:										/**< �ػ���Ļ������������ */
			case SC_MONITORPOWER:									/**< �ػ���ʾ��ʡ��ģʽ�������� */
				return 0;											/**< ���������������� */
				break;
			}
			break;															/**< �˳� */

		case WM_CLOSE:													/**< �رմ��� */
			//TerminateApplication();										/**< ����TerminateApplication���� */
			return 0;
			break;

		case WM_EXITMENULOOP:
		case WM_EXITSIZEMOVE:
			//m_LastTickCount = GetTickCount();							/**< ���¼�������ֵ */
			return 0;
			break;

		case WM_MOVE:
			//m_Window.SetPosX(LOWORD(lParam));							/**< ������������ */
		//	m_Window.SetPosY(HIWORD(lParam));
			return 0;
			break;

		case WM_PAINT:
			//if (m_ResizeDraw == true)									/**< �����Ҫ�ػ� */
			//{
			//	m_Window.ReshapeGL();									/**< �������ô��ڵĴ�С */
			//	Draw();													/**< ���»��� */
			//	m_Window.SwapBuffers();									/**< ����ǰ��֡���� */
			//}
			break;

		case WM_SIZING:													/**< �������ڸı��С */
		{
			RECT * rect = (RECT *)lParam;
			//m_Window.SetWidth(rect->right - rect->left);				/**< ���ô��ڿ�� */
			//m_Window.SetHeight(rect->bottom - rect->top);				/**< ���ô��ڸ߶� */
			return TRUE;
		}
		break;

		case WM_SIZE:													/**< ���ڸı��С�� */
			switch (wParam)												/**< ����ͬ�Ĵ���״̬ */
			{
			case SIZE_MINIMIZED:									/**< �Ƿ���С��? */
				//m_IsVisible = false;								/**< ����ǣ������ò��ɼ� */
				return 0;
				break;

			case SIZE_MAXIMIZED:									/**< �����Ƿ����? */
			case SIZE_RESTORED:										/**< ���ڱ���ԭ? */
				//m_IsVisible = true;									/**< ����Ϊ�ɼ� */
				//m_Window.SetWidth(LOWORD(lParam));					/**< ���ô��ڿ�� */
				//m_Window.SetHeight(HIWORD(lParam));					/**< ���ô��ڸ߶� */
				//m_Window.ReshapeGL();								/**< �ı䴰�ڴ�С */
				//m_LastTickCount = GetTickCount();					/**< ���¼�������ֵ */
				return 0;
				break;
			}
			break;

		case WM_KEYDOWN:												/**< ���°�����Ϣ */
		
			return 0;
			break;

		case WM_KEYUP:													/**< �����ͷż���Ϣ */
			
			return 0;
			break;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);					/**< ����Ĭ�ϵĴ�����Ϣ������ */
	}

	/** �������ѭ�� */
	int DimensionWorld::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		/// ע��һ������
		WNDCLASSEX windowClass;												/**< ������ */
		ZeroMemory(&windowClass, sizeof(WNDCLASSEX));						/**< ��սṹΪ0 */
		windowClass.cbSize = sizeof(WNDCLASSEX);					/**< ���ڽṹ�Ĵ�С */
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	/**< ���ô�������Ϊ���ƶ�ʱ�ػ�����Ϊ����ȡ��DC */
		windowClass.lpfnWndProc = (WNDPROC)(WindowProc);				/**< WndProc������Ϣ */
		windowClass.hInstance = hInstance;							/**< ����ʵ�� */
		windowClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);			/**< ���ñ��� */
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);			/**< ������ */
		windowClass.lpszClassName = m_ClassName;							/**< �������� */
		if (RegisterClassEx(&windowClass) == 0)								/**< ����ע�ᴰ���� */
		{																	/**< NOTE: Failure, Should Never Happen */
			MessageBox(HWND_DESKTOP, _T("ע�ᴰ��ʧ��!"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
			return -1;														/**< �˳�������FALSE */
		}

		while (mExit)											/**< ѭ��ֱ��WM_QUIT�˳����� */
		{
			/// ����һ������
			if (create(_T("��Ԫ"), m_ClassName, m_IsFullScreen, hInstance, this))
			{

				// �����ʼ��ʧ�ܣ����˳�
				if (!(init()&&initSystem()))									/**< �����Զ���ĳ�ʼ������ */
				{															/**< ʧ�� */
					//TerminateApplication();									/**< �رմ����˳����� */
				}
				else														/**< �ɹ���ʼ��Ϣѭ�� */
				{
					MSG msg;												/**< Window��Ϣ�ṹ */
					bool isMessagePumpActive = true;						/**< ����Ϣ��Ϊ��ʱ��������Ϣѭ�� */
					while (isMessagePumpActive == true)						/**< ����Ϣ��Ϊ��ʱ��������Ϣѭ�� */
					{														/**< �ɹ��������ڣ���ⴰ����Ϣ */
						if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE) != 0)
						{
							/// ����Ƿ�ΪWM_QUIT��Ϣ
							if (msg.message != WM_QUIT)
							{
								DispatchMessage(&msg);						/**< ������Ƿ�����Ϣ����Ϣ�ص������д��� */
							}
							else
							{
								isMessagePumpActive = false;				/**< ����ǣ����˳� */
							}
						}
						/// ���û����Ϣ
						else
						{
							//if (m_IsVisible == false)						/**< ������ڲ��ɼ� */
							//{
								//WaitMessage();								/**< ��ͣ���򣬵ȴ���Ϣ */
							//}
							//else											/**< ������ڿɼ� */
							//{
								/**< ִ����Ϣѭ�� */
								DWORD tickCount = GetTickCount();			/**< ���ؼ�ʱ���ĵ�ǰֵ */
								updateFPS();
								run();										/**< �����û��Զ���Ļ��ƺ��� */
								SwapBuffers(hDC);					/**< ����ǰ��֡���� */
							//}
								if (mExit == false)
									break;
						}
					}														/**< ���isMessagePumpActive == true����ѭ�� */
				}
				destroyAll();											/**< ɾ������ */
			}
			else															/**< �����������ʧ�� */
			{
				MessageBox(HWND_DESKTOP, _T("����OpenGL���ڴ���"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
				mExit = false;									/**< ֹͣ����ѭ�� */
			}
		}

		UnregisterClass(m_ClassName, hInstance);							/**< ȡ��ע��Ĵ��� */
		return 0;
	}

	/** ��������Ϣ */
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LONG user_data = GetWindowLong(hWnd, GWL_USERDATA);					/**< �����û��Զ����32λ�ĳ��򸽼�ֵ */
		if (user_data == 0)
		{
			/// ��������һ������
			if (uMsg == WM_CREATE)											/**< �����ڴ�����Ϣ */
			{
				/// ���ش��ڽṹ��ָ�룬������մ����ĳ���ʵ������
				CREATESTRUCT * creation = reinterpret_cast<CREATESTRUCT *>(lParam);
				/// ��ó���ʵ����ָ��
				DimensionWorld * dimension = reinterpret_cast<DimensionWorld *>(creation->lpCreateParams);
				/// �������ʵ����ָ��Ϊ�û��Զ���ĳ��򸽼�ֵ
				SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<LONG>(dimension));							/**< ���ó���ɼ� */
				return 0;													/**< ���� */
			}
		}
		else
		{	/// ������ǵ�һ�δ��ڣ����س���ʵ����ָ��
			DimensionWorld * appl = reinterpret_cast<DimensionWorld *>(user_data);
			return appl->Message(hWnd, uMsg, wParam, lParam);				/**< ���ó���ʵ���Լ�����Ϣ������ */
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);					/**< ����Ĭ�ϵĴ�����Ϣ������ */
	}

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int ret = -1;
	DW::DimensionWorld * dimension = DW::DimensionWorld::Create(_T("DimensionWorld"));			/**< ���������� */
	if (dimension != 0)
	{
		ret = dimension->Main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);/**< ִ�г�����ѭ�� */
		delete dimension;													/**< ɾ�������ࣨ�ڼ̳����У�ʹ��GL_Example * example = new GL_Example(class_name);������һ���ڴ棩*/
	}
	else
	{																	/**< ����������� */
		MessageBox(HWND_DESKTOP, _T("�����������"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
	}
	return ret;
}