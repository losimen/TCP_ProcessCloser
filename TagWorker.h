#ifndef TAG_WORKER_H
#define TAG_WORKER_H

#include <string>
#include <algorithm>

class TagWorker {
public:
    static std::string createTag(const std::string& tagName, const::std::string &tagContent);
    static std::string getTagContent(const std::string &buffer, const std::string& tagName); 
};

#endif //LISTENER_H