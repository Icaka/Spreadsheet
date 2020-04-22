#include "Spreadsheet.h"
#include <iostream>

const int MAXN = 1024;

Spreadsheet::Spreadsheet()
{
	row = 0;
	col = 0;

	table = new Cell * [row];
	for (int i = 0; i < row; ++i)
		table[i] = new Cell[col];
}

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

		table = new Cell * [row];
		for (int i = 0; i < row; ++i)
			table[i] = new Cell[col];

		fillTable(ifs);
	}

	ifs.close();
}

Spreadsheet::~Spreadsheet()
{
	for (int i = 0; i < row; ++i)
		delete[] table[i];
	delete[] table;
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

void Spreadsheet::openFile(const char* fName)
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

		table = new Cell * [row];
		for (int i = 0; i < row; ++i)
			table[i] = new Cell[col];

		fillTable(ifs);
	}

	ifs.close();
}

void Spreadsheet::fillTable(std::ifstream& ifs)
{
	int rCounter = 0;
	char* buffer = new char[MAXN];
	while (ifs)
	{
		ifs.getline(buffer, MAXN);
		manageLine(rCounter, buffer);
		buffer = new char[MAXN];
		rCounter++;
	}
	delete[] buffer;
}

void Spreadsheet::manageLine(const int curRow, const char* buff)
{
	/*
	std::cout << buff << std::endl;
	int i = 0;
	while (buff[i] != '\0')
	{
		std::cout << buff[i];
		i++;
	}
	std::cout << std::endl;
	*/
	
	char* smallBuff = new char[256];
	int i = 0;
	int n = 0;
	int column = 0;
	int quotesCounter = 0;
	while (buff[n] != '\0')
	{
		if (buff[n] == '"')
		{
			if (n != 0) // if a quote is the first element on a row it can't have a \ before it
			{
				if (buff[n - 1] != '\\') 
					quotesCounter++;
			}
			else {
				quotesCounter++;
			}
		}

		if (buff[n] == ',')
		{
			if (quotesCounter % 2 == 0) // only when we know that a quote has been closed by another can we store content in a cell
			{
				smallBuff[i] = '\0';
				if(i != 0)
					table[curRow][column].setContent(smallBuff);
				//table[curRow][column].print();
				//std::cout << std::endl;
				smallBuff = new char[256];
				column++;
				i = 0;
			}
			else {
				smallBuff[i] = buff[n]; // if there is a comma between quotes it should still go in the cell
				i++;
			}
		}
		else {
			if (buff[n] == ' ') // if a whitespace is outside of quotes it should't be taken into account
			{
				if (quotesCounter % 2 == 1)
				{
					smallBuff[i] = buff[n];
					i++;
				}
			}
			else {
				smallBuff[i] = buff[n];
				i++;
			}
		}
		if (buff[n + 1] == '\0')
		{

			smallBuff[i] = '\0';
			if(i != 0)
				table[curRow][column].setContent(smallBuff);
			//table[curRow][column].print();
			//std::cout << std::endl;
		}

		n++;
	}

	delete[] smallBuff;
	
}
/*
void Spreadsheet::removeWhitespaces()
{
	for (int i = 0; i < row; i++)
	{
		for (int t = 0; t < col; t++)
		{

		}
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

int Spreadsheet::getColumns() const
{
	return col;
}

void Spreadsheet::save(const char* fName)
{
	if (!strcmp(fName, fileName))
	{
		remove(fileName);
	}

	std::ofstream ofs;
	ofs.open(fName);
	if (ofs.is_open())
	{
		for (int i = 0; i < row; i++)
		{
			for (int t = 0; t < col; t++)
			{
				if (table[i][t].isEmpty())
				{
					ofs << " ";
				}
				else {
					ofs << table[i][t].getContent();
				}
				if (t != col - 1)
					ofs << ",";
			}
			ofs << "\n";
		}

		ofs.close();
	}
	else {
		std::cout << "failed saving" << std::endl;
	}
}

void Spreadsheet::testing()
{
	for (int i = 0; i < row; i++)
	{
		for (int t = 0; t < col; t++)
		{
			table[i][t].setContent("test");
		}
	}
	testPrint();
}

void Spreadsheet::testPrint()
{
	for (int i = 0; i < row; i++)
	{
		for (int t = 0; t < col; t++)
		{
			std::cout << "table[" << i << "][" << t << "]: ";
			table[i][t].print();
			std::cout << "|" << std::endl;
		}
		//std::cout << std::endl;
	}

	for (int i = 0; i < row; i++)
	{
		for (int t = 0; t < col; t++)
		{
			std::cout << " ";
			table[i][t].print();
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	//table[row - 1][col - 1].print();
}
