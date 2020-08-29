#pragma once

#include "CGM_Canvas.h"
#include "CGM_Sprite2.h"

namespace CGM {

	class Animation;
	void Load_Animation_FromFile(CGM::Animation* Anim, std::string FileName);

	class Animation {

		CGM::Canvas* MyCan;

		std::vector<CGM::Sprite> MySpriteArray;

		CGM::Vector2i MySize;
		CGM::Vector2i MyPos;

		int MyIgnoredColor = CGM::Color::Black;
		int MyCurrFrame = 0;

		bool MyLoopMode = true;

		void resize_SpriteArray();

	public:

		Animation(CGM::Canvas* Can) { this->MyCan = Can; }
		Animation(CGM::Canvas* Can, CGM::Vector2i Size) : Animation(Can) { this->SetSize(Size); }
		Animation(CGM::Canvas* Can, int xSize, int ySize) : Animation(Can, CGM::Vector2i(xSize, ySize)) {}

		Animation(CGM::Canvas* Can, std::string FileName) : Animation(Can) { CGM::Load_Animation_FromFile(this, FileName); }

		void SetSize(CGM::Vector2i Size);
		void SetSize(int xSize, int ySize) { this->SetSize(CGM::Vector2i(xSize, ySize)); }
		void SetPosition(CGM::Vector2i Pos) { this->MyPos = Pos; }
		void SetPosition(int xPos, int yPos) { this->SetPosition(CGM::Vector2i(xPos, yPos)); }

		void SetIgnoredColor(int Color) { this->MyIgnoredColor = Color; }
		void SetCurrentFrame(int FrameIndex);

		void NextFrame();
		void LastFrame();

		void SetLoopMode(bool Mode) { this->MyLoopMode = Mode; }

		void SetAt(int Color, int FrameIndex, int x, int y) { this->SetAt(Color, FrameIndex, CGM::Vector2i(x, y)); }
		void SetAt(int Color, int FrameIndex, CGM::Vector2i Index);
		void SetAt_CurrentFrame(int Color, int x, int y) { this->SetAt(Color, this->MyCurrFrame, x, y); }
		void SetAt_CurrentFrame(int Color, CGM::Vector2i Index) { this->SetAt(Color, this->MyCurrFrame, Index); }

		int GetAt(int FrameIndex, int x, int y) const { return this->GetAt(FrameIndex, CGM::Vector2i(x, y)); }
		int GetAt(int FrameIndex, CGM::Vector2i Index) const;
		int GetAt_CurrentFrame(int x, int y) const { return this->GetAt(this->MyCurrFrame, x, y); }
		int GetAt_CurrentFrame(CGM::Vector2i Index) const { return this->GetAt(this->MyCurrFrame, Index); }

		int GetFrameCount() const { return this->MySpriteArray.size(); }
		int GetFrameCurrent() const { return this->MyCurrFrame; }

		bool GetLoopMode() const { return this->MyLoopMode; }

		CGM::Vector2i GetSize() const { return this->MySize; }
		CGM::Vector2i GetPosition() const { return this->MyPos; }

		CGM::Colider2i GetColider() const { return CGM::Get_Colider2_FromPosAndSize(this->MyPos, this->MySize); }

		void AddFrame() { this->MySpriteArray.emplace_back(this->MySize); }
		void PopFrame() { this->MySpriteArray.pop_back(); }

		void DropAllFrames() { this->MySpriteArray.clear(); }

		void Clear() { for (auto& el : this->MySpriteArray) el.Clear(); }
		void Clear_CurrentFrame() { this->MySpriteArray[this->MyCurrFrame].Clear(); }

		void Append();
		void AppendAndNextFrame();

		friend void Save_Animation_ToFile(CGM::Animation* Anim, std::string FileName);
		friend void Save_Animation_SaveSingleFrameAsSprite(CGM::Animation* Anim, int FrameIndex, std::string FileName);

		friend void Load_Animation_FromFile(CGM::Animation* Anim, std::string FileName);
		friend bool Load_Animation_LoadSpriteFromFileAndAddToAnimation(CGM::Animation* Anim, std::string FileName);

	};

	void Save_Animation_ToFile(CGM::Animation* Anim, std::string FileName);
	void Save_Animation_SaveSingleFrameAsSprite(CGM::Animation* Anim, int FrameIndex, std::string FileName);

	void Load_Animation_FromFile(CGM::Animation* Anim, std::string FileName);
	bool Load_Animation_LoadSpriteFromFileAndAddToAnimation(CGM::Animation* Anim, std::string FileName);

}