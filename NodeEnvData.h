#pragma once

#include "TreeNode.h"


struct EnvPalette
{
	std::string block_name;
	uint32_t block_metadata{ 0 };
	uint8_t block_id{ 0 };
};

class NodeEnvData : public TreeNode
{
public:
	NodeEnvData(std::span<const char> buffer);
	~NodeEnvData();

	void display() override;

private:
	std::vector<EnvPalette> blocks_palette;
	std::vector<std::string> env_data_ordered;
	std::span<const char> block_storage;

	std::string block_storage_hex;
};

