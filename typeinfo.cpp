//
//  main.cpp
//  typetest
//
//  Created by Scott T. Miller on 4/28/15.
//  Copyright (c) 2015 Scott T. Miller. All rights reserved.
//

#include <iostream>

#include <memory>
#include <list>
#include <typeinfo>

// Name demangling
//#include <cxxabi.h>


int main(int argc, const char * argv[]) {
    
    double* vec = new double[7];
    
    vec[5] = 3.14159;
    
    const std::type_info& ti = typeid(vec);
    
    std::cout<<"\n type_info of vec = " << ti.name() << std::endl;
    
    decltype(vec) nv;
    
    std::cout<<"\n type_info of nv = " << typeid(nv).name() << std::endl;

    delete [] vec;
    
    return 0;
}
