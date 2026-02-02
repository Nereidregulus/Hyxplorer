#include "NodeComponents.h"
#include "NodeBlockComponentChunk.h"
#include "NodeEnvironmentChunk.h"
#include "NodeChunkColumn.h"
#include "NodeBlocks.h"




NodeComponents::NodeComponents(std::span<const char> buffer)
{
	uint32_t cursor_pos = parseHeader(buffer);

	bool end_of_node = false;
	uint32_t cumulated_size = 5; // Size + header
	// Get sub components. Components are not at a defined order!
	while (!end_of_node)
	{
		// Get child name
		uint32_t child_pos = cursor_pos;
		std::string child_name(&buffer[child_pos]);
		cursor_pos += child_name.size() + 1;
		uint32_t child_size = *reinterpret_cast<const uint32_t*>(&buffer[cursor_pos]);
		cursor_pos += child_size;

		addNode(child_name, std::span(buffer).subspan(child_pos));
		
		uint32_t end_of_component = buffer[cursor_pos];
		cursor_pos += 1;

		cumulated_size += child_size + 1 + child_name.size() + 1;
		if (cumulated_size >= size)
			break;
	}
}

NodeComponents::~NodeComponents()
{

}