#pragma once

#include "TreeNode.h"

class NodeSubSection : public TreeNode
{
public:
	NodeSubSection(std::span<const char> buffer);
	~NodeSubSection();

private:
};

