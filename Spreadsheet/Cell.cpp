#include "Cell.h"
#include "iostream"

Cell::Cell()
{
	content = nullptr;
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
}

char* Cell::getContent() const
{
	return content;
}

void Cell::setContent(const char* newContent)
{
	content = new char[strlen(newContent) + 1];
	strcpy_s(content, strlen(newContent) + 1, newContent);
}

int Cell::getLength() const
{
	return strlen(content);
}