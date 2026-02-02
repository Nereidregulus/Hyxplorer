#include "NodeEnvironmentChunk.h"
#include "NodeEnvData.h"

NodeEnvironmentChunk::NodeEnvironmentChunk(std::span<const char> buffer)
{
	uint32_t cursor_pos = parseHeader(buffer);

	add(std::make_shared<NodeEnvData>(std::span(buffer).subspan(cursor_pos)));
}

NodeEnvironmentChunk::~NodeEnvironmentChunk()
{

}