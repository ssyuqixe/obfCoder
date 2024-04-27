#ifndef COMPONENT_H
#define COMPONENT_H
#include <vector>

class Component{
public:
    virtual ~Component() = default;
    //todo: check if change vector<int> to vector<T> or vector<char/byte> is better
    //or maybe just give block of memory and convert it in function e.g void to vector
    virtual bool Update(std::vector<int> &settings) = 0;
    virtual bool DoTechnique() = 0;
};



#endif // COMPONENT_H