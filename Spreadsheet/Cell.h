#pragma once
#include <fstream>
class Cell
{
private:
	char* content;
	int intContent;
	double doubleContent;
	bool empty;
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
	int getLength() const;
	void writeToFile(std::ofstream&);

	bool isEmpty();
	void print() const;
};