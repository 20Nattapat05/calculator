#include <windows.h>

HWND hDisplay;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
    case WM_CREATE:
        hDisplay = CreateWindow("EDIT","0",
            WS_VISIBLE|WS_CHILD|ES_RIGHT,
            20,20,240,40,
            hwnd,NULL,NULL,NULL);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd,msg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR args,int show) {
    WNDCLASS wc={0};
    wc.lpfnWndProc=WndProc;
    wc.hInstance=hInst;
    wc.lpszClassName="CalcV1";
    RegisterClass(&wc);

    CreateWindow("CalcV1","Calculator V1",
        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
        200,100,300,200,
        NULL,NULL,hInst,NULL);

    MSG msg;
    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
