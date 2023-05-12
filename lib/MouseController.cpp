#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <string>
#include "dataTypes.h"
#include "MouseController.h"

using namespace std;

namespace controller{
    INPUT Input={0};
    // sends a mouse press event
    void sendPress(MouseButtons m){
        ::ZeroMemory(&Input,sizeof(INPUT));
        Input.type      = INPUT_MOUSE;
        Input.mi.dwFlags  = m;

        SendInput(1,&Input,sizeof(INPUT));
    }

    // sends a mouse release event
    void sendRelease(MouseButtons m){
        ::ZeroMemory(&Input,sizeof(INPUT));
        Input.type      = INPUT_MOUSE;
        Input.mi.dwFlags  = m + 0x0002;

        SendInput(1,&Input,sizeof(INPUT));
    }
    // sends a mouse click event
    void sendCLick(MouseButtons inp){
        ::ZeroMemory(&Input,sizeof(INPUT));
        Input.type      = INPUT_MOUSE;
        Input.mi.dwFlags  = inp;

        SendInput(1,&Input,sizeof(INPUT));

        ::ZeroMemory(&Input,sizeof(INPUT));
        Input.type      = INPUT_MOUSE;
        Input.mi.dwFlags  = inp + 0x0002;

        SendInput(1,&Input,sizeof(INPUT));
    }

    // normalises mouse position to screen size for windows
    POINT normalize(POINT const& pt_in_px, RECT const& display_size_in_px)
    {
        POINT pt_normalized{};

        auto const width_in_px{ display_size_in_px.right - display_size_in_px.left };
        auto const height_in_px{ display_size_in_px.bottom - display_size_in_px.top };

        pt_normalized.x = ::MulDiv(pt_in_px.x, 65536, width_in_px);
        pt_normalized.y = ::MulDiv(pt_in_px.y, 65536, height_in_px);

        return pt_normalized;
    }

    // sets mouse position to (x, y)
    void moveMouseAbsolute(int x, int y){
        RECT screen_rect{};
        ::GetWindowRect(::GetDesktopWindow(), &screen_rect);

        POINT const pt_normalized{ normalize({ x, y }, screen_rect) };

        INPUT input{};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        input.mi.dx = pt_normalized.x;
        input.mi.dy = pt_normalized.y;

        ::SendInput(1, &input, sizeof(INPUT));
    }

    // lerps mouse to absolute position (x, y) in time (time)
    void lerpToPosition(int x, int y, int time, double speed = 10){
        POINT p;
        GetCursorPos(&p);
        int x1 = p.x;
        int y1 = p.y;
        int x2 = x;
        int y2 = y;
        int dx = x2 - x1;
        int dy = y2 - y1;
        int steps = time / speed;
        int xInc = dx / steps;
        int yInc = dy / steps;

        int posx = x1;
        int posy = y1;
        for (int i = 0; i < steps; i++){
            posx += xInc;
            posy += yInc;
            moveMouseAbsolute(posx, posy);
            Sleep(speed);
        }
    }

    

    // move mouse relative to current position (x, y)
    void moveMouseRelative(int x, int y){
        INPUT input{};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;
        input.mi.dx = x;
        input.mi.dy = y;

        ::SendInput(1, &input, sizeof(INPUT));
    }

    // lerps mouse to relative position (x, y) in time (time)
    // will not move absolutly so should help with movemnet in certain games
    void gameSafeLerpToPosition(int x, int y, int time, double speed = 10){
        POINT p;
        GetCursorPos(&p);
        int x1 = p.x;
        int y1 = p.y;
        int x2 = x;
        int y2 = y;
        int dx = x2 - x1;
        int dy = y2 - y1;
        int steps = time / speed;
        int xInc = dx / steps;
        int yInc = dy / steps;

        int posx = x1;
        int posy = y1;
        for (int i = 0; i < steps; i++){
            moveMouseRelative(posx, posy);
            Sleep(speed);
        }
    }


    void Click(MouseButtons m){
        sendCLick(m);
    }

    void Click(MouseButtons m, int x, int y){
        moveMouse(x, y);
        sendCLick(m);
    }

    void Press(MouseButtons m){
        sendPress(m);
    }

    void Release(MouseButtons m){
        sendRelease(m);
    }

    void Click(MouseButtons m, v2 pos){
        moveMouse(pos);
        sendCLick(m);
    }

    void Click(mouseData m){
        moveMouse(m);
        sendCLick(m.button);
    }  
    
    v2 getMousePos(){
        POINT p;
        GetCursorPos(&p);
        return v2(p.x, p.y);
    }

    void moveMouse(v2 pos){
        moveMouseAbsolute(pos.x, pos.y);
    }

    void SetMousePos(v2 pos){
        moveMouseAbsolute(pos.x, pos.y);
    }

    void SetMousePos(int x, int y){
        moveMouseAbsolute(x, y);
    }

    void moveMouse(int x, int y){
        lerpToPosition(x, y, 10);
    }

    void moveMouse(int x, int y, int time){
        lerpToPosition(x, y, time);
    }

    void gameSafeMoveMouse(int x, int y, int time){
        gameSafeLerpToPosition(x, y, time);
    }

    void moveMouse(mouseData m){
        lerpToPosition(m.x, m.y, 10);
    }    

    // to be deprecated
    mouseData getMouseData(){
        POINT p;
        GetCursorPos(&p);
        mouseData m;
        m.pos = v2(p.x, p.y);
        m.x = p.x;
        m.y = p.y;

        return m;
    }  
}