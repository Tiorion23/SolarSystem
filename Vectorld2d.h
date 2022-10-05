#ifndef VECTORLD2D
#define VECTORLD2D
//class for vectors of long double numbers and mathematic actions on them
class Vectorld2d
{
public:
	long double x;
	long double y;

	//default constructor, creates (0, 0) vector
	class Vectorld2d();
	//constructor, creates (x, y) vector
	Vectorld2d(long double x, long double y );
	//operator == overload for Vector class
	friend bool operator== (const Vectorld2d& v1, const Vectorld2d& v2);
	//operator != overload for Vector class
	friend bool operator!= (const Vectorld2d& p1, const Vectorld2d& p2);
	//operator [] overload
    long double& operator[](int index);

	//operator= overload
	Vectorld2d& operator= (const Vectorld2d& v);

	//vector sum of two vectors
	friend Vectorld2d operator+ (const Vectorld2d& v1, const Vectorld2d& v2);

	//multiplying vector by number
	friend Vectorld2d operator* (const Vectorld2d& v1, const int m);
	friend Vectorld2d operator* (const Vectorld2d& v1, const long double m);

	//multiplies vector by vector, no realiztion yet
	friend Vectorld2d& operator* (const Vectorld2d& v1, const Vectorld2d& v2);

	//vector length
	const long double length();
};

#endif