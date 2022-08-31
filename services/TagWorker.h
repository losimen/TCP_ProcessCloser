#ifndef TAG_WORKER_H
#define TAG_WORKER_H

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>


class TagWorker {
public:
    static std::string createTag(const std::string &tagName, const::std::string &tagContent);
    static std::string getTagContent(const std::string &buffer, const std::string &tagName); 
    static std::vector<std::string> getTagContentList(const std::string &buffer, const std::string &listTagName, const std::string &itemTagName);
};

#endif //LISTENER_H