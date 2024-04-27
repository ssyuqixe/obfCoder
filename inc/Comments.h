#ifndef COMMENTS_H
#define COMMENTS_H

#include "Functions.h"
#include "Component.h"
#include <iostream>
#include <vector>
#include <string>

class Comments : public Component
{
    std::vector<std::wstring> *p_ContentFile;

public:
    Comments(std::vector<std::wstring> *mainString) : p_ContentFile(mainString) {}

    //todo: to split later
    bool DeleteLineComments();
    bool DeleteBlockComments();

	bool Update(std::vector<int> &settings) override;
	bool DoTechnique() override;
};

#endif // COMMENTS_H