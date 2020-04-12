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
protected:
	void fillTable(std::ifstream&);
	void manageLine(const int, const char*); // arguments are row number and the whole (not yet fragmented) row
	void removeWhitespaces();
public:
	Spreadsheet(const char*);
	~Spreadsheet();
	int getNumberOfRows(std::ifstream&) const;
	int getNumberOfColumns(std::ifstream&) const;
	void setRows(const int);
	int getRows() const;
	int getColumns() const;


	void testing();
	void testPrint();
};