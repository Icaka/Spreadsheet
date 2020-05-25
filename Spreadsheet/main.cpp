#include <iostream>
#include "Spreadsheet.h"
using namespace std;

const int MAXN = 256;
int main() //  github repository: https://github.com/Icaka/Spreadsheet
{
	//float ron = (float)1 / (float)2;
	//cout << "ron : " << ron << endl;
	Spreadsheet table;
	bool openFile = false;
	char* fileName = new char[MAXN];
	char* command = new char[MAXN];
	int i, t; // for command "edit"
	char* newContent = new char[MAXN]; // for command "edit"

	while (true)
	{
		cout << "Input command: ";
		cin >> command;

		if (!strcmp(command, "open"))
		{
			if (openFile)
			{
				cout << "close previous file" << endl;
			}
			else {
				cin >> fileName;
				openFile = true;

				table.openFile(fileName);
				cout << "rows: " << table.getRows() << endl;
				cout << "cols: " << table.getColumns() << endl;
				//table.testPrint();
			}
		}

		if (!strcmp(command, "close"))
		{
			if (openFile)
			{
				cout << "closed " << fileName << endl;
				fileName = new char[MAXN];
				openFile = false;
			}
			else {
				cout << "There is no file opened" << endl;
			}
		}

		if (!strcmp(command, "save"))
		{
			if (openFile)
			{
				table.save(fileName);
				cout << "saved " << fileName << endl;
			}
			else {
				cout << "There is no file opened" << endl;
			}
		}

		if (!strcmp(command, "saveas"))
		{
			cin >> command;
			if (openFile)
			{
				table.save(command);
			}
			else {
				cout << "There is no file opened" << endl;
			}
		}

		if (!strcmp(command, "print"))
		{
			if (openFile)
			{
				table.testPrint();
			}
			else {
				cout << "There is no file opened" << endl;
			}
		}

		if (!strcmp(command, "edit"))
		{
			if (openFile)
			{
				cin >> i;
				cin >> t;
				cin >> newContent;
				table.editCell(i, t, newContent);
			}
			else {
				cout << "There is no file opened" << endl;
			}
		}

		if (!strcmp(command, "help"))
		{
			cout << "The following commands are supported : " << endl
				<< "open <file>	        opens <file> " << endl
				<< "close			closes currently opened file" << endl
				<< "save			saves the currently open file" << endl
				<< "saveas <file>		saves the currently open file in <file>" << endl
				<< "help			prints this information" << endl
				<< "exit			exists the program" << endl;
		}

		if (!strcmp(command, "exit"))
		{
			cout << "bye" << endl << endl;;
			break;
		}
	}

	delete[] fileName;
	delete[] command;
	delete[] newContent;
	/*
	Spreadsheet t("test.txt");
	cout << "ro;ws: " << t.getRows() << endl;
	cout << "cols: " << t.getColumns() << endl;
	t.testPrint();
	//t.testing();
	*/
	return 0;
}