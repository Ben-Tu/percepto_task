


#include "converter.h"

std::string converter::hex_converter(std::string const& hex_string){

	tools *t; // pointer to class tools,for handle functions
	std::string res_hex_string;
	if(t->run_validation_functions(hex_string)){ //check if the input is valid.

		std::string bin_str;
		bin_str = t->convert_hex_to_bin(hex_string); // convert hex(str) to binary string
		bin_str = t->binary_flip_by_significant_bit(bin_str);// flip bits.
		res_hex_string = t->convert_bin_to_hex(bin_str); // convert bin(str) to hex(str)
	}
	return res_hex_string;

}

converter::~converter() {delete[] t;}
