#include "CGM_Colider2.h"

CGM::Colider2i CGM::Get_Colider2_FromStartAndEnd(CGM::Vector2i Start, CGM::Vector2i End) {
    CGM::Vector2i tStart = CGM::Get_Vector2_MinVector(Start, End);
    CGM::Vector2i tEnd = CGM::Get_Vector2_MaxVector(Start, End);

    CGM::Colider2i tCol;
    tCol.Position = tStart;
    tCol.Size = tEnd - tStart;
    tCol.Size.Offset(1, 1);

    return tCol;
}

CGM::Colider2i CGM::Get_Colider2_FromStartAndEnd(int xStart, int yStart, int xEnd, int yEnd) {
    return CGM::Get_Colider2_FromStartAndEnd(CGM::Vector2i(xStart, yStart), CGM::Vector2i(xEnd, yEnd));
}

CGM::Colider2d CGM::Get_Colider2_FromStartAndEnd(CGM::Vector2d Start, CGM::Vector2d End) {
    CGM::Vector2d tStart = CGM::Get_Vector2_MinVector(Start, End);
    CGM::Vector2d tEnd = CGM::Get_Vector2_MaxVector(Start, End);

    CGM::Colider2d tCol;
    tCol.Position = tStart;
    tCol.Size = tEnd - tStart;
    tCol.Size.Offset(1.0, 1.0);

    return tCol;
}

CGM::Colider2d CGM::Get_Colider2_FromStartAndEnd(double xStart, double yStart, double xEnd, double yEnd) {
    return CGM::Get_Colider2_FromStartAndEnd(CGM::Vector2d(xStart, yStart), CGM::Vector2d(xEnd, yEnd));
}

CGM::Colider2i CGM::Get_Colider2_FromPosAndSize(CGM::Vector2i Pos, CGM::Vector2i Size) {
    CGM::Colider2i tCol;

    tCol.Position = Pos;
    tCol.Size = Size;

    return tCol;
}

CGM::Colider2i CGM::Get_Colider2_FromPosAndSize(int xPos, int yPos, int xSize, int ySize) {
    return CGM::Get_Colider2_FromPosAndSize(CGM::Vector2i(xPos, yPos), CGM::Vector2i(xSize, ySize));
}

CGM::Colider2d CGM::Get_Colider2_FromPosAndSize(CGM::Vector2d Pos, CGM::Vector2d Size) {
    CGM::Colider2d tCol;

    tCol.Position = Pos;
    tCol.Size = Size;

    return tCol;
}

CGM::Colider2d CGM::Get_Colider2_FromPosAndSize(double xPos, double yPos, double xSize, double ySize) {
    return CGM::Get_Colider2_FromPosAndSize(CGM::Vector2d(xPos, yPos), CGM::Vector2d(xSize, ySize));
}

bool CGM::Check_Colider2_VectorInColider(CGM::Vector2i Vec2i, CGM::Colider2i Col2i) {
    return (Vec2i.x >= Col2i.Position.x && Vec2i.x < (Col2i.Position + Col2i.Size).x)
        && (Vec2i.y >= Col2i.Position.y && Vec2i.y < (Col2i.Position + Col2i.Size).y);
}

bool CGM::Check_Colider2_VectorInColider(CGM::Vector2d Vec2d, CGM::Colider2d Col2d) {
    return (Vec2d.x >= Col2d.Position.x && Vec2d.x < (Col2d.Position + Col2d.Size).x)
        && (Vec2d.y >= Col2d.Position.y && Vec2d.y < (Col2d.Position + Col2d.Size).y);
}

bool CGM::Check_Colider2_ColiderInColider(CGM::Colider2i Col2i1, CGM::Colider2i Col2i2) {
    if ((Col2i1.Position + Col2i1.Size).x < Col2i2.Position.x || (Col2i1.Position.x >= (Col2i2.Position + Col2i2.Size).x)) return false;
    if ((Col2i1.Position + Col2i1.Size).y < Col2i2.Position.y || (Col2i1.Position.y >= (Col2i2.Position + Col2i2.Size).y)) return false;
    return true;
}

bool CGM::Check_Colider2_ColiderInColider(CGM::Colider2d Col2d1, CGM::Colider2d Col2d2) {
    if ((Col2d1.Position + Col2d1.Size).x < Col2d2.Position.x || (Col2d1.Position.x >= (Col2d2.Position + Col2d2.Size).x)) return false;
    if ((Col2d1.Position + Col2d1.Size).y < Col2d2.Position.y || (Col2d1.Position.y >= (Col2d2.Position + Col2d2.Size).y)) return false;
    return true;
}
