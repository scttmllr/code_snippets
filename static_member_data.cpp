//
//  main.cpp
//  staticMemberData
//
//  Created by Scott T. Miller on 5/28/15.
//  Copyright (c) 2015 Scott T. Miller. All rights reserved.
//

#include <iostream>

struct NodeIds
{
    static const int attribute = 1;
};

struct NodeCoords
{
    static const int attribute = 2;
};

struct FaceIds
{
    static const int attribute = 3;
};

struct Connectivity
{
    static const int attribute = 4;
};

template <class Type>
class SomeClass
{
public:
    SomeClass(){};
    ~SomeClass(){};
    
    SomeClass(SomeClass&) = delete;
    SomeClass& operator=(SomeClass&) = delete;
    
    static const int data = Type::attribute;
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "We can use this structure:"<<std::endl;
    std::cout << "\n\t SomeClass<NodeIds>:: = " << SomeClass<NodeIds>::data;
    std::cout << "\n\t SomeClass<NodeCoords>:: = " << SomeClass<NodeCoords>::data;
    std::cout << "\n\t SomeClass<FaceIds>:: = " << SomeClass<FaceIds>::data;
    std::cout << "\n\t SomeClass<Connectivity>:: = " << SomeClass<Connectivity>::data;
    
    return 0;
}
