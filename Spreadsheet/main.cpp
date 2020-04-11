#include <iostream>
#include "Spreadsheet.h"
using namespace std;

int main()
{
	Spreadsheet t("test.txt");
	cout << "rows: " << t.getRows() << endl;
	cout << "cols: " << t.getColumns() << endl;
	t.testPrint();
	return 0;
}