#include "Spreadsheet.h"
#include <iostream>

const int MAXN = 1024;

Spreadsheet::Spreadsheet(const char* fName)
{
	fileName = new char[strlen(fName) + 1];
	strcpy_s(fileName, strlen(fName) + 1, fName);

	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {

		std::cout << "failed openning!";
	}
	else {

		row = getNumberOfRows(ifs);
		col = getNumberOfColumns(ifs);


	}

	ifs.close();
}

int Spreadsheet::getNumberOfRows(std::ifstream& ifs) const
{
	int r = 0;
	char c;
	ifs.get(c);
	while (ifs)
	{
		while (ifs && c != '\n')
		{
			ifs.get(c);
		}
		r++;
		ifs.get(c);
	}
	ifs.clear();				 //
	ifs.seekg(0, std::ios::beg); // putting the stream back at the beginning
	return r;
}

int Spreadsheet::getNumberOfColumns(std::ifstream& ifs) const
{
	int maxWordsOnARow = 0;
	int currWordsOnRow = 0;
	char c;
	
	while (ifs)
	{
		ifs.get(c);
		if (c == '\n')
		{
			if (currWordsOnRow > maxWordsOnARow)
				maxWordsOnARow = currWordsOnRow;
			currWordsOnRow = 0;
		}
		if (c == ',')
		{
			if (currWordsOnRow == 0)
			{
				currWordsOnRow = 1;
			}
			currWordsOnRow++;
		}
	}
	ifs.clear();				 //
	ifs.seekg(0, std::ios::beg); // putting the stream back at the beginning
	return maxWordsOnARow;
}

void Spreadsheet::setRows(const int rows)
{
	row = rows;
}

int Spreadsheet::getRows() const
{
	return row;
}

int Spreadsheet::getColumns() const
{
	return col;
}
