#include "TreeNode.h"
#include "NodeGenericList.h"
#include "NodeBlockComponentChunk.h"
#include "NodeEnvironmentChunk.h"
#include "NodeChunkColumn.h"
#include "NodeBlocks.h"



TreeNode::TreeNode()
{
}

TreeNode::TreeNode(std::span<const char> buffer)
{
	uint32_t cursor_pos = parseHeader(buffer);

	if (size > 5)
	{
		std::string child_name(&buffer[cursor_pos]);

		addNode(child_name, std::span(buffer).subspan(cursor_pos));
	}
}

void TreeNode::addNode(std::string type, std::span<const char> buffer)
{
	if (type == "Components") { add(std::make_shared<NodeGenericList>(buffer)); return; }
	if (type == "BlockComponentChunk") {add(std::make_shared<NodeBlockComponentChunk>(buffer)); return;}
	if (type == "ChunkColumn") {add(std::make_shared<NodeChunkColumn>(buffer)); return;}
	if (type == "EnvironmentChunk") {add(std::make_shared<NodeEnvironmentChunk>(buffer)); return;}
	if (type == "Block"){ add(std::make_shared<NodeBlocks>(buffer)); return;}
	//if (type == "EntityChunk") {add(std::make_shared<NodeGenericList>(buffer)); return;}

	// Default 
	add(std::make_shared<TreeNode>(buffer));
}


void TreeNode::expand()
{
	expanded = true;
}
void TreeNode::collapse()
{
	expanded = false;
}


uint32_t TreeNode::length()
{
	return size + name.size() + 1;
}

uint32_t TreeNode::parseHeader(std::span<const char> buffer)
{
	uint32_t cursor_pos = 0;
	name = std::string(&buffer[cursor_pos]);
	cursor_pos += name.size() + 1;
	size = *reinterpret_cast<const uint32_t*>(&buffer[cursor_pos]);
	cursor_pos += 4;
	header = buffer[cursor_pos];
	cursor_pos += 1;

	return cursor_pos;
}

void TreeNode::add(std::shared_ptr<TreeNode> ptr) {
	child_nodes.push_back(ptr);
}

void TreeNode::display()
{
	if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_DrawLinesFull))
	{
		for (auto& child_node : child_nodes)
		{
			child_node->display();
		}
		ImGui::TreePop();
	}
}
