
#include "tools.h"


int tools::convert_hex_string_to_int(std::string const& hex_string){

#if WITH_DEBUG_PRINT
std::cout << "DEBUG(convert_hex_string_to_int)-> Input hex string: " << hex_string <<std::endl;
#endif

	const char* c = hex_string.c_str();

#if WITH_DEBUG_PRINT
std::cout << "DEBUG(convert_hex_string_to_int)-> Input intger: " << (int)strtol(c, NULL, 0) <<std::endl;
#endif

	return (int)strtol(c, NULL, 0); // convert to integer
}

std::string tools::create_result_msg(std::string const& input_string,std::string const& converter_string){
	std::string res;
	res = input_string +"_"+ converter_string;
	return res;
}

std::string tools::convert_hex_to_bin(std::string const& hex_string){

#if WITH_DEBUG_PRINT
std::cout << "DEBUG(convert_hex_to_bin)-> Input hex string: " << hex_string <<std::endl;
#endif

	int i;
	std::string hex_str = hex_string.substr (2,hex_string.size()); //ignore the prefix '0x'
	std::string bin;

	    for(i = 0; hex_str[i]; ++i){ //for each char in the hex string convert it to binary number.
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
	        	std::cout << "invalid character " << hex_str[i] << std::endl;
	            return ""; //return empty str if the hex notation are not valid
	        }
	    }
#if WITH_DEBUG_PRINT
std::cout << "DEBUG(convert_hex_to_bin)-> Output bin string: " << bin <<std::endl;
#endif
	 return bin;
}
std::string tools::convert_bin_to_hex(std::string const& bin_string){

#if WITH_DEBUG_PRINT
std::cout << "DEBUG(convert_bin_to_hex)-> Input bin string: " << bin_string <<std::endl;
#endif

    int result =0 ;

    for(size_t count = 0; count < bin_string.length() ; ++count)
    {
        result *=2;
        result += bin_string[count]=='1'? 1 :0;
    }

    std::stringstream ss;
    ss << "0x" << std::hex << std::setw(8) << std::setfill('0') << result;
    std::string hexVal(ss.str());

#if WITH_DEBUG_PRINT
std::cout << "DEBUG(convert_bin_to_hex)-> Output hex string: " << hexVal <<std::endl;
#endif

    return hexVal;
}

char tools::binary_flip_handle(const char& bit){
	return bit == '0' ? '1' :'0';
}

std::string tools::binary_flip_by_significant_bit(std::string const& bin_string){

#if WITH_DEBUG_PRINT
std::cout << "DEBUG(binary_flip_by_significant_bit)-> Input bin string: " << bin_string <<std::endl;
#endif

	int i;
	std::string res_bin_flip_str = "";

	bool is_most_significant_bit_one;

	if (bin_string[0] == '1'){ //check the significant bit
		is_most_significant_bit_one = true;
	}else{ // bin_string[0] == 0
		is_most_significant_bit_one = false;
	}

	for(i = 0; i != bin_string.size(); ++i){
		char c = bin_string[i];

		if (is_most_significant_bit_one){ // flip add bits
			if (i % 2 == 0){
				res_bin_flip_str += binary_flip_handle(c);

			}else{
				res_bin_flip_str += c;
			}
		}else{ //flip even bits
			if (i % 2 == 0){
				res_bin_flip_str += c;
			}else{
				res_bin_flip_str += binary_flip_handle(c);
			}
		}
	}

#if WITH_DEBUG_PRINT
std::cout << "DEBUG(binary_flip_by_significant_bit)-> Output bin string: " << res_bin_flip_str <<std::endl;
#endif

	return res_bin_flip_str;

}


bool tools::is_hex_notation(std::string const& hex_string)
{
  if( hex_string.compare(0, 2, "0x") == 0 // check if the hex start with '0x'
      && hex_string.size() > 2
	  && hex_string.size() <= 10
      && hex_string.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos){
	  return 1;
  }
  std::cout << "Error input: The hex number invalid!" << std::endl;
  return 0;
}

bool tools::is_4byte_number(std::string const& hex_string){
	int number = convert_hex_string_to_int(hex_string);
	if (sizeof(number) == FOUR_BYTE_TYPE) //check if the number is 4 bytes
		return 1;
	std::cout << "Error input: The hex number are not 4-Byte type!" << std::endl;
	return 0;
}

tools::~tools() {}
