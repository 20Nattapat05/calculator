#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char display[50] = "0";
char op = 0;
double num1 = 0;
int newInput = 1;

HWND hDisplay;

void UpdateDisplay() {
    SetWindowText(hDisplay, display);
}

double Calculate(double a, double b, char oper) {
    switch (oper) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 0;
        case '%': return (a * b) / 100.0;
    }
    return 0;
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

        // ปุ่ม 1-9
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

        // ปุ่ม =
        CreateWindow("BUTTON", "=",
            WS_VISIBLE | WS_CHILD,
            160, y, 60, 40,
            hwnd, (HMENU)300, NULL, NULL);

        // Operator
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

        // ===== ตัวเลข =====
        if (id >= 100 && id <= 109) {
            char num = (id - 100) + '0';

            if (newInput || strcmp(display, "0") == 0) {
                sprintf(display, "%c", num);
                newInput = 0;
            } else {
                int len = strlen(display);
                display[len] = num;
                display[len + 1] = '\0';
            }

            UpdateDisplay();
        }

        // ===== Operator =====
        if (id >= 200 && id <= 204) {
            num1 = atof(display);
            op = "+-*/%"[id - 200];
            newInput = 1;
        }

        // ===== = =====
        if (id == 300 && op != 0) {
            double num2 = atof(display);
            double result = Calculate(num1, num2, op);

            sprintf(display, "%.2f", result);
            UpdateDisplay();

            newInput = 1;
            op = 0;
        }

        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR args, int show) {

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "CalcV4";

    RegisterClass(&wc);

    CreateWindow("CalcV4", "Calculator V4",
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
