
#include "../inc/Instance.hpp"    // Instance class.
#include <iostream>             // cout and cin.
#include <string>               // String.
#include <boost/algorithm/string.hpp>   // String split.

using namespace std;

struct vote{

    int category = -1;
    int amount = 0;

};

// used to ordenated the samples vector by dissimilarity
bool myfunction (Instance* inst0, Instance* inst1){

    return (inst0->getDissimilarity() < inst1->getDissimilarity());

}

int main() {

    vector<Instance *> samples;         // Data structure to store samples.
    vector<Instance *> new_instances;   // Data structure to store new instances that are going to be classified.
    string user_input;                  // Variable to interact with user.
    vector<float>       instance_input_float;  // Intermediary attributes vector.
    vector<std::string> instance_input_string; // Used in the get line split.
    int K;  // Amount of Neares Neighbors that vote
    // vector

    cout << "Please, insert K: ";
    cin >> K;

    // User interaction. Asks for Instances attributes.
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

    getline(cin, user_input);   // Get first user input.

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

        // Creates new Instance instance with class and attributes.
        int category = (int)*(instance_input_float.begin());        // Gets class information.
        instance_input_float.erase(instance_input_float.begin());   // Removes class for vector reuse.
        samples.push_back(new Instance(category, instance_input_float));  // Creates new sample.

        getline(cin, user_input);   // Get user input (new attributes set).
    }

    // Shows samples and their attributes
    int count = 0;  // Counter to help user. (Helps to see the ordered list of samples).
    for (std::vector<Instance *>::iterator it = samples.begin(); it != samples.end(); ++it){

        std::cout << "Sample " <<  count++ << ": "
            << "class: " << (*it)->getCategory() << " "
            << "attributes: ";
        (*it)->showAttributes();

    }

    // Instance to be classified input
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

    // calculates Dissimilarity
    for (std::vector<Instance *>::iterator it = samples.begin(); it != samples.end(); ++it){

        (*it)->calculateDissimilarityByEuclidianDistance((*(new_instances.begin()))->attributes);

    }

    // Shows samples dissimilarities
    count = 0;
    for (std::vector<Instance *>::iterator it = samples.begin(); it != samples.end(); ++it){

        std::cout << "Sample " << count++ << ". Dissimilarity: " << (*it)->getDissimilarity() << "." << endl;

    }

    // Order objects by dissimilarity
    std::sort (samples.begin(), samples.end(), myfunction);

    // Shows samples ordered by dissimilarities
    count = 0;
    for (std::vector<Instance *>::iterator it = samples.begin(); it != samples.end(); ++it){

        std::cout << "Sample " << count++ << ". Dissimilarity: " << (*it)->getDissimilarity() << "." << endl;

    }

    // Count vote of K neares neighbors
    for(int i = 1; i != K; i++) {

        // samples[i-1]

    }


    // classify new object



    return 0;
}
