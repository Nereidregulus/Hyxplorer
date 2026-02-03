#include "NodeRegion.h"


NodeRegion::NodeRegion() {}

NodeRegion::NodeRegion(const std::string& region_file)
{
    name = "Region";
    std::ifstream file(region_file, std::ios::binary | std::ios::ate);
    if (!file)
        throw std::runtime_error("Failed to open file");

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer_file(size);
    if (!file.read(buffer_file.data(), size))
        throw std::runtime_error("Failed to read file");

    buffer = buffer_file;

    // Read version
    version = read_be<unsigned int>(&buffer[version_position]);

    // Read number of sections
    nb_section = read_be<unsigned int>(&buffer[nb_section_position]);
    section_indexes.resize(nb_section);

    // Read section size
    section_size = read_be<unsigned int>(&buffer[section_size_position]);

    // Read list of indexes of sections. 1024 in total
    unsigned int cursor_pos = section_offset;
    for (size_t i = 0; i < nb_section; ++i)
    {
        unsigned int next_section_idx = read_be<unsigned int>(&buffer[cursor_pos]);
        section_indexes[i] = next_section_idx;

        unsigned int next_section_position = next_section_idx * section_size + section_offset;

        add(std::make_shared<NodeRoot>(std::span(buffer).subspan(next_section_position)));

        cursor_pos += 4;
    }
}

NodeRegion::~NodeRegion() {}


void NodeRegion::display()
{
    if (ImGui::TreeNode(name.c_str()))
    {
        int i = 0;
        for (auto& child_node : child_nodes)
        {
            int x = 0;
            int y = 0;
            x = i % 32;
            y = floor(i / 32);
            std::string idx = "[" + std::to_string(x) + "][" + std::to_string(y) + "]";
            if (ImGui::TreeNodeEx(idx.c_str(), ImGuiTreeNodeFlags_DrawLinesFull))
            {
                ImGui::PushID(i);
                child_node->display();
                ImGui::PopID();

                ImGui::TreePop();
            }

            i++;
        }
        ImGui::TreePop();
    }
}