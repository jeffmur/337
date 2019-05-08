// Jeffrey Murray CSS 343 B SP19
// Created: 4/4/19
// Last Modified: 4/9/19

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "poly.h"
using namespace std;

// ----------Helper Functions---------------------------------------------------
/* ------------------------------------fill-------------------------------------
 * Description: Set array with 0's to avoid redundant for loops
 * -----------------------------------------------------------------------------*/
void Poly::fill(){
    for(int i = 0; i < size; i++)
        setCoeff(0,i);
}
/* ------------------------------------resize-----------------------------------
 * Description: Resize Array (increase only) to power + 1
 * Parameters : exponent aka power
 * -----------------------------------------------------------------------------*/
void Poly::resize(int exp){
    // bad efficiency check
    if(exp <= size)
        return;
    // store old values
    double* oldArray = coeffPtr;
    int oldSize = size;
    // reset poly with new size
    size = exp + 1;
    coeffPtr = new double[size+1];
    fill();
    // copy over prev values
    for(int i = 0; i < oldSize; i++)
        coeffPtr[i] = oldArray[i];
}

/* ------------------------------------getCoeff---------------------------------
 * Description: Fetch value stored in array
 * Parameters : exponent aka power
 * Returns    : int position in coeffptr
 * -----------------------------------------------------------------------------*/
int Poly::getCoeff(int exp) {
    // check for bad call
    if (exp < size && exp >= 0)
        return coeffPtr[exp];
    else
        return -1;
}
/* ------------------------------------setCoeff---------------------------------
 * Description: Set coefficient in Array with power(location)
 * Parameters : (Value, Location)
 * -----------------------------------------------------------------------------*/
void Poly::setCoeff(int co, int exp) {
    // check for bad call
    if(exp < 0)
        return;
    // sunny day
    else if(exp < size) {
        coeffPtr[exp] = co;
    }
    // rainy day - exp >= size
    else {
        resize(exp);
        coeffPtr[exp] = co;
    }
}
// ----------Constructors-------------------------------------------------------
/* ------------------------------------Poly(co, exp)----------------------------
 * Description: Memory is reserved for array when called and inserts coefficient
 * Parameters : (Value, Location)
 * Sunny Day  : Poly A(5,7); = 5x^7
 * -----------------------------------------------------------------------------*/
Poly::Poly(int new_co, int new_exp) {
    // New array or larger exp
    if(size == 0 || new_exp > size) {
        resize(new_exp);
        setCoeff(new_co, new_exp);
    }
    else
        setCoeff(new_co, new_exp);
}
/* ------------------------------------Poly(co)---------------------------------
 * Description: Constructor that initializes with coefficient x^0
 * Sunny Day  : Poly B(2); = +2x^0
 * -----------------------------------------------------------------------------*/
Poly::Poly(int new_co){
    size = 1;
    coeffPtr = new double[size];
    fill();
    coeffPtr[0] = new_co;
}
/* ------------------------------------Poly()-----------------------------------
 * Description: Initialized to 0x^0 (zero polynomial)
 * Sunny Day  : Poly X; = 0x^0
 * -----------------------------------------------------------------------------*/
Poly::Poly(){
    size = 1;
    coeffPtr = new double[1];
    coeffPtr[0] = 0;
}
/* ------------------------------------Poly(Poly& old)--------------------------
 * Description: Exact copy (deep copy) of Poly object old
 * Parameter  : Memory address of Poly object
 * Sunny Day  : Poly C(A); = 5x^7
 * -----------------------------------------------------------------------------*/
Poly::Poly(Poly& old){
    size = old.size;
    coeffPtr = new double[size];
    // copy old values
    for(int i = 0; i < size; i++)
        coeffPtr[i] = old.coeffPtr[i];
}
/* ------------------------------------~Poly()----------------------------------
 * Description: Deconstructs memory of arrays
 * -----------------------------------------------------------------------------*/
Poly::~Poly(){
    delete[] coeffPtr;
    coeffPtr = nullptr;
}
// ----------Math operators-----------------------------------------------------
/* ------------------------------------Addition (+)-----------------------------
 * Description: Overloads + operator to add two poly arrays
 * Parameter  : Poly object a
 * Returns    : Poly object sum = this + a
 * -----------------------------------------------------------------------------*/
Poly Poly::operator+( const Poly& a ) const {
    Poly sum;
    // Sum is set to largest size'd array
    if(size > a.size)
        sum.resize(size-1);
    else
        sum.resize(a.size-1);
    // iterates through sum and add values
    for(int i = 0; i < sum.size; i++){
        int tempSum = coeffPtr[i] + a.coeffPtr[i];
        // check for out of bounds of either array
        if(i >= size)
            tempSum = a.coeffPtr[i];
        else if(i >= a.size)
            tempSum = coeffPtr[i];
        sum.coeffPtr[i] = tempSum;
    }
    return sum;
}
/* ------------------------------------Subtraction(-)---------------------------
 * Description: Overloads - operator to subtract two poly arrays
 * Parameter  : Poly object a
 * Returns    : Poly object difference = this - a
 * -----------------------------------------------------------------------------*/
Poly Poly::operator-( const Poly& a ) const {
    Poly difference;
    // Difference is set to largest size'd array
    if(size > a.size)
        difference.resize(size-1);
    else
        difference.resize(a.size-1);
    // iterates through difference and subtract values
    for(int i = 0; i < difference.size; i++){
        int tempSub = coeffPtr[i] - a.coeffPtr[i];
        // check for out of bounds of either array
        if(i >= size)
            tempSub = -a.coeffPtr[i];
        else if(i >= a.size)
            tempSub = coeffPtr[i];
        difference.coeffPtr[i] = tempSub;
    }
    return difference;
}
/* ------------------------------------Multiplication(*)------------------------
 * Description: Overloads * operator to multiply two poly arrays
 * Parameter  : Poly object a
 * Returns    : Poly object difference = this * a
 * -----------------------------------------------------------------------------*/
Poly Poly::operator*( const Poly& a ) const {
    Poly product;
    // Product is set to the sum of two largest exponents
    product.resize(size+a.size);
    // iterates through product[i] and multiplies values[j]
    for(int i = 0; i < size; i++){
        for(int j = 0; j < a.size; j++){
            int tempProd = coeffPtr[i] * a.coeffPtr[j];
            if(tempProd != 0)
                product.coeffPtr[i+j] += tempProd;
        }
    }
    return product;
}
// -------Comparison------------------------------- 0 = False , 1 = True -------
/* ------------------------------------Equal To (==)----------------------------
 * Description: Overloads == operator to compare two poly arrays
 * Parameter  : Poly object a
 * Returns    : Poly object returns this == a
 * -----------------------------------------------------------------------------*/
bool Poly::operator==(const Poly& a) const {
    // sunny day
    if(size != a.size)
        return false;
    // rainy day - else check each value
    for(int i = 0; i < size; i++){
        if(coeffPtr[i] != a.coeffPtr[i])
            return false;
    }
    return true;
}
/* ------------------------------------Not Equal To (!=)------------------------
 * Description: Overloads != operator to compare two poly arrays
 * Parameter  : Poly object a
 * Returns    : Poly object returns this != a
 * -----------------------------------------------------------------------------*/
bool Poly::operator!=(const Poly& a) const {
    return !(*this == a);

}
// ----------Assignment---------------------------------------------------------
/* ------------------------------------Equal (=)--------------------------------
 * Description: This object is a deep copy of Poly object a
 * Parameter  : Poly object a
 * Returns    : Pointer of this(assigned) object
 * -----------------------------------------------------------------------------*/
Poly& Poly::operator=(const Poly& a) {
    // initialize array
    resize(a.size-1);
    // copy values
    for(int i = 0; i <= size; i++)
        coeffPtr[i] = a.coeffPtr[i];
    return *this;
}
/* ------------------------------------Plus Equal (+=)--------------------------
 * Description: This object is assigned this + a
 * Parameter  : Poly object a
 * Returns    : Pointer of this(assigned) object
 * -----------------------------------------------------------------------------*/
Poly& Poly::operator+=(const Poly& a) {
    *this = *this + a;
    return *this;
}
/* ------------------------------------Subtract Equal (-=)----------------------
 * Description: This object is assigned this - a
 * Parameter  : Poly object a
 * Returns    : Pointer of this(assigned) object
 * -----------------------------------------------------------------------------*/
Poly& Poly::operator-=(const Poly& a) {
    *this = *this - a;
    return *this;
}
/* ------------------------------------Multiply Equal (*=)----------------------
 * Description: This object is assigned this * a
 * Parameter  : Poly object a
 * Returns    : Pointer of this(assigned) object
 * -----------------------------------------------------------------------------*/
Poly& Poly::operator*=(const Poly& a) {
    *this = *this * a;
    return *this;
}
// ---------Stream I/O----------------------------------------------------------
/* ------------------------------------ostream (<<)-----------------------------
 * Description    : overload cout << object from ostream class
 * Parameter      : ostream& output , Poly object a
 * Returns        : entire polynomial expression stored in array
 * Expected Output: +5x^7 -4x^3 +10x -2
 * -----------------------------------------------------------------------------*/
ostream& operator<<(ostream& output, const Poly& a) {
    if(a.size == 1)  // check for zero poly
        output << a.coeffPtr[0]; // 0
    else {
        for (int i = a.size - 1; i > -1; i--) {
            if (a.coeffPtr[i] > 0) {             // positive values
                if (i > 1)
                    output << "+" << a.coeffPtr[i] << "x^" << i << " ";
                else if (i == 1)
                    output << "+" << a.coeffPtr[i] << "x ";
                else if (i == 0)
                    output << "+" << a.coeffPtr[i];
            } else if (a.coeffPtr[i] < 0) {       // negative values
                if (i > 1)
                    output << a.coeffPtr[i] << "x^" << i << " ";
                else if (i == 1)
                    output << a.coeffPtr[i] << "x ";
                else if (i == 0)
                    output << a.coeffPtr[i];
            }
        }
    }
    return output;
}
/* ------------------------------------istream (>>)-----------------------------
 * Description   : overload cin >> object from istream class
 * Parameter     : istream& input , Poly object a
 * Returns       : when -1 -1 is entered
 * Expected Input: NUM EXP ... NUM EXP -1 -1
 * -----------------------------------------------------------------------------*/
istream& operator>>(istream& input, Poly& a) {
    int num = 0, exp = 0;
    while(num != -1 && exp != -1){ // repeat until -1 -1 is reached
        input >> num >> exp;
        a.resize(exp);
        a.setCoeff(num, exp);
    }
    return input;
}

/* ------------------------------------integrate---------------------------------
 * Description: integrate a polynomial exp
 * -----------------------------------------------------------------------------*/
void Poly::integrate() {
    Poly I;
    I.size = size+1;
    I.coeffPtr = new double[I.size];
    I.fill();
    // copy old values
    for(int i = 0; i < size; i++)
	I.coeffPtr[i+1] = this->coeffPtr[i]/(i+1);
    // this points to new Poly created 
    *this = I;
    size++;
}

/* ------------------------------------derive---------------------------------
 * Description: derivative of a polynomial exp
 * -----------------------------------------------------------------------------*/
void Poly::derive() {
    // initialize Derivative Poly
    Poly D;
    D.size = this->size-1;
    D.coeffPtr = new double[size];
    D.fill();
    for(int i = 1; i <= size; i++)
    	D.coeffPtr[i-1] = (i)*coeffPtr[i];
    *this = D;
    size--;
    
}

