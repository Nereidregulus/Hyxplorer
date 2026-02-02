#include "NodeSections.h"

NodeSections::NodeSections(std::span<const char> buffer)
{
	uint32_t cursor_pos = parseHeader(buffer);

	for (int i = 0; i < 10; ++i)
	{
		uint32_t sub_size_position = cursor_pos + 2;
		uint32_t sub_size = *reinterpret_cast<const uint32_t*>(&buffer[sub_size_position]);


		add(std::make_shared<NodeSubSection>(std::span(buffer).subspan(cursor_pos)));

		cursor_pos += sub_size + 2 + 1;
	}

}

NodeSections::~NodeSections()
{

}

void NodeSections::display()
{
    if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_DefaultOpen))
    {
        for (int i = 0; i < child_nodes.size(); ++i)
        {
            std::string idx = "[" + std::to_string(i) + "]";
            ImGui::PushID(i);
            child_nodes[i]->display();
            ImGui::PopID();
        }
        ImGui::TreePop();
    }
}