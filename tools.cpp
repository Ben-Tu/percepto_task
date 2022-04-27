
#include "tools.h"


int tools::convert_hex_string_to_int(std::string const& s){

	const char* c = s.c_str();
	return (int)strtol(c, NULL, 0);

}

std::string tools::convert_hex_to_bin(std::string const& hex_string){
	int i;
	std::string hex_str = hex_string.substr (2,hex_string.size());
	std::string bin;

	    for(i = 0; hex_str[i]; ++i){
	        switch(std::toupper(hex_str[i])){
	        case '0': bin += "0000"; break;
	        case '1': bin += "0001"; break;
	        case '2': bin += "0010"; break;
	        case '3': bin += "0011"; break;
	        case '4': bin += "0100"; break;
	        case '5': bin += "0101"; break;
	        case '6': bin += "0110"; break;
	        case '7': bin += "0111"; break;
	        case '8': bin += "1000"; break;
	        case '9': bin += "1001"; break;
	        case 'A': bin += "1010"; break;
	        case 'B': bin += "1011"; break;
	        case 'C': bin += "1100"; break;
	        case 'D': bin += "1101"; break;
	        case 'E': bin += "1110"; break;
	        case 'F': bin += "1111"; break;
	        default:
	            printf("invalid character %c\n", hex_str[i]);
	            bin += "0000";
	            break;
	        }
	    }

	 return bin;
}

std::string tools::binary_flip(std::string const& bin_string){

	int max_bin_one = 0;
	int max_bin_zero = 0;
	int i, j;
	std::string odd_bits_flip = "";
	std::string even_bits_flip = "";

	std::cout << bin_string << std::endl;
	for(i = 0; i != bin_string.size(); ++i){
		char c = bin_string[i];

		if (c == '1'){
			max_bin_one += 1;
			if (i % 2 == 0){
				even_bits_flip += "0";
				odd_bits_flip += "1";
			}else{
				even_bits_flip += "1";
				odd_bits_flip += "0";
			}
		}
		if (c == '0'){
			max_bin_zero += 1;
			if (i % 2 == 0){
				even_bits_flip += "1";
				odd_bits_flip += "0";
			}else{
				even_bits_flip += "0";
				odd_bits_flip += "1";
			}
		}

	}

	if (max_bin_one > max_bin_zero)
		return odd_bits_flip;
	return even_bits_flip;

//	std::string bin_str(bin_string);
////	std::string odd_bits_flip_str = odd_bits_flip.str();
////	std::string even_bits_flip_str = even_bits_flip.str();
//
//	std::cout << "odd_bits_flip_str "<<odd_bits_flip << std::endl;
//	std::cout << "even_bits_flip_str "<<even_bits_flip << std::endl;
//
//	std::cout << "max_bin_one "<< max_bin_one << std::endl;
//	std::cout << "max_bin_zero "<< max_bin_zero << std::endl;
//
//	std::cout << bin_string << std::endl;
//	bin_string.copy(bin_str,sizeof bin_string);
//	return (bin_str );
}


bool tools::is_hex_notation(std::string const& s)
{
  return s.compare(0, 2, "0x") == 0
      && s.size() > 2
	  && s.size() == 10
      && s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
}

bool tools::is_four_byte_number(std::string const& s){
	int number = convert_hex_string_to_int(s);
	if (sizeof(number) == 4)
		return 1;
	return 0;
}

bool tools::run_all_validation_functions(std::string const& s){
	if (is_hex_notation(s) && is_four_byte_number(s))
		return 1;
}

tools::~tools() {}
