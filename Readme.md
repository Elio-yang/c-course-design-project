## 1. How to compile?
```shell
mkdir build
cd build
cmake ..
make
```
the binary will be put into ``bin/``

CMAKE_MINIMAL_REQUIRED 3.10

## 2.Directories

1. ``Tests`` contains some of the testing files

2. ``tools`` contains many useful tools(APIs) which can be used 
anywhere.
   ``print_color.h`` used for color print in linux shell

    ``process_bar.h`` used for creating a dynamic loading bar

    ``time_related.h`` used for time-related work
   
    ``tools`` are welcomed to get contributed and adjusted,if you want to add 
   some small tools which are not system(the system you are developed) specified,just 
   add them into this file but make sure that the api is well designed and
   related usage are well written :)!
   
