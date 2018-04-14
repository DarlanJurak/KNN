
#include "../inc/Sample.hpp"    // Sample class.
#include <iostream>             // cout and cin.
#include <string>               // String.
#include <boost/algorithm/string.hpp>   // String split.

using namespace std;

int main() {

    vector<Sample *> samples;   // Data structure to store samples.
    string user_input;          // Variable to interact with user.
    vector<float> attributes_float;  // Intermediary attributes vector.
    vector<std::string> attributes_string;

    // User interaction. Asks for Samples attributes.
    cout << "Please, insert the training base as follow: \n"
        << "* All attributes values related to the same instance in one line (ordered and separated by <space>) \n"
        << "* Lines separated by <enter> \n"
        << "* Finish insertion by entering <enter> \n"
        << "Examples:   \n"
        << "2 3.6       \n"
        << "17 5        \n"
        << "2.2 15.8    \n" << endl;

    getline(cin, user_input);   // Get first user input.

    // While receives input, set them as Samples's attributes.
    while(user_input.size() > 0){

        // Splits input string by <space>.
        boost::split(attributes_string, user_input, [](char c){return c == ' ';});

        // Transforms from string vector to float vector.
        vector<float> attributes_float(attributes_string.size());
        transform(attributes_string.begin(), attributes_string.end(), attributes_float.begin(), [](const std::string& val)
        {
            return std::stof(val);
        });

        // Creates new Sample instance with attributes.
        samples.push_back(new Sample(attributes_float));

        getline(cin, user_input);   // Get user input (new attributes set).
    }

    int count = 0;
    for (std::vector<Sample *>::iterator it = samples.begin(); it != samples.end(); ++it){

        std::cout << "Sample " <<  count << ": ";
        count++;
        (*it)->showAttributes();

    }


    return 0;
}
