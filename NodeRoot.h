#pragma once

#include "TreeNode.h"
#include "NodeComponents.h"

class NodeRoot : public TreeNode
{
public:
	NodeRoot() = default;
	NodeRoot(std::span<const char> buffer);
	~NodeRoot();

	void display() override;
	void expand() override;

private:
	unsigned int uncompressed_size{ 0 };
	unsigned int compressed_size{ 0 };

	NodeComponents node_components;

	std::span<const char> buffer_stored;
};


