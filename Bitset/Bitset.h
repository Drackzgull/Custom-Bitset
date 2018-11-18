/*
 * File:   Bitset.cpp
 * Author: Drackzgull
 *
 * Created on 4 de octubre de 2017, 11:18 PM
 *
 * This is a bitset class implementation meant to act as a set of multiple
 * binary flags in single variable, accessing and matipulating each of the
 * variable's bits independently so that each of them is one of the flags.
 *
 * The implentation is optimized for sizes known in compile time (i.e. the size
 * of any Bitset you will use is hard-set in your code, or at least determined
 * during compilation, rather than depending on the value of a runtime
 * variable), and it's guaranteed to produce fixed static sized data. If you
 * need runtime dependent sizes, your code won't compile when using this class,
 * and you will need an alternative implementation.
 *
 * The Bitset_t class definitions aren't meant to be used directly (you can use
 * them, but template paramater values aren't  properly validated this way, it
 * won't cause crashes or exceptions, but may result in erroneus behavior),
 * instead the Bitset class is an interface class meant for the code this file
 * is included from and only needs the size template parameter, then selects the
 * optimal Bitset_t definition for that size to use internally (this is all done
 * in compile time).
 */

#ifndef BITSET_HPP
#define BITSET_HPP

#include <cstdint>
#include <cstring>
#include "Bitset_t.h"

namespace Dkz
{

 /* Abstract definition meant to be used directly in the code this file is
  * included from, it acts as an interface that implements the optimal Bitset_t
  * definition based on desired size. */
	template<size_t N>
class Bitset
{
	static_assert(N > 0, "Bitset size must be greater than 0");

private:
	Bitset_t<N, (N <= 64), ((N % 64) > 32) ? 64 : ((N % 64) > 16) ? 32 : ((N % 64) > 8) ? 16 : ((N % 64) > 0) ? 8 : 64> data;

public:
	Bitset() :
		data()
	{};

	void reset() { data.reset(); }
	void set(const size_t & pos, const bool & value = true) { data.set(pos, value); }
	void flip(const size_t & pos) { data.flip(pos); }
	bool get(const size_t & pos) const { return data.get(pos); }
	bool operator[](const size_t & pos) const { return data.get(pos); }
	BitsetMemorySize getDataSize() { return data.getDataSize(); }
};

} //End of namespace Dkz

#endif //BITSET_HPP
