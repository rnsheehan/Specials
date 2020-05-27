#ifndef USEFUL_H
#define USEFUL_H

// Library of functions that are very useful
// R. Sheehan 4 - 7 - 2011

namespace useful_funcs{
	
	std::string TheTime();

	void exit_failure_output(std::string reason);

	void set_directory(std::string &dir_name, bool &dir_set);

	double poly(double x, double *b, int m); 

}

#endif