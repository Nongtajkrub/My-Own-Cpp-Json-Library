# My-Own-Cpp-Json-Loader 0.1 VERSION
 **This is my own Json loader it is for loading json file**

You can download the file in the release page this guide is for the version 0.1

 Here are some example code for using this Json loader.

```cpp
#include <iostream>
#include "json.hpp"

int main()
{
	Json json("test.json");

	json.call({"key1", "key2", "key3" ...});

	return 0;
}
```

*This code wont work this it just an example*

1. First intilize the Json object and the file name as an parameter  
2. Second use the json.call function to get the value from a certain key in the Json file
3. Build the code

```
g++ json.cpp your_other_file.cpp -o your_.exe_file_name
```

4. Run the code

```
./your_.exe_file_name
```
_The current version of the loader will only work with key that is a string and value that is a string_    
_They are example code in the OTHERS/EXAMPLE/0.1 file_


**NOT RECOMMENDED FOR PUBLIC USE THIS IS JUST A WAY TO SHOW WHAT I AM DOING**

**--MORE UPDATAE AND INFO COMMING SOON--**

# My-Own-Cpp-Json-Loader 0.15 VERSION

**This is my own Json loader it is for loading json file**

You can download the file in the release page this guide is for the version 0.15

 Here are some example code for using this Json loader.

```cpp
#include <iostream>
#include "json.hpp"

int main()
{
	Json json("test.json");

	std::string* element;
	element = json.call({"key1", "key2", "key3" ...});
	*element = "test";
	delete element;

	return 0;
}
```

*This code wont work this it just an example*

1. First intilize the Json object and the file name as an parameter  
2. Second use the json.call function to get the pointer to the element you are trying to find using key to navigate
3. You can now use the pointer to change the element in the json file but still cant update the change to the json file that is being work on  
4. Build the code

```
g++ json.cpp your_other_file.cpp -o your_.exe_file_name
```

5. Run the code

```
./your_.exe_file_name
```
_The current version of the loader will only work with key that is a string and value that is a string_    
_They are example code in the OTHERS/EXAMPLE/0.15 file_


**NOT RECOMMENDED FOR PUBLIC USE THIS IS JUST A WAY TO SHOW WHAT I AM DOING**
