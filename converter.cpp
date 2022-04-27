


#include "converter.h"

std::string converter::hex_converter(std::string const& hex_string){
	tools *t;
	std::cout << "run_all_validation_functions"<<t->run_all_validation_functions(hex_string) << std::endl;
	if(t->run_all_validation_functions(hex_string)){

		std::string bin_str;
		bin_str = t->convert_hex_to_bin(hex_string);

		bin_str = t->binary_flip(bin_str);
		std::cout << "flip bin  "<< bin_str << std::endl;
//		std::cout << bin_str << std::endl;
	}
	std::cout << hex_string << std::endl;
	return "s";

}

converter::~converter() {delete[] t;}
