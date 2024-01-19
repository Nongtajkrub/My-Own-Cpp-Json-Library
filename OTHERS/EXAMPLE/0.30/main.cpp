#include <cstddef>
#include <iostream>
#include "json.hpp"

int main()
{
	std::string json_test = "{\"cat\": 10}"; //Make a string to be convert into Json
	Json json(""); //Make a Json object with no arg
	
	json.convertStringToJson(json_test); //Use the convertStringToJson function to convert the string from above to Json
	std::cout << json.call({"cat"}) << std::endl; //Call the cat key and print it out to show that you can call it
	json.change({"cat"}, "15", 'i', false, false); //Change the value of the "cat" key to 15 as an int the two false behind mean we wont write to any file and since we are not writing the format when writing arg can also be false
	std::cout << json.call({"cat"}) << std::endl; //Show that the cat value had been change 
	json.file_name = "test.json"; //Change the file name from no file to a file name "test.json"
	json.writeJson(true); //Write to the file with the name "test.json" and the true mean to format the data when writing the file from emty will now have a {"cat": 10} in it
	json.showData(true); //This will show the detail of the json object like all the current key and value the true mean to show it in more detail
	json.clearFile(); //This will clear the "test.json" file completely

	//ALL THE FUNCTION THAT WORK WITH READING DATA FROM FILE WILL ALSO WORK WITH READING DATA FROM A STRING AND CONVERT IT TO A JSON

	return 0;
}
