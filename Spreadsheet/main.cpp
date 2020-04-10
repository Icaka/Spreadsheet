#include <iostream>
#include "Spreadsheet.h"
using namespace std;

int main()
{
	Spreadsheet t("test.txt");
	cout << "rows: " << t.getRows() << endl;

	return 0;
}