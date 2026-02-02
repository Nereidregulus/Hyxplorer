#pragma once
#include "TreeNode.h"

class NodeBlockComponentChunk : public TreeNode
{
public:
	NodeBlockComponentChunk(std::span<const char> buffer);
	~NodeBlockComponentChunk();

private:
};

