//
//  Instance.cpp
//  Implementation
//
//  Created by Darlan Alves Jurak on 13/04/2018.
//
//

#include "../inc/Instance.hpp"
#include <iostream>
#include <math.h>   // pow(x, y) x^y

Instance::Instance(){}

/**
*** Creates instance with category and attributes
***
*/
Instance::Instance(int c, std::vector<float> v){

    category = c;
    attributes = v;

}

/**
*** Print attributes using cout
***
*/
void Instance::showAttributes(){

    for (std::vector<float>::iterator it = attributes.begin(); it != attributes.end(); ++it){

        std::cout << *it << ' ';

    }

    std::cout << "\n";
}

/**
*** Calculates
*** Improvement: compare attribute amounts and choose the lowest
***
*/
void Instance::calculateDissimilarityByEuclidianDistance(std::vector<float> new_instance_attributes){

    float squaresSum = 0; // Summation variable.

    // Summation process.
    for(std::vector<int>::size_type i = 0; i != new_instance_attributes.size(); i++) {
        squaresSum += pow(new_instance_attributes.at(i) - attributes.at(i), 2);

    }

    dissimilarity = squaresSum;

}

Instance::~Instance(){}
