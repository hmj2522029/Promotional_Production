#include "ImageLoader.h"
#include "DxLib.h"

int ImageLoader::LoadResource(const std::string& path)
{
	return LoadGraph(path.c_str());
}

void ImageLoader::DeleteResource(int id)
{
	DeleteGraph(id);
}
