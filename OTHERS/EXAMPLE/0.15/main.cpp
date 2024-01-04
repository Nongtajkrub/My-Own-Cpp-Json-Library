#include <iostream>
#include "json.hpp"

int main()
{
	Json json("test.json");

	std::string* element;
	element = json.call({"test", "na me"});
	*element = "test";
	std::cout << *json.call({"test", "na me"});
	delete element;

	return 0;
}
