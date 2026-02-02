#pragma once

#include "TreeNode.h"

class NodeBlocks : public TreeNode
{
public:
	NodeBlocks(std::span<const char> buffer);
	~NodeBlocks();

private:
};

