



#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>

class tools{
public:


	int convert_hex_string_to_int(std::string const& s);

	std::string converter(std::string const& hex_string);

	std::string convert_hex_to_bin(std::string const& hex_string);

	std::string binary_flip(std::string const& bin_string);

	bool is_hex_notation(std::string const& s);

	bool is_four_byte_number(std::string const& s);

	bool run_all_validation_functions(std::string const& s);

	virtual ~tools();

};



