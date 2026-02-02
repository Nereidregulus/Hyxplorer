#include "NodeBlockComponentChunk.h"
#include "NodeBlockComponents.h"
#include "NodeGenericList.h"


NodeBlockComponentChunk::NodeBlockComponentChunk(std::span<const char> buffer)
{
	uint32_t cursor_pos = parseHeader(buffer);

	// NodeBlockComponents node_block_components(std::span(buffer).subspan(cursor_pos));
	if (size > 27)
		add(std::make_shared<NodeGenericList>(std::span(buffer).subspan(cursor_pos)));
}

NodeBlockComponentChunk::~NodeBlockComponentChunk()
{

}