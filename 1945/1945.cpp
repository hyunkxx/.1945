#include "pch.h"
#include "1945.h"
#include "CCore.h"

HWND      g_hWnd;
HINSTANCE g_hInst;

RECT g_clientRect{ 0, 0, WIDTH, HIGHT };

WCHAR szTitle[TEXT_LENGTH];
WCHAR szWindowClass[TEXT_LENGTH];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, TEXT_LENGTH);
    LoadStringW(hInstance, IDC_MY1945, szWindowClass, TEXT_LENGTH);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    CCore* pCore = new CCore;
    pCore->Initalize(g_hWnd, hInstance, g_clientRect);

    MSG msg;

    while (true)
    {
        LARGE_INTEGER timer, begin, end;
        static float fDeltaTime;

        QueryPerformanceFrequency(&timer);
        QueryPerformanceCounter(&begin);

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                PostQuitMessage(0);
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            pCore->Update(fDeltaTime);
            pCore->Render();

            QueryPerformanceCounter(&end);
            fDeltaTime = (end.QuadPart - begin.QuadPart) / (float)timer.QuadPart; // 1초당 진동수
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1945));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    g_hInst = hInstance;

    AdjustWindowRect(&g_clientRect, WS_OVERLAPPEDWINDOW, FALSE);

    g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, g_clientRect.right, g_clientRect.bottom, nullptr, nullptr, hInstance, nullptr);

    SetWindowPos(g_hWnd, NULL, 0, 0, g_clientRect.right - g_clientRect.left, g_clientRect.bottom - g_clientRect.top,
        SWP_NOMOVE | SWP_NOZORDER);

    if (!g_hWnd)
    {
        return FALSE;
    }

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}