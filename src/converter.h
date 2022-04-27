

#include "tools.h"

class converter{

	tools t;

public:

	//run_validation_functions:
	//The function call to is_hex_notation and is_4byte_number functions.
	bool run_validation_functions(std::string const& hex_string);

	/*
	hex_converter:
	The function get hex string e.g: '0xa4172bd2' and return hex string that manipulated by the following conditions:
	1.First of all convert from hex to binary.
	2.Check if the most significant bit is '1' or '0'.
	3.If most significant bit of the number is '1':
	 	-Flip all odd bits on the number.
	  If most significant bit of the number is '0':
		-Flip all even bits on the number.
	e.g input hex -> '0xa4172bd2' output hex -> '0xebd8178
	*/
	std::string hex_converter(std::string const& hex_string);

	virtual ~converter();
};
