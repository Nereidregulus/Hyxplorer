#include "NodeChunkColumn.h"
#include "NodeSections.h"

NodeChunkColumn::NodeChunkColumn(std::span<const char> buffer)
{
	uint32_t cursor_pos = parseHeader(buffer);

	add(std::make_shared<NodeSections>(std::span(buffer).subspan(cursor_pos)));
}

NodeChunkColumn::~NodeChunkColumn()
{

}