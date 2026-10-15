# C++ Class Generator

A lightweight CLI tool to automate boilerplate generation for C++ `.h` header and `.cpp` implementation files.

## Compilation and Execution

Compile the source code:
```bash
g++ main.cpp -o classgen
```

Run the binary:
```bash
./classgen
```

## Available Commands

The CLI interactive loop accepts the following commands:

| Command | Description | Example |
| :--- | :--- | :--- |
| `model <name>` | Creates a template `.txt` definition file for the given class name. | `model Person` |
| `create <file>` | Parses the specified `.txt` configuration and generates `.h` and `.cpp` files. | `create Person.txt` |
| `exit` | Terminates execution. | `exit` |

## Template File Structure (.txt)

Input files must strictly follow this line order:
1. **Class Name**
2. **Includes** (space-separated list)
3. **Attributes** (space-separated pairs of `type name` on a single line)
4. **Methods** (one line per method: `return_type method_name param1_type param1_name ...`)

## Custom Type Modifiers

Prefix types (in attributes, parameters, or return types) to apply C++ type modifiers automatically:

| Prefix | C++ Modifier | Input Example | Generated Output |
| :--- | :--- | :--- | :--- |
| `*` | `const` | `*int` | `const int` |
| `_` | Reference (`&`) | `_string` | `string&` |
| `*_` or `_*`| `const` Reference (`&`) | `*_float` | `const float&` |
| `%` | `const` Method (return type only) | `%void print` | `void print() const;` |

---

## Example: Before and After Parsing

### Input Template File (`Person.txt`)

```text
Person
<string> <iostream>
std::string name int age *_std::string address
%std::string toString
void updateAddress *_std::string newAddress
```

### Generated Header File (`Person.h`)

```cpp
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class Person{
private:
	std::string name;
	int age;
	const std::string& address = {};
public:
	void setName(std::string);
	std::string getName();
	void setAge(int);
	int getAge();
	const std::string& getAddress() const;
	std::string toString() const;
	void updateAddress(const std::string&);
};

#endif
```

### Generated Implementation File (`Person.cpp`)

```cpp
#include "Person.h"

void Person::setName(std::string name){
	this->name = name;
}
std::string Person::getName(){
	return this->name;
}

void Person::setAge(int age){
	this->age = age;
}
int Person::getAge(){
	return this->age;
}

const std::string& Person::getAddress() const{
	return this->address;
}

std::string Person::toString() const{}

void Person::updateAddress(const std::string& newAddress){}

```
