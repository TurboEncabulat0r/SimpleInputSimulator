#ifndef DATA_TYPES_H
#define DATA_TYPES_H

namespace controller{
    class v2{
        public:
            int x;
            int y;

        v2 (const int, const int);
        v2 ();
        v2 (const int);

        void set(const int, const int);

        v2 operator+(v2);
        v2 operator-(v2);
        v2 operator*(v2);
        v2 operator/(v2);
        v2 operator+(int);
        v2 operator-(int);
        v2 operator*(int);
        v2 operator/(int);
    };

    enum MouseButtons{
        LEFT = 0x0002,
        RIGHT = 0x0008,
        MIDDLE = 0x0020
    };

    // to be deprecated
    class mouseData{
    public:
        MouseButtons button;
        v2 pos;
        int x;
        int y;

        mouseData(MouseButtons, v2);
        mouseData(MouseButtons, int, int);
        mouseData(MouseButtons);
        mouseData(v2 pos);
        mouseData(int, int);
        mouseData();
    };

}

#endif
