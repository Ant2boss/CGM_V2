#pragma once

#include "CGM_Canvas.h"
#include "CGM_Colider2.h"
#include "CGM_TextBox.h"

namespace CGM {

	class Button {

		CGM::Canvas* MyCan;

		CGM::Colider2i MyColider;
		CGM::TextBox MyTextBox;

		int MyColor = CGM::Color::Black;
		int MyHoveredColor = CGM::Color::Black;

	public:

		Button(CGM::Canvas* Can) : Button(Can, CGM::Vector2i(0, 0)) {}
		Button(CGM::Canvas* Can, CGM::Vector2i Size);
		Button(CGM::Canvas* Can, int xSize, int ySize) : Button(Can, CGM::Vector2i(xSize, ySize)) {}

		void SetColor(int Color);
		void SetBaseColor(int Color) { this->MyColor = Color; }
		void SetSelectedColor(int Color) { this->MyHoveredColor = Color; }

		void SetButtonText(std::string str, int str_color);

		void SetSize(int x, int y) { this->SetSize(CGM::Vector2i(x, y)); }
		void SetSize(CGM::Vector2i Size);
		void SetPosition(int x, int y) { this->SetPosition(CGM::Vector2i(x, y)); }
		void SetPosition(CGM::Vector2i Pos);

		void SetColider(CGM::Colider2i Col);

		CGM::Vector2i GetSize() const { return this->MyColider.Size; }
		CGM::Vector2i GetPosition() const { return this->MyColider.Position; }

		CGM::Colider2i GetColider() const { return this->MyColider; }

		int GetBaseColor() const { return this->MyColor; }
		int GetSelectedColor() const { return this->MyHoveredColor; }

		bool IsHovered() const;
		bool IsPressed() const { return (CGM::Check_Mouse_LeftClick() && this->IsHovered()); }

		void ClearText();

		void Append();

	};

	class Button_Matrix {

		CGM::Canvas* MyCan;

		std::vector<CGM::Button> MyButtonArray;

		CGM::Vector2i MyMatrixSize;
		CGM::Vector2i MyMatrixOrigin;
		CGM::Vector2i MySpaceBetweenButtons = {2, 1};

		CGM::Vector2i MyButtonSize;
		int MyButtonBaseColor = CGM::Color::Black;
		int MyButtonSelectColor = CGM::Color::Black;

		bool MyArrayNeedsUpdating = true;

		int indexOf(int x, int y) const { return y * this->MyMatrixSize.x + x; }
		int indexOf(CGM::Vector2i Index) const { return this->indexOf(Index.x, Index.y); }
		
		void resize_ButtonArray();
		void move_ButtonArray();
		void update_ButtonArray();

	public:

		Button_Matrix(CGM::Canvas* Can) { this->MyCan = Can; }
		Button_Matrix(CGM::Canvas* Can, CGM::Vector2i MatrixSize);
		Button_Matrix(CGM::Canvas* Can, int RowCount, int ColumnCount) : Button_Matrix(Can, CGM::Vector2i (RowCount, ColumnCount)) {}

		void SetButtonSize(CGM::Vector2i Size);
		void SetButtonSize(int xSize, int ySize) { this->SetButtonSize(CGM::Vector2i(xSize, ySize)); }

		void SetButtonColor(int Color);
		void SetButtonBaseColor(int Color);
		void SetButtonSelectedColor(int Color);

		void SetMatrixOrigin(CGM::Vector2i Pos);
		void SetMatrixOrigin(int xPos, int yPos) { this->SetMatrixOrigin(CGM::Vector2i(xPos, yPos)); }

		void SetMatrixSize(CGM::Vector2i Size);
		void SetMatrixSize(int xSize, int ySize) { this->SetMatrixSize(CGM::Vector2i(xSize, ySize)); }

		void SetSpaceBetweenButtons(int Distance) { this->SetSpaceBetweenButtons(Distance * 2, Distance); }
		void SetSpaceBetweenButtons(int xDist, int yDist);

		void SetButtonText(std::string str, int str_color, int x, int y) { this->SetButtonText_Index(str, str_color, this->indexOf(x, y)); }
		void SetButtonText(std::string str, int str_color, CGM::Vector2i Index) { this->SetButtonText_Index(str, str_color, this->indexOf(Index)); }
		void SetButtonText_Index(std::string str, int str_color, unsigned int Index);

		CGM::Vector2i GetSpaceBetweenButtons() const { return this->MySpaceBetweenButtons; }

		int GetButtonBaseColor() const { return this->MyButtonBaseColor; }
		int GetButtonSelectedColor() const { return this->MyButtonSelectColor; }

		CGM::Vector2i GetButtonSize() const { return this->MyButtonSize; }

		CGM::Vector2i GetMatrixSize() const { return this->MyMatrixSize; }
		CGM::Vector2i GetMatrixOrigin() const { return this->MyMatrixOrigin; }

		CGM::Colider2i GetMatrixColider() const;

		bool IsHovered(CGM::Vector2i* HoveredIndex);
		bool IsPressed(CGM::Vector2i* PressedIndex) { return CGM::Check_Mouse_LeftClick() && this->IsHovered(PressedIndex); }

		bool IsHovered_Index(int* HoveredIndex);
		bool IsPressed_Index(int* PressedIndex) { return CGM::Check_Mouse_LeftClick() && this->IsHovered_Index(PressedIndex); }

		bool operator>>(CGM::Vector2i& Index) { return this->IsPressed(&Index); }
		bool operator>>(int& Index) { return this->IsPressed_Index(&Index); }

		void Clear_ButtonTexts() { for (auto& el : this->MyButtonArray) el.ClearText(); }

		void Append();

	};

}