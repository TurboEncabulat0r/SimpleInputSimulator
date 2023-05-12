#ifndef KBCONTROLLER
#define KBCONTROLLER


namespace controller{
    void PressKey(char);
    void ReleaseKey(char);
    void PressAndRelease(unsigned short int, bool);
    void WriteString(char*);
    void WriteString(char*, int);
}

#endif