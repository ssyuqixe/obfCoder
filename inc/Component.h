#ifndef COMPONENT_H
#define COMPONENT_H
#include <vector>

class Component{
public:
    virtual ~Component() = default;
    virtual bool Update(std::vector<int> &settings) = 0;
    virtual bool DoTechnique() = 0;
};



#endif // COMPONENT_H