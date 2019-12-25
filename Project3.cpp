// Project3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <iostream>
#include "project3.hpp"
#include "History_Transaction_definitions.hpp"
#ifndef MARMOSET_TESTING  
unsigned int Transaction::assigned_trans_id = 0;
int main() 
{
History trans_history{};
std::cout << 1;
trans_history.read_history();
std::cout << 2;
std::cout << "[Starting history]:" << std::endl;trans_history.print();
std::cout << 3;
//trans_history.sort_by_date();
std::cout << 4;
std::cout << "[Sorted          ]:" << std::endl;
std::cout << 5;
trans_history.print();
std::cout << 6;

trans_history.update_acb_cgl();
std::cout << 7;

trans_history.print();
std::cout << 8;

std::cout << "[CGL for 2018    ]: " << trans_history.compute_cgl(2018) << std::endl;
std::cout << 9;
std::cout << "[CGL for 2019    ]: " << trans_history.compute_cgl(2019) << std::endl;
std::cout << 10;
return 0;
}
#endif

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
