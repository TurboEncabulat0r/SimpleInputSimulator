#include "dataTypes.h"

#ifdef _WIN32

#include <windows.h>
#include <WinUser.h>
#include <ctype.h>

#endif
#ifdef linux
#include <unistd.h>

#endif

namespace cauldron{
    // takes in a virtual key code and sends the input to the system
    // needs to be updated for linux support
    void sendPress(unsigned short VK){
        KEYBDINPUT  KeyDown = { 0 };
        INPUT Input = { 0 };

        KeyDown.wVk = VK;
        KeyDown.wScan = 0;
        KeyDown.time = 10;
        KeyDown.dwFlags = 0;
        KeyDown.dwExtraInfo = 0;

        Input.type = INPUT_KEYBOARD;
        Input.ki = KeyDown;

        SendInput(1, &Input, sizeof(Input));
    }

    // takes in a virtual key code and sends the input to the system
    // needs to be updated for linux support
    void sendRelease(unsigned short VK){
        KEYBDINPUT  KeyUp = { 0 };
        INPUT Input = { 0 };

        KeyUp.wVk = VK;
        KeyUp.wScan = 0;
        KeyUp.dwFlags = KEYEVENTF_KEYUP;
        KeyUp.dwExtraInfo = 0;

        Input.type = INPUT_KEYBOARD;
        Input.ki = KeyUp;

        SendInput(1, &Input, sizeof(Input));
    }

    // sends a press and release event
    void _sendPressAndRelease(unsigned short VK){
        sendPress(VK);
        sendRelease(VK);
    }

    // Takes in a char, presses the key. will not release it, is intended to be used for async button presses. 
    void PressKey(char key){
        if (isupper(key))
        {
            sendPress(VK_SHIFT);
            sendPress(key);
            sendRelease(VK_SHIFT);
            return;
        }

        if (key == ' ')
        {
            sendPress(VK_SPACE);
            return;
        }

        sendPress(key - 32);
    }

    // Takes in a char, presses the key. will not release it, is intended to be used for async button presses. 
    void ReleaseKey(char key){
        if (isupper(key))
        {
            sendPress(VK_SHIFT);
            sendRelease(key);
            sendRelease(VK_SHIFT);
            return;
        }

        if (key == ' ')
        {
            sendRelease(VK_SPACE);
            return;
        }

        sendRelease(key - 32);
    }

    // presses and releases a key, takes in a virtual key code
    void PressAndRelease(char key)
    {
        if (isupper(key))
        {
            sendPress(VK_SHIFT);
            _sendPressAndRelease(key);
            sendRelease(VK_SHIFT);
            return;
        }

        if (key == ' ')
        {
            _sendPressAndRelease(VK_SPACE);
            return;
        }

       _sendPressAndRelease(key - 32);
    }

    // takes in a char array and writes it out.
    // time is the delay in miliseconds between each key press
    void writeString(char* str, int time)
    {
        int len = strlen(str);
        for (int i = 0; i < len; i++)
        {
            if (isupper(str[i]))
            {
                sendPress(VK_SHIFT);
                _sendPressAndRelease(str[i] - 0);
                Sleep(time);
                sendRelease(VK_SHIFT);
                continue;
            }
            if (str[i] == ' ')
            {
                _sendPressAndRelease(VK_SPACE);
                Sleep(time);
                continue;
            }
            _sendPressAndRelease(str[i] - 32);
            Sleep(time);
        }
    }

    void WriteString(char* str, int time){
        writeString(str, time);
    }

    void WriteString(char* str){
        writeString(str, 0);
    }
}