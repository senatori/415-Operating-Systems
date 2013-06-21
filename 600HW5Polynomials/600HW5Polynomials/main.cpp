//
//  main.cpp
//  600HW5Polynomials
//
//  Created by Stephen Senatori on 3/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

//#include <iostream>
//
//int main (int argc, const char * argv[])
//{
//
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    return 0;
//}

#include <iostream>

using namespace std;

// defining the class for polynomials
class Poly
{
    
    // private data members and function of class Poly
private:
	// array to hold up to 100 coefficients; I will not be creating
	// polynomials of this many terms, but the multiply function
	// requires adequate array space for its operation
	// the index will be the degree to which each variable x is raised
	// i.e. coef[0] will be x^0 and coef[9] will be x^9, etc.
	// the actual value at each index will be the coefficient
	double coef[100];
	// variable for degree of polynomial
	double degree;
    
    // public members of Poly
public:
	// default constructor initializes all coefficients to 0
	Poly::Poly()
	{
		for(int i = 0; i < 100; i++)
		{
			coef[i] = 0;
		}
	}
    
	// degrees function will determine the highest degree of any term in a 
	// given polynomial and will set the degree variable to that value
	int degrees()
	{
		// initialize degree to 0, then traverse array and assign the 
		// value of largest non-zero index of coef[] to degree
        
        int deg = 0;
		for(int i = 0; i < 100; i++)
		{
			if(coef[i] != 0)
			{
				deg = i;
			}
		}
		return deg;
	}
    
	// setter function to set coefficients and exponents
	void set(int co, int exp)
	{
		// set the coefficient at index exp to co and set degree to index exp
		coef[exp] = co;
		degree = degrees();
	}
    
	// printer function to print a given polynomial
	void print()
	{
		// starting at last index, check if there is a coefficient
		// if so, print the coefficient and the degree and the operator
		for(int i = 99; i >= 0; i--)
		{
			if(coef[i] != 0)
			{
				if(i > 1 && coef[i] > 0)
				{
					cout << "+" << coef[i] << "x^" << i << "  ";
				}
				else if(i > 1 && coef[i] < 0)
				{
					cout << coef[i] << "x^" << i << " ";
				}
				else if(i == 1 && coef[i] > 0)
				{
					cout << "+" << coef[i] << "x ";
				}
				else if(i == 1 && coef[i] < 0)
				{
					cout << coef[i] << "x ";
				}
				else if(i == 0 && coef[i] > 0)
				{
					cout << "+" << coef[i];
				}
				else if(i == 0 && coef[i] < 0)
				{
					cout << coef[i];
				}
			}
		}
		cout << "\n\n";
	}
    // addition function to add two polynomials
	Poly add(Poly second)
	{
		// create variable for pointer to calling polynomial and temp
		// to hold the addition of the caller plus the second
		// polynomial which is passed as a parameter to add()
		Poly caller = *this;
		Poly temp;
        
		// make two loop passes through temp, first transferring exponent
		// values from the calling polynomial, then on the second pass, adding
		// to these the values of the second polynomial being added to the first
		for(int i = 0; i <= caller.degree; i++)
		{
			temp.coef[i] += caller.coef[i];
		}
		for(int i = 0; i <= second.degree; i++)
		{
			temp.coef[i] += second.coef[i];
		}
		// set degree of temp polynomial
		temp.degree = temp.degrees();
		return temp;
	}
    
	// multiplication function for two polynomials
	Poly multiply(Poly second)
	{
		// same variables as add function
		Poly caller = *this;
		Poly temp;
		
		// this time use nested loops to multiply coefficients and store in temp
		// since we are not combining terms of same degree but multiplying
		// all terms sequentially
		for(int i = 0; i <= caller.degree; i++)
		{
			for(int j = 0; j <= second.degree; j++)
			{
				temp.coef[i+j] += (caller.coef[i] * second.coef[j]);
			}
		}
		// set degree and return temp
		temp.degree = temp.degrees();
		return temp;
	}
	
	// polynomial differentiation function
	Poly derivative()
	{
		// if the overall degree of a polynomial is zero, create a temp
		// Poly object and return 0
		if(degree == 0)
		{
            Poly der;
			der. set(0, 0);
			return der;
		}
		// otherwise create a temp Poly object and return the derivative of the
		// polynomial passed as a parameter to the derivative() function
		Poly deriv;
		// differentiation reduces the highest degree by one
		deriv.degree = degree - 1;
		// in the newly decremented Poly object, each coefficient
		// is now the coefficient from the original polynomial
		// times the original exponent value at each valid index
		for(int i = 0; i < degree; i++)
		{
			deriv.coef[i] = coef[i + 1] * (i + 1);
		}
		return deriv;
	}
    
	// polynomial integration function
	Poly integral()
	{
		// create a temp Poly object and return the integral of
		// the polynomial passed as a parameter to the integral() function
		Poly integral;
		// increase the highest degree by 1
		integral.degree = degree + 1;
		// in the newly created integral Poly object, each coefficient becomes
		// the original polynomials coefficient, divided by the exponenent of
		// the next highest index value, and each exponential value is shifted
		// one index up to raise the exponent by 1
		for(int i = 0; i <= degree; i++)
		{
			integral.coef[i+1] = coef[i] / (i + 1);
		}
		return integral;
	}
};

int main()
{
	// declare Poly type variables for use in demonstration of functions
	Poly first, second, added, multiplied, differentiated, integrated;
	// set values of first polynomial: 3x^5 + 4x^2 - 7x
	first.set(3, 5);
	first.set(4, 2);
	first.set(-7, 1);
	cout << "Your first polynomial is: ";
	first.print();
	// set values of second polynomial: -12x^4 + 6x^3 + 2x^2 + 9x + 1
	second.set(-12, 4);
	second.set(6, 3);
	second.set(2, 2);
	second.set(9, 1);
	second.set(1, 0);
	cout << "Your second polynomial is: ";

    Poly der;
    der. set(0, 0);
    return der;
}
// otherwise create a temp Poly object and return the derivative of the
// polynomial passed as a parameter to the derivative() function
Poly deriv;
// differentiation reduces the highest degree by one
deriv.degree = degree - 1;
// in the newly decremented Poly object, each coefficient
// is now the coefficient from the original polynomial
// times the original exponent value at each valid index
for(int i = 0; i < degree; i++)
{
    deriv.coef[i] = coef[i + 1] * (i + 1);
}
return deriv;
}

// polynomial integration function
Poly integral()
{
    // create a temp Poly object and return the integral of
    // the polynomial passed as a parameter to the integral() function
    Poly integral;
    // increase the highest degree by 1
    integral.degree = degree + 1;
    // in the newly created integral Poly object, each coefficient becomes
    // the original polynomials coefficient, divided by the exponenent of
    // the next highest index value, and each exponential value is shifted
    // one index up to raise the exponent by 1
    for(int i = 0; i <= degree; i++)
    {
        integral.coef[i+1] = coef[i] / (i + 1);
    }
    return integral;
}
};

int main()
{
	// declare Poly type variables for use in demonstration of functions
	Poly first, second, added, multiplied, differentiated, integrated;
	// set values of first polynomial: 3x^5 + 4x^2 - 7x
	first.set(3, 5);
	first.set(4, 2);
	first.set(-7, 1);
	cout << "Your first polynomial is: ";
	first.print();
	// set values of second polynomial: -12x^4 + 6x^3 + 2x^2 + 9x + 1
	second.set(-12, 4);
	second.set(6, 3);
	second.set(2, 2);
	second.set(9, 1);
	second.set(1, 0);
	cout << "Your second polynomial is: ";
    Poly der;
    der. set(0, 0);
    return der;
}
// otherwise create a temp Poly object and return the derivative of the
// polynomial passed as a parameter to the derivative() function
Poly deriv;
// differentiation reduces the highest degree by one
deriv.degree = degree - 1;
// in the newly decremented Poly object, each coefficient
// is now the coefficient from the original polynomial
// times the original exponent value at each valid index
for(int i = 0; i < degree; i++)
{
    deriv.coef[i] = coef[i + 1] * (i + 1);
}
return deriv;
}

// polynomial integration function
Poly integral()
{
    // create a temp Poly object and return the integral of
    // the polynomial passed as a parameter to the integral() function
    Poly integral;
    // increase the highest degree by 1
    integral.degree = degree + 1;
    // in the newly created integral Poly object, each coefficient becomes
    // the original polynomials coefficient, divided by the exponenent of
    // the next highest index value, and each exponential value is shifted
    // one index up to raise the exponent by 1
    for(int i = 0; i <= degree; i++)
    {
        integral.coef[i+1] = coef[i] / (i + 1);
    }
    return integral;
}
};

int main()
{
	// declare Poly type variables for use in demonstration of functions
	Poly first, second, added, multiplied, differentiated, integrated;
	// set values of first polynomial: 3x^5 + 4x^2 - 7x
	first.set(3, 5);
	first.set(4, 2);
	first.set(-7, 1);
	cout << "Your first polynomial is: ";
	first.print();
	// set values of second polynomial: -12x^4 + 6x^3 + 2x^2 + 9x + 1
	second.set(-12, 4);
	second.set(6, 3);
	second.set(2, 2);
	second.set(9, 1);
	second.set(1, 0);
	cout << "Your second polynomial is: ";
    return 0;
}

