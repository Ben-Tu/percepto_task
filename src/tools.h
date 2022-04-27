



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


#define SETSIZE 4
#define FOUR_BYTE_TYPE 4
class tools{
public:

	//convert_hex_string_to_int:
	//The function get a hex string and covert it to int number.
	int convert_hex_string_to_int(std::string const& hex_string);

	//convert_hex_to_bin:
	//The function convert hex string to binary string
	//e.g:  get '0xa4172bd2' return '10100100000101110010101111010010'
	std::string convert_hex_to_bin(std::string const& hex_string);

	//convert_bin_to_hex:
	//The function convert bin string to hex string
	//e.g:  get '10100100000101110010101111010010' return '0xa4172bd2'
	std::string convert_bin_to_hex(std::string const& bin_string);

	//binary_flip_by_significant_bit:
	//The function get bin string and flip binary bits by the following definitions:
	//If most significant bit of the number is '1' -> flip all odd bits on the number.
	//If most significant bit of the number is '0' -> flip all even bits on the number.
	std::string binary_flip_by_significant_bit(std::string const& bin_string);

	//binary_flip_handle:
	//The function get a char and flip
	//e.g the function get '0' and return 1, get '1' return '0'.
	char binary_flip_handle(const char& bit);

	//create_result_msg:
	//The function get two strings and generate string in the following format: {input_string}_{converter_string}
	std::string create_result_msg(std::string const& input_string,std::string const& converter_string);

	//is_hex_notation:
	//The function check if a string is hexadecimal.
	bool is_hex_notation(std::string const& hex_string);

	//is_4byte_number:
	// The function check if the hex number is 4 byte number.
	bool is_4byte_number(std::string const& hex_string);

	~tools();

};



