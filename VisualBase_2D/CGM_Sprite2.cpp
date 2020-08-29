#include "CGM_Sprite2.h"

#include <fstream>

void CGM::Save_Sprite_ToFile(CGM::Sprite* Arr, std::string FileName) {
    std::ofstream MyFile("./Sprite/" + FileName + ".CGM_Sprite", std::ios_base::binary);
#ifdef _DEBUG
    if (!MyFile) DebugBreak();
#endif

    CGM::Vector2i Size = Arr->Size();
    MyFile.write((char*)&Size, sizeof(CGM::Vector2i));

    int total = Size.x * Size.y;
    MyFile.write((char*)(Arr->begin()), sizeof(Arr->GetAt(0, 0)) * total);

    MyFile.close();
}

void CGM::Load_Sprite_FromFile(CGM::Sprite* Arr, std::string FileName) {
    std::ifstream MyFile("./Sprite/" + FileName + ".CGM_Sprite", std::ios_base::binary);
#ifdef _DEBUG
    if (!MyFile) DebugBreak();
#endif

    CGM::Vector2i Size;
    MyFile.read((char*)&Size, sizeof(CGM::Vector2i));

    int Total = Size.x * Size.y;
    Arr->Resize(Size);
    MyFile.read((char*)(Arr->begin()), sizeof(Arr->GetAt(0, 0)) * Total);

    MyFile.close();
}

void CGM::Append_Sprite_ToCanvas(CGM::Canvas* Can, CGM::Sprite* Spr, int xPos, int yPos, int IgnoredColor) {
    CGM::Append_Sprite_ToCanvas(Can, Spr, CGM::Vector2i(xPos, yPos), IgnoredColor);
}

void CGM::Append_Sprite_ToCanvas(CGM::Canvas* Can, CGM::Sprite* Spr, CGM::Vector2i Position, int IgnoredColor) {

    for (int y = 0; y < Spr->Size().y; ++y) {
        for (int x = 0; x < Spr->Size().x; ++x) {
            CGM::Vector2i tOff(x, y);
            tOff += Position;

            if (!CGM::Check_Colider2_VectorInColider(tOff, Can->GetColider())) continue;

            int Col = (int)Spr->GetAt(x, y);
            if (Col == IgnoredColor) continue;

            Can->at(tOff).Attributes = CGM::Get_Color_ClacBackColor(Col);

        }
    }

}
