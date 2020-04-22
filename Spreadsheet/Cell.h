#pragma once

class Cell
{
private:
	char* content;

protected:
	void clear();
	void copy(const Cell&);
	//void cleanContent(char*); // is used to clean a received word before it's written in content( remove the whitespaces or quotes)
public:
	Cell();
	~Cell();
	Cell& operator=(const Cell&);

	char* getContent() const;
	void setContent(const char*);
	int getLength() const;

	bool isEmpty();
	void print() const;
};