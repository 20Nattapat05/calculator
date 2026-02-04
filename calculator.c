#include <windows.h>
#include <stdio.h>
#include <string.h>

char display[50]="0";
HWND hDisplay;

void Update(){ SetWindowText(hDisplay,display); }

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam){
    switch(msg){
    case WM_CREATE:{
        hDisplay=CreateWindow("EDIT","0",
            WS_VISIBLE|WS_CHILD|ES_RIGHT,
            20,20,240,40,hwnd,NULL,NULL,NULL);

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
    return DefWindowProc(hwnd,msg,wParam,lParam);
}
int WINAPI WinMain(HINSTANCE h,HINSTANCE p,LPSTR a,int s){
    WNDCLASS wc={0}; wc.lpfnWndProc=WndProc;
    wc.hInstance=h; wc.lpszClassName="CalcV2";
    RegisterClass(&wc);
    CreateWindow("CalcV2","Calculator V2",
        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
        200,100,320,350,NULL,NULL,h,NULL);
    MSG m; while(GetMessage(&m,NULL,0,0)){TranslateMessage(&m);DispatchMessage(&m);}
    return 0;
}