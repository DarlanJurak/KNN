//
//  Sample.hpp
//  Implementation
//
//  Created by Darlan Alves Jurak on 13/04/2018.
//
//

#ifndef Sample_hpp
#define Sample_hpp

#include <vector>

class Sample {
private:

    int category;
    std::vector<float> attributes;

public:

    Sample();
    Sample(int, std::vector<float>);
    int getCategory(){return category;};
    void showAttributes();
    ~Sample();

protected:

};


#endif /* Sample_hpp */
