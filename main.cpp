#include <iostream>

#include "Arguments.hpp"

int main(int argc, char** argv)
{
	dbr::util::Arguments args("Testing dbr::util::Arguments");

	args.add([](auto& v) { std::cout << "a = " << v << '\n'; return true; }, "a", "Sets a to the provided value.");
	args.add([](auto&) { std::cout << "b = true\n"; return true; }, "b", "Flags b as true if present. False by default.");
	args.add([](auto& v) { std::cout << "G = " << v << '\n'; return true; }, "G", "Flags G as true, if present. False by default.");
	args.add([](auto& v) { std::cout << "set = " << v << '\n'; return true; }, "set", "sets set to a value");

	args.run(argc, argv, std::cout);

	return 0;
}
