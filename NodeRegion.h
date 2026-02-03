#pragma once
#include <string>
#include <fstream>

#include "TreeNode.h"
#include "NodeRoot.h"

class NodeRegion : public TreeNode
{
public:
	NodeRegion();
	NodeRegion(const std::string& region_file);
	~NodeRegion();

	void display() override;

private:
	std::string hytale_header[20];

	unsigned int section_offset{ 0x20 };

	unsigned int version_position{ 0x14 };
	unsigned int nb_section_position{ 0x18 };
	unsigned int section_size_position{ 0x1C };

	unsigned int version{ 0 };
	unsigned int nb_section{ 1024 };
	unsigned int section_size{ 0x1000 };

	std::vector<unsigned int> section_indexes;

	std::vector<char> buffer;
};

