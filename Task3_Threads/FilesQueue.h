#pragma once
#include<queue>
#include<mutex>
#include<condition_variable>
#include<string>

namespace Threads
{

class FilesQueue
{
    mutable std::mutex mtx;
    std::queue<std::string> file_paths;

public:
    FilesQueue();
    void PushToQueue(std::string path_to_file);
    std::string PopFromQueue();
    bool QueueIsEmpty()const;
};

}
