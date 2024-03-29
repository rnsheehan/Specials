#ifndef ATTACH_H
#include "Attach.h"
#endif

// Definition of the special functions declared in the namespace
// R. Sheehan 23 - 11 - 2015

void special::two_F_one(double a, double b, double c, double x, double &F, double &dF)
{
	// Implementation of the hypergeometric function, {2}_F_{1}(a, b, c; z)
	// This series is valid for |x| < 1, with rapid convergence when |x| <= 1/2
	// Series is divergent when (c - a - b) <= -1
	// Series is absolutely convergent when (c - a - b) > 0
	// Series is conditionally convergent when -1 < (c - a - b) < 0 and x = 1 is excluded
	// See Abramowitz and Stegun, Ch. 15

	// This implementation is based on that given in NRinC, sect. 6.13
	// The function returns the value of F and its derivative at some point x
	// An implementation involving std::complex arguments is also possible
	// R. Sheehan 15 - 4 - 2014

	if(fabs(x) < 1.0){

		int i, nterms; 
		double fac, temp, aa, bb, cc;

		F = dF = 0.0; 
		fac = 1.0; temp = fac;
		aa = a; bb = b; cc = c; 

		nterms = 1000; // compute the partial sum out to nterms

		for(i=1; i<=nterms; i++){
		
			fac *= ((aa*bb)/cc); 
		
			dF += fac; 
		
			fac *= ( ( 1.0 / ( static_cast<double>(i) ) )*x);
		
			F = temp + fac; 
		
			if(F == temp){
				return; 
			}
		
			temp = F; 

			aa += 1.0; bb += 1.0; cc += 1.0; 
		}

	}
	else{
		
		F = dF = 0.0; 

	}
}

double special::bessj0(double x)
{
	//Return the Bessel Function J0(x) for all real x
	double z,ax,xx,y,ans,ans1,ans2;

	if((ax=fabs(x))<8.0){
		y=template_funcs::DSQR(x);
		ans1=57568490574.0+y*(-13362590354.0+y*(651619640.7+
			y*(-11214424.18+y*(77392.33017+y*(-184.9052456)))));
		ans2=57568490411.0+y*(1029533985.0+y*(9494680.718+
			y*(59272.64853+y*(267.8532712+y))));
		ans=ans1/ans2;
	}
	else{
		z=8.0/ax;
		y=template_funcs::DSQR(z);
		xx=ax-0.785398164;
		ans1=1.0+y*(-0.1098628627e-2+y*(0.2734510407e-4+
			y*(-0.2073370639e-5+y*0.2093887211e-6)));
		ans2=-0.1562499995e-1+y*(0.1430488765e-3+
			y*(-0.6911147651e-5+y*(0.7621095161e-6-y*0.934945152e-7)));
		ans=sqrt(0.636619772/ax)*(cos(xx)*ans1-z*sin(xx)*ans2);
	}
	return ans;
}

double special::bessj1(double x)
{
	//Returns the Bessel function J1(x) for all real x
	double ax,z,xx,y,ans,ans1,ans2;

	if((ax=fabs(x))<8.0){
		y=template_funcs::DSQR(x);
		ans1=x*(72362614232.0+y*(-7895059235.0+y*(242396853.1
			+y*(-2972611.439+y*(15704.48260+y*(-30.16036606))))));
		ans2=144725228442.0+y*(2300535178.0+y*(18583304.74
			+y*(99447.43394+y*(376.9991397+y))));
		ans=ans1/ans2;
	}
	else{
		z=8.0/ax;
		y=template_funcs::DSQR(z);
		xx=ax-2.356194491;
		ans1=1.0+y*(0.183105e-2+y*(-0.3516396496e-4
			+y*(0.245752017e-5+y*(-0.240337019e-6))));
		ans2=0.04687499995+y*(-0.2002690873e-3
			+y*(0.8449199096e-5+y*(-0.88228987e-6
			+y*0.105787412e-6)));
		ans=sqrt(0.636619772/ax)*(cos(xx)*ans1-z*sin(xx)*ans2);
		if(x<0.0) ans=-ans;
	}
	return ans;
}

double special::bessj(int n,double x)
{
	//Returns te Bessel function Jn(x) for all real x and n >= 2
	int j,jsum,m;
	double ax,bj,bjm,bjp,sum,tox,ans;

	static const double ACC=40.0;
	static const double BIGNO=1e10;
	static const double BIGNI=1.0e-10;

	if(n<2){
		std::cerr<<"Index n less than 2 in bessj\n";	
	}
	ax=fabs(x);
	if(ax==0.0){
		return 0.0;	
	}
	else if(ax>static_cast<double>(n)){
		//Upwards recurrence from J0 and J1
		tox=2.0/ax;
		bjm=bessj0(ax);
		bj=bessj1(ax);
		for(j=1;j<n;j++){
			bjp=j*tox*bj-bjm;
			bjm=bj;
			bj=bjp;
		}
		ans=bj;
	}
	else{
		//Downwards recurrence from an even m here computed
		tox=2.0/ax;
		m=2*((n+static_cast<int>(sqrt(ACC*n)))/2);
		jsum=0;
		bjp=ans=sum=0.0;
		bj=1.0;
		for(j=m;j>0;j--){
			bjm=j*tox*bj-bjp;
			bjp=bj;
			bj=bjm;
			if(fabs(bj)>BIGNO){
				bj*=BIGNI;
				bjp*=BIGNI;
				ans*=BIGNI;
				sum*=BIGNI;
			}
			if(jsum) sum+=bj;
			jsum=!jsum;
			if(j==n) ans=bjp;
		}
		sum=2.0*sum-bj;
		ans/=sum;
	}
	return x<0.0 && (n&1) ? -ans:ans; 
}

double special::bessel_J(int n,double x)
{
	if(n==0){
		return bessj0(x);	
	}
	else if(n==1){
		return bessj1(x);	
	}
	else{
		return bessj(n,x);	
	}
}

double special::bessy0(double x)
{
	//Returns the Bessel Function Y0(x) for real positive values of x
	double z,xx,y,ans,ans1,ans2;

	if(x<8.0){
		y=template_funcs::DSQR(x);
		ans1=-2957821389.0+y*(7062834065.0+y*(-512359803.6+
			y*(10879881.29+y*(-86327.92757+y*228.4622733))));
		ans2=40076544269.0+y*(745249964.8+y*(7189466.438+
			y*(47447.26470+y*(226.1030244+y))));
		ans=(ans1/ans2)+0.636619772*bessj0(x)*log(x);
	}
	else{
		z=8.0/x;
		y=template_funcs::DSQR(z);
		xx=x-0.785398164;
		ans1=1.0+y*(-0.1098628627e-2+y*(0.2734510407e-4+
			y*(-0.2073370639e-5+y*0.2093887211e-6)));
		ans2=-0.1562499995e-1+y*(0.1430488765e-3+
			y*(-0.6911147651e-5+y*(0.7621095161e-6+y*(-0.934945152e-7))));
		ans=sqrt(0.636619772/x)*(sin(xx)*ans1+z*cos(xx)*ans2);
	}
	return ans;
}

double special::bessy1(double x)
{
	//Returns the Bessel Function Y1(x) for real positive x
	double z,xx,y,ans,ans1,ans2;

	if(x<8.0){
		y=template_funcs::DSQR(x);
		ans1=x*(-0.4900604943e13+y*(0.1275274390e13
			+y*(-0.5153438139e11+y*(0.7349264551e9
			+y*(-0.4237922726e7+y*0.8511937935e4)))));
		ans2=0.2499580570e14+y*(0.424441966e12
			+y*(0.3733650367e10+y*(0.2245904002e8
			+y*(0.1020426050e6+y*(0.3549632885e3+y)))));
		ans=(ans1/ans2)+0.636619772*(bessj1(x)*log(x)-1.0/x);
	}
	else{
		z=8.0/x;
		y=template_funcs::DSQR(z);
		xx=x-2.356194491;
		ans1=1.0+y*(0.183105e-2+y*(-0.3516396496e-4
			+y*(0.245752017e-5+y*(-0.240337019e-6))));
		ans2=0.04687499995+y*(-0.2002690873e-3
			+y*(0.8449199096e-5+y*(-0.88228987e-6
			+y*0.105787412e-6)));
		ans=sqrt(0.636619772/x)*(sin(xx)*ans1+z*cos(xx)*ans2);
	}
	return ans;
}

double special::bessy(int n,double x)
{
	//Returns the Bessel Function Yn(x) for n >= 2
	int j;
	double by,bym,byp,tox;

	if(n<2){
		std::cerr<<"Index n less than 2 in bessy\n";
	}
	tox=2.0/x;
	by=bessy1(x);
	bym=bessy0(x);
	for(j=1;j<n;j++){
		byp=j*tox*by-bym;
		bym=by;
		by=byp;
	}
	return by;
}

double special::bessel_Y(int n,double x)
{
	if(n==0){
		return bessy0(x);
	}
	else if(n==1){
		return bessy1(x);
	}
	else{
		return bessy(n,x);
	}
}

double special::bessi0(double x)
{
	//Returns the modified Bessel Function I0(x) for any real x
	double ax,ans,y;

	if((ax=fabs(x))<3.75){
		y=x/3.75;
		y*=y;
		ans=1.0+y*(3.5156229+y*(3.0899424+y*(1.2067492
			+y*(0.2659732+y*(0.360768e-1+y*0.45813e-2)))));
	}
	else{
		y=3.75/ax;
		ans=(exp(ax)/sqrt(ax))*(0.39894228+y*(0.132859e-1
			+y*(0.225319e-2+y*(-0.157565e-2+y*(0.916281e-2
			+y*(-0.2057706e-1+y*(0.2635537e-1+y*(-0.1647633e-1
			+y*0.392377e-2))))))));
	}
	return ans;
}

double special::bessi1(double x)
{
	//Returns the modified Bessel Function I1(x) for any real x
	double ax,ans,y;
	if((ax=fabs(x))<3.75){
		y=x/3.75;
		y*=y;
		ans=ax*(0.5+y*(0.87890594+y*(0.51498869+y*(0.15084934
			+y*(0.2658733e-1+y*(0.301532e-2+y*0.32411e-3))))));
	}
	else{
		y=3.75/ax;
		ans=0.2282967e-1+y*(-0.2895312e-1+y*(0.1787654e-1
			-y*0.420059e-2));
		ans=0.39894228+y*(-0.3988024e-1+y*(-0.362018e-2
			+y*(0.163801e-2+y*(-0.1031555e-1+y*ans))));
		ans*=(exp(ax)/sqrt(ax));
	}
	return x<0.0?-ans:ans;
}

double special::bessi(int n,double x)
{
	//Returns the modified Bessel Function In(x) for n>=2 for any real x
	int j;
	double bi,bim,bip,tox,ans;

	static const double ACC=40.0;
	static const double BIGNO=1e10;
	static const double BIGNI=1.0e-10;

	if(n<2) std::cerr<<"Index n less than 2 in bessi\n";

	if(x==0.0){
		return 0.0;
	}
	else{
		tox=2.0/fabs(x);
		bip=ans=0.0;
		bi=1.0;
		for(j=2*(n+static_cast<int>(sqrt(ACC*n)));j>0;j--){
			bim=bip+j*tox*bi;
			bip=bi;
			bi=bim;
			if(fabs(bi)>BIGNO){
				ans*=BIGNI;
				bi *=BIGNI;
				bip*=BIGNI;
			}
			if(j==n) ans=bip;
		}
		ans*=bessi0(x)/bi;
		return x<0.0 && (n&1) ? -ans:ans;
	}
}

double special::bessel_I(int n,double x)
{
	if(n==0){
		return bessi0(x);
	}
	else if(n==1){
		return bessi1(x);
	}
	else{
		return bessi(n,x);
	}
}

double special::bessk0(double x)
{
	//Returns the modified Bessel function K0(x) for positive real x
	double y,ans;
	if(x<=2.0){
		y=template_funcs::DSQR(x)/4.0;
		ans=(-log(x/2.0)*bessi0(x))+(-0.57721566+y*(0.42278420
			+y*(0.23069756+y*(0.3488590e-1+y*(0.262698e-2
			+y*(0.10750e-3+y*0.74e-5))))));
	}
	else{
		y=2.0/x;
		ans=(exp(-x)/sqrt(x))*(1.25331414+y*(-0.7832358e-1
			+y*(0.2189568e-1+y*(-0.1062446e-1+y*(0.587872e-2
			+y*(-0.251540e-2+y*0.53208e-3))))));
	}
	return ans;
}

double special::bessk1(double x)
{
	//Returns the modified Bessel function K1(x) for real positive x	
	double y,ans;
	if(x<=2.0){
		y=x*x/4.0;
		ans=(log(x/2.0)*bessi1(x))+(1.0/x)*(1.0+y*(0.15443144
			+y*(-0.67278579+y*(-0.18156897+y*(-0.1919402e-1
			+y*(-0.110404e-2+y*(-0.4686e-4)))))));
	}
	else{
		y=2.0/x;
		ans=(exp(-x)/sqrt(x))*(1.25331414+y*(0.23498619
			+y*(-0.3655620e-1+y*(0.1504268e-1+y*(-0.780353e-2
			+y*(0.325614e-2+y*(-0.68245e-3)))))));
	}
	return ans;
}

double special::bessk(int n,double x)
{
	//Returns the modified Bessel function Kn(x) for n >=2
	int j;
	double bk,bkm,bkp,tox;

	if(n<2) std::cerr<<"Index n less than 2 in bessk\n";

	tox=2.0/x;
	bkm=bessk0(x);
	bk=bessk1(x);
	for(j=1;j<n;j++){
		bkp=bkm+j*tox*bk;
		bkm=bk;
		bk=bkp;
	}
	return bk;
}

double special::bessel_K(int n,double x)
{
	if(n==0){
		return bessk0(x);
	}
	else if(n==1){
		return bessk1(x);
	}
	else{
		return bessk(n,x);
	}
}

void special::bessjy(double x, double xnu, double *rj, double *ry, double *rjp, double *ryp)
{
	// Returns the Bessel functions J_{\nu}(x), Y_{\nu}(x) and their derivatives for x > 0 and \nu >= 0
	// J_{\nu}(x) is stored in rj
	// Y_{\nu}(x) is stored in ry
	// J_{\nu}'(x) is stored in rjp
	// Y_{\nu}'(x) is stored in ryp

	int i,isign,l,nl;
	double a,b,br,bi,c,cr,ci,d,del,del1,den,di,dlr,dli,dr,e,f,fact,fact2,
		fact3,ff,gam,gam1,gam2,gammi,gampl,h,p,pimu,pimu2,q,r,rjl,
		rjl1,rjmu,rjp1,rjpl,rjtemp,ry1,rymu,rymup,rytemp,sum,sum1,
		temp,w,x2,xi,xi2,xmu,xmu2;

	int MAXIT = 10000; 
	double XMIN = 2.0; 

	if (x <= 0.0 || xnu < 0.0) std::cerr<<"bad arguments in bessjy\n";
	nl=(x < XMIN ? (int)(xnu+0.5) : std::max(0,(int)(xnu-x+1.5)));
	xmu=xnu-nl;
	xmu2=xmu*xmu;
	xi=1.0/x;
	xi2=2.0*xi;
	w=xi2/PI;
	isign=1;
	h=xnu*xi;
	if (h < FPMIN) h=FPMIN;
	b=xi2*xnu;
	d=0.0;
	c=h;
	for (i=1;i<=MAXIT;i++) {
		b += xi2;
		d=b-d;
		if (fabs(d) < FPMIN) d=FPMIN;
		c=b-1.0/c;
		if (fabs(c) < FPMIN) c=FPMIN;
		d=1.0/d;
		del=c*d;
		h=del*h;
		if (d < 0.0) isign = -isign;
		if (fabs(del-1.0) < EPS) break;
	}
	if (i > MAXIT) std::cerr<<"x too large in bessjy; try asymptotic expansion\n";
	rjl=isign*FPMIN;
	rjpl=h*rjl;
	rjl1=rjl;
	rjp1=rjpl;
	fact=xnu*xi;
	for (l=nl;l>=1;l--) {
		rjtemp=fact*rjl+rjpl;
		fact -= xi;
		rjpl=fact*rjtemp-rjl;
		rjl=rjtemp;
	}
	if (rjl == 0.0) rjl=EPS;
	f=rjpl/rjl;
	if (x < XMIN) {
		x2=0.5*x;
		pimu=PI*xmu;
		fact = (fabs(pimu) < EPS ? 1.0 : pimu/sin(pimu));
		d = -log(x2);
		e=xmu*d;
		fact2 = (fabs(e) < EPS ? 1.0 : sinh(e)/e);
		beschb(xmu,&gam1,&gam2,&gampl,&gammi);
		ff=2.0/PI*fact*(gam1*cosh(e)+gam2*fact2*d);
		e=exp(e);
		p=e/(gampl*PI);
		q=1.0/(e*PI*gammi);
		pimu2=0.5*pimu;
		fact3 = (fabs(pimu2) < EPS ? 1.0 : sin(pimu2)/pimu2);
		r=PI*pimu2*fact3*fact3;
		c=1.0;
		d = -x2*x2;
		sum=ff+r*q;
		sum1=p;
		for (i=1;i<=MAXIT;i++) {
			ff=(i*ff+p+q)/(i*i-xmu2);
			c *= (d/i);
			p /= (i-xmu);
			q /= (i+xmu);
			del=c*(ff+r*q);
			sum += del;
			del1=c*p-i*del;
			sum1 += del1;
			if (fabs(del) < (1.0+fabs(sum))*EPS) break;
		}
		if (i > MAXIT) std::cerr<<"bessy series failed to converge\n";
		rymu = -sum;
		ry1 = -sum1*xi2;
		rymup=xmu*xi*rymu-ry1;
		rjmu=w/(rymup-f*rymu);
	} else {
		a=0.25-xmu2;
		p = -0.5*xi;
		q=1.0;
		br=2.0*x;
		bi=2.0;
		fact=a*xi/(p*p+q*q);
		cr=br+q*fact;
		ci=bi+p*fact;
		den=br*br+bi*bi;
		dr=br/den;
		di = -bi/den;
		dlr=cr*dr-ci*di;
		dli=cr*di+ci*dr;
		temp=p*dlr-q*dli;
		q=p*dli+q*dlr;
		p=temp;
		for (i=2;i<=MAXIT;i++) {
			a += 2*(i-1);
			bi += 2.0;
			dr=a*dr+br;
			di=a*di+bi;
			if (fabs(dr)+fabs(di) < FPMIN) dr=FPMIN;
			fact=a/(cr*cr+ci*ci);
			cr=br+cr*fact;
			ci=bi-ci*fact;
			if (fabs(cr)+fabs(ci) < FPMIN) cr=FPMIN;
			den=dr*dr+di*di;
			dr /= den;
			di /= -den;
			dlr=cr*dr-ci*di;
			dli=cr*di+ci*dr;
			temp=p*dlr-q*dli;
			q=p*dli+q*dlr;
			p=temp;
			if (fabs(dlr-1.0)+fabs(dli) < EPS) break;
		}
		if (i > MAXIT) std::cerr<<"cf2 failed in bessjy\n";
		gam=(p-f)/q;
		rjmu=sqrt(w/((p-f)*gam+q));
		rjmu=template_funcs::SIGN(rjmu,rjl);
		rymu=rjmu*gam;
		rymup=rymu*(p+q/gam);
		ry1=xmu*xi*rymu-rymup;
	}
	fact=rjmu/rjl;
	*rj=rjl1*fact;
	*rjp=rjp1*fact;
	for (i=1;i<=nl;i++) {
		rytemp=(xmu+i)*xi2*ry1-rymu;
		rymu=ry1;
		ry1=rytemp;
	}
	*ry=rymu;
	*ryp=xnu*xi*rymu-ry1;
}

void special::bessik(double x, double xnu, double *ri, double *rk, double *rip, double *rkp)
{
	// Returns the modified Bessel functions I_{\nu}(x), K_{\nu}(x) and their derivatives for x > 0 and \nu >= 0
	// I_{\nu}(x) is stored in ri
	// K_{\nu}(x) is stored in rk
	// I_{\nu}'(x) is stored in rip
	// K_{\nu}'(x) is stored in rkp
	
	int i,l,nl;
	double a,a1,b,c,d,del,del1,delh,dels,e,f,fact,fact2,ff,gam1,gam2,
		gammi,gampl,h,p,pimu,q,q1,q2,qnew,ril,ril1,rimu,rip1,ripl,
		ritemp,rk1,rkmu,rkmup,rktemp,s,sum,sum1,x2,xi,xi2,xmu,xmu2;

	int MAXIT = 10000; 
	double XMIN = 2.0;

	if (x <= 0.0 || xnu < 0.0) std::cerr<<"bad arguments in bessik\n";
	nl=(int)(xnu+0.5);
	xmu=xnu-nl;
	xmu2=xmu*xmu;
	xi=1.0/x;
	xi2=2.0*xi;
	h=xnu*xi;
	if (h < FPMIN) h=FPMIN;
	b=xi2*xnu;
	d=0.0;
	c=h;
	for (i=1;i<=MAXIT;i++) {
		b += xi2;
		d=1.0/(b+d);
		c=b+1.0/c;
		del=c*d;
		h=del*h;
		if (fabs(del-1.0) < EPS) break;
	}
	if (i > MAXIT) std::cerr<<"x too large in bessik; try asymptotic expansion\n";
	ril=FPMIN;
	ripl=h*ril;
	ril1=ril;
	rip1=ripl;
	fact=xnu*xi;
	for (l=nl;l>=1;l--) {
		ritemp=fact*ril+ripl;
		fact -= xi;
		ripl=fact*ritemp+ril;
		ril=ritemp;
	}
	f=ripl/ril;
	if (x < XMIN) {
		x2=0.5*x;
		pimu=PI*xmu;
		fact = (fabs(pimu) < EPS ? 1.0 : pimu/sin(pimu));
		d = -log(x2);
		e=xmu*d;
		fact2 = (fabs(e) < EPS ? 1.0 : sinh(e)/e);
		beschb(xmu,&gam1,&gam2,&gampl,&gammi);
		ff=fact*(gam1*cosh(e)+gam2*fact2*d);
		sum=ff;
		e=exp(e);
		p=0.5*e/gampl;
		q=0.5/(e*gammi);
		c=1.0;
		d=x2*x2;
		sum1=p;
		for (i=1;i<=MAXIT;i++) {
			ff=(i*ff+p+q)/(i*i-xmu2);
			c *= (d/i);
			p /= (i-xmu);
			q /= (i+xmu);
			del=c*ff;
			sum += del;
			del1=c*(p-i*ff);
			sum1 += del1;
			if (fabs(del) < fabs(sum)*EPS) break;
		}
		if (i > MAXIT) std::cerr<<"bessk series failed to converge\n";
		rkmu=sum;
		rk1=sum1*xi2;
	} else {
		b=2.0*(1.0+x);
		d=1.0/b;
		h=delh=d;
		q1=0.0;
		q2=1.0;
		a1=0.25-xmu2;
		q=c=a1;
		a = -a1;
		s=1.0+q*delh;
		for (i=2;i<=MAXIT;i++) {
			a -= 2*(i-1);
			c = -a*c/i;
			qnew=(q1-b*q2)/a;
			q1=q2;
			q2=qnew;
			q += c*qnew;
			b += 2.0;
			d=1.0/(b+a*d);
			delh=(b*d-1.0)*delh;
			h += delh;
			dels=q*delh;
			s += dels;
			if (fabs(dels/s) < EPS) break;
		}
		if (i > MAXIT) std::cerr<<"bessik: failure to converge in cf2\n";
		h=a1*h;
		rkmu=sqrt(PI/(2.0*x))*exp(-x)/s;
		rk1=rkmu*(xmu+x+0.5-h)*xi;
	}
	rkmup=xmu*xi*rkmu-rk1;
	rimu=xi/(f*rkmu-rkmup);
	*ri=(rimu*ril1)/ril;
	*rip=(rimu*rip1)/ril;
	for (i=1;i<=nl;i++) {
		rktemp=(xmu+i)*xi2*rk1+rkmu;
		rkmu=rk1;
		rk1=rktemp;
	}
	*rk=rkmu;
	*rkp=xnu*xi*rkmu-rk1;
}

void special::beschb(double x, double *gam1, double *gam2, double *gampl, double *gammi)
{
	// Computes \Gamma_{1} and \Gamma_{2} by Chebyshev expansion for |x| <= 1/2
	// Returns 1/\Gamma(1+x) and 1/\Gamma(1-x)
	// This function is used to compute Bessel functions of non-integer order
	
	double xx;
	static double c1[] = {
		-1.142022680371172e0,6.516511267076e-3,
		3.08709017308e-4,-3.470626964e-6,6.943764e-9,
		3.6780e-11,-1.36e-13};
	static double c2[] = {
		1.843740587300906e0,-0.076852840844786e0,
		1.271927136655e-3,-4.971736704e-6,-3.3126120e-8,
		2.42310e-10,-1.70e-13,-1.0e-15};

	int NUSE1 = 7; 
	int NUSE2 = 8; 

	xx=8.0*x*x-1.0;
	*gam1=cheb_appr::chebev(-1.0,1.0,c1,NUSE1,xx);
	*gam2=cheb_appr::chebev(-1.0,1.0,c2,NUSE2,xx);
	*gampl= *gam2-x*(*gam1);
	*gammi= *gam2+x*(*gam1);
}

void special::sphbes(int n, double x, double *sj, double *sy, double *sjp, double *syp)
{
	// Spherical Bessel functions j_{n}(x), y_{n}(x) and their derivatives at integer order
	// j_{n}(x) is stored in sj
	// y_{n}(x) is stored in sy
	// j_{n}'(x) is stored in sjp
	// y_{n}'(x) is stored in syp

	double factor,order,rj,rjp,ry,ryp;
	double RTPIO2 = sqrt(PI_2); 

	if (n < 0 || x <= 0.0) std::cerr<<"bad arguments in sphbes\n";
	order=n+0.5;
	bessjy(x,order,&rj,&ry,&rjp,&ryp);
	factor=RTPIO2/sqrt(x);
	*sj=factor*rj;
	*sy=factor*ry;
	*sjp=factor*rjp-(*sj)/(2.0*x);
	*syp=factor*ryp-(*sy)/(2.0*x);
}

double special::struveh0(double x)
{
	// Polynomial approximation for the Struve function H_{0}(x)
	// On 0 <= x <= 3, error is O(10^{-8})
	// On x >= 3, error is O(10^{-9})
	// H_{0}(x) is odd => H_{0}(x) = -H_{0}(-x)
	// For details of polynomial approximation see J. N. Newman, Math. Comp., 43 (168), 1984

	double ax, ans, y, ysqr; 

	ax = fabs(x); 

	if(ax >= 0.0 && ax <= 3.0){
		// 0 <= x <= 3

		y = ax/3.0; ysqr = template_funcs::DSQR(y); 
		
		ans = y * ( 1.909859164 + ysqr * ( -1.909855001 + ysqr * ( 0.687514637 + ysqr * ( -0.126164557 + ysqr * ( 0.013828813 - 0.000876918*ysqr ) ) ) ) ); 
	}
	else{
		// x >= 3
		double Nx, Dx; 

		y = 3.0 / ax; ysqr = template_funcs::DSQR(y);

		Nx = 2.0 * (0.99999906 + ysqr * (4.7722892 + ysqr * ( 3.85542044 + 0.3230360 * ysqr ) ) ); 
		Dx = (PI * ax) * (1.0 + ysqr * ( 4.88331068 + ysqr * ( 4.28957333 + 0.52120508 * ysqr) ) ); 

		ans = Nx/Dx; 

		ans += bessy0(x); // Polynomial approximation is defined for H_{0}(x) - Y_{0}(x) so add Y_{0}(x)
	}

	// H_{0}(x) is odd

	return x < 0.0 ? -ans : ans ;
}

double special::struveh1(double x)
{
	// Polynomial approximation for the Struve function H_{1}(x)
	// On 0 <= x <= 3, error is O(10^{-9})
	// On x >= 3, error is O(10^{-8})
	// H_{1}(x) is even => H_{1}(x) = H_{1}(-x)
	// For details of polynomial approximation see J. N. Newman, Math. Comp., 43 (168), 1984
	// H_{0}'(x) = (2/pi) - H_{1}(x)

	double ax, ans, y, ysqr; 

	ax = fabs(x); 

	if(ax >= 0.0 && ax <= 3.0){
		// 0 <= x <= 3

		y = ax/3.0; ysqr = template_funcs::DSQR(y); 
		
		ans = y * ( 1.909859286 + ysqr * ( -1.145914713 + ysqr * ( 0.294656958 + ysqr * ( -0.042070508 + ysqr * ( 0.003785727 -0.000207183*ysqr ) ) ) ) ); 
	}
	else{
		// x >= 3
		double Nx, Dx; 

		y = 3.0 / ax; ysqr = template_funcs::DSQR(y);

		Nx = 2.0 * (1.00000004 + ysqr * (3.92205313 + ysqr * ( 2.64893033 + 0.27450895 * ysqr ) ) ); 
		Dx = PI * (1.0 + ysqr * ( 3.81095112 + ysqr * ( 2.26216956 + 0.10885141 * ysqr) ) ); 

		ans = Nx/Dx;

		ans += bessy1(x); // Polynomial approximation is defined for H_{1}(x) - Y_{1}(x) so add Y_{1}(x)
	}

	// H_{1}(x) is even

	return ans;
}

void special::airy(double x, double *ai, double *bi, double *aip, double *bip)
{
	// Returns Airy Functions Ai(x), Bi(x) and their derivatives
	// Ai(x) is stored in ai
	// Bi(x) is stored in bi
	// Ai'(x) is stored in aip
	// Bi'(x) is stored in bip

	double THIRD = (1.0/3.0); 
	double TWOTHR = (2.0/3.0); 
	double ONOVRT = (1.0/sqrt(3.0)); 
	double absx,ri,rip,rj,rjp,rk,rkp,rootx,ry,ryp,z;

	absx=fabs(x);
	rootx=sqrt(absx);
	z=TWOTHR*absx*rootx;
	if (x > 0.0) {
		bessik(z,THIRD,&ri,&rk,&rip,&rkp);
		*ai=rootx*ONOVRT*rk/PI;
		*bi=rootx*(rk/PI+2.0*ONOVRT*ri);
		bessik(z,TWOTHR,&ri,&rk,&rip,&rkp);
		*aip = -x*ONOVRT*rk/PI;
		*bip=x*(rk/PI+2.0*ONOVRT*ri);
	} else if (x < 0.0) {
		bessjy(z,THIRD,&rj,&ry,&rjp,&ryp);
		*ai=0.5*rootx*(rj-ONOVRT*ry);
		*bi = -0.5*rootx*(ry+ONOVRT*rj);
		bessjy(z,TWOTHR,&rj,&ry,&rjp,&ryp);
		*aip=0.5*absx*(ONOVRT*ry+rj);
		*bip=0.5*absx*(ONOVRT*rj-ry);
	} else {
		*ai=0.35502805;
		*bi=(*ai)/ONOVRT;
		*aip = -0.25881940;
		*bip = -(*aip)/ONOVRT;
	}
}

void special::fresnel(double x, double *s, double *c)
{
	// Computes the Fresnel integrals S(x) and C(x) for all real x.
	// Taken from NRinC
	// R. Sheehan 26 - 3 - 2009

	int k, n, odd;

	double a,ax,fact,pix2,sign,sum,sumc,sums,term,test;

	std::complex<double> b,cc,d,h,del,cs;

	std::complex<double> one(1.0, 0.0); 

	static const int MAXIT=100;
	static const int TRUE=1;

	static const double FPMIN=1.0e-30;
	static const double XMIN=1.5;
	static const double EPS=(3.0e-12);

	ax=fabs(x);

	if(ax<sqrt(FPMIN)){					// Special case: avoid failure of convergence
		*s=0.0;							// test because of underflow.
		*c=ax;
	}else if(ax<=XMIN){					// Evaluate both series simultaneously.
		sum=sums=0.0;
		sumc=ax;
		sign=1.0;
		fact=PI_2*ax*ax;
		odd=TRUE;
		term=ax;
		n=3;
		for(k=1;k<=MAXIT;k++){
			term *= fact/k;
			sum += sign*term/n;
			test=fabs(sum)*EPS;
			if(odd){
				sign = -sign;
				sums=sum;
				sum=sumc;
			}else{
				sumc=sum;
				sum=sums;
			}
			if(term<test)break;
			odd=!odd;
			n+=2;
		}
//		if (k > MAXIT) nrerror("series failed in frenel");
		*s=sums;							
		*c=sumc;
	}else{								// Evaluate Integrals by use of Lentz's Continued Fraction Expansion Method
		pix2=PI*ax*ax;
		b=std::complex<double>(1.0,-pix2);
		cc=std::complex<double>(1.0/FPMIN,0.0);
		d=h=one/b;
		n = -1;
		for(k=2;k<=MAXIT;k++){
			n+=2;
			a=-n*(n+1);
			b=b+4.0;
			d=one/((a*d)+b);
			cc=(b+(a/cc));
			del=(cc*d);
			h=(h*del);
			if(fabs(del.real()-1.0)+fabs(del.imag())<EPS)break;
		}
//		if (k > MAXIT) nrerror("cf failed in frenel");
		h=(std::complex<double>(ax,-ax)*h);
		cs=(std::complex<double>(0.5,0.5)*(one-(std::complex<double>(cos(0.5*pix2),sin(0.5*pix2))*h)));
		*c=cs.real();
		*s=cs.imag();
	}
	if(x<0.0){						// Use antisymmetry to obtain values for negative x
		*c=-(*c);
		*s=-(*s);
	}
}

double special::Ell_K(double x, bool conjugate)
{
	// Complete elliptic integral of the first kind defined by Hypergeometric function
	// Abramowitz and Stegun, Ch 17, sect 17.3
	// function computes K'(k) = K(1-k) when conjugate = true, otherwise returns K(k)
	// R. Sheehan 23 - 11 - 2015

	try{

		if(x >= 0.0 && x < 1){

			double F, dF; 

			special::two_F_one( 0.5, 0.5, 1, ( conjugate ? 1.0 - x :  x ), F, dF); 
		
			return (F*PI_2);

		}
		else{
			std::string reason; 

			reason = "Error in special::Ell_K(double x, bool conjugate)\n"; 
			reason += "input argument x = " + template_funcs::toString(x, 3) + "\n"; 

			throw std::invalid_argument(reason); 
		}

	}
	catch(std::invalid_argument &e){		
		useful_funcs::exit_failure_output(e.what()); 
		exit(EXIT_FAILURE); 
	}
}

double special::Ell_E(double x, bool conjugate)
{
	// Complete elliptic integral of the second kind defined by Hypergeometric function
	// Abramowitz and Stegun, Ch 17, sect 17.3
	// function computes E'(k) = E(1-k) when conjugate = true, otherwise returns E(k)
	// R. Sheehan 23 - 11 - 2015

	try{

		if(x >= 0.0 && x < 1){

			double F, dF; 

			special::two_F_one( -0.5, 0.5, 1, ( conjugate ? 1.0 - x :  x ), F, dF); 
		
			return (F*PI_2);

		}
		else{
			std::string reason; 

			reason = "Error in special::Ell_E(double x, bool conjugate)\n"; 
			reason += "input argument x = " + template_funcs::toString(x, 3) + "\n"; 

			throw std::invalid_argument(reason); 
		}

	}
	catch(std::invalid_argument &e){		
		useful_funcs::exit_failure_output(e.what()); 
		exit(EXIT_FAILURE); 
	}
}

void special::Ell_K_E(double k, double &Kval, double &Eval, bool conjugate)
{
	// complete elliptic integrals of the first and second kind
	// polynomial approximation accurate to within |eps| <= 2e-8 when 0 <= k < 1
	// Abramowitz and Stegun, Ch 17, sect 17.3
	// functions compute K'(k) = K(1-k) when conjugate = true, otherwise returns K(k), or E(k)
	// R. Sheehan 23 - 11 - 2015

	//double arg = (conjugate ? k: 1.0 - k); // decide on the argument, i.e. return K(k) or K'(k) = K(1-k)

	try{

		if(k >= 0.0 && k < 1){

			// polynomial coefficients for K(k)
			double AK[5] = {1.38629436112, 0.09666344259, 0.03590092383, 0.03742563713, 0.01451196212}; 
			double BK[5] = {0.5, 0.12498593597, 0.06880248576, 0.03328355346, 0.00441787012};

			// polynomial coefficients for E(k)
			double AE[5] = {1.0, 0.44325141463, 0.06260601220, 0.04757383546, 0.01736506451}; 
			double BE[5] = {0.0, 0.24998368310, 0.09200180037, 0.04069697526, 0.00526449639};

			double m1 = (1.0 - ( conjugate ? 1.0 - k :  k ) ); 
			double lnm1 = log(1.0/m1); 
			double akval, bkval, aeval, beval; 

			// evaluate all polynomials simultaneously
			akval = AK[4]; bkval = BK[4]; // K(k)
			aeval = AE[4]; beval = BE[4]; // E(k)
			for(int i=3; i>=0; i--){
				// K(k)
				akval = akval*m1 + AK[i]; 
				bkval = bkval*m1 + BK[i]; 

				// B(k)
				aeval = aeval*m1 + AE[i]; 
				beval = beval*m1 + BE[i]; 
			}

			// multiply b polynomials by lnm1
			bkval *= lnm1; beval *= lnm1; 

			// Assign values for K(k) and E(k)
			Kval = (akval + bkval); 
			Eval = (aeval + beval);

		}
		else{
			std::string reason; 

			reason = "Error in special::Ell_K_E(double k, double &Kval, double &Eval, bool conjugate)\n"; 
			reason += "input argument k = " + template_funcs::toString(k, 3) + "\n"; 

			throw std::invalid_argument(reason); 
		}

	}
	catch(std::invalid_argument &e){		
		useful_funcs::exit_failure_output(e.what()); 
		exit(EXIT_FAILURE); 
	}
}

double special::Voigt(double x, double h, double G, double x0)
{
	// This is an implementation of the Voigt function
	// presumably x represents frequency
	// x0 represents centre frequency
	// h represents amplitude factor
	// G represents HWHM

	// There are problems with this implementation
	// Technically Lorentz HWHM != Gauss HWHM so there should be another parameter
	// Also the scale factor of 2.0 * sqrt(log10(2.0)) doesn't make any sense
	// unless the idea was to have that factor be related to the real Gaussian HWHM 
	// which is sqrt( 2 log(2) ) c
	// R. Sheehan 30 - 11 - 2021

	std::complex<double> z = ((x - x0 + 0.5*eye * G) * (2.0 * sqrt(log10(2.0)) / G));
	std::complex<double> acb = 2.0 * sqrt(log10(2.0)) / (sqrt(PI) * G);
	
	return ( real(h * Faddeeva::w(z)) );
}