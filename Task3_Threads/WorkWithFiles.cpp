#include"WorkWithFiles.h"

namespace Threads
{

Info::Info()
    : path_to_files_(),is_searching_files_(true),proceeded_files_(0)
    ,count_of_lines_(0),count_of_comment_lines_(0),count_of_blank_lines_(0) {}

void Info::SearchFiles(boost::filesystem::path path_to_root_folder)
{
    std::string temp_path = "";
    boost::filesystem::recursive_directory_iterator root_folder(path_to_root_folder);
    boost::filesystem::recursive_directory_iterator end_folder;
    while(root_folder != end_folder)
    {
        std::string ext_files = root_folder->path().extension().string();
        temp_path = root_folder->path().string();
        if ((ext_files == ".cpp")||(ext_files == ".c")||(ext_files == ".hpp")||(ext_files == ".h"))
        {
            path_to_files_.PushToQueue(temp_path);
        }
        ++root_folder;
    }
    is_searching_files_ = false;
}

void Info::ParseFile()
{
    while(!path_to_files_.IsQueueEmpty() || is_searching_files_)
    {
        std::string copy_file_path = path_to_files_.PopFromQueue();
        if (copy_file_path.empty())
            continue;
        ++proceeded_files_;
        std::ifstream parse_file;
        parse_file.open(copy_file_path);
        if (!parse_file.is_open())
        {
            std::cout << "Cannot open file: " << copy_file_path << std::endl;
            continue;
        }
        std::string line = "";
        bool is_multi_line_comment = false;
        while(std::getline(parse_file,line))
        {
            ++count_of_lines_;
            line.erase(std::remove_if(line.begin(),line.end(),isspace), line.end());
            if(line.empty())
                ++count_of_blank_lines_;
            else if (line.substr(0,2) == "//")
                ++count_of_comment_lines_;
            else if (line.substr(0,2)== "/*")
            {
                is_multi_line_comment = true;
                ++count_of_comment_lines_;
            }
            else if (is_multi_line_comment)
            {
                ++count_of_comment_lines_;
                if (std::string::npos != line.find("*/"))
                    is_multi_line_comment = false;
            }
        }
        parse_file.close();
    }
}

void Info::RecordResults(std::ostream& os)
{
    os << "Proceeded files: " << '\t' << proceeded_files_ << std::endl;
    os << "Count of lines: " << '\t' <<count_of_lines_ << std::endl;
    os << "Count of comment lines: " << count_of_comment_lines_ << std::endl;
    os << "Count of blank lines: " << '\t' << count_of_blank_lines_ << std::endl;
    os << "Count of code lines: " << '\t'
    << count_of_lines_ - count_of_comment_lines_ - count_of_blank_lines_ << std::endl;
    os << "Working time: " << "\t\t" << work_time << " ms" << std::endl;
}

}
