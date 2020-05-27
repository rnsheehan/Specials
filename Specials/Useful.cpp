#ifndef ATTACH_H
#include "Attach.h"
#endif

std::string useful_funcs::TheTime()
{
	// Implementation of a function returning the current time as a string
	// This is just a neater way of ensuring that the time can be correctly and easily accessed
	// without being hassled about whether or not you've remembered to use non-deprecated versions 
	// of certain functions
	// R. Sheehan 4 - 7 - 2011
	
	const int N=30;	
	char time_str[N];	
	size_t bytes=( N*sizeof(char) );
	
	time_t rawtime;
	
	struct tm timeinfo;
	struct tm *timeinfo_ptr;
	
	timeinfo_ptr=&timeinfo;
	
	// Get current time information
	time(&rawtime);
	
	localtime_s(timeinfo_ptr,&rawtime);
	
	asctime_s(time_str,bytes,timeinfo_ptr);
	
	// Deprecated calls
	//timeinfo=localtime(&rawtime);
	//asctime(timeinfo);
	
	std::string the_time;
	the_time.append(time_str);
	
	return the_time;
}

void useful_funcs::exit_failure_output(std::string reason)
{
	// Code that creates a file and writes a reason in it why the program crashed
	// If it is called of course
	// Call before using the exit(EXIT_FAILURE) command

	// This function outputs to a file an explanation of why the program exited with an EXIT_FAILURE
	// R. Sheehan 17 - 5 - 2011
	
	// Get current time information
	std::string time = TheTime();

	std::ofstream write; // open file for writing
	
	write.open("Exit_Failure_Explanation.txt",std::ios_base::out|std::ios_base::trunc);
	
	//if(!write){
	//	std::cout<<"You're not going to see this statement\n";
	//	std::cout<<"\n";
	//}
	//else{
	//	//printf ( "Current local time and date: %s", asctime (timeinfo) );
	//	write<<"Program Exit Explanation\n\n";
	//	write<<"Error occurred "<<time<<"\n";
	//	write<<reason<<"\n";
	//	write.close();
	//}

	if( write.is_open() ){
		
		write<<"Program Exit Explanation\n\n";
		write<<"Error occurred: "<<time<<"\n";
		write<<reason<<"\n";

		write.close();
	}
}

void useful_funcs::set_directory(std::string &dir_name, bool &dir_set)
{
	// Set the current working directory
	// _chdir return a value of 0 if successful. 
	// A return value of �1 indicates failure. If the specified path could not be found, errno is set to ENOENT. 
	// If dirname is NULL, the invalid parameter handler is invoked
	// R. Sheehan 6 - 8 - 2012
	
	if(_chdir( dir_name.c_str() ) ){
		switch (errno){
			case ENOENT:
				//printf( "Unable to locate the directory: %s\n", dir_name );
				std::cout<<"Unable to locate the directory: "<<dir_name<<"\n";
				break;
			case EINVAL:
				std::cout<<"Invalid buffer.\n";
				break;
			default:
				std::cout<<"Unknown error.\n";
		}
		
		dir_set = false; 
	}
	else{
		
		//cout<<"Directory has been changed\n"; 

		dir_set = true; 
	}
}

double useful_funcs::poly(double x, double *b, int m)
{
	// This evaluates the polynomial of degree m at the point x
	// The coefficients of the polynomial are stored in the vector b
	// Polynomial of degree m is represented numerically as a stored array of coefficients
	// b[j] with j=0..m, so array has size m with b[0] representing the constant term
	// It is assumed that evaluated polynomial takes the form
	// p = b[0] + b[1]*x + b[2]*x^{2} + b[3]*x^{3} + ... b[m]*x^{m}
	
	double p;

	p = b[m]; // initialise the value of p

	// loop over the remaining coefficients
	for(int j=m-1;j>=0;j--){ // For one-offset arrays replace j>=0 by j>0

		p = p*x + b[j];
	}

	return p;
}