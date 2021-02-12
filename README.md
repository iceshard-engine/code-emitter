# Iceshard Code Emitter 

[![](https://github.com/iceshard-engine/code-emitter/workflows/Nightly/badge.svg)](https://github.com/iceshard-engine/code-emitter/actions?workflow=Nightly)
[![](https://github.com/iceshard-engine/code-emitter/workflows/Validation/badge.svg)](https://github.com/iceshard-engine/code-emitter/actions?workflow=Validation)

## Quick introduction

This project aims to provide a simple abstraction layer between three different tasks. 
* Parsing
* Processing
* Generating

This project provides an API which allows easily to connect and mix different parsers, generators and processing modules. 
This can be used to:
* Transpile code from language to language. *(limited to the AST available in the API)*
* Generate bindings to a scripting API.  *(like LUA or AngelScript)*
* Generate metadata for input files. *(generate rich RTTI information for C++ types)*
* Validate input files by a given pattern. *(check coding guielines for submissions)*


## Quick details

This API was created with C++ in mind. It's designed to fully support the C++ `[[attribute]]` syntax and thus heavily uses naming used in C++, for example: **ice::input::Namespace**, **ice::input::Class**, **ice::input::Enum**. 

However during the development time the API will be generalized on the way, maybe allowed to be extended. 

**Note: One simple rule currently used with the associated C++ parsed is to ignore any Preprocessor statements.**
This is because there is already a good API for such a task called Clang. However this project aims to just work on a single file and return things that are parsed 'as is'. 


### Small example

```cpp
// Header file generated with this tool
// foo.gen.h
class Box;

namespace ice::rtti
{
  template<>
  void print_class_info<::Box>() noexcept;
}

// foo.h
#include <foo.gen.h>

struct [[ice::rtti]] Box
{
  float _weight{ 1 };
  int _size{ 2 };
};

// Source file generated with this tool
// foo.gen.cxx
#include "{full_path_to}/foo.h"
#include <iostream>

template<>
void ice::rtti::print_class_info<::Box>() noexcept
{
    std::cout << "Box : structure" << std::endl;
    std::cout << "Fields: " << std::endl;
    std::cout << "- name: _weight" << std::endl;
    std::cout << "  type: float" << std::endl;
    std::cout << "  default: 1" << std::endl;
    std::cout << "- name: _size" << std::endl;
    std::cout << "  type: int" << std::endl;
    std::cout << "  default: 0.5" << std::endl;
}
```
