#ifndef _INCLUDE_FILES
#define _INCLUDE_FILES

#include "common.h"

#include <string>

std::string get_base_dir(const std::string  &filepath);

int file_exists(const std::string &abs_filename);

#endif // _INCLUDE_FILES