#pragma once
#include <fstream>
class Cell
{
private:
	char* content;
	int intContent;
	double doubleContent;
	bool empty;
	bool formula;
	size_t physicalLength; // used mainly when printing the table
protected:
	void clear();
	void copy(const Cell&);

	bool checkIfDouble(const char*);
	bool checkIfInt(const char*);
public:
	Cell();
	~Cell();
	Cell& operator=(const Cell&);

	char* getContent() const;
	int getIntContent() const;
	double getDoubleContent() const;
	void setContent(const char*);
	void setIntContent(const int);
	void setDoubleContent(const double);
	int getPhysicalLength() const;
	void writeToFile(std::ofstream&);
	float getSumOfCell() const;

	void edit(const char*);
	bool isEmpty();
	void print() const;
	void printCharContent() const;

	bool isFormula() const;
	void checkQuotes(); // will remove physical length for every quote and dash that wouldn't be printed
};