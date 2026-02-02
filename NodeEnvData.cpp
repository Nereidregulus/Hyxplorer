#include "NodeEnvData.h"

#include <sstream> 
#include <iostream>
#include <iomanip>
#include <format>

NodeEnvData::NodeEnvData(std::span<const char> buffer) : env_data_ordered(1024)
{
	uint32_t cursor_pos = parseHeader(buffer);

	uint8_t nb_block_palette = *reinterpret_cast<const uint8_t*>(&buffer[cursor_pos+3]);
	cursor_pos += 4;

	uint32_t full_size_storage = size - 4;
	// Palette
	for (int i = 0; i < nb_block_palette; i++)
	{
		uint8_t block_id = *reinterpret_cast<const uint8_t*>(&buffer[cursor_pos+3]);
		cursor_pos += 4;
		uint8_t nothing = *reinterpret_cast<const uint8_t*>(&buffer[cursor_pos]);
		cursor_pos += 1;
		uint8_t block_name_length = *reinterpret_cast<const uint8_t*>(&buffer[cursor_pos]);
		cursor_pos += 1;
		std::string block_name(&buffer[cursor_pos], block_name_length);
		cursor_pos += block_name_length;

		blocks_palette.push_back(EnvPalette{ block_name , 0 , block_id });

		full_size_storage = full_size_storage - 1 - block_name_length - 4 - 1;
	}

	block_storage = buffer.subspan(cursor_pos, full_size_storage);


	uint32_t data_cursor = 0;
	int nb_sections = 0;
	while (data_cursor < full_size_storage)
	{
		uint8_t nb_delimiters = *reinterpret_cast<const uint8_t*>(&block_storage[data_cursor + 3]);
		data_cursor += 4;

		std::vector<int8_t> delimiters;
		for (int i = 0; i < nb_delimiters; ++i)
		{
			delimiters.push_back(*reinterpret_cast<const int8_t*>(&block_storage[data_cursor + 3]));
			data_cursor += 4;
		}

		uint8_t nb_biomes = nb_delimiters + 1;
		std::vector<uint8_t> biomes;
		for (int i = 0; i < nb_biomes; ++i)
		{
			biomes.push_back(*reinterpret_cast<const uint8_t*>(&block_storage[data_cursor + 3]));
			data_cursor += 4;
		}

		for (int i = 0; i < nb_biomes + nb_delimiters; ++i)
		{
			if (i % 2)
				env_data_ordered[nb_sections].append(std::to_string(delimiters[floor((i - 1) / 2)]) + " < ");
			else
			{
				uint32_t biome_id = biomes[floor(i / 2)];
				for (int i = 0; i < blocks_palette.size(); ++i)
				{
					if (biome_id == blocks_palette[i].block_id)
					{
						env_data_ordered[nb_sections].append(blocks_palette[i].block_name + " < ");
						break;
					}
				}
			}
		}

		nb_sections++;
	}
}

NodeEnvData::~NodeEnvData()
{

}

void NodeEnvData::display()
{
	static bool window_opened = false;
	std::string name_tree = name + ":" + std::to_string(size);
	if (ImGui::TreeNodeEx(name_tree.c_str(), ImGuiTreeNodeFlags_DrawLinesFull))
	{
		if (ImGui::TreeNodeEx("Palette", ImGuiTreeNodeFlags_DrawLinesFull))
		{
			for (int i = 0; i < blocks_palette.size(); ++i)
			{
				if (ImGui::TreeNodeEx(blocks_palette[i].block_name.c_str(), ImGuiTreeNodeFlags_DrawLinesFull))
				{
					ImGui::Text(("Id:" + std::to_string(blocks_palette[i].block_id)).c_str());
					//ImGui::Text(("Metadata:" + std::to_string(blocks_palette[i].block_metadata)).c_str());
					ImGui::Text(("Metadata:" + std::format("{:04X}", blocks_palette[i].block_metadata)).c_str());

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
			if (ImGui::TreeNode("Environment Biome Column"))
			{
				for (int i = 0; i < env_data_ordered.size(); ++i)
				{
					int x = 0;
					int y = 0;
					x = i % 32;
					y = floor(i / 32);
					std::string idx = "[" + std::to_string(x) + "][" + std::to_string(y) + "]";
					if (ImGui::TreeNodeEx(idx.c_str(), ImGuiTreeNodeFlags_DrawLinesFull))
					{
						ImGui::Text(env_data_ordered[i].c_str());
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
			ImGui::End();
		}

		ImGui::TreePop();
	}
}