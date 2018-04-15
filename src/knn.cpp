
//
//  knn.cpp
//  Simple Implementation of K-NN (K-Nearest Neighbors)
//
// Version: Interaction with user by terminal.
//
// Future improvement: 1- Get data from file.
//                      2-  Classify more than 1 new instance.
//
//  Created by Darlan Alves Jurak on 13/04/2018.
//
//

#include "../inc/Instance.hpp"          // Instance class.
#include <iostream>                     // cout and cin.
#include <string>                       // String.
#include <boost/algorithm/string.hpp>   // String split.

using namespace std;

struct Vote{

    int category = -1;
    int amount = 0;

};

// Used to ordenated the samples vector by dissimilarity. (Ascend).
bool lowDissimilarity (Instance* inst0, Instance* inst1){

    return (inst0->getDissimilarity() < inst1->getDissimilarity());

}

// Comparison between a vote category and a sample category.
bool categoryComparison(Vote v, int cat)
{
	if(v.category == cat)
		return true;
	else
		return false;
}

void showVote (Vote v) {

  std::cout << "Class: " << v.category << ". Votes: " << v.amount << endl;

}

// Used to ordenated the votes vector by votes amount. (Descendant).
bool votesAmount_descendant(Vote v0, Vote v1){

    return (v0.amount > v1.amount);

}

int main() {

    int K;  // Amount of Neares Neighbors that can vote.
    vector<Instance *> samples;         // Data structure to store samples.
    vector<Instance *> new_instances;   // Data structure to store new instances that are going to be classified.
    string user_input;                  // Variable to interact with user.
    vector<float>       instance_input_float;  // Intermediary attributes vector.
    vector<std::string> instance_input_string; // Used in the get line split.
    std::vector<Vote> votes;    // Data structure to store votes.

    cout << "\n=================== K Insertion ===================" << endl;
    cout << "Please, insert K: " << endl;
    getline(cin, user_input);
    K = stoi(user_input);

    // User interaction. Asks for Instances attributes.
    cout << "\n================ Samples Insertion ================" << endl;
    cout << "Please, insert the training base respecting the following rules: \n"
        << "* Insert numbers only (they CAN be float) \n"
        << "* The FIRST number in a line represents a CLASS \n"
        << "* Insert all attributes values related to the same instance in one line (ordered and separated by <space>) \n"
        << "* Insert lines separated by <enter> \n"
        << "* Finish insertion by entering <enter> \n"
        << "Example:    \n"
        << "1 2 3.6       \n"
        << "2 17 5        \n"
        << "1 2.2 15.8    \n" << endl;

    getline(cin, user_input);   // Get first user input related to samples.

    // While receives input, set them as Instances's attributes.
    while(user_input.size() > 0){

        // Splits input string by <space>.
        boost::split(instance_input_string, user_input, [](char c){return c == ' ';});

        // Transforms from string vector to float vector.
        vector<float> instance_input_float(instance_input_string.size());
        transform(instance_input_string.begin(), instance_input_string.end(), instance_input_float.begin(), [](const std::string& val)
        {
            return std::stof(val);
        });

        // Creates new Sample instance with class and attributes.
        int category = (int)*(instance_input_float.begin());        // Gets class information.
        instance_input_float.erase(instance_input_float.begin());   // Removes class for vector reuse.
        samples.push_back(new Instance(category, instance_input_float));  // Creates new sample.

        getline(cin, user_input);   // Get user input (new attributes set).
    }

    cout << "\n================== Show Samples ==================" << endl;
    // Shows samples and their attributes.
    int count = 0;  // Counter to help user. (Helps to see the ordered list of samples).
    for (std::vector<Instance *>::iterator it = samples.begin(); it != samples.end(); ++it){

        std::cout << "Sample " <<  count++ << ": "
            << "class: " << (*it)->getCategory() << " "
            << "attributes: ";
        (*it)->showAttributes();

    }

    cout << "\n============== New Instance Insertion ==============" << endl;
    // Instance to be classified - input.
    cout << "\n Now please, insert the instance to be classified. Remember:\n"
        << "* Insert numbers only (they CAN be float) \n"
        << "* Finish insertion by entering <enter> \n"
        << "Example:   \n"
        << "1.2 3.6      \n" << endl;

    getline(cin, user_input);   // Get user input. (Idealy the new object's attributes).

    // Splits input string by <space>.
    boost::split(instance_input_string, user_input, [](char c){return c == ' ';});

    // Transforms from string vector to float vector.
    instance_input_float.resize(instance_input_string.size());
    transform(instance_input_string.begin(), instance_input_string.end(), instance_input_float.begin(), [](const std::string& val)
    {
        return std::stof(val);
    });

    // Creates new Instance instance with attributes.
    new_instances.push_back(new Instance(NULL, instance_input_float));  // Creates new sample.

    // Calculates dissimilarity.
    for (std::vector<Instance *>::iterator it = samples.begin(); it != samples.end(); ++it){

        (*it)->calculateDissimilarityByEuclidianDistance((*(new_instances.begin()))->attributes);

    }

    cout << "\n=============== Samples Dissimilarity ===============" << endl;
    // Shows samples dissimilarities.
    count = 0;
    for (std::vector<Instance *>::iterator it = samples.begin(); it != samples.end(); ++it){

        std::cout << "Sample " << count++ << ". Dissimilarity: " << (*it)->getDissimilarity() << "." << endl;

    }

    // Order objects by dissimilarity.
    std::sort (samples.begin(), samples.end(), lowDissimilarity);

    cout << "\n========= Samples Dissimilarity Ordered ========" << endl;
    // Shows samples ordered by dissimilarities.
    count = 0;
    for (std::vector<Instance *>::iterator it = samples.begin(); it != samples.end(); ++it){

        std::cout << "Sample " << count++ << ". Dissimilarity: " << (*it)->getDissimilarity() << "." << endl;

    }

    // Compute vote of K-Nearest Neighbors.
    for(int i = 0; i != K; i++) {
        // Looks for same kind of vote (same class/category)
        std::vector<Vote>::iterator it;
        it = std::find_if(votes.begin(), votes.end(), std::bind(categoryComparison,  std::placeholders::_1 , samples[i]->getCategory()) );
        if(it != votes.end()){  //Class found.

            (*it).amount++;    // Increase vote amount.

        }
        else{ // Class not found.

            Vote newVote;
            newVote.category = samples[i]->getCategory();
            newVote.amount = 1;
            votes.push_back(newVote); // Add new type of Vote.

        }

    }

    cout << "\n============ K-Nearest Neighbors Votes ============" << endl;
    // Show votes
    for_each (votes.begin(), votes.end(), showVote);

    // Classify new object
    cout << "\n================== Classification =================" << endl;

    std::sort (votes.begin(), votes.end(), votesAmount_descendant); // Order votes by amount. (Descendant)

    std::cout << "New Instance classification - Class: " << votes.begin()->category << "." << endl;

    return 0;
}
