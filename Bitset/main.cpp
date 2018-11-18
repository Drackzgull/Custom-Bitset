/*
 * File:   main.cpp
 * Author: Drackzgull
 *
 * Created on 4 de octubre de 2017, 11:18 PM
 */

#include "pch.h"
#include <cstdlib>
#include <iostream>
#include "Bitset.h"
#include <string>

using namespace std;

/*
 * Bitset class template metaprogramming optimization tests successful
 */
int main(int argc, char** argv)
{
	Dkz::Bitset<8> setOf8;
	Dkz::Bitset<16> setOf16;
	Dkz::Bitset<32> setOf32;
	Dkz::Bitset<64> setOf64;
	Dkz::Bitset<72> arrayOf8;
	Dkz::Bitset<80> arrayOf16;
	Dkz::Bitset<96> arrayOf32;
	Dkz::Bitset<128> arrayOf64;

	unsigned a = unsigned(setOf8.getDataSize());
	unsigned b = unsigned(setOf16.getDataSize());
	unsigned c = unsigned(setOf32.getDataSize());
	unsigned d = unsigned(setOf64.getDataSize());
	unsigned e = unsigned(arrayOf8.getDataSize());
	unsigned f = unsigned(arrayOf16.getDataSize());
	unsigned g = unsigned(arrayOf32.getDataSize());
	unsigned h = unsigned(arrayOf64.getDataSize());

	cout << "Set of 8: " << a << endl;
	cout << "Set of 16: " << b << endl;
	cout << "Set of 32: " << c << endl;
	cout << "Set of 64: " << d << endl;
	cout << "Array of 8: " << e << endl;
	cout << "Array of 16: " << f << endl;
	cout << "Array of 32: " << g << endl;
	cout << "Array of 64: " << h << endl;

	system("pause");
	return 0;
}

