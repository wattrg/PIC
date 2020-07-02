

#include<vector>
#include<iostream>
#include "setup.h"

#ifndef io_h
#define io_h

namespace PIC_IO 
{
    template <typename T>
    void printVec(std::vector<T> vec, bool el = true) {
		int len = vec.size();
		std::cout << "[";
		for (int i = 0; i < len; i++) {
			std::cout << vec[i];
			if (i < len - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "]";
		if (el){
			std::cout << std::endl;
		}
    }
}




#endif // io_h