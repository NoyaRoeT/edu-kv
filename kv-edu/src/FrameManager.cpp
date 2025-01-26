#include "FrameManager.h"

FrameManager FrameManager::instance;

std::weak_ptr<Frame> FrameManager::GetFrame(uint32_t pageNum)
{
	auto it = framesMap.find(pageNum);
	if (it != framesMap.end())
	{
		return it->second;
	}

	// Create the frame if it doesn't exist
	framesMap[pageNum] = std::make_shared<Frame>(PAGE_SIZE);
	// Need to load data from disk
	return framesMap[pageNum];
}