#pragma once
#include <stdint.h>
#include <memory>
#include <unordered_map>

class Frame
{
public:
	Frame(size_t size) : data(new uint8_t[size]), pinCount(0) {}
	~Frame() { delete data; }

	void PinFrame() { ++pinCount; }
	void UnpinFrame() { --pinCount; }
	bool isPinned() const { return pinCount > 0; }

	void* GetData() { return data; }
	void SetData(void* data) { this->data = data; }

private:
	void* data;
	uint32_t pinCount = 0;
};

class FrameManager
{
public:
	std::weak_ptr<Frame> GetFrame(uint32_t pageNum);

	static FrameManager& Get() { return instance; }

private:
	std::unordered_map<uint32_t, std::shared_ptr<Frame>> framesMap;

	// configuration
	static const uint32_t PAGE_SIZE = 4096;

	FrameManager() {}
	static FrameManager instance;
};