#include "dataTypes.h"

namespace controller{

    // v2
    v2::v2(const int x, const int y){
        set(x, y);
    }

    v2::v2(){
        set(0, 0);
    }

    void v2::set(const int x, const int y){
        this->x = x;
        this->y = y;
    }

    v2::v2(const int x){
        set(x, 0);
    }

    inline v2 operator+(const v2 &u, const v2 &v){
        return v2(u.x + v.x, u.y + v.y);
    }

    inline v2 operator-(const v2 &u, const v2 &v){
        return v2(u.x - v.x, u.y - v.y);
    }

    inline v2 operator*(const v2 &u, const v2 &v){
        return v2(u.x * v.x, u.y * v.y);
    }

    inline v2 operator/(const v2 &u, const v2 &v){
        return v2(u.x / v.x, u.y / v.y);
    }

    inline v2 operator+(const v2 &u, int i){
        return v2(u.x + i, u.y + i);
    }

    inline v2 operator-(const v2 &u, int i){
        return v2(u.x - i, u.y - i);
    }

    inline v2 operator*(const v2 &u, int i){
        return v2(u.x * i, u.y * i);
    }

    inline v2 operator/(const v2 &u, int i){
        return v2(u.x / i, u.y / i);
    }

    // mouseData
    mouseData::mouseData(MouseButtons button, v2 pos){
        this->button = button;
        this->pos = pos;
    }

    mouseData::mouseData(MouseButtons button){
        this->button = button;
        this->pos = v2();
    }

    mouseData::mouseData(const int x, const int y){
        this->button = MouseButtons::LEFT;
        this->pos = v2(x, y);
    }

    mouseData::mouseData(v2 pos){
        this->button = MouseButtons::LEFT;
        this->pos = pos;
    }

    mouseData::mouseData(){
        this->button = MouseButtons::LEFT;
        this->pos = v2();
    }

}