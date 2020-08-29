#include "CGM_Animation2.h"

#include <fstream>

#define FILE_ANIMATION_ADDON ".CGM_Anim"

void CGM::Animation::resize_SpriteArray() {
	for (auto& el : this->MySpriteArray) el.Resize(this->GetSize());
}

void CGM::Animation::SetSize(CGM::Vector2i Size) {
	this->MySize = Size;
	this->resize_SpriteArray();
}

void CGM::Animation::SetCurrentFrame(int FrameIndex) {
	if (FrameIndex < 0) FrameIndex = 0;
	if (FrameIndex >= this->GetFrameCount()) FrameIndex = this->GetFrameCount() - 1;

	this->MyCurrFrame = FrameIndex;
}

void CGM::Animation::NextFrame() {
	++this->MyCurrFrame;

	if (this->MyCurrFrame >= this->GetFrameCount()) {
		
		if (this->MyLoopMode) this->MyCurrFrame = 0;
		else this->MyCurrFrame = this->GetFrameCount() - 1;

	}
}

void CGM::Animation::LastFrame() {
	--this->MyCurrFrame;

	if (this->MyCurrFrame < 0) {
		
		if (this->MyLoopMode) this->MyCurrFrame = this->GetFrameCount() - 1;
		else this->MyCurrFrame = 0;

	}
}

void CGM::Animation::SetAt(int Color, int FrameIndex, CGM::Vector2i Index) {
#ifdef _DEBUG
	if (Index.x < 0 || Index.x >= this->GetSize().x || Index.y < 0 || Index.y >= this->GetSize().y) DebugBreak();
#endif
	this->MySpriteArray[FrameIndex].SetAt(Color, Index);
}

int CGM::Animation::GetAt(int FrameIndex, CGM::Vector2i Index) const {
#ifdef _DEBUG
	if (Index.x < 0 || Index.x >= this->GetSize().x || Index.y < 0 || Index.y >= this->GetSize().y) DebugBreak();
#endif
	return this->MySpriteArray[FrameIndex].GetAt(Index);
}

void CGM::Animation::Append() {
	CGM::Append_Sprite_ToCanvas(this->MyCan, &this->MySpriteArray[this->MyCurrFrame], this->MyPos, this->MyIgnoredColor);
}

void CGM::Animation::AppendAndNextFrame() {
	this->Append();
	this->NextFrame();
}

void CGM::Save_Animation_ToFile(CGM::Animation* Anim, std::string FileName) {
	//[broj frameova] [CGM::Vector2i -> Size] [ ... ]

	std::ofstream MyFile("./Animation/" + FileName + FILE_ANIMATION_ADDON, std::ios_base::binary);
#ifdef _DEBUG
	if (!MyFile) DebugBreak();
#endif


	int tFrameCount;
	tFrameCount = Anim->GetFrameCount();

	MyFile.write((char*)&tFrameCount, sizeof(int));
	MyFile.write((char*)&Anim->MySize, sizeof(CGM::Vector2i));

	for (int i = 0; i < tFrameCount; ++i) {

		int totalSize = Anim->MySpriteArray[i].Size().x * Anim->MySpriteArray[i].Size().y;
		MyFile.write(Anim->MySpriteArray[i].begin(), sizeof(char) * totalSize);

	}

	MyFile.close();

}

void CGM::Save_Animation_SaveSingleFrameAsSprite(CGM::Animation* Anim, int FrameIndex, std::string FileName) {
	CGM::Save_Sprite_ToFile(&Anim->MySpriteArray[FrameIndex], FileName);
}

void CGM::Load_Animation_FromFile(CGM::Animation* Anim, std::string FileName) {

	std::ifstream MyFile("./Animation/" + FileName + FILE_ANIMATION_ADDON, std::ios_base::binary);
#ifdef _DEBUG
	if (!MyFile) DebugBreak();
#endif

	Anim->DropAllFrames();

	int tFrameCount;
	CGM::Vector2i tAnimSize;
	MyFile.read((char*)&tFrameCount, sizeof(int));
	MyFile.read((char*)&tAnimSize, sizeof(CGM::Vector2i));

	Anim->SetSize(tAnimSize);
	int totalSize = tAnimSize.x * tAnimSize.y;

	for (int i = 0; i < tFrameCount; ++i) {
		Anim->AddFrame();
		MyFile.read(Anim->MySpriteArray[i].begin(), sizeof(char) * totalSize);
	}

	MyFile.close();
}

bool CGM::Load_Animation_LoadSpriteFromFileAndAddToAnimation(CGM::Animation* Anim, std::string FileName) {
	CGM::Sprite tSpr;
	CGM::Load_Sprite_FromFile(&tSpr, FileName);

	if (tSpr.Size() == Anim->GetSize()) {
		
		Anim->AddFrame();
		Anim->MySpriteArray[Anim->GetFrameCount() - 1] = tSpr;
		return true;
	}

	return false;
}


