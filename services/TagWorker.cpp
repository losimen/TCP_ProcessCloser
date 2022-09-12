#include "TagWorker.h"

#include <chrono>
#include <thread>


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
        throw std::runtime_error("Invalid tag: " + tagName);
    
    tagContent = buffer.substr(start + tag.length(), end - start - tag.length());

    return tagContent;
}


std::vector<std::string> TagWorker::getTagContentList(const std::string &buffer, const std::string &listTagName, const std::string &itemTagName) {
    std::vector<std::string> result;
    const std::string tagEnd = "</" + itemTagName + ">";
    const int itemTagNameSize = itemTagName.size();
    std::string dataList = TagWorker::getTagContent(buffer, listTagName);

    while (!dataList.empty()) {
        result.push_back(TagWorker::getTagContent(dataList, itemTagName));
        size_t endIt = dataList.find(tagEnd);
        dataList = dataList.substr(endIt + itemTagNameSize + 3);
    }

    return result;
}