
#ifndef MOUSECONTROLL_H
#define MOUSECONTROLL_H
#ifndef DATA_TYPES_H
#include "dataTypes.h"
#endif

namespace controller{

    void Click(MouseButtons);

    void Click(MouseButtons, int, int);

    void Press(MouseButtons);

    void moveMouse(int, int);

    void moveMouse(v2);

    void CLick(MouseButtons, v2);

    void CLick(mouseData);

    void moveMouse(mouseData);

    void moveMouse(v2);

    void moveMouse(int, int, int);

    void gameSaveMoveMouse(int, int, int);

    void SetMousePos(int, int);

    void SetMousePos(v2);

    int getMousePosY();

    mouseData getMouseData();

    v2 getMousePos();
}

#endif