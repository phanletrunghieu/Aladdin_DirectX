#include "Game.h"
#include "SceneManager.h"
#include "../Scenes/MainScene.h"
#include "../Scenes/JafarScene.h"

Game::Game(LPCWSTR applicationName, float fps, bool isFullScreen)
{
	this->_applicationName = applicationName;
	this->_fps = fps;
	this->_isFullScreen = isFullScreen;

	this->_hInstance = GetModuleHandle(NULL);

	this->_input = 0;
	this->_graphics = 0;
	this->_timer = 0;
}

Game::~Game()
{
	Release();
}

bool Game::Initialize()
{
	int screenWidth, screenHeight;
	bool result;

	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	if (!InitializeWindows(screenWidth, screenHeight))
	{
		MessageBox(NULL, L"Couldn't create window", L"Error", MB_OK);
		return false;
	}

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	this->_input = new Input(this->_hWnd, screenWidth, screenHeight);
	if (!this->_input)
	{
		return false;
	}

	// Initialize the input object.
	result = this->_input->Init();
	if (!result)
	{
		MessageBox(this->_hWnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	this->_graphics = new Graphics(this->_hWnd, this->_hInstance, screenWidth, screenHeight, this->_isFullScreen);
	if (!this->_graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = this->_graphics->Init();
	if (!result)
	{
		MessageBox(this->_hWnd, L"Could not initialize the graphics object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	this->_timer = Timer::GetInstance();

	// Show MainScene
	SceneManager::GetInstance()->ReplaceScene(new MainScene());

	// init rand
	srand(time(0));

	return true;
}

void Game::Release()
{
	// Release the timer object.
	if (this->_timer)
	{
		delete this->_timer;
		this->_timer = 0;
	}

	// Release the graphics object.
	if (this->_graphics)
	{
		delete this->_graphics;
		this->_graphics = 0;
	}

	// Release the input object.
	if (this->_input)
	{
		delete this->_input;
		this->_input = 0;
	}

	// Shutdown the window.
	ShutdownWindows();
}

void Game::Run()
{
	MSG msg;
	bool done, result;

	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	float tickPerFrame = 1.0f / _fps, delta = 0;

	// Loop until there is a quit message from the window or the user.
	done = false;
	while (!done)
	{
		// Start timer
		Timer::GetInstance()->StartCounter();

		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// If windows signals to end the application then exit out.
			if (msg.message == WM_QUIT)
			{
				done = true;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		delta += Timer::GetInstance()->GetCouter();

		if (delta >= tickPerFrame)
		{
			// Otherwise do the frame processing.  If frame processing fails then exit.
			result = Frame(delta);
			if (!result)
			{
				MessageBox(this->_hWnd, L"Frame Processing Failed", L"Error", MB_OK);
				done = true;
			}


			delta = 0;
		}
		else
		{
			Sleep(tickPerFrame - delta);
			delta = tickPerFrame;
		}

		if (_input->IsKeyPressed(DIK_ESCAPE))
			done = true;
	}
}

LRESULT Game::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// Check if the window is being closed.
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

		// All other messages pass to the message handler in the system class.
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

bool Game::Frame(float detaTime)
{
	bool result;
	auto device = _graphics->GetDevice();
	Scene* currentScene = SceneManager::GetInstance()->GetCurrentScene();

	// Do the input frame processing.
	result = _input->Frame();
	if (!result)
	{
		return false;
	}

	// Update scene
	currentScene->Update(detaTime);

	// clear screen
	device->Clear(0, NULL, D3DCLEAR_TARGET, currentScene->GetBackcolor(), 1.0f, 0);

	if (!FAILED(device->BeginScene()))
	{
		// begin draw
		_graphics->GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

		// draw items in scene
		currentScene->Draw();

		// end draw
		_graphics->GetSpriteHandler()->End();

		// end graphics
		device->EndScene();
	}

	device->Present(0, 0, 0, 0);

	return true;
}

bool Game::InitializeWindows(int & screenWidth, int & screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	
	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (this->_isFullScreen)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 690;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}
	

	// Create the window with the screen settings and get the handle to it.
	this->_hWnd = CreateWindow(this->_applicationName, this->_applicationName, WS_OVERLAPPEDWINDOW, posX, posY, screenWidth, screenHeight, NULL, NULL, this->_hInstance, NULL);
	if (this->_hWnd == NULL)
		return false;

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(this->_hWnd, SW_SHOW);
	UpdateWindow(this->_hWnd);

	return true;
}

void Game::ShutdownWindows()
{
	// Fix the display settings if leaving full screen mode.
	if (this->_isFullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(this->_hWnd);
	this->_hWnd = NULL;

	// Remove the application instance.
	UnregisterClass(this->_applicationName, this->_hInstance);
	this->_hInstance = NULL;
}
