#include "TextSearcherMulticore.h"

std::mutex mtx;

TextSearcherMulticore::TextSearcherMulticore(const std::string& path)
{
    try
    {
        if (fs::exists(path))
        {
            path_ = path;
        }
        else
        {
            throw std::runtime_error(path + " does not exist");
        }
    }
    catch (const std::exception& ex)
    {
        throw;
    }
}


void TextSearcherMulticore::Find(const std::string& text)
{
    if (fs::is_regular_file(path_))
    {
        FindImpl(fs::directory_entry(path_), text);
    }
    else if (fs::is_directory(path_))
    {
        std::cout << path_ << " is a directory containing:\n";
        std::vector<std::thread> threads;
        
        for (fs::directory_entry& x : fs::directory_iterator(path_))
        {
            if (x.path().extension() == ".txt")
            {
                threads.push_back(std::thread(&TextSearcherMulticore::FindImpl, x, text));
            }
        }
        std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    }
    else
    {
        std::cout << path_ << " exists, but is not a regular file or directory\n";
    }
}


void TextSearcherMulticore::FindImpl(const fs::directory_entry& file, const std::string& text)
{
    std::ifstream fileBuf(file.path().c_str());
    fileBuf >> std::noskipws;

    std::string str((std::istream_iterator<char>(fileBuf)), std::istream_iterator<char>());
    auto result = boost::algorithm::knuth_morris_pratt_search(str.begin(), str.end(), text);

    std::lock_guard<std::mutex> lock(mtx);
    std::cout << file.path() << std::endl;
    std::cout << "contain " <<  (result.first != result.second) << std::endl;
}
