#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

const double EPS = 0.000001; //For check double equ 
const double NO_ROOT = 0.0;  //For create struct SqEqRoots with one or zero roots


//---------------------------------------------------------------
typedef struct SqEqArgs_ {
	double a, b, c;
} SqEqArgs;

typedef enum RootsCount_ {
  	ZERO_ROOTS,
  	ONE_ROOT, 
  	TWO_ROOTS,
  	INF_ROOTS
} RootsCount;

typedef struct SqEqRoots_ {
	double x1, x2;
	RootsCount count;
} SqEqRoots; 
//---------------------------------------------------------------



//---------------------------------------------------------------
//For print answer of SqEq and info about count roots
void PrintInfoOut(SqEqRoots roots);

bool ReadArgs(SqEqArgs* args);

//Check double equ
bool DoubleEqu(double a, double b, double eps);

//If SqEq is LinEq, i solve LinEq
SqEqRoots LinEq(SqEqArgs args);

//Solve SqEq
SqEqRoots SqEq(SqEqArgs args);
//---------------------------------------------------------------



//---------------------------------------------------------------
//For testing, check SqEqRoots equ
bool RootsEqu(SqEqArgs out, SqEqArgs correct);

//Start Unit Testing
void UnitTest();
//---------------------------------------------------------------



int main() {
#ifdef TEST
	UnitTest();
	return 0;
#endif

	puts("Please, enter three arguments for square equation");

	SqEqArgs args;
	if (ReadArgs(&args))
		PrintInfoOut(SqEq(args));
	else
		puts("Can't read input args");

 	return 0;
}

//Func to avoid copy past in PrintInfoOut
void StandartInfoOut(const char* args_count) {
 	assert(args_count);

 	printf("Square equation have %s roots\n", args_count);
}

void PrintInfoOut(SqEqRoots roots) {
 	switch(roots.count) {
 	 	case ZERO_ROOTS:
 	 		StandartInfoOut("zero");
 	 		break;
 	 	case ONE_ROOT:
 	 		StandartInfoOut("one");
 	 		printf("%lf\n", roots.x1);
 	 		break;
 	    case TWO_ROOTS:
 	    	StandartInfoOut("two");
 	    	printf("%lf %lf\n", roots.x1, roots.x2);
 	    	break;
 	    case INF_ROOTS:
 	    	StandartInfoOut("infinity");
 	}
}

bool ReadArgs(SqEqArgs* args) {
	assert(args);

	//ax^2 + bx + c = 0
	double a = 0.0,
		   b = 0.0,
		   c = 0.0;

	unsigned int count_read = scanf("%lf%lf%lf", &a, &b, &c);
	if (count_read < 3)
		return false; 	

	*args = {a, b, c};
	return true;             
}

bool DoubleEqu(double a, double b, double eps) {
 	return (fabs(a - b) < eps);
}

SqEqRoots LinEq(SqEqArgs args) {
 	if (DoubleEqu(args.b, 0.0, EPS)) {
		if (DoubleEqu(args.c, 0.0, EPS))
		 	return {NO_ROOT, NO_ROOT, INF_ROOTS};
		else 
			return {NO_ROOT, NO_ROOT, ZERO_ROOTS};
 	} else
 	 	return {-args.c / args.b, NO_ROOT, ONE_ROOT};
}

SqEqRoots SqEq(SqEqArgs args) {
	if (DoubleEqu(args.a, 0.0, EPS))
		return LinEq(args);
	else {
		double dd = args.b*args.b - 4*args.a*args.c; //Determinant square
		if (dd < 0.0)
			return {NO_ROOT, NO_ROOT, ZERO_ROOTS};
		else if (DoubleEqu(dd, 0.0, EPS))
			return {-args.b / (2*args.a), NO_ROOT, ONE_ROOT};	
		else {
		 	double d = sqrt(dd); //Determinant
		 	return {(-args.b + d) / (2*args.a), 
		 		    (-args.b - d) / (2*args.a), 
		 	        TWO_ROOTS};
		}
	}
}

bool RootsEqu(SqEqRoots out, SqEqRoots correct) {
 	return (out.x1    == correct.x1 &&
 			out.x2    == correct.x2 &&
 			out.count == correct.count); 
}

void LinEqTest() {
 	assert(RootsEqu(LinEq({0.0, 0.0, 0.0}), {NO_ROOT, NO_ROOT, INF_ROOTS}));
 	assert(RootsEqu(LinEq({0.0, 0.0, 1.0}), {NO_ROOT, NO_ROOT, ZERO_ROOTS}));
 	assert(RootsEqu(LinEq({0.0, 2.0, 4.0}), {-2.0, NO_ROOT, ONE_ROOT}));

 	puts("Unit-test LinEqTest: OK");
}

void SqEqTest() {
 	assert(RootsEqu(SqEq({0.0, 0.0, 0.0}), {NO_ROOT, NO_ROOT, INF_ROOTS}));
 	assert(RootsEqu(SqEq({0.0, 0.0, 1.0}), {NO_ROOT, NO_ROOT, ZERO_ROOTS}));
 	assert(RootsEqu(SqEq({0.0, 2.0, 4.0}), {-2.0, NO_ROOT, ONE_ROOT}));

 	assert(RootsEqu(SqEq({1.0, 4.0, -5.0}), {1.0, -5.0, TWO_ROOTS}));
 	assert(RootsEqu(SqEq({2.0, 1.0, 3.0}), {NO_ROOT, NO_ROOT, ZERO_ROOTS}));
 	assert(RootsEqu(SqEq({1.0, -2.0, 1.0}), {1.0, NO_ROOT, ONE_ROOT}));
 	assert(RootsEqu(SqEq({1.0, 2.0, 1.0}), {-1.0, NO_ROOT, ONE_ROOT}));

 	puts("Unit-test SqEqTest: OK"); 	
}

void UnitTest() {
	LinEqTest();
	SqEqTest();		 	
}
