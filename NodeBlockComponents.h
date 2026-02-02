#pragma once
#include "TreeNode.h"

class NodeBlockComponents : public TreeNode
{
public:
	NodeBlockComponents(std::span<const char> buffer);
	~NodeBlockComponents();

private:
};

