#pragma once

#include "TreeNode.h"

class NodeComponents : public TreeNode
{
public:
	NodeComponents() = default;
	NodeComponents(std::span<const char> buffer);
	~NodeComponents();

private:
};


