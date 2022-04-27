
#include "tools.h"

#define SETSIZE 4

int tools::convert_hex_string_to_int(std::string const& hex_string){

	const char* c = hex_string.c_str();
	return (int)strtol(c, NULL, 0);

}

std::string tools::create_result_msg(std::string const& input_string,std::string const& converter_string){
	std::string res;
	res = input_string +"_"+ converter_string;
	return res;

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
	            return "";
	        }
	    }

	 return bin;
}
std::string tools::convert_bin_to_hex(std::string const& bin_string){
	std::string bin("00001110101111011000000101111000");
    int result =0 ;

    for(size_t count = 0; count < bin_string.length() ; ++count)
    {
        result *=2;
        result += bin_string[count]=='1'? 1 :0;
    }

    std::stringstream ss;
    ss << "0x" << std::hex << std::setw(8) << std::setfill('0')  << result;

    std::string hexVal(ss.str());
    return hexVal;
//    std::string hexVal(ss.str());
//    std::cout << hexVal << std::endl;

}

char tools::binary_flip_handle(const char& bit){
	if (bit == '0')
		return '1';
	return '0';
}

std::string tools::binary_flip_by_significant_bit(std::string const& bin_string){

	int i;
	std::string res_bin_flip_str = "";

	bool is_most_significant_bit;

	if (bin_string[0] == '1'){
		is_most_significant_bit = true;
	}else{ // bin_string[0] == 0
		is_most_significant_bit = false;
	}

	for(i = 0; i != bin_string.size(); ++i){
		char c = bin_string[i];

		if (is_most_significant_bit){
			if (i % 2 == 0){
				res_bin_flip_str += binary_flip_handle(c);

			}else{
				res_bin_flip_str += c;
			}

		}else{
			if (i % 2 == 0){
				res_bin_flip_str += c;
			}else{
				res_bin_flip_str += binary_flip_handle(c);
			}
		}
	}

	return res_bin_flip_str;

}


bool tools::is_hex_notation(std::string const& hex_string)
{
  if( hex_string.compare(0, 2, "0x") == 0
      && hex_string.size() > 2
	  && hex_string.size() == 10
      && hex_string.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos){
	  return 1;
  }
  std::cout << "Error input: The hex number invalid!" << std::endl;
  return 0;
}

bool tools::is_4byte_number(std::string const& hex_string){
	int number = convert_hex_string_to_int(hex_string);
	if (sizeof(number) == 4)
		return 1;
	std::cout << "Error input: The hex number are not 4-Byte type!" << std::endl;
	return 0;
}

bool tools::run_validation_functions(std::string const& hex_string){
	if (is_hex_notation(hex_string) && is_4byte_number(hex_string))
		return 1;
	return 0;
}

tools::~tools() {}
