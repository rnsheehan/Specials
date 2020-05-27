#ifndef ATTACH_H
#include "Attach.h"
#endif

void Struve_Test(); 
void Airy_Test(); 
void Gamm_Test(); 

int main(int argc, char *argv[])
{
	Gamm_Test(); 

	//Airy_Test(); 

	std::cout<<"Press enter to close\n"; 
	std::cin.get(); 

	return 0; 

}

void Airy_Test()
{
	// Values for positive and negative arguments match those tabulated in Abramowitz and Stegun, Table 10.11, pg 475


	double x, delta_x, stop_x;
	double ai, bi, aip, bip; 

	x = 0.0; 

	delta_x = 0.1; 

	stop_x = 5.05; 

	std::cout << "Values for positive argument\n"; 
	while(x < stop_x){
		special::airy(x, &ai, &bi, &aip, &bip); 
		std::cout<<x<<" , "<<ai<<" , "<<aip << " , " << bi << " , " << bip <<"\n";
		x+=delta_x; 
	}

	x = 0.0;

	std::cout << "\nValues for negative argument\n";
	while (x > -stop_x) {
		special::airy(x, &ai, &bi, &aip, &bip);
		std::cout << x << " , " << ai << " , " << aip << " , " << bi << " , " << bip << "\n";
		x -= delta_x;
	}

}

void Struve_Test()
{
	double x, delta_x, stop_x;

	x = 0.0; 

	delta_x = 0.1; 

	stop_x = 5.05; 

	while(x < stop_x){
		std::cout<<x<<" , "<<special::struveh0(x)<<" , "<<special::struveh1(x)<<"\n"; 
		x+=delta_x; 
	}
}

void Gamm_Test()
{
	// output some values of the gamma related functions

	double x = 2.0; 
	double a = 0.25; 

	std::cout<<probability::gammln(x)<<"\n";
	std::cout<<probability::gammp(a,x)<<"\n";
	std::cout<<probability::gammq(a,x)<<"\n";

	double galn, gaser, gacf;

	probability::gser(&gaser, a, x, &galn);

	std::cout<<gaser<<"\n"; 
	std::cout<<galn<<"\n"; 

	probability::gcf(&gacf, a, x, &galn);

	std::cout<<gacf<<"\n"; 
	std::cout<<galn<<"\n"; 

	std::cout<< "\n";
	std::cout << "Bico(10, 5) = " << probability::bico(10, 5) << "\n"; 
	std::cout << "Bico(101, 101) = " << probability::bico(101, 101) << "\n";
	std::cout << "Bico(54, 101) = " << probability::bico(54, 101) << "\n";
	std::cout << "Bico(33, 25) = " << std::setprecision(10) << probability::bico(33, 25) << "\n";
	std::cout << "Bico(23, 11) = " << std::setprecision(10) << probability::bico(23, 11) << "\n";
	std::cout << "Bico(169, 40) = " << std::setprecision(10) << probability::bico(169, 40) << "\n";
	std::cout << "Bico(169, 0) = " << std::setprecision(10) << probability::bico(169, 0) << "\n";
	std::cout << "Bico(169, 1) = " << std::setprecision(10) << probability::bico(169, 1) << "\n";
	//std::cout << "Bico(33, -25) = " << std::setprecision(10) << probability::bico(33, -25) << "\n";

	std::cout << "\n"; 
	int n = 40; 
	for (int i = 0; i <= n; i+=2) {
		std::cout << "Berno(" << i << ") = " << probability::berno(i) << "\n"; 
	}

	// "With the help of this table, it took me less than half of a quarter of an hour
	// to find that the tenth power of the first 1000 numbers being added together will
	// yield the sum  91,409,924,241,424,243,424,241,924,242,500"
	// Jacob Bernoulli, Summae Potestatum, 1713
	// Today we can do a little better

	std::cout << "\n"; 
	std::cout << "S_{1}(50) = " << probability::faulhaber(50, 1) << "\n"; 
	std::cout << "S_{2}(50) = " << probability::faulhaber(50, 2) << "\n"; 
	std::cout << "S_{3}(50) = " << probability::faulhaber(50, 3) << "\n"; 
	std::cout << "S_{4}(50) = " << probability::faulhaber(50, 4) << "\n"; 
	std::cout << "S_{5}(50) = " << probability::faulhaber(50, 5) << "\n"; 
	std::cout << "\n"; 
	std::cout << "S_{1}(310) = " << probability::faulhaber(310, 1) << "\n"; 
	std::cout << "S_{2}(310) = " << probability::faulhaber(310, 2) << "\n"; 
	std::cout << "S_{3}(310) = " << probability::faulhaber(310, 3) << "\n"; 
	std::cout << "S_{4}(310) = " << probability::faulhaber(310, 4) << "\n"; 
	std::cout << "S_{5}(310) = " << probability::faulhaber(310, 5) << "\n"; 
	std::cout << "\n";
	std::cout << "S_{1}(1000) = " << probability::faulhaber(1000, 1) << "\n";
	std::cout << "S_{2}(1000) = " << probability::faulhaber(1000, 2) << "\n";
	std::cout << "S_{3}(1000) = " << probability::faulhaber(1000, 3) << "\n";
	std::cout << "S_{4}(1000) = " << probability::faulhaber(1000, 4) << "\n";
	std::cout << "S_{5}(1000) = " << probability::faulhaber(1000, 5) << "\n";
	std::cout << "\n";
	std::cout << "S_{10}(1000) = " << probability::faulhaber(1000, 10) << "\n";
	std::cout << "S_{10}(10000) = " << probability::faulhaber(10000, 10) << "\n";
	std::cout << "S_{10}(100000) = " << probability::faulhaber(100000, 10) << "\n";
	std::cout << "S_{10}(1000000) = " << probability::faulhaber(1000000, 10) << "\n";
}