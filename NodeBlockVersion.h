#pragma once

#include "TreeNode.h"

class NodeBlockVersion : public TreeNode
{
public:
	NodeBlockVersion(std::span<const char> buffer);
	~NodeBlockVersion();

private:
};


