

#include "tools.h"

class converter{

	tools* t;

public:

	std::string hex_converter(std::string const& hex_string);

	virtual ~converter();
};
