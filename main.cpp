#include <iostream>

#include "Translator.h"
#include "TableStorage.h"

using namespace std;

int main( int argc, char ** argv )
{
	Translator translator;
	string path;
	if ( argc == 2 )
		path = argv[1];
	else
		path = "test1.cpp";
	translator.loadProgram( path );
	translator.analyzeLexical();

	cout << "=============== id table ===============" << endl;
	theTableStorage.printIdentificatorTable();

	cout << "=============== const table ===============" << endl;
	theTableStorage.printConstTable();

	return 0;
}
