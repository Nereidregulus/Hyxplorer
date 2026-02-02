#pragma once

#include "TreeNode.h"

class NodeGenericList : public TreeNode
{
public:
	NodeGenericList() = default;
	NodeGenericList(std::span<const char> buffer);
	~NodeGenericList();

private:
};


