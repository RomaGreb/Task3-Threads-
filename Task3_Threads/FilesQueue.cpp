#include"FilesQueue.h"

namespace Threads
{

FilesQueue::FilesQueue(): file_paths_(),mtx_()
{
}

bool FilesQueue::IsQueueEmpty()const
{
    std::lock_guard<std::mutex> lock(mtx_);
    return file_paths_.empty();
}

void FilesQueue::PushToQueue(std::string path_to_file)
{
    std::lock_guard<std::mutex> lock(mtx_);
    file_paths_.push(path_to_file);
}

std::string FilesQueue::PopFromQueue()
{
    std::unique_lock<std::mutex> lock(mtx_);
    std::string temp;
    if (!file_paths_.empty())
    {
        temp = file_paths_.front();
        file_paths_.pop();
    }
    return temp;
}

}
