#include <windows.h>
#include <stdio.h>
#include <string.h>

char display[50] = "0";
char op = 0;

char display[50]="0";
HWND hDisplay;

void UpdateDisplay() {
    SetWindowText(hDisplay, display);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {

    case WM_CREATE: {
        // ช่องแสดงผล
        hDisplay = CreateWindow("EDIT", "0",
            WS_VISIBLE | WS_CHILD | ES_RIGHT,
            20, 20, 260, 40,
            hwnd, NULL, NULL, NULL);

        int x = 20, y = 80;
        char txt[3];

        // ปุ่มตัวเลข 1-9
        for (int i = 1; i <= 9; i++) {
            sprintf(txt, "%d", i);
            CreateWindow("BUTTON", txt,
                WS_VISIBLE | WS_CHILD,
                x, y, 60, 40,
                hwnd, (HMENU)(100 + i), NULL, NULL);

            x += 70;
            if (i % 3 == 0) {
                x = 20;
                y += 50;
            }
        }

        // ปุ่ม 0
        CreateWindow("BUTTON", "0",
            WS_VISIBLE | WS_CHILD,
            90, y, 60, 40,
            hwnd, (HMENU)100, NULL, NULL);

        // ปุ่ม Operator
        char ops[] = {'+', '-', '*', '/', '%'};
        for (int i = 0; i < 5; i++) {
            txt[0] = ops[i];
            txt[1] = '\0';

            CreateWindow("BUTTON", txt,
                WS_VISIBLE | WS_CHILD,
                230, 80 + (i * 50), 50, 40,
                hwnd, (HMENU)(200 + i), NULL, NULL);
        }

        break;
    }

    case WM_COMMAND: {
        int id = LOWORD(wParam);

        // ===== ปุ่มตัวเลข =====
        if (id >= 100 && id <= 109) {
            char num = (id - 100) + '0';

            if (strcmp(display, "0") == 0) {
                sprintf(display, "%c", num);
            } else {
                int len = strlen(display);
                display[len] = num;
                display[len + 1] = '\0';
            }

            UpdateDisplay();
        }

        // ===== ปุ่ม Operator =====
        if (id >= 200 && id <= 204) {
            op = "+-*/%"[id - 200];

            char msg[50];
            sprintf(msg, "Selected Operator: %c", op);
            MessageBox(hwnd, msg, "Operator", MB_OK);
        }

        break;
    }

        int x=20,y=80;
        char txt[2];
        for(int i=0;i<=9;i++){
            sprintf(txt,"%d",i);
            CreateWindow("BUTTON",txt,
                WS_VISIBLE|WS_CHILD,
                x,y,50,40,hwnd,(HMENU)(100+i),NULL,NULL);
            x+=60;
            if((i+1)%3==0){x=20;y+=50;}
        }
        break;}
    case WM_COMMAND:{
        int id=LOWORD(wParam);
        if(id>=100&&id<=109){
            char n=(id-100)+'0';
            if(strcmp(display,"0")==0) sprintf(display,"%c",n);
            else{
                int l=strlen(display);
                display[l]=n; display[l+1]=0;
            }
            Update();
        }
        break;}
    case WM_DESTROY: PostQuitMessage(0); break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR args, int show) {

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "CalcV3";

    RegisterClass(&wc);

    CreateWindow("CalcV3", "Calculator V3",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        200, 100, 330, 380,
        NULL, NULL, hInst, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}