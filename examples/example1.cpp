#include "MouseController.h"
#include "KeyboardController.h"

int main(){
    controller::moveMouse(100, 100);
    controller::Click(controller::MouseButtons::LEFT);
    controller::SetMousePos(200, 200);
    controller::Click(controller::MouseButtons::RIGHT);   

    char* str = "Hello World!";
    controller::WriteString(str);

    controller::PressKey('a');
    controller::ReleaseKey('a');

    controller::PressAndRelease('a', true);

    return 0;
}