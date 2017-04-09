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
    FilesQueue path_to_files;
    bool searching_files;
    unsigned long int work_time;
    std::atomic<unsigned long int> proceeded_files;
    std::atomic<unsigned long int> count_of_lines;
    std::atomic<unsigned long int> count_of_comment_lines;
    std::atomic<unsigned long int> count_of_blank_lines;
};

void SearchFiles(boost::filesystem::path path_to_root_folder, Info& info);
void ParseFile(Info& info);
void RecordResults(const Info& info, std::ostream& os);

}
