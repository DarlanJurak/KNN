//
//  Instance.hpp
//  Implementation
//
//  Created by Darlan Alves Jurak on 13/04/2018.
//
//

#ifndef Instance_hpp
#define Instance_hpp

#include <vector>

class Instance {
private:

    int category;
    float dissimilarity;    // Dissimilarity (distance) between this sample and the new instance to be classified.

public:

    std::vector<float> attributes;

    Instance();
    Instance(int, std::vector<float>);
    int getCategory(){return category;};
    float getDissimilarity(){return dissimilarity;};
    void showAttributes();
    void calculateDissimilarityByEuclidianDistance(std::vector<float>);
    ~Instance();

protected:

};

#endif /* Instance_hpp */
