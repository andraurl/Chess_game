//
//  Unique_ptr.hpp
//  Chess
//
//  Created by Andreas Aurlien on 16.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#ifndef Unique_ptr_hpp
#define Unique_ptr_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <utility>

using namespace std;

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif /* Unique_ptr_hpp */
