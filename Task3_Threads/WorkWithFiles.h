#pragma once
#include<iostream>
#include<atomic>
#include<boost/filesystem.hpp>
#include"FilesQueue.h"

namespace Threads
{

class Info
{
public:
    Info();
    void SearchFiles(boost::filesystem::path path_to_root_folder);
    void ParseFile();
    void RecordResults(std::ostream& os);
    unsigned long int work_time;

private:
    FilesQueue path_to_files;
    bool searching_files;
    std::atomic<unsigned long int> proceeded_files;
    std::atomic<unsigned long int> count_of_lines;
    std::atomic<unsigned long int> count_of_comment_lines;
    std::atomic<unsigned long int> count_of_blank_lines;
};

}
