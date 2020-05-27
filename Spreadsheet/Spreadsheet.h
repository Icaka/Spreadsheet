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

	float getSumOfFormulaMember(const char*);
public:
	Spreadsheet();
	Spreadsheet(const char*);
	~Spreadsheet();
	int getNumberOfRows(std::ifstream&) const;
	int getNumberOfColumns(std::ifstream&) const;
	void setRows(const int);
	int getRows() const;
	int getColumns() const;
	void openFile(const char*);
	//void save();
	void save(const char*);
	void testing();
	void testPrint();
	void prettyPrint();

	bool getSumOfFormula(const char*, double&);
	void editCell(const int, const int, const char*);
};