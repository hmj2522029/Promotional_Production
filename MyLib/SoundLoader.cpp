#include "SoundLoader.h"
#include "DxLib.h"

int SoundLoader::LoadResource(const std::string& path)
{
	//path‚ð•¶Žš—ñ‚É‚µ‚Ä“n‚·
	return LoadSoundMem(path.c_str());
}

void SoundLoader::DeleteResource(int id)
{
	DeleteSoundMem(id);
}
