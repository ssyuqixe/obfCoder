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
    std::string m_Tag = "Comments";
public:
    Comments(std::vector<std::wstring> *mainString) : p_ContentFile(mainString) {}

    //todo: to split later
    bool DeleteLineComments();
    bool DeleteBlockComments();

	bool Update(std::vector<int> &settings) override;
	bool DoTechnique() override;
    std::string GetTag() override { return m_Tag; };
    void SetTag(std::string tag) override { this->m_Tag = tag;};
};

#endif // COMMENTS_H