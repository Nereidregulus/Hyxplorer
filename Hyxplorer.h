#pragma once
#include "TreeNode.h"
#include "NodeRegion.h"

class Hyxplorer
{
public:
	Hyxplorer();
	~Hyxplorer();

	void loadFile();
	void loadFile(std::string file_path);

	void display();

private:
	NodeRegion* m_region;
	bool file_opened{ false };
};

