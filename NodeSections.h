#pragma once
#include "TreeNode.h"
#include "NodeSubSection.h"

class NodeSections : public TreeNode
{
public:
	NodeSections(std::span<const char> buffer);
	~NodeSections();

	void display() override;

private:
	std::vector<NodeSubSection> chunk_section;
};
