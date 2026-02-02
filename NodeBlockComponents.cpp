#include "NodeBlockComponents.h"
#include "NodeBlockComponents.h"

NodeBlockComponents::NodeBlockComponents(std::span<const char> buffer)
{
	uint32_t cursor_pos = parseHeader(buffer);

	std::string identifier(&buffer[cursor_pos]);

	uint32_t num = *reinterpret_cast<const uint32_t*>(&buffer[cursor_pos]);

}

NodeBlockComponents::~NodeBlockComponents()
{

}