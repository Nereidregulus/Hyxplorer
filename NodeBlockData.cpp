#include "NodeBlockData.h"

#include <sstream> 
#include <iostream>
#include <iomanip>
#include <format>

NodeBlockData::NodeBlockData(std::span<const char> buffer)
{
	uint32_t cursor_pos = parseHeader(buffer);

	uint32_t header2 = *reinterpret_cast<const uint32_t*>(&buffer[cursor_pos]);
	cursor_pos += 4;
	uint16_t header3 = *reinterpret_cast<const uint16_t*>(&buffer[cursor_pos]);
	cursor_pos += 2;
	uint8_t nb_block_palette = *reinterpret_cast<const uint8_t*>(&buffer[cursor_pos]);
	cursor_pos += 1;

	uint32_t full_size_storage = size - 4;
	// Palette
	for (int i = 0; i < nb_block_palette; i++)
	{
		uint16_t block_id = *reinterpret_cast<const uint16_t*>(&buffer[cursor_pos]);
		cursor_pos += 2;
		uint8_t block_name_length = *reinterpret_cast<const uint8_t*>(&buffer[cursor_pos]);
		cursor_pos += 1;
		std::string block_name(&buffer[cursor_pos], block_name_length);
		cursor_pos += block_name_length;
		uint16_t block_metadata = *reinterpret_cast<const uint16_t*>(&buffer[cursor_pos]);
		cursor_pos += 2;

		blocks_palette.push_back(BlockPalette{ block_id ,block_name , block_metadata });

		full_size_storage = full_size_storage - 2 - 1 - block_name_length - 2;
	}
	
	block_storage = buffer.subspan(cursor_pos, full_size_storage);
	/*
	std::stringstream ss;
	for (int i = 0; i < block_storage.size(); ++i)
		ss << std::hex << (int)block_storage[i];
	block_storage_hex = ss.str();
	*/
}

NodeBlockData::~NodeBlockData()
{

}

void NodeBlockData::display()
{
	static bool window_opened = false;
	if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_DrawLinesFull))
	{
		if (ImGui::TreeNodeEx("Palette", ImGuiTreeNodeFlags_DrawLinesFull))
		{
			for (int i = 0; i < blocks_palette.size(); ++i)
			{
				if (ImGui::TreeNodeEx(blocks_palette[i].block_name.c_str(), ImGuiTreeNodeFlags_DrawLinesFull))
				{
					ImGui::Text(("Id:"+std::to_string(blocks_palette[i].block_id)).c_str());
					ImGui::Text(("Metadata:" + std::to_string(blocks_palette[i].block_metadata)).c_str());

					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
		if (ImGui::Button("Block Data"))
		{
			window_opened = !window_opened;
			std::stringstream ss;
			for (int i = 0; i < block_storage.size(); ++i)
			{
				ss << std::format("{:02X}", block_storage[i]);
				ss << " ";
				//std::string s = std::format("{:4x}", block_storage[i]);
				if (i % 32 == 31)
					ss << std::endl;
			}
			ss << '\0';
			block_storage_hex = ss.str();
		}
		if (window_opened)
		{
			ImGui::Begin("Block Data Layout");
			ImGui::InputTextMultiline("##source", (char*)block_storage_hex.c_str(), block_storage_hex.size(), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_ReadOnly);
			ImGui::End();
		}

		ImGui::TreePop();
	}
}