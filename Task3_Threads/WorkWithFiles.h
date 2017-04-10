#pragma once
#include"FilesQueue.h"
#include<iostream>
#include<atomic>
#include<boost/filesystem.hpp>


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
    FilesQueue path_to_files_;
    bool is_searching_files_;
    std::atomic<unsigned long int> proceeded_files_;
    std::atomic<unsigned long int> count_of_lines_;
    std::atomic<unsigned long int> count_of_comment_lines_;
    std::atomic<unsigned long int> count_of_blank_lines_;
};

}
