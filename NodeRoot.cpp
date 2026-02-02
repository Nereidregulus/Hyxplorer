#include <zstd.h>      // presumes zstd library is installed

#include "NodeRoot.h"


NodeRoot::NodeRoot(std::span<const char> buffer) : buffer_stored(buffer)
{
	uncompressed_size = read_be<unsigned int>(&buffer[0]);

	compressed_size = read_be<unsigned int>(&buffer[4]);

	name = "Root";
}

NodeRoot::~NodeRoot()
{

}

void NodeRoot::display()
{

	if (ImGui::IsItemToggledOpen())
	{
		if(!expanded) expand();
	}

	TreeNode::display();
}

void NodeRoot::expand()
{
	expanded = true;

	void* const rBuff = malloc((size_t)uncompressed_size);

	size_t const dSize = ZSTD_decompress(rBuff, uncompressed_size, &buffer_stored[8], compressed_size);

	unsigned char* charBuf = (unsigned char*)rBuff;

	std::vector<char> uc_buffer(charBuf, charBuf + uncompressed_size);

	size = *reinterpret_cast<const uint32_t*>(&uc_buffer[0]);
	header = *reinterpret_cast<const uint32_t*>(&uc_buffer[4]);

	add(std::make_shared<NodeComponents>(std::span(uc_buffer).subspan(5)));
}