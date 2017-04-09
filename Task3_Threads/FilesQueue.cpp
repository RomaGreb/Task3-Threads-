#include"FilesQueue.h"

namespace Threads
{

FilesQueue::FilesQueue(): file_paths(),mtx(),con_var()
{
}

bool FilesQueue::QueueIsEmpty()const
{
    std::lock_guard<std::mutex> lock(mtx);
    return file_paths.empty();
}

void FilesQueue::PushToQueue(std::string path_to_file)
{
    std::lock_guard<std::mutex> lock(mtx);
    file_paths.push(path_to_file);
    con_var.notify_one();
}

std::string FilesQueue::PopFromQueue()
{
    std::unique_lock<std::mutex> lock(mtx);
    std::string temp;
    if(!file_paths.empty())
    {
        temp = file_paths.front();
        file_paths.pop();
    }
    return temp;
}

}
