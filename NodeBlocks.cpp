#include "NodeBlocks.h"
#include "NodeBlockVersion.h"
#include "NodeBlockData.h"


NodeBlocks::NodeBlocks(std::span<const char> buffer)
{
	uint32_t cursor_pos = parseHeader(buffer);

	add(std::make_shared<NodeBlockVersion>(std::span(buffer).subspan(cursor_pos)));

	// cursor_pos += node_block_version.length();
	cursor_pos += 13;

	add(std::make_shared<NodeBlockData>(std::span(buffer).subspan(cursor_pos)));
}

NodeBlocks::~NodeBlocks()
{

}