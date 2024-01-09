#include <iostream>
#include "json.hpp"

int main()
{
	Json json("test.json");
	std::string *element = json.call({"test", "na me"});

	*element = "Taj";
	json.writeJson();

	return 0;
}
