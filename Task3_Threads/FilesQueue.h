#pragma once
#include<queue>
#include<mutex>
#include<condition_variable>
#include<string>

namespace Threads
{

class FilesQueue
{
public:
    FilesQueue();
    void PushToQueue(std::string path_to_file);
    std::string PopFromQueue();
    bool IsQueueEmpty()const;

private:
    mutable std::mutex mtx_;
    std::queue<std::string> file_paths_;
};

}
