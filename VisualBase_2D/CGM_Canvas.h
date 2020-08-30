#pragma once

#include "CGM_Vector2.h"
#include "CGM_Colider2.h"

#include <vector>
#include <string>
#include <Windows.h>

namespace CGM {

	struct Color {

		Color() = delete;

		static const int Black = 0;

		static const int Gray = 1;
		static const int White = 2;

		static const int Red = 3;
		static const int DarkRed = 4;

		static const int Cyan = 5;
		static const int Blue = 6;
		static const int DarkBlue = 7;

		static const int Green = 8;
		static const int DarkGreen = 9;

		static const int Magenta = 10;
		static const int Indigo = 11;

		static const int Brown = 12;
		static const int Bisque = 13;
		static const int Yellow = 14;
		static const int Orange = 15;

	};

	class Canvas {

		std::vector<CHAR_INFO> MyScreenArray;
		CGM::Vector2i Mysize;

		CONSOLE_SCREEN_BUFFER_INFOEX MyCSBI;
		CONSOLE_SCREEN_BUFFER_INFOEX MyBackupCSBI;

		COORD MyBuffCoord;
		COORD MyBuffSize;
		SMALL_RECT MySR;

		int indexOf(int x, int y) const;
		int indexOf(CGM::Vector2i Vec) const;

	protected:
		HANDLE MyOutput;
		HANDLE MyInput;

	public:

		Canvas(CGM::Vector2i Size);
		Canvas(int xSize, int ySize);

		~Canvas();

		CHAR_INFO& at(int x, int y);
		CHAR_INFO& at(CGM::Vector2i index);

		CGM::Vector2i GetSize() const;
		CGM::Colider2i GetColider() const;

		void Pause();

		void Clear(int Color = CGM::Color::Black);

		void Draw() const;

	};

	template<typename T>
	class Array2D {
		std::vector<T> MyArray;
		CGM::Vector2i MySize;

	public:
		Array2D() {}
		Array2D(CGM::Vector2i Size);
		Array2D(int xSize, int ySize) : Array2D(CGM::Vector2i(xSize, ySize)) {}

		void SetAt(T Val, int x, int y);
		void SetAt(T Val, CGM::Vector2i Index) { this->SetAt(Val, Index.x, Index.y); }

		T GetAt(int x, int y) const;
		T GetAt(CGM::Vector2i Index) const { return this->GetAt(Index.x, Index.y); }

		T* begin() { return &this->MyArray[0]; }

		CGM::Vector2i Size() const { return this->MySize; }

		void Resize(CGM::Vector2i Size) { this->Resize(Size.x, Size.y); }
		void Resize(int xSize, int ySize);

		void Clear(T Value = 0);

	};

	typedef Array2D<int> Array2Di;
	typedef Array2D<CHAR_INFO> CanvasData;

	bool Check_Mouse_MousePosition(const CGM::Canvas* Can, CGM::Vector2i* MousePos);
	bool Check_Mouse_LeftClick();
	bool Check_Mouse_RightClick();

	int Get_Color_ClacBackColor(int BackColor);
	int Get_Color_ClacFontColor(int FontColor);
	int Get_Color_ClacMixColor(int BackColor, int FronColor);

	int Get_Color_BackColorFromMix(int MixedColor);
	int Get_Color_FontColorFromMix(int MixedColor);

	void Append_Canvas_Rectangle(CGM::Canvas* Can, int Color, int xStart, int yStart, int xEnd, int yEnd, bool FillShape = true);
	void Append_Canvas_Rectangle(CGM::Canvas* Can, int Color, CGM::Vector2i Start, CGM::Vector2i End, bool FillShape = true);
	void Append_Canvas_Rectangle(CGM::Canvas* Can, int Color, CGM::Colider2i Area, bool FillShape = true);

	void Append_Canvas_ColorArray2D(CGM::Canvas* Can, CGM::Array2Di* ColorArr, CGM::Vector2i Position, int IgnoredColor = CGM::Color::Black);
	void Append_Canvas_ColorArray2D(CGM::Canvas* Can, CGM::Array2Di* ColorArr, int xPos, int yPos, int IgnoredColor = CGM::Color::Black);

	bool Check_Canvas_CopyCanvasToCanvasData(CGM::Canvas* Can, CGM::CanvasData* Data);
	bool Check_Canvas_CopyCanvasDataToCanvas(CGM::Canvas* Can, CGM::CanvasData* Data);

	template<typename T>
	inline Array2D<T>::Array2D(CGM::Vector2i Size) {
		this->Resize(Size);
	}

	template<typename T>
	inline void Array2D<T>::SetAt(T Val, int x, int y) {
#ifdef _DEBUG
		if (x < 0 || x >= this->Size().x || y < 0 || y >= this->Size().y) DebugBreak();
#endif
		this->MyArray[y * this->MySize.x + x] = Val;
	}

	template<typename T>
	inline T Array2D<T>::GetAt(int x, int y) const {
#ifdef _DEBUG
		if (x < 0 || x >= this->Size().x || y < 0 || y >= this->Size().y) DebugBreak();
#endif
		return this->MyArray[y * this->MySize.x + x];
	}

	template<typename T>
	inline void Array2D<T>::Resize(int xSize, int ySize) {
		MyArray.clear();
		MyArray.resize(xSize * ySize);
		this->MySize = CGM::Vector2i(xSize, ySize);
	}

	template<typename T>
	inline void Array2D<T>::Clear(T Value) {
		for (int i = 0; i < this->MyArray.size(); ++i) this->MyArray[i] = Value;
	}

}