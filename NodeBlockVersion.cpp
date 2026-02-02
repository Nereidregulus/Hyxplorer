#include "NodeBlockVersion.h"

NodeBlockVersion::NodeBlockVersion(std::span<const char> buffer)
{
	uint32_t cursor_pos = parseHeader(buffer);


}

NodeBlockVersion::~NodeBlockVersion()
{

}