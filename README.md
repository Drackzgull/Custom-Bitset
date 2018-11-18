# Custom-Bitset
Custom bitset class implementation with template metaprogramming size-memory-alignment optimizations

This is a bitset class implementation meant to act as a set of multiple
binary flags in single variable, accessing and matipulating each of the
variable's bits independently so that each of them is one of the flags.

 The implentation is optimized for sizes known in compile time (i.e. the size
 of any Bitset you will use is hard-set in your code, or at least determined
 during compilation, rather than depending on the value of a runtime
 variable), and it's guaranteed to produce fixed static sized data. If you
 need runtime dependent sizes, your code won't compile when using this class,
 and you will need an alternative implementation.

The Bitset_t class definitions aren't meant to be used directly (you can use
them, but template paramater values aren't  properly validated this way, it
won't cause crashes or exceptions, but may result in erroneus behavior),
instead the Bitset class is an interface class meant for the code this file
is included from and only needs the size template parameter, then selects the
optimal Bitset_t definition for that size to use internally (this is all done
in compile time).
