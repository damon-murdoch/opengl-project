#include "files.h"

std::string get_base_dir(const std::string  &filepath){
	if(filepath.find_last_of("/\\") != std::string::npos)
		return filepath.substr(0,filepath.find_last_of("/\\"));
	return "";
}

int file_exists(const std::string &abs_filename) {
	int ret;
	FILE *fp = fopen(abs_filename.c_str(), "rb");
	if (fp) {
		ret = 1;
		fclose(fp);
	} else {
		ret = 0;
	}
	return ret;
}