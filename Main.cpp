#include <iostream>
#include <boost/filesystem.hpp>

#include "TextSearcherMulticore/TextSearcherMulticore.h"

int main(int argc, char* argv[])
{
    
    if (argc < 2)
    {
        std::cout << "Usage: TextSearcher path\n";
        return 1;
    }

    std::string path(argv[1]);

    try
    {
        TextSearcherMulticore tsm(path);
        tsm.Find("kek");

    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << '\n';
    }


    return 0;
}