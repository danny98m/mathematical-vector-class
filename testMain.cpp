#include "testMain.h"

/*
*	Vector class test suite.
*/

bool DOUBLE_EQ ( double a, double b );
#define CLOSE_ENOUGH	0.01

int main (void) {

    // review the test_vectIO() code; this test assumes you
    // have the parameterized CTOR and operator[] working;
    test_vectIO();
	
	// ALL of these tests `assert' their expected values. Therefore, if
	// flow control gets to the output at the end of main(), all tests
	// have passed.

	test_element_access();	// test element access (operator[])
	test_copy_ctor();		// test copy constructor (try to change values in sub-func)


    test_assignment_op();   // make sure assignment= handles various size vector assignments

	test_relational_ops();	// test relational ops (<,>,<=,>=,==,!=)
	test_arithmetic_ops();	// test arithmetic ops (+,-, and Vector*scalar multiplication)
	test_dot_product();		// test dot product (operator*)
	test_cross_product();	// test cross product (operator%)

	cout << "VECTOR CLASS PASSES ALL TESTS.\n";
	return 0;
}

void test_vectIO ( void ) {

    // This test doesn't actually assert anything, since the heuristic for
	// determining if IO has worked or not is by looking at the output on
	// the screen...
    {
		Vect A(3);
		A[0]	= 1;
		A[1]	= 2;
		A[2]	= 3;

		// now test operator<<()
		cout << endl << A << endl;
    }
	
}

void test_element_access ( void ) {
	// Set elements, and then try to retrieve them again (simple!).
	
	Vect A(4);
	A[0]	= 2;
	A[1]	= 6;
	A[2]	= 0;
	A[3]	= 0;

	assert( A[0] == 2 );
	assert( A[1] == 6 );
	assert( A[2] == 0 );
	assert( A[3] == 0 );
	cout << "element access OK\n";
}


void test_copy_ctor ( void ) {
	// Create a vector. Pass that vector to a function which will change element
	// values. Copy constructor should give that function it's own copy of the
	// vector. If original element values remain intact after function invocation,
	// copy ctor works.
	
	Vect A(3);
	A[0]	= 10;
	A[1]	= 20;
	A[2]	= 40;
	
	modify_vect( A );
	
    // but is A still the same once we return from the function?
	assert( A[0] == 10 );
	assert( A[1] == 20 );
	assert( A[2] == 40 );
	cout << "copy constructor OK\n";
}

void modify_vect (Vect X) {
	// X is a local Vect(3), but whose local (copy only) memory is being changed
	X[0] = 97;  X[1] = 98;  X[2] = 99;
	// oh no, scope of X is done; call DTOR for X!!!
}

void test_assignment_op( void ) {
    
    Vect A (5);
	A[0]	= 1;
	A[1]	= 2;
	A[2]	= 3;
    A[3]	= 4;
	A[4]	= 5;	
	
	Vect B (3);
	B[0]	= 1;
	B[1]	= 1;
	B[2]	= 1;
    
    Vect C (2);
	C[0]	= 8;
	C[1]	= 8;
    
    Vect D (3);
	D[0]	= 6;
	D[1]	= 5;
	D[2]	= 4;

    D = B;   // assign 3D to 3D
    cout << D << endl;
    assert( D[0] == 1 );
    assert( D[1] == 1 );
    assert( D[2] == 1 );
    
    B = C;   // assign 2D to 3D
    assert( B[0] == 8 );
    assert( B[1] == 8 );
    //assert( B[2] == 0 );

    C = A;   // assign 5D to 2D
    assert( C[0] == 1 );
    assert( C[1] == 2 );
    assert( C[2] == 3 );
    assert( C[3] == 4 );
    assert( C[4] == 5 );
    cout << D << endl;  // why is D <3,4,5> here?????????????

    D = D;   // assign to itself (code should trap this situation)HOW THE FUCK DO I DO THIS

    assert( D[0] == 1 );
    assert( D[1] == 1 );
    assert( D[2] == 1 );


    cout << "assignment op OK\n";
}

void test_relational_ops ( void ) {
	// this test defines 3 vectors, and attempts to query the expected results of
	// all relations between them.
	
	Vect A (3);
	A[0]	= 1;
	A[1]	= 2;
	A[2]	= 0;	// length now == sqrt(5)
	
	Vect B (3);
	B[0]	= 1;
	B[1]	= 1;
	B[2]	= 1;	// length now == sqrt(3)
	
	Vect C (3);
	C[0]	= 1;
	C[1]	= 1;
	C[2]	= 1;	// length now == sqrt(3)
	
	Vect D (3);
	D[0]	= 0;
	D[1]	= 2;
	D[2]	= 1;	// length now == sqrt(5)
	
	assert( B < A );
	assert( !( B > A ) );
	
	assert( B <= A );
	assert( !( B >= A ) );
	
	assert( !( B < C ) );
	assert( !( C < B ) );
	assert( B <= C );
	assert( C <= B );
	
	assert( A == D );
	assert( B == C );
	
	assert( !( A == B ) );
	assert( !( C == D ) );
	assert( A != B );
	assert( C != D );
	
	cout << "relational ops OK\n";
}


void test_arithmetic_ops ( void ) {
	// Very simple element-wise test of addition and subtraction.
	
	Vect A (3);
	A[0]	= 1;
	A[1]	= 2;
	A[2]	= 0;	// length now == sqrt(5)
	
	Vect B (3);
	B[0]	= 1;
	B[1]	= 1;
	B[2]	= 1;	// length now == sqrt(3)

    Vect V(4);
    V[0] = 3;
    V[1] = 2;
    V[2] = 7;
    V[3] = 8;
	
	{
		Vect C (3); // same dimension
		C		= A + B;
		
		assert( C[0] == 2 );
		assert( C[1] == 3 );
		assert( C[2] == 1 );
	}

    {
        Vect F;   // different dimensions (4 + 3)
        F = V + B;

        assert( F[0] == 4 );
        assert( F[1] == 3 );
        assert( F[2] == 8 );
        assert( F[3] == 8 );
    }

    {
        Vect F;   // testing for commutative property.
        F = B + V;

        assert( F[0] == 4 );
        assert( F[1] == 3 );
        assert( F[2] == 8 );
        assert( F[3] == 8 );
    }
	
	{
		Vect C (3);
		C		= A - B;
		
		assert( C[0] == 0 );
		assert( C[1] == 1 );
		assert( C[2] == -1 );
	}

    {
        Vect C (3);   // testing commutativity
        C		= B - A;

        assert( C[0] == 0 );
        assert( C[1] == -1 );
        assert( C[2] == 1 );
    }

    {
        Vect F;   // different dimensions (4 + 3)
        F = V - B;

        assert( F[0] == 2 );
        assert( F[1] == 1 );
        assert( F[2] == 6 );
        assert( F[3] == 8 );
    }

    {
        Vect F;   // different dimensions (4 + 3) && commutativity
        F = B - V;

        assert( F[0] == -2 );
        assert( F[1] == -1 );
        assert( F[2] == -6 );
        assert( F[3] == -8 );
    }

    // test Vector*scalar
	{
		Vect C (3);
		C		= A * 4;
		
		assert( C[0] == 4 );
		assert( C[1] == 8 );
		assert( C[2] == 0 );
	}
	
	cout << "arithmetic ops OK\n";
}


void test_dot_product ( void ) {
	// Test basic properties of the dot product:
	// * dot product of a vector by itself is the length of that vector
	// * dot product of orthogonal vectors is zero
	
	Vect A (3);
	A[0]	= 1;
	A[1]	= 0;
	A[2]	= 0;
	
	Vect B (3);
	B[0]	= 0;
	B[1]	= 1;
	B[2]	= 0;	// A and B are now orthogonal
	
	{
		double c	= A * A;
		assert( DOUBLE_EQ(c, 1.0) );
	}

	{
		double c	= A * B;
		assert( DOUBLE_EQ(c, 0.0) );
	}
	
	cout << "dot product OK\n";
}


void test_cross_product ( void ) {
	// Test basic property of the cross product:
	// * cross product of two orthogonal vectors is a third orthogonal vector
	// In this case, the basis vectors of three-space are used.
	
	Vect A (3);
	A[0]	= 1;
	A[1]	= 0;
	A[2]	= 0;
	
	Vect B (3);
	B[0]	= 0;
	B[1]	= 1;
	B[2]	= 0;	// A and B are now orthogonal
	
	Vect C	= A ^ B;
	assert( C[0] == 0 );
	assert( C[1] == 0 );
	assert( C[2] == 1 );

	cout << "cross product OK\n";
}


// PRE	: none
// POST	: <retval> == true || <retval> == false
// PARAMETERS:
//	a	IN
//	b	IN
bool DOUBLE_EQ ( double a, double b ) {
	double c	= a - b;						// difference between a and b
	if (c < 0)
		c = -1.0 * c;							// absolute value
	return (c < CLOSE_ENOUGH);					// close enough to zero?
}



