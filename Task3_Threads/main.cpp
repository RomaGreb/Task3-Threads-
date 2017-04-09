#include<thread>
#include<chrono>
#include<vector>
#include"WorkWithFiles.h"

using namespace Threads;

int main()
{
    std::cout << "start" << std::endl;
    boost::filesystem::path root_folder = R"(C:\Qt\boost_1_63_0\boost)";
    std::cout << root_folder << std::endl;
    unsigned int maximum_threads = std::thread::hardware_concurrency();
    std::cout << "Max threads " << maximum_threads << std::endl;
    std::vector<std::thread> num_of_threads;
    Info info;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::cout << "clock started" << std::endl;
    std::thread search_files(SearchFiles,root_folder,std::reference_wrapper<Info>(info));
    std::cout << "thread created" << std::endl;


    for(unsigned int i = 0; i < (maximum_threads/2+0.5); ++i)
        num_of_threads.emplace_back(std::thread(ParseFile,std::ref(info)));

    std::cout << "vector filled " << num_of_threads.size() << std::endl;

    if(search_files.joinable())
        search_files.join();
    else
        std::cout << "Cannot join thread" << std::endl;

    std::cout << "search thread joined" << std::endl;


    for(unsigned int j = 0; j < num_of_threads.size(); ++j)
    {
        if(num_of_threads[j].joinable())
            num_of_threads[j].join();
        else
            std::cout << "Cannot join parese threads";
    }

    std::cout << "parse threads joined" << std::endl;

    std::chrono::steady_clock::time_point finish = std::chrono::steady_clock::now();

    std::cout << "clock finished" << std::endl;

    info.work_time = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count() / CLOCKS_PER_SEC;

    std::ofstream results;
    results.open("E:\\Results.txt");
    if(!results.is_open())
    {
        std::cout << "Error! Cannot open file for writting" << std::endl;
        return -1;
    }
    else
    {
        RecordResults(info, results);
        results.close();
    }

    std::cout << "program finished" << std::endl;
    return 0;
}

