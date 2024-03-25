# My-Own-Cpp-Json-Loader 0.35 VERSION

![Image of JSON text](/assets/images/Json_main_title.png)

## INFO

Hello! This is my own C++ library designed for interacting with JSON files. It simplify tasks such as reading, writing, and manipulating JSON data. The current version is 0.35, and I have been developing this library for almost three months now. The latest release was on January 26, 2024. There are numerous planned features for the future, including the ability to map JSON data into a structure resembling a map, enabling seamless calls. Additionally, performance updates are in the pipeline.

You can contact me on my email sunanborthwic@gmail.com or on my [instragram](https://www.instagram.com/nongtajkrub/)

## GUIDE

### Setup

```cpp
#include "json.hpp"
```

Include the json.hpp file

```cpp
int main()
{
	Json json("your_json_file_name");
}
```

Create a Json object in C++ by instantiating the class with your JSON file name as an argument.

### The call function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.call({"path_to_your_value_using_key"})
}
```

The call function allows retrieval of values from keys in the JSON file, taking a vector of strings as an argument to represent the path to the desired value. For instance, to access a value nested within keys 'key1,' 'key2,' and 'key3,' you would provide the path as {"key1", "key2", "key3"}."

### The writeJson function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.writeJson(true);
}
```

The writeJson function, when invoked, updates or writes edited data to the specified JSON file. Additionally, it features an optional boolean argument: when set to true, the function formats the JSON file for readability, while setting it to false maintains the original formatting during the writing process.

### The clearFile function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.clearFile();
}
```

The clearFile function, when called, empties the content of the JSON file it is associated with. This function does not require any arguments.

### The clearData function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.clearData();
}
```

This function is use to clear data out of the program but not the Json file.

### The add function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.add({"path_to_your_value_using_key"}, "the_name_of_your_key", "the_value_of_your_key", 'data_type_of_your_value');
}
```

The add function is employed to introduce a new key-value pair to the associated JSON file. It takes in four arguments    
- The first argument is a path to the desired value represented as a vector of strings, such as {"key1", "key2", "key3"}.  
- The second argument is the name of the key, provided as a string.  
- The third argument is the value associated with the key, provided as a string.  
- The fourth argument is the data type of the value, denoted by a character ('i' for integer, 's' for string).  

-example-

```cpp
json.add({"key1", "key2", "key3"}, "name", "John", 's');
```

### The change function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.change("path_to_your_value_using_key"}, "the_value_you_want_to_change_to", 'data_type_of_your_value', do_you_want_to_update_the_change_to_the_file, do_you_want_to_format_json_data_when_updating);
}
```

The change function is employed to modify the value of a key in a JSON file. It accepts five arguments:  
- The first argument is a path to the desired value represented as a vector of strings, such as {"key1", "key2", "key3"}.  
- The second argument is the new value to be assigned to the key, provided as a string.  
- The third argument is the data type of the value, indicated by a character ('i' for integer, 's' for string).  
- The fourth argument is a boolean indicating whether you want to immediately update the change to the file (true) or defer it for later using the writeJson function (false).  
- The fifth argument is a boolean indicating whether you want to format the JSON data when updating the change (true) or maintain the original formatting (false)  

### The showData function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.showData(do_you_want_to_shwo_the_data_in_detail);
}
```

The showData function is utilized to display how the program perceives your JSON file or data. It takes a single argument that is a boolean value determines whether to display the data in detail (true) or simply show a summary (false).

### The convertStringToJson function
```cpp
int main()
{
	Json json("");
	json.convertStringToJson("your_string_data");
}
```

The convertStringToJson function serves to convert a string, such as '{"test": 10}', into a JSON data structure. This function accepts a single argument that is a string containing the data you wish to convert to JSON format. When using this function to create a Json object, it is necessary to provide an empty string as the initial argument for the Json object."

-example-
```cpp
int main()
{
	std::string string_to_conver = "{\"test\": 10}"
	Json json("");
	json.convertStringToJson(string_to_convert);
}
```
You can also write the data to the Json file by using the json.changeFileName function to change the name of the Json file.
```cpp
int main()
{
	std::string string_to_conver = "{\"test\": 10}"
	Json json("");
	json.convertStringToJson(string_to_convert);
	json.changeFileName("test.json");
	json.writeJson(true);
}
```
### The changeFileName function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.changeFileName(new_file_name, do_you_want_to_clea_the_old_data);
}
```

The changeFileName function is designed for altering the file name associated with your Json object. However, it is recommended to create a new Json object for a different file rather than using this function. It take in 2 arguments:
- The first argument is the new file name you want your Json object to interact with provide as a string.
- The second argument is a boolean flag indicating whether you wish to clear the existing program data (true for clearing, false otherwise).

### The convertTypeInt function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.convertTypeInt(the_value_you_want_to_convert_into_an_int_after_calling_it);
}
```
When utilizing the call function, the returned value is always in string format. To convert this string representation to an integer, you can use the convertTypeInt function. It takes a single argument, which is the original string you want you change to an int.		 
		
-example-
```cpp
int main()
{
	Json json("your_json_file_name");
	int result = convertTypeInt(json.call({"and_int_value"}));
}
```

Internally, this function simply uses std::stoi for the conversion.

### The convertTypeArrayInt function adn The convertTypeArrayString function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.convertTypeArrayInt(the_string_you_want_to_convert_to_a_vector_that_contain_int);
	json.convertTypeArrayString(the_string_you_want_to_convert_to_a_vector_that_contain_string);
}
```

When utilizing the call function, it returns values as strings. To convert these string representations of arrays (containing either integers or strings) into actual vector objects, two functions are provided. The convertTypeArrayInt function is used for converting arrays containing integers returned as strings into vectors of integers. Similarly, the convertTypeArrayString function is employed for converting arrays containing strings returned as strings into vectors of strings. These functions take a single argument, which is the original string you want to convert to a vector . It's important to note that these functions cannot be used with arrays containing a mixture of integers and strings.

-example-
```cpp
int main()
{
	Json json("your_json_file_name");
	json.convertTypeArrayInt(json.call({"array_of_ints"}));
	json.convertTypeArrayInt(json.call({"array_of_strings"}));
}
```

### The is_true function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.is_true({"path_to_your_value"});
}
```

The is_true function is use to check if a certain value the a Json file is true. It take in a single argument which is the path to your value (the "path to your value" is explain more in the document section of the call function).

### The items function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.items();
}
```

Use to get all the item in the Json file (The key and the value) and map it together.

### The values funcion
```cpp
int main()
{
	Json json("your_json_file_name");
	json.values();
}
```

Use to get all the value in the Json file.

### The keys function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.keys();
}
```

Use the get all the key in the Json file.

## EXAMPLE CODE

You can also check out the EXMAPLE CODE in more detail in the folder OTHERS -> EXAMPLE -> 0.35

### main.cpp

```cpp
#include <iostream>
#include "json.hpp"

int main()
{
	// Create a string containing JSON data to be converted
	std::string json_test = "{\"cat\": 10}";

	// Create a Json object with an empty file name
	Json json("");

	// Convert the string into Json using convertStringToJson function
	json.convertStringToJson(json_test);

	// Call the "cat" key and print its value to demonstrate retrieval
	std::cout << json.call({"cat"}) << std::endl;

	// Change the value of the "cat" key to 15 as an integer
	// The two 'false' parameters indicate that the change won't be immediately written to a file,
	// and the formatting won't be applied when updating the file
	json.change({"cat"}, "15", 'i', false, false);

	// Print the updated value of the "cat" key
	std::cout << json.call({"cat"}) << std::endl;

	// Change the file name from no file to "test.json"
	json.changeFileName("test.json", false);

	// Write the JSON data to the file "test.json" and format it
	json.writeJson(true);

    	// Show detailed information about the JSON object, including current keys and values
    	json.showData(true);

    	// All functions that work with reading data from a file also work with reading data from a string and converting it to JSON
	
    	//Second example
	
    	std::cout << "\nsecond example\n\n";

	// Create a Json object with the file name of Secondtest.json
    	Json secondJson("Secondtest.json");

    	// Show his hobbies
    	std::cout << secondJson.call({"name"}) << " hoobies is";
    	// Convert a string that were return from json.call({"hoobies"}) to a vector.
    	// Loop through it then print the value.
    	// This will also work to convert a string to a vector that contain int using the convertTypeArrayInt function.
    	for (const std::string& hobbie : secondJson.convertTypeArrayString(secondJson.call({"hobbies"}))) {
        	std::cout << " " << hobbie;
    	}
    	std::cout << "." << std::endl;

    	// Check if he a student using the json.is_true({"isStudent"}).
    	if (secondJson.is_true({"isStudent"})) {
        	// If he a student print "He is a student".
        	std::cout << "He is a student." << std::endl;
    	} else {
        	// If he is not a student print "He is not a student".
		std::cout << "He is not a student." << std::endl;
    	}

    	// Print his grade using the json.call({"grades", "math"})
    	std::cout << "His math grade is " << secondJson.call({"grades", "math"}) << "." << std::endl;
    	// Print his grade plus by 5 using the json.convertTypeInt(json.cal({"grades", "math"})) to convert from a stirng
    	// that is return from the json.call function to an int. Then plus it by five.
    	std::cout << "His math grade plus by five is " << secondJson.convertTypeInt(secondJson.call({"grades", "math"})) + 5 << "." << std::endl;

    	return 0;
}
```

### json.test
Before the code is run.
```json

```
After the code is run.
```json
{
	"cat":15
}
```

### Secondtest.json
```json
{
	"name": "John Doe",
	"age": 30,
	"city": "Randomville",
	"isStudent": true,
	"grades": {
		"math": 85,
		"english": 78,
		"history": 92
	},
	"hobbies": ["reading", "traveling", "coding"],
	"address": {
		"street": "123 Random Street",
		"city": "Randomville",
		"zipcode": "98765"
	}
}
```

## DRAWBACKS

The current draw back for the version 0.30 that I know about
1. When using the convertTypeArrayInt function and the convertTypeArrayString the array can only contain either a string or an int and not both.
2. The convertTypeArrayInt function and the convertTypeArrayString can only take in array that conatian either a string or an int no any other datatype.

This is all that I know for now!
