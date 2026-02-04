#include <windows.h>
#include <stdio.h>
#include <string.h>

char display[50] = "0";
char op = 0;
double num1 = 0;
int newInput = 1;

HWND hDisplay;

void Update() { SetWindowText(hDisplay, display); }

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        hDisplay = CreateWindow("EDIT", "0",
                                WS_VISIBLE | WS_CHILD | ES_RIGHT,
                                20, 20, 240, 40, hwnd, NULL, NULL, NULL);

        int x = 20, y = 80;
        char txt[3];

        // ปุ่ม 1-9
        for (int i = 1; i <= 9; i++)
        {
            sprintf(txt, "%d", i);
            CreateWindow("BUTTON", txt,
                         WS_VISIBLE | WS_CHILD,
                         x, y, 60, 40,
                         hwnd, (HMENU)(100 + i), NULL, NULL);

            x += 70;
            if (i % 3 == 0)
            {
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
        for (int i = 0; i < 5; i++)
        {
            txt[0] = ops[i];
            txt[1] = '\0';

            CreateWindow("BUTTON", txt,
                         WS_VISIBLE | WS_CHILD,
                         230, 80 + (i * 50), 50, 40,
                         hwnd, (HMENU)(200 + i), NULL, NULL);
        }

        break;
    }

    case WM_COMMAND:
    {
        int id = LOWORD(wParam);

        // ===== ตัวเลข =====
        if (id >= 100 && id <= 109)
        {
            char num = (id - 100) + '0';

            if (newInput || strcmp(display, "0") == 0)
            {
                sprintf(display, "%c", num);
                newInput = 0;
            }
            else
            {
                int len = strlen(display);
                display[len] = num;
                display[len + 1] = '\0';
            }

            UpdateDisplay();
        }

        // ===== Operator =====
        if (id >= 200 && id <= 204)
        {
            num1 = atof(display);
            op = "+-*/%"[id - 200];
            newInput = 1;
        }

        // ===== = =====
        if (id == 300 && op != 0)
        {
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
int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPSTR a, int s)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = h;
    wc.lpszClassName = "CalcV2";
    RegisterClass(&wc);
    CreateWindow("CalcV2", "Calculator V2",
                 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 200, 100, 320, 350, NULL, NULL, h, NULL);
    MSG m;
    while (GetMessage(&m, NULL, 0, 0))
    {
        TranslateMessage(&m);
        DispatchMessage(&m);
    }
    return 0;
}
