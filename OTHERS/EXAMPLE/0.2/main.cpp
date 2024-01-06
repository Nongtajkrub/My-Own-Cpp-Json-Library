#include <iostream>
#include "json.hpp"

int main()
{
	Json json("test.json");
	std::string* element;
		
	element = json.call({"test", "na me"}); //Get the value using keys
	*element = "change"; //Changing the value
	json.writeJson(); //Update the change to the file (write to file)
	delete element; //Delete the pointer

	return 0;
}
