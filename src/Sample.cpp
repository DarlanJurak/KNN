//
//  Sample.cpp
//  Implementation
//
//  Created by Darlan Alves Jurak on 13/04/2018.
//
//

#include "../inc/Sample.hpp"
#include <iostream>
#include <math.h>   // pow(x, y) x^y

Sample::Sample(){}

/**
*** Creates sample with category and attributes
***
*/
Sample::Sample(int c, std::vector<float> v){

    category = c;
    attributes = v;

}

/**
*** Print attributes using cout
***#include <math.h>
*/
void Sample::showAttributes(){

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
void Sample::calculateSimilarityByEuclidianDistance(std::vector<float> new_instance_attributes){

    float squaresSum = 0; // Summation variable.

    // Summation process.
    for(std::vector<int>::size_type i = 0; i != new_instance_attributes.size(); i++) {
        squaresSum += pow(new_instance_attributes.at(i), 2) + pow(attributes.at(i) , 2);

    }

    similarity = squaresSum;

}

Sample::~Sample(){}
