#include "NodeSubSection.h"
#include "NodeComponents.h"

NodeSubSection::NodeSubSection(std::span<const char> buffer)
{
	uint32_t x_pos = buffer[0];
	uint32_t y_pos = buffer[1];

	name = "[" + std::to_string(x_pos) + "][" + std::to_string(y_pos) + "]";

	size = *reinterpret_cast<const uint32_t*>(&buffer[2]);
	header = buffer[6];

	add(std::make_shared<NodeComponents>(std::span(buffer).subspan(7)));


}

NodeSubSection::~NodeSubSection()
{

}