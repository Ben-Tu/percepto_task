


#include "converter.h"

std::string converter::hex_converter(std::string const& hex_string){
	tools *t;
//	std::cout << "run_all_validation_functions"<<t->run_validation_functions(hex_string) << std::endl;
	std::string res_msg = "";
	if(t->run_validation_functions(hex_string)){

		std::string bin_str;

		bin_str = t->convert_hex_to_bin(hex_string);
		bin_str = t->binary_flip_by_significant_bit(bin_str);
//		std::cout << "flip bin  "<< bin_str << std::endl;
		std::string res_hex_string = t->convert_bin_to_hex(bin_str);
		res_msg = t->create_result_msg(hex_string,res_hex_string);
//		std::cout << res_msg << std::endl;
	}
//	std::cout << hex_string << std::endl;
	return res_msg;

}

converter::~converter() {delete[] t;}
