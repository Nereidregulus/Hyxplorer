#pragma once
#include "TreeNode.h"

class NodeEnvironmentChunk : public TreeNode
{
public:
	NodeEnvironmentChunk(std::span<const char> buffer);
	~NodeEnvironmentChunk();

private:
};

