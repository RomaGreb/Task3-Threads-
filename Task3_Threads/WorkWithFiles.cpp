#include"WorkWithFiles.h"

namespace Threads
{

Info::Info(): path_to_files(),searching_files(true),proceeded_files(0)
  ,count_of_lines(0),count_of_comment_lines(0),count_of_blank_lines(0)
{
}

void SearchFiles(boost::filesystem::path path_to_root_folder, Info& info)
{
    std::string temp_path = "";
    boost::filesystem::recursive_directory_iterator root_folder(path_to_root_folder);
    boost::filesystem::recursive_directory_iterator end_folder;
    while(root_folder != end_folder)
    {
        std::string ext_files = root_folder->path().extension().string();
        temp_path = root_folder->path().string();
        if((ext_files == ".cpp")||(ext_files == ".c")||(ext_files == ".hpp")||(ext_files == ".h"))
        {
            info.path_to_files.PushToQueue(temp_path);
        }
        ++root_folder;
    }
    info.searching_files = false;
}

void ParseFile(Info& info)
{
    while(!info.path_to_files.QueueIsEmpty() || info.searching_files)
    {
        std::string copy_file_path = info.path_to_files.PopFromQueue();
        if(copy_file_path.empty())
            continue;
        ++info.proceeded_files;
        std::ifstream parse_file;
        parse_file.open(copy_file_path);
        if(!parse_file.is_open())
        {
            std::cout << "Cannot open file: " << copy_file_path << std::endl;
            continue;
        }
        std::string line = "";
        bool multi_line_comment = false;
        while(std::getline(parse_file,line))
        {
            ++info.count_of_lines;
            line.erase(std::remove_if(line.begin(),line.end(),isspace), line.end());
            if(line.empty())
                ++info.count_of_blank_lines;
            else if(line.substr(0,2) == "//")
                ++info.count_of_comment_lines;
            else if(line.substr(0,2)== "/*")
            {
                multi_line_comment = true;
                ++info.count_of_comment_lines;
            }
            else if(multi_line_comment)
            {
                ++info.count_of_comment_lines;
                if(std::string::npos != line.find("*/"))
                    multi_line_comment = false;
            }
        }
        parse_file.close();
    }
}

void RecordResults(const Info& info, std::ostream& os)
{
    os << "Proceeded files: " << '\t' << info.proceeded_files << std::endl;
    os << "Count of lines: " << '\t' <<info.count_of_lines << std::endl;
    os << "Count of comment lines: " << info.count_of_comment_lines << std::endl;
    os << "Count of blank lines: " << '\t' << info.count_of_blank_lines << std::endl;
    os << "Count of code lines: " << '\t' << info.count_of_lines - info.count_of_comment_lines - info.count_of_blank_lines << std::endl;
    os << "Working time: " << "\t\t" << info.work_time << " ms" << std::endl;
}

}
