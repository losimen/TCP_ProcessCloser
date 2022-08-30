#include "TagWorker.h"


std::string TagWorker::createTag(const std::string& tagName, const::std::string &tagContent) {
    std::string tag = "<" + tagName + ">" + tagContent + "</" + tagName + ">";
    return tag;
}


std::string TagWorker::getTagContent(const std::string &buffer, const std::string& tagName) {
    std::string tagContent = "";

    std::string tag = "<" + tagName + ">";
    std::string tagEnd = "</" + tagName + ">";
    size_t start = buffer.find(tag);
    size_t end = buffer.find(tagEnd);

    if (start == std::string::npos || end == std::string::npos)
        throw std::runtime_error("Invalid tag");
    
    tagContent = buffer.substr(start + tag.length(), end - start - tag.length());

    return tagContent;
}