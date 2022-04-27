


#include "converter.h"

std::string converter::hex_converter(std::string const& hex_string){

	std::string res_hex_string;
	if(run_validation_functions(hex_string)){ //check if the input is valid.

		std::string bin_str;
		bin_str = t.convert_hex_to_bin(hex_string); // convert hex(str) to binary string
		bin_str = t.binary_flip_by_significant_bit(bin_str);// flip bits.
		res_hex_string = t.convert_bin_to_hex(bin_str); // convert bin(str) to hex(str)
	}
	return res_hex_string;

}

bool converter::run_validation_functions(std::string const& hex_string){
	if (t.is_hex_notation(hex_string) && t.is_4byte_number(hex_string))
		return 1;
	return 0;
}

converter::~converter() {}
