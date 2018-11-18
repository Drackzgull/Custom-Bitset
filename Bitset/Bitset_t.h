/*
 * File:   Bitset_t.hpp
 * Author: Drackzgull
 *
 * Created on 9 de octubre de 2017, 06:43 PM
 */

#ifndef BITSET_T_HPP
#define BITSET_T_HPP

#include <cstdint>
#include <cstring>

namespace Dkz
{

 /* Return values of the getMemSize functions, for debug purposes.
  * The array size enum values are the minimum memory a bitset using that
  * type would use, but not necesarily (nor usually) the actual memory that Bitset
  * uses, which would be an integer multiplier of 64 + the basic size of a single
  * element in the array.
  */
enum class BitsetMemorySize : uint8_t
{
	size_8 = 8,
	size_16 = 16,
	size_32 = 32,
	size_64 = 64,
	size_8Array = 72,
	size_16Array = 80,
	size_32Array = 96,
	size_64Array = 128
};

/* Template definition and specializations of the class Bitset_t. Not to be used
 * directly, this file is included from Bitset.hpp and the class Bitset defined
 * there implements one of the following definitions depending on the size of
 * it's template paramenter N.
 * The class Bitset should always be used instead, using wrong combinations of
 * template parameter values with the Bitset_t class may cause erroneus behavior
 * or non-optimal data sizes for the amount of bits to be used.
 */

 /* Base template definition. */
template<size_t N, bool smallSize, uint8_t dataSize>
class Bitset_t
{
private:
	uint32_t data[(N + 31) / 32];

public:
	Bitset_t()
	{
		reset();
	}

	void reset()
	{
		memset(data, 0, sizeof(data));
	}

	void set(const size_t & pos, const bool & value = true)
	{
		if (pos >= N)
			return;

		auto & element = data[pos / 32];
		uint8_t bit = pos % 32;
		if (value)
			element |= (uint32_t(1) << bit);
		else
			element &= ~(uint32_t(1) << bit);
	}

	void flip(const size_t & pos)
	{
		if (pos >= N)
			return;

		auto & element = data[pos / 32];
		uint8_t bit = pos % 32;
		element ^= (uint32_t(1) << bit);
	}

	bool get(const size_t & pos) const
	{
		if (pos >= N)
			return false;

		auto & element = data[pos / 32];
		uint8_t bit = pos % 32;
		return (element & (uint32_t(1) << bit)) != 0;
	}

	BitsetMemorySize getDataSize() { return BitsetMemorySize::size_32Array; }
};

/* Definition for sets of 8 or less bits. */
template<size_t N>
class Bitset_t<N, true, 8>
{
private:
	uint8_t data;

public:
	Bitset_t() :
		data(0)
	{}

	void reset()
	{
		data = 0;
	}

	void set(const size_t & pos, const bool & value = true)
	{
		if (pos >= N)
			return;

		if (value)
			data |= (uint8_t(1) << pos);
		else
			data &= ~(uint8_t(1) << pos);
	}

	void flip(const size_t & pos)
	{
		if (pos >= N)
			return;

		data ^= (uint8_t(1) << pos);
	}

	bool get(const size_t & pos) const
	{
		if (pos >= N)
			return false;

		return (data & (uint8_t(1) << pos)) != 0;
	}

	BitsetMemorySize getDataSize() { return BitsetMemorySize::size_8; }
};

/* Definition for sets of 9 to 16 bits */
template<size_t N>
class Bitset_t<N, true, 16>
{
private:
	uint16_t data;

public:
	Bitset_t() :
		data(0)
	{}

	void reset()
	{
		data = 0;
	}

	void set(const size_t & pos, const bool & value = true)
	{
		if (pos >= N)
			return;

		if (value)
			data |= (uint16_t(1) << pos);
		else
			data &= ~(uint16_t(1) << pos);
	}

	void flip(const size_t & pos)
	{
		if (pos >= N)
			return;

		data ^= (uint16_t(1) << pos);
	}

	bool get(const size_t & pos) const
	{
		if (pos >= N)
			return false;

		return (data & (uint16_t(1) << pos)) != 0;
	}

	BitsetMemorySize getDataSize() { return BitsetMemorySize::size_16; }
};

/* Definition for sets of 17 to 32 bits */
template<size_t N>
class Bitset_t<N, true, 32>
{
private:
	uint32_t data;

public:
	Bitset_t() :
		data(0)
	{}

	void reset()
	{
		data = 0;
	}

	void set(const size_t & pos, const bool & value = true)
	{
		if (pos >= N)
			return;

		if (value)
			data |= (uint32_t(1) << pos);
		else
			data &= ~(uint32_t(1) << pos);
	}

	void flip(const size_t & pos)
	{
		if (pos >= N)
			return;

		data ^= (uint32_t(1) << pos);
	}

	bool get(const size_t & pos) const
	{
		if (pos >= N)
			return false;

		return (data & (uint32_t(1) << pos)) != 0;
	}

	BitsetMemorySize getDataSize() { return BitsetMemorySize::size_32; }
};


/* Definition for sets of 33 to 64 bits */
template<size_t N>
class Bitset_t<N, true, 64>
{
private:
	uint64_t data;

public:
	Bitset_t() :
		data(0)
	{}

	void reset()
	{
		data = 0;
	}

	void set(const size_t & pos, const bool & value = true)
	{
		if (pos >= N)
			return;

		if (value)
			data |= (uint64_t(1) << pos);
		else
			data &= ~(uint64_t(1) << pos);
	}

	void flip(const size_t & pos)
	{
		if (pos >= N)
			return;

		data ^= (uint64_t(1) << pos);
	}

	bool get(const size_t & pos) const
	{
		if (pos >= N)
			return false;

		return (data & (uint64_t(1) << pos)) != 0;
	}

	BitsetMemorySize getDataSize() { return BitsetMemorySize::size_64; }
};

/* Definition for sets of more than 64 bits, were no more than 8 bits are
 * needed after last full set of 64
 **/
template<size_t N>
class Bitset_t<N, false, 8>
{
private:
	uint8_t data[(N + 7) / 8];

public:
	Bitset_t()
	{
		reset();
	}

	void reset()
	{
		memset(data, 0, sizeof(data));
	}

	void set(const size_t & pos, const bool & value = true)
	{
		if (pos >= N)
			return;

		auto & element = data[pos / 8];
		uint8_t bit = pos % 8;
		if (value)
			element |= (uint8_t(1) << bit);
		else
			element &= ~(uint8_t(1) << bit);
	}

	void flip(const size_t & pos)
	{
		if (pos >= N)
			return;

		auto & element = data[pos / 8];
		uint8_t bit = pos % 8;
		element ^= (uint8_t(1) << bit);
	}

	bool get(const size_t & pos) const
	{
		if (pos >= N)
			return false;

		auto & element = data[pos / 8];
		uint8_t bit = pos % 8;
		return (element & (uint8_t(1) << bit)) != 0;
	}

	BitsetMemorySize getDataSize() { return BitsetMemorySize::size_8Array; }
};

/* Definition for sets of more than 64 bits, were no more than 16 bits are
 * needed after last full set of 64
 **/
template<size_t N>
class Bitset_t<N, false, 16>
{
private:
	uint16_t data[(N + 15) / 16];

public:
	Bitset_t()
	{
		reset();
	}

	void reset()
	{
		memset(data, 0, sizeof(data));
	}

	void set(const size_t & pos, const bool & value = true)
	{
		if (pos >= N)
			return;

		auto & element = data[pos / 16];
		uint8_t bit = pos % 16;
		if (value)
			element |= (uint16_t(1) << bit);
		else
			element &= ~(uint16_t(1) << bit);
	}

	void flip(const size_t & pos)
	{
		if (pos >= N)
			return;

		auto & element = data[pos / 16];
		uint8_t bit = pos % 16;
		element ^= (uint16_t(1) << bit);
	}

	bool get(const size_t & pos) const
	{
		if (pos >= N)
			return false;

		auto & element = data[pos / 16];
		uint8_t bit = pos % 16;
		return (element & (uint16_t(1) << bit)) != 0;
	}

	BitsetMemorySize getDataSize() { return BitsetMemorySize::size_16Array; }
};

/* Definition for sets of more than 64 bits, were no more than 32 bits are
 * needed after last full set of 64
 **/
template<size_t N>
class Bitset_t<N, false, 32>
{
private:
	uint32_t data[(N + 31) / 32];

public:
	Bitset_t()
	{
		reset();
	}

	void reset()
	{
		memset(data, 0, sizeof(data));
	}

	void set(const size_t & pos, const bool & value = true)
	{
		if (pos >= N)
			return;

		auto & element = data[pos / 32];
		uint8_t bit = pos % 32;
		if (value)
			element |= (uint32_t(1) << bit);
		else
			element &= ~(uint32_t(1) << bit);
	}

	void flip(const size_t & pos)
	{
		if (pos >= N)
			return;

		auto & element = data[pos / 32];
		uint8_t bit = pos % 32;
		element ^= (uint32_t(1) << bit);
	}

	bool get(const size_t & pos) const
	{
		if (pos >= N)
			return false;

		auto & element = data[pos / 32];
		uint8_t bit = pos % 32;
		return (element & (uint32_t(1) << bit)) != 0;
	}

	BitsetMemorySize getDataSize() { return BitsetMemorySize::size_32Array; }
};

/* Definition for sets of more than 64 bits, were at least 33 bits are needed
 * after last full set of 64
 **/
template<size_t N>
class Bitset_t<N, false, 64>
{
private:
	uint64_t data[(N + 63) / 64];

public:
	Bitset_t()
	{
		reset();
	}

	void reset()
	{
		memset(data, 0, sizeof(data));
	}

	void set(const size_t & pos, const bool & value = true)
	{
		if (pos >= N)
			return;

		auto & element = data[pos / 64];
		uint8_t bit = pos % 64;
		if (value)
			element |= (uint64_t(1) << bit);
		else
			element &= ~(uint64_t(1) << bit);
	}

	void flip(const size_t & pos)
	{
		if (pos >= N)
			return;

		auto & element = data[pos / 64];
		uint8_t bit = pos % 64;
		element ^= (uint64_t(1) << bit);
	}

	bool get(const size_t & pos) const
	{
		if (pos >= N)
			return false;

		auto & element = data[pos / 64];
		uint8_t bit = pos % 64;
		return (element & (uint64_t(1) << bit)) != 0;
	}

	BitsetMemorySize getDataSize() { return BitsetMemorySize::size_64Array; }
};

} //End of namespace Dkz

#endif  /* BITSET_T_HPP */