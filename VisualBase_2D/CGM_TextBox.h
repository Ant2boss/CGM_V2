#pragma once

#include "CGM_Canvas.h"

#define ENDLINE '\n'

namespace CGM {

	class TextBox {

		CGM::Canvas* MyCan;

		CGM::Array2D<char> MyCharArray;
		CGM::Array2D<int> MyColorArray;
		CGM::Array2D<bool> MyBoolArray;

		CGM::Vector2i MyCursorPos;
		int MyTextColor = CGM::Color::White;

		CGM::Colider2i MyColider;

		void resize_my_arrays();
		void check_cursor_pos();
		void add_word_to_arrays(std::string word);

	public:

		TextBox(CGM::Canvas* Can) : TextBox(Can, Can->GetSize()) {}
		TextBox(CGM::Canvas* Can, CGM::Vector2i Size);
		TextBox(CGM::Canvas* Can, int xSize, int ySize) : TextBox(Can, CGM::Vector2i(xSize, ySize)) {}

		CGM::TextBox& operator<< (std::string str);

		CGM::TextBox& operator<< (const char* str) { return this->operator<<(std::string(str)); }
		CGM::TextBox& operator<< (bool Val);
		CGM::TextBox& operator<< (char Val);
		CGM::TextBox& operator<< (int Val);
		CGM::TextBox& operator<< (float Val);
		CGM::TextBox& operator<< (double Val);

		void SetTextColor(int Color) { this->MyTextColor = Color; }
		void SetCursorPosition(int x, int y) { this->SetCursorPosition(CGM::Vector2i(x, y)); }
		void SetCursorPosition(CGM::Vector2i Pos);

		void SetPosition(int x, int y) { this->SetPosition(CGM::Vector2i(x, y)); }
		void SetPosition(CGM::Vector2i Pos) { this->MyColider.Position = Pos; }

		void SetSize(int x, int y) { this->SetSize(CGM::Vector2i(x, y)); }
		void SetSize(CGM::Vector2i Size);

		void SetColider(CGM::Colider2i Col);

		int GetTextColor(int Color) const { return this->MyTextColor; }

		CGM::Vector2i GetSize() const { return this->MyColider.Size; }
		CGM::Vector2i GetPosition() const { return this->MyColider.Position; }
		CGM::Vector2i GetCursorPosition() const { return this->MyCursorPos; }

		CGM::Colider2i GetColider() const { return this->MyColider; }

		void Center() { this->Center_LeftRight(); this->Center_TopBottom(); }
		void Center_TopBottom();
		void Center_LeftRight();

		void Clear();

		void Append();

	};

	std::string Get_User_InputFromTextBox(CGM::Canvas* Can, CGM::TextBox* Text);

}