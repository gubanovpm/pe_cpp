# First task on qt

## Setup build environment

```
mkdir build 
cd build
```

## Build in Debug mode

```
cmake ..
cmake --build .
```

## Build in Release mode

```
cmake -DCMAKE_BUILD_TYPE=Relase ..
cmake --build .
```

## Difference between pure C++ and this Qt application

  * Used qt framework for create window
  * Used qt paradigm of slots and signals 

## Difference between std::string and QString

  1. C++ doesn't contain a String class, STL does
  2. STL String is 8-bit based whereas QString is Unicode based, thus we can express things with QString which we wouldn't be able to express with std::string
  3. QString is much faster in many ways than std::string
  4. QString has many functionality std::string doesn't have
  5. QString has practically all useful functionality of std::string
