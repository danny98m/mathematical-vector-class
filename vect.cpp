// Vect.cpp

//-----------------------------------------------------------------------
// Description: contains the class vector
//              which provides methods and variables useful in
//              calculations involving mathematical vectors.
//
// Programmer: Daniel P. Mullen
//
// Date Last Modified: 1/11/2017(DPM) -  Finished CTORs & DTORs.
//                     2/11/2017(DPM) -  Finished assignment operator,
//                                       get magnitude, and arithmetic
//                                       operators.
//                     3/11/2017(DPM) -  Finished relational operators,
//                                       scalar multiplication, dot product,
//                                       & cross product.
//                     5/11/2017(DPM) -  Better documentation.
//                     7/11/2017(DPM) -  Neater relational operators & neater
//                                       assignment.
//                     11/11/2017(DPM) - Better documentation.
//-----------------------------------------------------------------------

//=============Preprocessors=============================================
#include "vect.h"

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <cassert>

using namespace std;
//=======================================================================

//=============Constants=================================================
const double CLOSE_ENOUGH = 0.005;            // is this close enough
const short DEFAULT_SIZE = 3;                 // default vector size
const short DEFAULT_VECT_VALUE = 0;           // defulat value in vector
const short SQUARED = 2;
const short NO_VALUE = 0;                     // represents non-dimension when comparing different dimension vectors
const short VECT_3D = 3;                      // sets 3d vects
const short X_VALUE = 0;
const short Y_VALUE = 1;
const short Z_VALUE = 2;
//=============EndConstants==============================================

//-----------------------------------------------------------------------
//========Constructors (CTOR)============================================

//--------Default CTOR---------------------------------------------------
Vect::Vect()
/*
PRE:  None
POST: Will create a new vector object with the default settings
*/
{
      this->size = DEFAULT_SIZE;                          // Default size
      this->pVect = new double[this->size];               // Creates a new block of doubles

      for (short i = 0; i < this->size; i++)
      {
          pVect[i] = DEFAULT_VECT_VALUE;

      } // fills vect with 0s

} // end default CTOR

//--------Parametrized CTOR---------------------------------------------
Vect::Vect(/*in*/long n)
/*
PRE:  n is assigned
POST: Will create a new vector object of the desired size n
*/
{
     // you do this ...
    this->size = n;                             // set size to n
    this->pVect = new double[size];             // creates new block of doubles

    for (short i = 0; i < this->size; i++)
    {
        pVect[i] = DEFAULT_VECT_VALUE;

    } // fills vect with 0s

} // end parametrized CTOR

//----------Copy CTOR----------------------------------------------------
Vect::Vect(/*in*/const Vect& vect2)
/*
PRE:  vect2 is assigned
POST: Will create a new vector object of the same size as vect2 and 
      with the same values
*/
{
    this->size = vect2.size;                // Size set to the size of vect2
    this->pVect = new double[this->size];   // Creates a new block of doubles

    short i = 0;
    while (i < vect2.size)    // INVariant: i <= vect2.size
    {
        pVect[i] = vect2[i];
        i++;

    } // copies values of vect2 into this

} // end copy CTOR

//=====EndConstructors===================================================

//----- Destructor (DTOR) -----------------------------------------------
Vect::~Vect()
/*
PRE:  None
POST: Will free pVect so that memory can be used again
*/
{
    delete []pVect;

} // end destructor

//-----------------------------------------------------------------------

//-----getMagnitude------------------------------------------------------
double Vect::getMagnitude()
/*
PRE:  None
POST: Returns the magnitude of the vector
*/
{
    double magnitude;        // Holds final magnitude of vector
    double sum = 0;          // Holds sum of all elements squared
    short i = 0;             // Counter Declaration

    while (i < this->size)   //INVariant: i <= this->size
    {
        double currentElement = pVect[i];
        sum += pow(currentElement, SQUARED); // add square to total sum
        i++;

    } // adds up the sum of every element squared

    magnitude = sqrt(sum);

    return magnitude;

} // end getMagnitude

//-----------------------------------------------------------------------

//----- Set elements of vector ------------------------------------------
double& Vect::operator[] (/*in*/long i) const
/*
PRE:  i is assigned
POST: Returns desired dereferenced vector element 
*/
{
      // Checks that i is a valid index, if not the program exits
      if (i < 0 || i >= this->size)
      {
            cerr << "ERROR:index [" << i << "] is out of bounds." << endl;
            system("PAUSE");
            exit(-1);
      }// end if
      
      return pVect[i];
} // end []

//-----------------------------------------------------------------------

//-----AssignmentOperator------------------------------------------------
Vect& Vect::operator=(/*in*/const Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Copies all elements of vect2 to vector making the call and
      changes its size if needed to match vect2
      Returns cloned vector
*/
{
    // check for self assignment
    if (this == &vect2)
    {
        return *this;
    } // end if

    else
    {
        delete []this->pVect;                   // Free memory in this->pVect
        this->size = vect2.size;                // Size set to the size of vect2
        this->pVect = new double[this->size];   // Creates a new block of doubles

        short i = 0;

        while (i < vect2.size)                  // INVariant: i <= vect2.size
        {
            this->pVect[i] = vect2[i];
            i++;

        } // fill this->pVect at i with element at vect2[i]

        return *this;
    } // end else

} // end assignment operator
//-----------------------------------------------------------------------

//=======Vector arithmetic===============================================

//-------Operator+-------------------------------------------------------
const Vect Vect::operator+(/*in*/const Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns vector temp which is the sum of the vector making 
*/

{
    long smaller;                       // stores smaller vector size
    Vect temp;                          // what will be returned

    //===FindingSmaller======================================
    if (this->size <= vect2.size)
    {
        temp.size = vect2.size;
        smaller = this->size;
    } // end if

    else
    {
        temp.size = this->size;
        smaller = vect2.size;
    } // end else
    //===EndFindingSmaller====================================

    short i = 0;
    while (i < temp.size)               //INVariant: i <= temp.size
    {
        if (i < smaller)
        {
            temp.pVect[i] = vect2[i] + this->pVect[i];
        } // while less than smaller dimension add values together

        else
        {
            if (smaller == this->size)
            {
                temp.pVect[i] = vect2[i] + NO_VALUE;
            } //

            else
            {
                temp.pVect[i] = this->pVect[i] + NO_VALUE;
            }

        } // add 0 for vectors of different dimensions

        i++;

    } // end while
    assert(i==temp.size);

    return temp;

} // end operator+

//------Operator(minus)------------------------------------------------
const Vect Vect::operator-(/*in*/const Vect &vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns vector temp which is the subtraction of the vector making
*/
{
    long smaller;               // stores smaller vector size
    Vect temp;                  // this will be returned

    //===FindingSmaller==========================================
    if (this->size <= vect2.size)
    {
        temp.size = vect2.size;
        smaller = this->size;
    }

    else
    {
        temp.size = this->size;
        smaller = vect2.size;
    }
    //===EndFindingSmaller=======================================

    short i = 0;
    while (i < temp.size)     //INVariant: i <= temp.size
    {

        if (i < smaller)
        {
            temp.pVect[i] = this->pVect[i] - vect2[i];
        } // while less than smaller subtract elements

        else
        {
            if (smaller == this->size)
            {
                temp.pVect[i] = NO_VALUE - vect2.pVect[i];
            }

            else
            {
                temp.pVect[i] = this->pVect[i] - NO_VALUE;
            }

        } // use zeroes for out of dimensions

        i++;
    }
    assert(i==temp.size);

    return temp;

} // end operator-

//--------ScalarMultiplication---------------------------------------
const Vect Vect::operator*(/*in*/const double &mult)
/*
PRE:  mult is a given double
POST: Returns vector temp which is the scalar multiplication of the vector making
*/
{
    Vect temp;                 // returned vector
    temp.size = this->size;    // set size of return vector to size of given vector

    short i = 0;
    while (i < temp.size)      // INVariant: i<=temp.size
    {
        temp.pVect[i] = this->pVect[i] * mult;
        i++;

    } // multiply each element by double
    assert(i==temp.size);

    return temp;

} // end scalar multiplication

//--------------DotProduct---------------------------------------------
const double Vect::operator*(const Vect &vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns vector temp which is the dot product of the vector making
*/
{
    assert(this->size == VECT_3D);    // Vect must be 3D

    double dotProduct = 0;            // sum of element products

    short i = 0;
    while (i < this->size)            //INVariant: i<= this->size
    {
        dotProduct += this->pVect[i] * vect2.pVect[i];
        i++;

    } // add product of each element
    assert(i==this->size);

    return dotProduct;

} // end dot product

//-----------CrossProduct-----------------------------------
const Vect Vect::operator^(const Vect &vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns vector temp which is the cross product of the vector making
*/
{
    assert(this->size == VECT_3D);    // Vector must be 3D

    Vect temp;                        // returned vector

    //===CrossProduct======================================================================================
    temp.pVect[X_VALUE] =
            (this->pVect[Y_VALUE] * vect2.pVect[Z_VALUE]) - (this->pVect[Z_VALUE] * vect2.pVect[Y_VALUE]);

    temp.pVect[Y_VALUE] =
            (this->pVect[Z_VALUE] * vect2.pVect[X_VALUE]) - (this->pVect[X_VALUE] * vect2.pVect[Z_VALUE]);

    temp.pVect[Z_VALUE] =
            (this->pVect[X_VALUE] * vect2.pVect[Y_VALUE]) - (this->pVect[Y_VALUE] * vect2.pVect[X_VALUE]);
    //=====================================================================================================

    return temp;

} // end cross product

//-----------------------------------------------------------------------

//-----------------------------------------------------------------------

//========Compare vectors================================================
//--------Operator==-----------------------------------------------------
bool Vect::operator==(/*in*/Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true or false
*/
{
    if (fabs(this->getMagnitude() - vect2.getMagnitude()) <= CLOSE_ENOUGH)
    {
        return true;
    } // end if

    else
    {
        return false;
    } // end else

} // end operator==

//------operator<---------------------------------------------------------
bool Vect::operator<(/*in*/Vect &vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true or false
*/
{
    // first checking to see if within close enough
    if (fabs(this->getMagnitude() - vect2.getMagnitude()) <= CLOSE_ENOUGH)
    {
        return false;
    } // end if

    // now check for less than
    else if (this->getMagnitude() < vect2.getMagnitude())
    {
        return true;
    } // end else if

    else
    {
        return false;
    } // end else

} // end operator<

//---------operator<=--------------------------------------------------------
bool Vect::operator<=(/*in*/Vect &vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true or false
*/
{
    // first check for close enough
    if (fabs(this->getMagnitude() - vect2.getMagnitude()) <= CLOSE_ENOUGH)
    {
        return true;
    } // end if

    // then check for less than or equal to
    else if (this->getMagnitude() <= vect2.getMagnitude())
    {
        return true;
    } // end else if

    else
    {
        return false;
    } // end else

} // end operator <=

//----------operator>---------------------------------------------------------
bool Vect::operator>(/*in*/Vect &vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true or false
*/
{
    // first check for close enough
    if (fabs(this->getMagnitude() - vect2.getMagnitude()) <= CLOSE_ENOUGH)
    {
        return false;
    } // end if

    // then check for greater than
    else if (this->getMagnitude() > vect2.getMagnitude())
    {
        return true;
    } // end else if

    else
    {
        return false;
    } // end else

} // end operator >

//-----------operator>=---------------------------------------------------
bool Vect::operator>=(/*in*/Vect &vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true or false
*/
{
    // first check for close enough
    if (fabs(this->getMagnitude() - vect2.getMagnitude()) <= CLOSE_ENOUGH)
    {
        return true;
    } // end if

    // then check for greater than or equal to
    else if (this->getMagnitude() >= vect2.getMagnitude())
    {
        return true;
    } // end else if

    else
    {
        return false;
    } // end else

} // end operator >=

//---------operator!=-----------------------------------------------------
bool Vect::operator!=(/*in*/Vect &vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true or false
*/
{
    if (fabs(this->getMagnitude() - vect2.getMagnitude()) <= CLOSE_ENOUGH)
    {
        return false;
    } // end if

    else
    {
        return true;
    } // end else

} // end operator !=

//-----------------------------------------------------------------------


//-----------------------------------------------------------------------

//----- Print vectors ---------------------------------------------------

ostream& operator<<(/*inout*/ostream& output, /*in*/const Vect& vector)
/*
PRE:  << operators still used with cout and vector is an assigned vector
POST: Returns ostream output for the vector

operator assignment "<<": prints vector in <a,b,c...> format
*/
{ 
      output << '<' << vector.pVect[0]; //front bracket
     
      // Loops through remaing elements and prints them
      for(short i=1; i < vector.size; i++)
            output << ',' << vector.pVect[i]; //dimen. values
     
      output << '>'; //back bracket
     
      return output;

} // end operator <<

//-----------------------------------------------------------------------

//------------------------------------------EOF--------------------------