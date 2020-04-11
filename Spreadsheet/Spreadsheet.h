#pragma once
#include "Cell.h"
#include <fstream>

class Spreadsheet
{
private:
	Cell** table;
	int row; // rows
	int col; //columns
	char* fileName;
public:
	Spreadsheet(const char*);

	int getNumberOfRows(std::ifstream&) const;
	int getNumberOfColumns(std::ifstream&) const;
	void setRows(const int);
	int getRows() const;
	int getColumns() const;
};