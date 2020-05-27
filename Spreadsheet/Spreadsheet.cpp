#include "Spreadsheet.h"
#include <iostream>
#include <iomanip>

const int MAXN = 1024;
const int error = 420; // will use this for error checkings

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
	openFile(fName);
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
					table[i][t].writeToFile(ofs); // ofs << table[i][t].getContent()
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
	/*
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
	*/
	for (int i = 0; i < row; i++)
	{
		for (int t = 0; t < col; t++)
		{
			std::cout << " ";
			if (table[i][t].isFormula())
			{
				double res;
				if (!getSumOfFormula(table[i][t].getContent(), res))
				{
					std::cout << "ERROR";
				}
				else {
					std::cout << res;
				}
				//std::cout << getSumOfFormula(table[i][t].getContent());
			}
			else {
				table[i][t].print();
			}
			//table[i][t].print();
			std::cout << " ";
		}
		std::cout << std::endl;
	}

	//std::cout << "Testing R2C3 + R1C1: " << getSumOfFormula("=R2C3+R1C1") << std::endl;;
	//table[row - 1][col - 1].print();
}

void Spreadsheet::prettyPrint()
{
	int p = 15;
	for (int i = 0; i < row; i++)
	{
		for (int t = 0; t < col; t++)
		{
			//std::cout << " ";
			if (table[i][t].isFormula())
			{
				double res;
				if (!getSumOfFormula(table[i][t].getContent(), res))
				{
					std::cout << "ERROR";
					if (t != (col - 1))
						std::cout  << std::setw(p - 5) << "|";
				}
				else {
					std::cout << res;
				}
			}
			else {
				table[i][t].print();
				if (t != (col - 1))
					std::cout  << std::setw(p - table[i][t].getPhysicalLength()) << "|";
			}
			//std::cout << " ";
		}
		std::cout << std::endl;
	}
}

bool Spreadsheet::getSumOfFormula(const char* form, double& sum)
{
	float result = 0;;
	char operation = 0;
	char* member1 = new char[32];
	int mem1Counter = 0;
	char* member2 = new char[32];
	int mem2Counter = 0;
	bool operationFound = false;
	int i = 1;
	do
	{
		if (form[i] == '+' || form[i] == '-' || form[i] == '*' || form[i] == '/')
		{
			operationFound = true;
			operation = form[i];
			member1[mem1Counter] = '\0'; // closing the first member
		}
		else {
			if (!operationFound)
			{
				member1[mem1Counter] = form[i];
				mem1Counter++;
			}
			else {
				member2[mem2Counter] = form[i];
				mem2Counter++;
			}
		}

		i++;
	} while (i < strlen(form));
	member2[mem2Counter] = '\0'; // closing the second member

	//std::cout  << "Member 1: " << member1 << std::endl;
	//std::cout << "Member 2: " << member2 << std::endl;
	//std::cout << "Member 1 Sum: " << getSumOfFormulaMember(member1) << std::endl;

	

	if (operation == '+')
	{
		result = getSumOfFormulaMember(member1) + getSumOfFormulaMember(member2);
	}
	else if (operation == '-') {
		result = getSumOfFormulaMember(member1) - getSumOfFormulaMember(member2);
	}
	else if (operation == '*') {
		result = getSumOfFormulaMember(member1) * getSumOfFormulaMember(member2);
	}
	else if (operation == '/') {
		if (getSumOfFormulaMember(member2) == 0)
		{
			delete[] member1;
			delete[] member2;
			return false;
		}
		else {
			result = getSumOfFormulaMember(member1) / getSumOfFormulaMember(member2);
		}
	}

	sum = result;
	delete[] member1;
	delete[] member2;
	return true;
}

float Spreadsheet::getSumOfFormulaMember(const char* member)
{
	float sum = 0;
	int c = 0;
	if (member[0] == 'R' || member[0] == 'r')
	{
		c = 1;
		char* firstNum = new char[8];
		int fNumCounter = 0;
		char* secondNum = new char[8];
		int sNumCounter = 0;
		bool foundC = false;
		do
		{
			if (member[c] == 'C' || member[c] == 'c')
			{
				foundC = true;
				firstNum[fNumCounter] = '\0';
			}
			else {
				if (!foundC)
				{
					firstNum[fNumCounter] = member[c];
					fNumCounter++;
				}
				else {
					secondNum[sNumCounter] = member[c];
					sNumCounter++;
				}
			}
			c++;
		} while (c < strlen(member));
		secondNum[sNumCounter] = '\0';

		//std::cout << "Number 1: " << firstNum << std::endl;
		//std::cout << "Number 2: " << secondNum << std::endl;


		sum = table[atoi(firstNum) - 1][atoi(secondNum) - 1].getSumOfCell();
		delete[] firstNum;
		delete[] secondNum;
		return sum;

	}
	else {
		bool foundPoint = false;
		for (int i = 0; i < strlen(member); i++)
		{
			if (member[i] == '-' && i == 0)
				continue;
			if (!isdigit(member[i]))
			{
				if (member[i] == '.')
				{
					if (!foundPoint)
					{
						foundPoint = true;
					}
					else {
						return 0;
					}
				}
				else {
					return 0;
				}
					
			}
				//return 0;
		}
		return atof(member);
	}

	return sum;
}

void Spreadsheet::editCell(const int r, const int c, const char* text)
{
	if (r <= 0 || r > row)
	{
		std::cout << "Row out of boundaries" << std::endl;
		return;
	}
	if (c <= 0 || c > col)
	{
		std::cout << "Column out of boundaries" << std::endl;
		return;
	}
	table[r - 1][c - 1].edit(text);
}
