#pragma once

#include "TreeNode.h"


struct BlockPalette
{
	uint16_t block_id{ 0 };
	std::string block_name;
	uint16_t block_metadata{ 0 };
};

class NodeBlockData : public TreeNode
{
public:
	NodeBlockData(std::span<const char> buffer);
	~NodeBlockData();

	void display() override;

private:
	std::vector<BlockPalette> blocks_palette;
	std::span<const char> block_storage;

	std::string block_storage_hex;
};

