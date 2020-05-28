#include "Cell.h"
#include <iostream>

Cell::Cell()
{
	content = new char[1];
	content = '\0';
	intContent = 0;
	doubleContent = 0;
	empty = true;
	formula = false;
	physicalLength = 0;
}

Cell::~Cell()
{
	clear();
}

Cell& Cell::operator=(const Cell& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

void Cell::copy(const Cell& other)
{
	content = new char[strlen(other.getContent()) + 1];
	strcpy_s(content, strlen(other.getContent()) + 1, other.getContent());
}

void Cell::clear()
{
	delete[] content;
	intContent = 0;
	doubleContent = 0;
	physicalLength = 0;
}

char* Cell::getContent() const
{
	return content;
}

int Cell::getIntContent() const
{
	return intContent;
}

double Cell::getDoubleContent() const
{
	return doubleContent;
}

void Cell::setContent(const char* newContent)
{
	physicalLength = strlen(newContent);
	if (newContent[0] == '=')
		formula = true;
	empty = false;
	if (checkIfInt(newContent))
	{
		setIntContent(atoi(newContent));
		return;
	}
	if (checkIfDouble(newContent))
	{
		setDoubleContent(atof(newContent));
		return;
	}
	content = new char[strlen(newContent) + 1];
	strcpy_s(content, strlen(newContent) + 1, newContent);
	checkQuotes();
}

void Cell::setIntContent(const int iC)
{
	intContent = iC;
}

void Cell::setDoubleContent(const double dC)
{
	doubleContent = dC;
}

int Cell::getPhysicalLength() const
{
	if (empty)
		return 5;
	
	return physicalLength;
}

void Cell::writeToFile(std::ofstream& ofs)
{
	if (content != '\0')
	{
		ofs << content;
		return;
	}
	if (intContent == 0)
	{
		if (doubleContent == 0.0)
		{
			ofs << 0;
		}
		else {
			ofs << doubleContent;
		}
	}
	else {
		ofs << intContent;
	}
}

float Cell::getSumOfCell() const
{
	if (empty)
		return 0;
	if (content != '\0')
		return 0;
	if (doubleContent != 0)
		return doubleContent;
	return intContent;
}

void Cell::edit(const char* newContent)
{
	clear();
	content = '\0';

	formula = false;
	setContent(newContent);
}

bool Cell::isEmpty()
{
	return empty;
}

void Cell::print() const
{
	if (empty)
	{
		std::cout << "empty";
		return;
	}
	if (content != '\0')
	{
		printCharContent();
	}
	else {
		if (intContent == 0)
		{
			std::cout << doubleContent;
		}
		else {
			std::cout << intContent;
		}
	}
}

void Cell::printCharContent() const
{
	size_t len = strlen(content);
	for (int i = 0; i < len; i++)
	{
		if (content[i] == '"')
		{
			if (i != 0)  // if a quote is the first element on a row it can't have a \ before it
			{
				if (content[i - 1] == '\\') // if a quote doesn't have a '\' before it, it shoudn't be written
				{
					std::cout << content[i];
				}
			}
		}
		else if (content[i] == '\\') {
			if (i + 1 != len)
			{
				if (content[i + 1] != '"') // if a '\' has a quote after it, it shouldn't be written 
				{
					std::cout << content[i];
				}
			}
			else {
				std::cout << content[i];
			}
		}
		else {
			std::cout << content[i];
		}
	}
}

bool Cell::checkIfDouble(const char* newCon)
{
	size_t len = strlen(newCon);
	short pointsNum = 0;
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(newCon[i]))
		{
			if (newCon[i] == '.')
			{
				pointsNum++;
			}
			else {
				return false;
			}
		}

		if (pointsNum > 1)
		{
			return false;
		}
	}
	return true;
}

bool Cell::checkIfInt(const char* newCon)
{
	size_t len = strlen(newCon);
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(newCon[i]))
		{
			if (newCon[i] == '-' && i == 0)
				continue;
			return false;
		}
	}
	return true;
}

bool Cell::isFormula() const
{
	return formula;
}

void Cell::checkQuotes()
{
	size_t len = strlen(content);
	for (int i = 0; i < len; i++)
	{
		if (content[i] == '"')
		{
			if (i != 0)  // if a quote is the first element on a row it can't have a \ before it
			{
				if (content[i - 1] != '\\') // if a quote doesn't have a '\' before it, it shoudn't be written
				{
					physicalLength--;
				}
			}
			else {
				physicalLength--;
			}
		}
		else if (content[i] == '\\') {
			if (i + 1 != len)
			{
				if (content[i + 1] == '"') // if a '\' has a quote after it, it shouldn't be written 
				{
					physicalLength = physicalLength - 1;
					i++;
				}
			}
		}
	}
}