#include <iostream>
#include "TList.h"

using namespace std;

int main()
{
	// data
	TList<string, int> cars_weight_1;

	string car_1 = "gazel";
	int car_1_weight = 2100;
	string car_2 = "zaporozhets";
	int car_2_weight = 840;
	string car_3 = "kamaz";
	int car_3_weight = 10000;
	string car_4 = "m1 abrams";
	int car_4_weight = 54000;
	string car_5 = "uaz";
	int car_5_weight = 1650;
	string car_6 = "velosiped";
	int car_6_weight = 12;
	string car_7 = "tu-104";
	int car_7_weight = 42000;
	string car_8 = "oslik";
	int car_8_weight = 150;

	// INSERT TO START, INSERT TO END
	cout << "-----------------------------------------------------------" << endl;
	cout << "Insert to start, insert to end test:" << endl;
	cout << "Starting from list:" << endl;
	cout << cars_weight_1 << endl;
	cars_weight_1.insert_to_end(car_1, &car_1_weight);
	cars_weight_1.insert_to_start(car_2, &car_2_weight);
	cars_weight_1.insert_to_end(car_3, &car_3_weight);
	cout << "Result" << endl << cars_weight_1 << endl;
	cout << "Right order of names is: " << car_2 << ' ' << car_1 << ' ' << car_3 << endl;
	cout << "Right order of weights is: " << car_2_weight << ' ' << car_1_weight << ' ' << car_3_weight << endl;
	cout << "Finished" << endl << endl;

	// COPY
	cout << "-----------------------------------------------------------" << endl;
	TList<string, int> cars_weight_2(cars_weight_1);
	cout << "Copying constructor test:" << endl;
	cout << cars_weight_2 << endl;
	cout << "Finished" << endl << endl;

	// INSERT BEFORE, INSERT AFTER
	cout << "-----------------------------------------------------------" << endl;
	cout << "Inserting keys inside test:" << endl;
	cout << "Starting from list:" << endl;
	cout << cars_weight_2 << endl;
	try
	{
		cout << endl << "Inserting " << car_4 << " with weight " << car_4_weight << " after " << car_3 << endl;
		cars_weight_2.insert_after(car_3, car_4, &car_4_weight);
		cout << cars_weight_2 << endl;
	}
	catch (const char* err_code)
	{
		cout << err_code << endl;
	}
	cout << endl << "Inserting " << car_5 << " with weight " << car_5_weight << " before " << car_4 << endl;
	try
	{
		cars_weight_2.insert_before(car_4, car_5, &car_5_weight);
		cout << cars_weight_2 << endl;
	}
	catch (const char* err_code)
	{
		cout << err_code << endl << endl;
	}
	cout << endl << "Inserting " << car_6 << " with weight " << car_6_weight << " after " << car_6 << endl;
	try
	{
		cars_weight_2.insert_after(car_6, car_6, &car_6_weight);
		cout << cars_weight_2 << endl;
	}
	catch (const char* err_code)
	{
		cout << err_code << endl;
	}
	cout << endl << "Inserting " << car_8 << " with weight " << car_8_weight << " before " << car_5 << endl;
	try
	{
		cars_weight_2.insert_before(car_5, car_8, &car_8_weight);
		cout << cars_weight_2 << endl;
	}
	catch (const char* err_code)
	{
		cout << err_code << endl << endl;
	}
	cout << "Finished" << endl << endl;

	// SEARCHING
	cout << "-----------------------------------------------------------" << endl;
	TNode<string, int>* found;
	cout << "Searching tests:" << endl;
	cout << "Starting from list:" << endl;
	cout << cars_weight_2 << endl;

	cout << "Looking for the " << car_8 << endl;
	try
	{
		found = cars_weight_2.find_key(car_8);
		if (found)
			cout << *(found) << " at adress " << found << endl;
		else
			cout << "element not found" << endl;
	}
	catch (const char* err_code)
	{
		cout << err_code << endl << endl;
	}

	cout << "Looking for the " << car_6 << endl;
	try
	{
		found = cars_weight_2.find_key(car_6);
		if (found)
			cout << *(found) << " at adress " << found << endl;
		else
			cout << "element not found" << endl;
	}
	catch (const char* err_code)
	{
		cout << err_code << endl << endl;
	}
	
	cout << "Finished" << endl << endl;

	// DELETING
	cout << "-----------------------------------------------------------" << endl;
	cout << "Deleting test:" << endl;
	cout << "Starting from list:" << endl;
	cout << cars_weight_2 << endl;
	cout << "Delete the element with key: " << car_8 << endl;
	try
	{
		cars_weight_2.remove_key(car_8);
		cout << cars_weight_2 << endl << endl;
	}
	catch (const char* err_code)
	{
		cout << err_code << endl << endl;
	}

	cout << "Deleting head test:" << endl;
	cout << "Starting from list:" << endl;
	cout << cars_weight_2 << endl;
	try
	{
		cars_weight_2.remove_head();
		cout << cars_weight_2 << endl << endl;
	}
	catch (const char* err_code)
	{
		cout << err_code << endl << endl;
	}

	cout << endl << "Access, moving & deleting current element: " << endl;
	try
	{
		cout << "Current key: " << cars_weight_2.get_current_key() << endl;
		cars_weight_2.go_next();
		cout << "Moved forward. New current key: " << cars_weight_2.get_current_key() << endl;
		cars_weight_2.remove_current();
		cout << "List after deleting current key: " << endl;
		cout << cars_weight_2 << endl;

	}
	catch (const char* err_code)
	{
		cout << err_code << endl;
	}
	cout << "Finished" << endl << endl;
	system("pause");
	return 0;
}