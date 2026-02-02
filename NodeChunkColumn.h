#pragma once
#include "TreeNode.h"

class NodeChunkColumn : public TreeNode
{
public:
	NodeChunkColumn(std::span<const char> buffer);
	~NodeChunkColumn();

private:
};

