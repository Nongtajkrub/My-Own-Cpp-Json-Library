# My-Own-Cpp-Json-Loader 0.25 VERSION
 **This is my own Json loader it is for loading and writing json file**

 Here are some example code for using this Json loader.

```cpp
#include <iostream>
#include "json.hpp"

int main()
{
	Json json("test.json");
	std::string *element;

	element = json.call({"key1", "key2", "key3" ...});
	*element = "change value to anything"
	json.writJson();
	delete element;
	
	return 0;
}
```

*This code wont work this it just an example*

1. First intilize the Json object and the file name as an parameter (Json json("test.json");)
2. Make a pointer variable (std::string *element;)
3. Second use the json.call function to get the value from a certain key in the Json file adn give the value to the pointer variable element (element = json.call({"key1", "key2", "key3" ...});)
4. Change the element in the file (*element = "change value to anything")
5. Update the change to the Json file (json.writJson();)
6. Delete the pointer (delete element;)
7. Build the code

```
g++ json.cpp your_other_file.cpp -o your_.exe_file_name
```

8. Run the code

```
./your_.exe_file_name
```
   
_They are example code in the OTHERS/EXAMPLE/0.25 file_

**NOT RECOMMENDED FOR PUBLIC USE THIS IS JUST A WAY TO SHOW WHAT I AM DOING**
