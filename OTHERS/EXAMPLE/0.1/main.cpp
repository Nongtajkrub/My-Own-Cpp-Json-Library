#include <iostream>
#include "json.hpp"

int main()
{
	Json json("test.json");
	std::string* element;

	element = json.call({"test", "na me"});
	*element= "hey";
	std::cout << *json.call({"test", "na me"}) << std::endl; //showing that the value inside of the element has been change
	delete element;

	return 0;
}
