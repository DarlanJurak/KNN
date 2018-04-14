//
//  Sample.cpp
//  Implementation
//
//  Created by Darlan Alves Jurak on 13/04/2018.
//
//

#include "../inc/Sample.hpp"
#include <iostream>

Sample::Sample(){}

Sample::Sample(int c, std::vector<float> v){

    category = c;
    attributes = v;

}

void Sample::showAttributes(){

    for (std::vector<float>::iterator it = attributes.begin(); it != attributes.end(); ++it){

        std::cout << *it << ' ';

    }

    std::cout << "\n";
}

Sample::~Sample(){}
