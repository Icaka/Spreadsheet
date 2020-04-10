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

		row = 0;
		char c;
		ifs.get(c);
		while (ifs)
		{
			while (ifs && c != '\n')
			{
				ifs.get(c);
			}
			row++;
			ifs.get(c);
		}


	}
}
/*
int Spreadsheet::getNumberOfRows(std::ifstream& inf) const
{
	int r = 0;
	char c;
	while (!inf.eof())
	{
		inf.get(c);
		if (c == '/n')
			r++;
	}

}
*/
void Spreadsheet::setRows(const int rows)
{
	row = rows;
}

int Spreadsheet::getRows() const
{
	return row;
}
