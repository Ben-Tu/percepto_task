



#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <bitset>
#include <iomanip>

class tools{
public:


	int convert_hex_string_to_int(std::string const& hex_string);

	std::string converter(std::string const& hex_string);

	std::string convert_hex_to_bin(std::string const& hex_string);

	std::string convert_bin_to_hex(std::string const& hex_string);

	std::string binary_flip_by_significant_bit(std::string const& bin_string);
	char binary_flip_handle(const char& bit);


	std::string create_result_msg(std::string const& input_string,std::string const& converter_string);

	bool is_hex_notation(std::string const& hex_string);

	bool is_4byte_number(std::string const& hex_string);

	bool run_validation_functions(std::string const& hex_string);

	virtual ~tools();

};



