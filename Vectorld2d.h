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
	Vectorld2d(const Vectorld2d& v);
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
	template <class T> friend Vectorld2d operator* (const Vectorld2d v1, const T value) {
		Vectorld2d result = Vectorld2d(v1.x * value, v1.y * value);
		return result;
	}
	
	//multiplies vector by vector, no realiztion yet
	friend Vectorld2d& operator* (const Vectorld2d& v1, const Vectorld2d& v2);

	//vector length
	const long double length();
	// mirrors this vector by both axis
	void mirror();
	
};

#endif