#include <iostream>

//test

class TreeNode
{
private:
	std::pair<char, std::string> thisElement;
	TreeNode* NextElements;
	int NextElementsAmount;

public:
	TreeNode(std::pair<char, std::string> thisElement, TreeNode* NextElements, int NextElementsAmount)
	{
		this->thisElement = thisElement;
		this->NextElements = NextElements;
		this->NextElementsAmount = NextElementsAmount;
	}

	std::pair<char, std::string> GetElement()
	{
		return thisElement;
	}

	TreeNode* GetNextElements()
	{
		return NextElements;
	}

	int GetNextElementsAmount()
	{
		return NextElementsAmount;
	}
};