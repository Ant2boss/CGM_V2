#include "CGM_Canvas.h"

int CGM::Canvas::indexOf(int x, int y) const{
    return y * this->Mysize.x + x;
}

int CGM::Canvas::indexOf(CGM::Vector2i Vec) const{
    return this->indexOf(Vec.x, Vec.y);
}

CGM::Canvas::Canvas(CGM::Vector2i Size) {

    this->Mysize = Size;
    this->MyScreenArray.resize(Size.x * Size.y);

    this->MyOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    this->MyInput = GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleMode(this->MyInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    this->MyBuffCoord.X = 0;
    this->MyBuffCoord.Y = 0;

    this->MyBuffSize.X = Size.x;
    this->MyBuffSize.Y = Size.y;

    this->MySR.Top = 0;
    this->MySR.Left = 0;
    this->MySR.Right = Size.x;
    this->MySR.Bottom = Size.y;

    this->MyCSBI.cbSize = sizeof(this->MyCSBI);
    GetConsoleScreenBufferInfoEx(this->MyOutput, &this->MyCSBI);

    this->MyBackupCSBI = this->MyCSBI;

    this->MyCSBI.dwSize.X = Size.x;
    this->MyCSBI.dwSize.Y = Size.y;

    this->MyCSBI.srWindow.Right = Size.x * 8;
    this->MyCSBI.srWindow.Bottom = Size.y * 16;

    this->MyCSBI.ColorTable[CGM::Color::Black]      = RGB(0, 0, 0);
    this->MyCSBI.ColorTable[CGM::Color::Gray]       = RGB(128, 128, 128);
    this->MyCSBI.ColorTable[CGM::Color::White]      = RGB(255, 255, 255);
    this->MyCSBI.ColorTable[CGM::Color::Red]        = RGB(255, 0, 0);
    this->MyCSBI.ColorTable[CGM::Color::DarkRed]    = RGB(128, 0, 0);
    this->MyCSBI.ColorTable[CGM::Color::Cyan]       = RGB(0, 255, 255);
    this->MyCSBI.ColorTable[CGM::Color::Blue]       = RGB(0, 0, 255);
    this->MyCSBI.ColorTable[CGM::Color::DarkBlue]   = RGB(0, 0, 128);
    this->MyCSBI.ColorTable[CGM::Color::Green]      = RGB(0, 255, 0);
    this->MyCSBI.ColorTable[CGM::Color::DarkGreen]  = RGB(0, 128, 0);
    this->MyCSBI.ColorTable[CGM::Color::Magenta]    = RGB(255, 0, 255);
    this->MyCSBI.ColorTable[CGM::Color::Indigo]     = RGB(75, 0, 130);
    this->MyCSBI.ColorTable[CGM::Color::Brown]      = RGB(160, 82, 45);
    this->MyCSBI.ColorTable[CGM::Color::Bisque]     = RGB(255, 228, 196);
    this->MyCSBI.ColorTable[CGM::Color::Yellow]     = RGB(255, 255, 0);
    this->MyCSBI.ColorTable[CGM::Color::Orange]     = RGB(255, 165, 0);

    SetConsoleScreenBufferInfoEx(this->MyOutput, &this->MyCSBI);

}

CGM::Canvas::Canvas(int xSize, int ySize)
    : Canvas(CGM::Vector2i(xSize, ySize)) {}

CGM::Canvas::~Canvas() {
    SetConsoleScreenBufferInfoEx(this->MyOutput, &this->MyBackupCSBI);
}

CHAR_INFO& CGM::Canvas::at(int x, int y) {
#ifdef _DEBUG
    //CGM::Canvas::at is out of bounds
    if (!CGM::Check_Colider2_VectorInColider(CGM::Vector2i(x, y), this->GetColider())) DebugBreak();
#endif
    return this->MyScreenArray[this->indexOf(x, y)];
}

CHAR_INFO& CGM::Canvas::at(CGM::Vector2i index) {
    return this->at(index.x, index.y);
}

CGM::Vector2i CGM::Canvas::GetSize() const{
    return this->Mysize;
}

CGM::Colider2i CGM::Canvas::GetColider() const{
    return CGM::Get_Colider2_FromPosAndSize(CGM::Vector2i(0, 0), this->Mysize);
}

void CGM::Canvas::Clear(int Color) {
    for (int i = 0; i < this->MyScreenArray.size(); ++i) {
        this->MyScreenArray[i].Char.UnicodeChar = ' ';
        this->MyScreenArray[i].Attributes = CGM::Get_Color_ClacBackColor(Color);
    }
}

void CGM::Canvas::Draw() const{
    SMALL_RECT tSR = this->MySR;

    WriteConsoleOutput(this->MyOutput, &this->MyScreenArray[0], this->MyBuffSize, this->MyBuffCoord, &tSR);
}

bool CGM::Check_Mouse_MousePosition(const CGM::Canvas* Can, CGM::Vector2i* MousePos) {
    POINT P;
    GetCursorPos(&P);

    if (ScreenToClient(GetConsoleWindow(), &P)) {
        MousePos->x = P.x;
        MousePos->y = P.y;
        
        if (MousePos->x < 0 || MousePos->y < 0) {
            MousePos->Init(-1, -1);
            return false;
        }
        
        MousePos->x /= 8;
        MousePos->y /= 16;

        if (MousePos->x >= Can->GetSize().x || MousePos->y >= Can->GetSize().y) {
            MousePos->Init(-1, -1);
            return false;
        }

        return true;
    }

    return false;
}

bool CGM::Check_Mouse_LeftClick() {
    return GetKeyState(VK_LBUTTON) < 0;
}

bool CGM::Check_Mouse_RightClick() {
    return GetKeyState(VK_RBUTTON) < 0;
}

int CGM::Get_Color_ClacBackColor(int BackColor) {
    return 16 * BackColor + BackColor;
}

int CGM::Get_Color_ClacFontColor(int FontColor) {
    return FontColor;
}

int CGM::Get_Color_ClacMixColor(int BackColor, int FontColor) {
    return 16 * BackColor + FontColor;
}

int CGM::Get_Color_BackColorFromMix(int MixedColor) {
    return MixedColor / 16;
}

int CGM::Get_Color_FontColorFromMix(int MixedColor) {
    return MixedColor % 16;
}

void CGM::Append_Canvas_Rectangle(CGM::Canvas* Can, int Color, int xStart, int yStart, int xEnd, int yEnd, bool FillShape) {
    CGM::Append_Canvas_Rectangle(Can, Color, CGM::Vector2i(xStart, yStart), CGM::Vector2i(xEnd, yEnd), FillShape);
}

void CGM::Append_Canvas_Rectangle(CGM::Canvas* Can, int Color, CGM::Vector2i Start, CGM::Vector2i End, bool FillShape) {
    CGM::Vector2i tStart = CGM::Get_Vector2_MinVector(Start, End);
    CGM::Vector2i tEnd = CGM::Get_Vector2_MaxVector(Start, End);

    for (int y = Start.y; y < End.y; ++y) {
        for (int x = Start.x; x < End.x; ++x) {
            if (!CGM::Check_Colider2_VectorInColider(CGM::Vector2i(x, y), Can->GetColider())) continue;

            switch (FillShape) {
            case false:
                if (x == Start.x || x == End.x - 1 || y == Start.y || y == End.y - 1)
                    Can->at(x, y).Attributes = CGM::Get_Color_ClacBackColor(Color);
                break;
            case true:
                Can->at(x, y).Attributes = CGM::Get_Color_ClacBackColor(Color);
                break;
            }
        }
    }

}

void CGM::Append_Canvas_Rectangle(CGM::Canvas* Can, int Color, CGM::Colider2i Area, bool FillShape) {
    CGM::Append_Canvas_Rectangle(Can, Color, Area.Position, (Area.Position + Area.Size), FillShape);
}

void CGM::Append_Canvas_ColorArray2D(CGM::Canvas* Can, CGM::Array2Di* ColorArr, CGM::Vector2i Position, int IgnoredColor) {
    
    for (int y = 0; y < ColorArr->Size().y; ++y) {
        for (int x = 0; x < ColorArr->Size().x; ++x) {
            CGM::Vector2i tOff(x, y);
            tOff += Position;
            
            if (!CGM::Check_Colider2_VectorInColider(tOff, Can->GetColider())) continue;
           
            int Col = ColorArr->GetAt(x, y);
            if (Col == IgnoredColor) continue;

            Can->at(tOff).Attributes = CGM::Get_Color_ClacBackColor(Col);

        }
    }

}

void CGM::Append_Canvas_ColorArray2D(CGM::Canvas* Can, CGM::Array2Di* ColorArr, int xPos, int yPos, int IgnoredColor) {
    CGM::Append_Canvas_ColorArray2D(Can, ColorArr, CGM::Vector2i(xPos, yPos), IgnoredColor);
}

bool CGM::Check_Canvas_CopyCanvasToCanvasData(CGM::Canvas* Can, CGM::CanvasData* Data) {
    Data->Resize(Can->GetSize());
    for (int y = 0; y < Can->GetSize().y; ++y) {
        for (int x = 0; x < Can->GetSize().x; ++x) {
            Data->SetAt(Can->at(x, y), x, y);
        }
    }

    return true;
}

bool CGM::Check_Canvas_CopyCanvasDataToCanvas(CGM::Canvas* Can, CGM::CanvasData* Data) {
    if (Data->Size() != Can->GetSize()) return false;

    for (int y = 0; y < Can->GetSize().y; ++y) {
        for (int x = 0; x < Can->GetSize().x; ++x) {
            Can->at(x, y) = Data->GetAt(x, y);
        }
    }

    return true;
}
