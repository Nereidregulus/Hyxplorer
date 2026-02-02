#pragma once
#include <vector>
#include <span>
#include <string>

#include "imgui.h"
#include <memory>
#include <unordered_map>

using Handler = void(*)(std::span<const char>);

class TreeNode {
public:
	TreeNode();
	TreeNode(std::span<const char> buffer);
	virtual ~TreeNode() = default;

    uint32_t parseHeader(std::span<const char> buffer);
	void add(std::shared_ptr<TreeNode> ptr);
	void addNode(std::string type, std::span<const char> buffer);

	void virtual expand();
	void virtual collapse();

	uint32_t length();
	virtual void display();
	void parse();

	std::vector<std::shared_ptr<TreeNode>> child_nodes;
	std::vector<std::shared_ptr<TreeNode>> parent_nodes;

protected:
	std::string name;
	unsigned int size{ 0 };
	uint8_t header{ 0 };

	bool expanded{ false };

};


template <typename T>
T read_be(const char* data)
{
    static_assert(std::is_unsigned_v<T>, "T must be unsigned");

    T value = 0;
    for (size_t i = 0; i < sizeof(T); ++i)
    {
        value = (value << 8) | static_cast<unsigned char>(data[i]);
    }
    return value;
}