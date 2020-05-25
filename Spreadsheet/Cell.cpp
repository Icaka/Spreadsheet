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
}

void Cell::setIntContent(const int iC)
{
	intContent = iC;
}

void Cell::setDoubleContent(const double dC)
{
	doubleContent = dC;
}

int Cell::getLength() const
{
	return strlen(content);
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
	setContent(newContent);
}

bool Cell::isEmpty()
{
	/*
	if (content == '\0')
	{
		return true;
	}
	return false;
	*/
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
		//std::cout << "" << content;// << " ";
	}
	else {
		if (intContent == 0)
		{
			if (doubleContent == 0.0)
			{
				std::cout << 0;
			}
			else {
				std::cout << doubleContent;
			}
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
			return false;
		}
	}
	return true;
}

bool Cell::isFormula() const
{
	return formula;
}