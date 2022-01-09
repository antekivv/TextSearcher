#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <boost/filesystem.hpp>
#include <thread>
#include <mutex>

#include <boost/algorithm/searching/knuth_morris_pratt.hpp>


namespace fs = boost::filesystem;

class TextSearcherMulticore
{
public:
	explicit TextSearcherMulticore(const std::string& path);

	void Find(const std::string& text);
private:
	static void FindImpl(const fs::directory_entry& file, const std::string& text);

private:
	fs::path path_;
};