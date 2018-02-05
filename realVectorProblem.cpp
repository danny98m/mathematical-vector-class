// realVectorProblem.cpp

//----------------------------------------------------------
// Programmer: Daniel P. Mullen
//
// Summary: Contains a demo vector problem to
//          show some functionality of the vect
//          class
//
// Date Last Modified: 11/11/2017 (DPM) - File created and
//                                        finished
//
// Out: Strings, vects, and doubles to stdout (console).
//----------------------------------------------------------
#include <iostream>
#include "vect.h"

using namespace std;

int main ()
{
    //problem--------------------------------------------------------------------------
    cout << "Vector A = <1,0,0> and Vector B = <1,6,3> and Vector C = <0,1,0>" << endl;
    cout << "Are A and B perpendicular to each other?" << endl;
    cout << "What about A and C?" << endl;

    Vect A;
    A[0] = 1;
    A[1] = 0;
    A[2] = 0;

    Vect B;
    B[0] = 1;
    B[1] = 6;
    B[2] = 3;

    Vect C;
    C[0] = 0;
    C[1] = 1;
    C[2] = 0;

    cout << "----------------------------------------------" << endl;

    if (A*B == 0)
    {
        cout << "Dot product of A and B = " << A * B << endl;
        cout << "A and B are perpendicular" << endl;
    } // end if

    else
    {
        cout << "Dot product of A and B = " << A * B << endl;
        cout << "A and B are not perpendicular" << endl;
    } // end else

    cout << "----------------------------------------------" << endl;

    if (A*C == 0)
    {
        cout << "Dot product of A and C = " << A * C << endl;
        cout << "A and C are perpendicular" << endl;
    } // end if

    else
    {
        cout << "Dot product of A and C = " << A * C << endl;
        cout << "A and C are not perpendicular" << endl;
    } // end else

    return 0;

} // end main
