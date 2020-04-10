#pragma once

class Cell
{
private:
	char* content;

protected:
	void clear();
	void copy(const Cell&);
public:
	Cell();
	~Cell();
	Cell& operator=(const Cell&);

	char* getContent() const;
	int getLength() const;
};