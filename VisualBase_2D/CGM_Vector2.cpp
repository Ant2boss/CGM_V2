#include "CGM_Vector2.h"

#include <cmath>

double CGM::Get_Vector2_Lenght(CGM::Vector2i Vec) {
    return CGM::Get_Vector2_Lenght(CGM::Vector2d(Vec.x, Vec.y));
}

double CGM::Get_Vector2_Lenght(CGM::Vector2d Vec) {
    return std::sqrt(std::pow(Vec.x, 2) + std::pow(Vec.y, 2));
}

double CGM::Get_Vector2_Angle(CGM::Vector2i Vec) {
    return Get_Vector2_Angle(CGM::Vector2d(Vec.x, Vec.y));
}

double CGM::Get_Vector2_Angle(CGM::Vector2d Vec) {
    return std::atan2(Vec.y, Vec.x);
}

double CGM::Get_Vector2_Angle(CGM::Vector2i Vec1, CGM::Vector2i Vec2) {
    return CGM::Get_Vector2_Angle(CGM::Vector2d(Vec1.x, Vec1.y), CGM::Vector2d(Vec2.x, Vec2.y));
}

double CGM::Get_Vector2_Angle(CGM::Vector2d Vec1, CGM::Vector2d Vec2) {
    return std::acos(CGM::Get_Vector2_Dot(Vec1, Vec2));
}

CGM::Vector2d CGM::Get_Vector2_Normal(CGM::Vector2i Vec) {
    return CGM::Get_Vector2_Normal(CGM::Vector2d(Vec.x, Vec.y));
}

CGM::Vector2d CGM::Get_Vector2_Normal(CGM::Vector2d Vec) {
    double vec_len = CGM::Get_Vector2_Lenght(Vec);
    return CGM::Vector2d(Vec.x / vec_len, Vec.y / vec_len);
}

double CGM::Get_Vector2_Dot(CGM::Vector2i V1, CGM::Vector2i V2) {
    return Get_Vector2_Dot(CGM::Vector2d(V1.x, V1.y), CGM::Vector2d(V2.x, V2.y));
}

double CGM::Get_Vector2_Dot(CGM::Vector2d V1, CGM::Vector2d V2) {
    CGM::Vector2d t1 = CGM::Get_Vector2_Normal(V1);
    CGM::Vector2d t2 = CGM::Get_Vector2_Normal(V2);
    return t1.x * t2.x + t1.y * t2.y;
}

double CGM::Get_Vector2_Distance(CGM::Vector2i V1, CGM::Vector2i V2) {
    return CGM::Get_Vector2_Distance(CGM::Vector2d(V1.x, V1.y), CGM::Vector2d(V2.x, V2.y));
}

double CGM::Get_Vector2_Distance(CGM::Vector2d V1, CGM::Vector2d V2) {
    return std::sqrt(std::pow(V1.x - V2.x, 2) + std::pow(V1.y - V2.y, 2));
}

CGM::Vector2i CGM::Get_Vector2_MinVector(CGM::Vector2i Vec1, CGM::Vector2i Vec2) {
    return CGM::Vector2i(std::fmin(Vec1.x, Vec2.y), std::fmin(Vec1.y, Vec2.y));
}

CGM::Vector2d CGM::Get_Vector2_MinVector(CGM::Vector2d Vec1, CGM::Vector2d Vec2) {
    return CGM::Vector2d(std::fmin(Vec1.x, Vec2.y), std::fmin(Vec1.y, Vec2.y));
}

CGM::Vector2i CGM::Get_Vector2_MaxVector(CGM::Vector2i Vec1, CGM::Vector2i Vec2) {
    return CGM::Vector2i(std::fmax(Vec1.x, Vec2.y), std::fmax(Vec1.y, Vec2.y));
}

CGM::Vector2d CGM::Get_Vector2_MaxVector(CGM::Vector2d Vec1, CGM::Vector2d Vec2) {
    return CGM::Vector2d(std::fmax(Vec1.x, Vec2.y), std::fmax(Vec1.y, Vec2.y));
}
