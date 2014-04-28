//////////////////////////////////////////////////////////////////////////
// Transformation.cpp -- Source file for useful Classes about 3D transformations
//
// Liming Zhao
// 11/02/2007
// University of Pennsylvania

#include "StdAfx.h" // Only needed in MFC

#include "Transformation.h"

/****************************************************************
*																*
*		    vec2 Member functions								*
*																*
****************************************************************/

// CONSTRUCTORS

vec2::vec2() 
{
}

vec2::vec2(const float x, const float y)
{
	n[VX] = x; n[VY] = y; 
}

vec2::vec2(const vec2& v)
{ 
	n[VX] = v.n[VX]; n[VY] = v.n[VY]; 
}

// ASSIGNMENT OPERATORS

vec2& vec2::operator = (const vec2& v)
{ 
	n[VX] = v.n[VX]; n[VY] = v.n[VY]; return *this; 
}

vec2& vec2::operator += ( const vec2& v )
{ 
	n[VX] += v.n[VX]; n[VY] += v.n[VY]; return *this; 
}

vec2& vec2::operator -= ( const vec2& v )
{ 
	n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; return *this; 
}

vec2& vec2::operator *= ( const float d )
{ 
	n[VX] *= d; n[VY] *= d; return *this; 
}

vec2& vec2::operator /= ( const float d )
{ 
	float d_inv = 1.0f/d; n[VX] *= d_inv; n[VY] *= d_inv; return *this; 
}

float& vec2::operator [] ( int i) 
{
	assert(!(i < VX || i > VY));		// subscript check
	return n[i];
}

float vec2::operator [] ( int i) const 
{
	assert(!(i < VX || i > VY));
	return n[i];
}


// SPECIAL FUNCTIONS

float vec2::Length() const
{ 
	return sqrt(SqrLength()); 
}

float vec2::SqrLength() const
{ 
	return n[VX]*n[VX] + n[VY]*n[VY]; 
}

vec2& vec2::Normalize() // it is up to caller to avoid divide-by-zero
{ 
	*this /= Length(); return *this; 
}

// FRIENDS

vec2 operator - (const vec2& a)
{ 
	return vec2(-a.n[VX],-a.n[VY]); 
}

vec2 operator + (const vec2& a, const vec2& b)
{ 
	return vec2(a.n[VX]+ b.n[VX], a.n[VY] + b.n[VY]); 
}

vec2 operator - (const vec2& a, const vec2& b)
{ 
	return vec2(a.n[VX]-b.n[VX], a.n[VY]-b.n[VY]); 
}

vec2 operator * (const vec2& a, const float d)
{ 
	return vec2(d*a.n[VX], d*a.n[VY]); 
}

vec2 operator * (const float d, const vec2& a)
{ 
	return a*d; 
}

float operator * (const vec2& a, const vec2& b)
{ 
	return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY]); 
}

vec2 operator / (const vec2& a, const float d)
{ 
	float d_inv = 1.0f/d; return vec2(a.n[VX]*d_inv, a.n[VY]*d_inv); 
}

vec3 operator ^ (const vec2& a, const vec2& b)
{ 
	return vec3(0.0, 0.0, a.n[VX] * b.n[VY] - b.n[VX] * a.n[VY]); 
}

int operator == (const vec2& a, const vec2& b)
{ 
	return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]); 
}

int operator != (const vec2& a, const vec2& b)
{ 
	return !(a == b); 
}

vec2 Prod(const vec2& a, const vec2& b)
{ 
	return vec2(a.n[VX] * b.n[VX], a.n[VY] * b.n[VY]); 
}

float Dot(const vec2& a, const vec2& b)
{
	return a*b;
}


/****************************************************************
*																*
*		    vec3 Member functions								*
*																*
****************************************************************/

// CONSTRUCTORS

vec3::vec3() 
{
}

vec3::vec3(const float x, const float y, const float z)
{ 
	n[VX] = x; n[VY] = y; n[VZ] = z; 
}

vec3::vec3(const vec3& v)
{ 
	n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; 
}

// ASSIGNMENT OPERATORS

vec3& vec3::operator = (const vec3& v)
{ 
	n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; return *this; 
}

vec3& vec3::operator += ( const vec3& v )
{ 
	n[VX] += v.n[VX]; n[VY] += v.n[VY]; n[VZ] += v.n[VZ]; return *this; 
}

vec3& vec3::operator -= ( const vec3& v )
{ 
	n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; n[VZ] -= v.n[VZ]; return *this; 
}

vec3& vec3::operator *= ( const float d )
{ 
	n[VX] *= d; n[VY] *= d; n[VZ] *= d; return *this; 
}

vec3& vec3::operator /= ( const float d )
{ 
	float d_inv = 1.0f/d; n[VX] *= d_inv; n[VY] *= d_inv; n[VZ] *= d_inv;
	return *this; 
}

float& vec3::operator [] ( int i) {
	assert(! (i < VX || i > VZ));
	return n[i];
}

float vec3::operator [] ( int i) const {
	assert(! (i < VX || i > VZ));
	return n[i];
}


// SPECIAL FUNCTIONS

float vec3::Length() const
{  
	return sqrt(SqrLength()); 
}

float vec3::SqrLength() const
{  
	return n[VX]*n[VX] + n[VY]*n[VY] + n[VZ]*n[VZ]; 
}

vec3& vec3::Normalize() // it is up to caller to avoid divide-by-zero
{ 
	*this /= Length(); return *this; 
}

vec3 vec3::Cross(vec3 &v) const
{
	vec3 tmp;
	tmp[0] = n[1] * v.n[2] - n[2] * v.n[1];
	tmp[1] = n[2] * v.n[0] - n[0] * v.n[2];
	tmp[2] = n[0] * v.n[1] - n[1] * v.n[0];
	return tmp;
}

// FRIENDS

vec3 operator - (const vec3& a)
{  
	return vec3(-a.n[VX],-a.n[VY],-a.n[VZ]); 
}

vec3 operator + (const vec3& a, const vec3& b)
{ 
	return vec3(a.n[VX]+ b.n[VX], a.n[VY] + b.n[VY], a.n[VZ] + b.n[VZ]); 
}

vec3 operator - (const vec3& a, const vec3& b)
{ 
	return vec3(a.n[VX]-b.n[VX], a.n[VY]-b.n[VY], a.n[VZ]-b.n[VZ]); 
}

vec3 operator * (const vec3& a, const float d)
{ 
	return vec3(d*a.n[VX], d*a.n[VY], d*a.n[VZ]); 
}

vec3 operator * (const float d, const vec3& a)
{ 
	return a*d; 
}

vec3 operator * (const mat3& a, const vec3& v) 
{
#define ROWCOL(i) a.v[i].n[0]*v.n[VX] + a.v[i].n[1]*v.n[VY] \
	+ a.v[i].n[2]*v.n[VZ]
	return vec3(ROWCOL(0), ROWCOL(1), ROWCOL(2));
#undef ROWCOL
}

float operator * (const vec3& a, const vec3& b)
{ 
	return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY] + a.n[VZ]*b.n[VZ]); 
}

vec3 operator / (const vec3& a, const float d)
{ 
	float d_inv = 1.0f/d; 
	return vec3(a.n[VX]*d_inv, a.n[VY]*d_inv, a.n[VZ]*d_inv); 
}

vec3 operator ^ (const vec3& a, const vec3& b) 
{
	return vec3(a.n[VY]*b.n[VZ] - a.n[VZ]*b.n[VY],
		a.n[VZ]*b.n[VX] - a.n[VX]*b.n[VZ],
		a.n[VX]*b.n[VY] - a.n[VY]*b.n[VX]);
}

int operator == (const vec3& a, const vec3& b)
{ 
	return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]) && (a.n[VZ] == b.n[VZ]);
}

int operator != (const vec3& a, const vec3& b)
{ 
	return !(a == b); 
}

vec3 Prod(const vec3& a, const vec3& b)
{ 
	return vec3(a.n[VX] * b.n[VX], a.n[VY] * b.n[VY], a.n[VZ] * b.n[VZ]); 
}

float Dot(const vec3& a, const vec3& b)
{
	return a*b;
}

/****************************************************************
*																*
*		    mat3 member functions								*
*																*
****************************************************************/

// CONSTRUCTORS

mat3::mat3() 
{
	v[0] = vec3(0.0,0.0,0.0);
	v[1] = v[2] = v[0];
}

mat3::mat3(const vec3& v0, const vec3& v1, const vec3& v2)
{ 
	v[0] = v0; v[1] = v1; v[2] = v2; 
}

mat3::mat3(const mat3& m)
{ 
	v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; 
}

// Static functions

mat3 mat3::Identity()
{
	return mat3(vec3(1.0, 0.0, 0.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0));
}

mat3 mat3::Rotation3DRad(const vec3& axis, const float angleRad)
{
	float c = cos(angleRad), s = sin(angleRad), t = 1.0f - c;
	vec3 Axis = axis;
	Axis.Normalize();
	return mat3(vec3(t * Axis[VX] * Axis[VX] + c,
		t * Axis[VX] * Axis[VY] - s * Axis[VZ],
		t * Axis[VX] * Axis[VZ] + s * Axis[VY]),
		vec3(t * Axis[VX] * Axis[VY] + s * Axis[VZ],
		t * Axis[VY] * Axis[VY] + c,
		t * Axis[VY] * Axis[VZ] - s * Axis[VX]),
		vec3(t * Axis[VX] * Axis[VZ] - s * Axis[VY],
		t * Axis[VY] * Axis[VZ] + s * Axis[VX],
		t * Axis[VZ] * Axis[VZ] + c)
		);
}


// ASSIGNMENT OPERATORS

mat3& mat3::operator = ( const mat3& m )
{ 
	v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; 
	return *this; 
}

mat3& mat3::operator += ( const mat3& m )
{ 
	v[0] += m.v[0]; v[1] += m.v[1]; v[2] += m.v[2]; 
	return *this; 
}

mat3& mat3::operator -= ( const mat3& m )
{ 
	v[0] -= m.v[0]; v[1] -= m.v[1]; v[2] -= m.v[2]; 
	return *this; 
}

mat3& mat3::operator *= ( const float d )
{ 
	v[0] *= d; v[1] *= d; v[2] *= d; 
	return *this; 
}

mat3& mat3::operator /= ( const float d )
{ 
	v[0] /= d; v[1] /= d; v[2] /= d; 
	return *this; 
}

vec3& mat3::operator [] ( int i) 
{
	assert(! (i < VX || i > VZ));
	return v[i];
}

const vec3& mat3::operator [] ( int i) const 
{
	assert(!(i < VX || i > VZ));
	return v[i];
}

// SPECIAL FUNCTIONS

mat3 mat3::Transpose() const 
{
	return mat3(vec3(v[0][0], v[1][0], v[2][0]),
		vec3(v[0][1], v[1][1], v[2][1]),
		vec3(v[0][2], v[1][2], v[2][2]));
}

// FRIENDS

mat3 operator - (const mat3& a)
{ 
	return mat3(-a.v[0], -a.v[1], -a.v[2]); 
}

mat3 operator + (const mat3& a, const mat3& b)
{ 
	return mat3(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2]); 
}

mat3 operator - (const mat3& a, const mat3& b)
{ 
	return mat3(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2]); 
}

mat3 operator * (const mat3& a, const mat3& b) 
{
#define ROWCOL(i, j) \
	a.v[i].n[0]*b.v[0][j] + a.v[i].n[1]*b.v[1][j] + a.v[i].n[2]*b.v[2][j]
	return mat3(vec3(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2)),
		vec3(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2)),
		vec3(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2)));
#undef ROWCOL // (i, j)
}

mat3 operator * (const mat3& a, const float d)
{ 
	return mat3(a.v[0] * d, a.v[1] * d, a.v[2] * d); 
}

mat3 operator * (const float d, const mat3& a)
{ 
	return a*d; 
}

mat3 operator / (const mat3& a, const float d)
{ 
	return mat3(a.v[0] / d, a.v[1] / d, a.v[2] / d); 
}

int operator == (const mat3& a, const mat3& b)
{ 
	return (a.v[0] == b.v[0]) && (a.v[1] == b.v[1]) && (a.v[2] == b.v[2]); 
}

int operator != (const mat3& a, const mat3& b)
{ 
	return !(a == b); 
}

/****************************************************************
*																*
*		    Quaternion member functions							*
*																*
****************************************************************/

// CONSTRUCTORS

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(const float w, const float x, const float y, const float z)
{
	n[VW] = w; n[VX] = x; n[VY] = y; n[VZ] = z;
}

Quaternion::Quaternion(const Quaternion& q)
{
	n[VW] = q.n[VW]; n[VX] = q.n[VX]; n[VY] = q.n[VY]; n[VZ] = q.n[VZ];
}

// Static functions

float Quaternion::Dot(const Quaternion& q0, const Quaternion& q1)
{
	return q0.n[VW] * q1.n[VW] + q0.n[VX] * q1.n[VX] + q0.n[VY] * q1.n[VY] + q0.n[VZ] * q1.n[VZ];
}

Quaternion Quaternion::UnitInverse(const Quaternion& q)
{
	return Quaternion(q.n[VW], -q.n[VX], -q.n[VY], -q.n[VZ]);
}

float Quaternion::CounterWarp(float t, float fCos)
{
	const float ATTENUATION = 0.82279687f;
	const float WORST_CASE_SLOPE = 0.58549219f;

	float fFactor = 1.0f - ATTENUATION * fCos;
	fFactor *= fFactor;
	float fK = WORST_CASE_SLOPE * fFactor;

	return t * (fK * t * (2.0f * t - 3.0f) + 1.0f + fK);
}

static const float ISQRT_NEIGHBORHOOD = 0.959066f;
static const float ISQRT_SCALE = 1.000311f;
static const float ISQRT_ADDITIVE_CONSTANT = ISQRT_SCALE / (float)sqrt(ISQRT_NEIGHBORHOOD);
static const float ISQRT_FACTOR = ISQRT_SCALE * (-0.5f / (ISQRT_NEIGHBORHOOD * (float)sqrt(ISQRT_NEIGHBORHOOD)));
float Quaternion::ISqrt_approx_in_neighborhood(float s)
{
	return ISQRT_ADDITIVE_CONSTANT + (s - ISQRT_NEIGHBORHOOD) * ISQRT_FACTOR;	
}

// Assignment operators

Quaternion& Quaternion::operator = (const Quaternion& q)
{
	n[VW] = q.n[VW]; n[VX] = q.n[VX]; n[VY] = q.n[VY]; n[VZ] = q.n[VZ];
	return *this;
}

Quaternion& Quaternion::operator += (const Quaternion& q)
{
	n[VW] += q.n[VW]; n[VX] += q.n[VX]; n[VY] += q.n[VY]; n[VZ] += q.n[VZ];
	return *this;
}

Quaternion& Quaternion::operator -= (const Quaternion& q)
{
	n[VW] -= q.n[VW]; n[VX] -= q.n[VX]; n[VY] -= q.n[VY]; n[VZ] -= q.n[VZ];
	return *this;
}

Quaternion& Quaternion::operator *= (const Quaternion& q)
{
	*this = Quaternion(n[VW] * q.n[VW] - n[VX] * q.n[VX] - n[VY] * q.n[VY] - n[VZ] * q.n[VZ],
		n[VW] * q.n[VX] + n[VX] * q.n[VW] + n[VY] * q.n[VZ] - n[VZ] * q.n[VY],
		n[VW] * q.n[VY] + n[VY] * q.n[VW] + n[VZ] * q.n[VX] - n[VX] * q.n[VZ],
		n[VW] * q.n[VZ] + n[VZ] * q.n[VW] + n[VX] * q.n[VY] - n[VY] * q.n[VX]);
	return *this;
}

Quaternion& Quaternion::operator *= (const float d)
{
	n[VW] *= d; n[VX] *= d;	n[VY] *= d; n[VZ] *= d;
	return *this;
}

Quaternion& Quaternion::operator /= (const float d)
{
	n[VW] /= d; n[VX] /= d;	n[VY] /= d; n[VZ] /= d;
	return *this;
}

// Indexing
float& Quaternion::operator [](int i)
{
	return n[i];
}

float Quaternion::operator [](int i) const
{
	return n[i];
}

float& Quaternion::W()
{
	return n[VW];
}

float Quaternion::W() const
{
	return n[VW];
}

float& Quaternion::X()
{
	return n[VX];
}

float Quaternion::X() const
{
	return n[VX];
}

float& Quaternion::Y()
{
	return n[VY];
}

float Quaternion::Y() const
{
	return n[VY];
}

float& Quaternion::Z()
{
	return n[VZ];
}

float Quaternion::Z() const
{
	return n[VZ];
}

// Friends

Quaternion operator - (const Quaternion& q)
{
	return Quaternion(-q.n[VW], -q.n[VX], -q.n[VY], -q.n[VZ]); 
}

Quaternion operator + (const Quaternion& q0, const Quaternion& q1)
{
	return Quaternion(q0.n[VW] + q1.n[VW], q0.n[VX] + q1.n[VX], q0.n[VY] + q1.n[VY], q0.n[VZ] + q1.n[VZ]);
}

Quaternion operator - (const Quaternion& q0, const Quaternion& q1)
{
	return Quaternion(q0.n[VW] - q1.n[VW], q0.n[VX] - q1.n[VX], q0.n[VY] - q1.n[VY], q0.n[VZ] - q1.n[VZ]);
}

Quaternion operator * (const Quaternion& q, const float d)
{
	return Quaternion(q.n[VW] * d, q.n[VX] * d, q.n[VY] * d, q.n[VZ] * d);
}

Quaternion operator * (const float d, const Quaternion& q)
{
	return Quaternion(q.n[VW] * d, q.n[VX] * d, q.n[VY] * d, q.n[VZ] * d);
}

Quaternion operator * (const Quaternion& q0, const Quaternion& q1)
{
	return Quaternion(q0.n[VW] * q1.n[VW] - q0.n[VX] * q1.n[VX] - q0.n[VY] * q1.n[VY] - q0.n[VZ] * q1.n[VZ],
		q0.n[VW] * q1.n[VX] + q0.n[VX] * q1.n[VW] + q0.n[VY] * q1.n[VZ] - q0.n[VZ] * q1.n[VY],
		q0.n[VW] * q1.n[VY] + q0.n[VY] * q1.n[VW] + q0.n[VZ] * q1.n[VX] - q0.n[VX] * q1.n[VZ],
		q0.n[VW] * q1.n[VZ] + q0.n[VZ] * q1.n[VW] + q0.n[VX] * q1.n[VY] - q0.n[VY] * q1.n[VX]);
}

Quaternion operator / (const Quaternion& q, const float d)
{
	return Quaternion(q.n[VW] / d, q.n[VX] / d, q.n[VY] / d, q.n[VZ] / d);
}

bool operator == (const Quaternion& q0, const Quaternion& q1)
{
	return (q0.n[VW] == q1.n[VW]) && (q0.n[VX] == q1.n[VX]) && (q0.n[VY] == q1.n[VY]) && (q0.n[VZ] == q1.n[VZ]);
}

bool operator != (const Quaternion& q0, const Quaternion& q1)
{
	return !(q0 == q1); 
}

// special functions

float Quaternion::SqrLength() const
{
	return n[VW] * n[VW] + n[VX] * n[VX] + n[VY] * n[VY] + n[VZ] * n[VZ];
}

float Quaternion::Length() const
{
	return sqrt(SqrLength());
}

Quaternion& Quaternion::Normalize()
{
	float l = Length();
	if (l < EPSILON || abs(l) > 1e6)
	{
		FromAxisAngle(axisY, 0.0f);
	}else
	{
		*this /= l;
	}

	return *this; 
}

Quaternion& Quaternion::FastNormalize() 
{
	float s = n[VW] * n[VW] + n[VX] * n[VX] + n[VY] * n[VY] + n[VZ] * n[VZ]; // length^2
	float k = ISqrt_approx_in_neighborhood(s);

	if (s <= 0.91521198) {
		k *= ISqrt_approx_in_neighborhood(k * k * s);

		if (s <= 0.65211970) {
			k *= ISqrt_approx_in_neighborhood(k * k * s);
		}
	}

	n[VW] *= k;
	n[VX] *= k;
	n[VY] *= k;
	n[VZ] *= k;

	return * this;
}

Quaternion Quaternion::Inverse() const
{
	return Quaternion(n[VW], -n[VX], -n[VY], -n[VZ]);
}

Quaternion Quaternion::Exp(const Quaternion& q)
{
	// q = A*(x*i+y*j+z*k) where (x,y,z) is unit length
	// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k)
	float angle = sqrt(q.n[VX] * q.n[VX] + q.n[VY] * q.n[VY] + q.n[VZ] * q.n[VZ]);
	float sn, cs;
	sn = sin(angle);
	cs = cos(angle);

	// When A is near zero, sin(A)/A is approximately 1.  Use
	// exp(q) = cos(A)+A*(x*i+y*j+z*k)
	float coeff = ( abs(sn) < EPSILON ? 1.0f : sn/angle );

	Quaternion result(cs, coeff * q.n[VX], coeff * q.n[VY], coeff * q.n[VZ]);

	return result;
}

Quaternion Quaternion::Log(const Quaternion& q)
{
	// q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length
	// log(q) = A*(x*i+y*j+z*k)

	float angle = acos(q.n[VW]);
	float sn = sin(angle);

	// When A is near zero, A/sin(A) is approximately 1.  Use
	// log(q) = sin(A)*(x*i+y*j+z*k)
	float coeff = ( abs(sn) < EPSILON ? 1.0f : angle/sn );

	return Quaternion(0.0f, coeff * q.n[VX], coeff * q.n[VY], coeff * q.n[VZ]);
}

void Quaternion::Zero()
{
	n[VW] = n[VX] = n[VY] = n[VZ] = 0.0f;
}

// Conversion functions
void Quaternion::ToAxisAngle (vec3& axis, float& angleRad) const
{
	//float fLength = Length();
	vec3 v(n[VX], n[VY], n[VZ]);
	float fLength = v.Length();

	if ( fLength < EPSILON )
	{
		angleRad = 0;
		axis[VX] = 0;
		axis[VY] = 0;
		axis[VZ] = 0;
	}
	else
	{
		angleRad = 2.0f * acos(n[VW]);
		float invLength = 1.0f / fLength;
		axis[VX] = n[VX] * invLength;
		axis[VY] = n[VY] * invLength;
		axis[VZ] = n[VZ] * invLength;
	}
}

void Quaternion::FromAxisAngle (const vec3& axis, float angleRad)
{
	float fHalfAngle = angleRad * 0.5f;
	float sn = sin(fHalfAngle);
	n[VW] = cos(fHalfAngle);
	n[VX] = axis[VX] * sn;
	n[VY] = axis[VY] * sn;
	n[VZ] = axis[VZ] * sn;
}



/****************************************************************
*																*
*		    Transform member functions							*
*																*
****************************************************************/

// Constructors
Transform::Transform()
{
	Identity();
}

Transform::Transform(const vec3& translation, const mat3& rotation)
{
	m_translation = translation;
	m_rotation = rotation;
}

Transform::Transform(const vec3& translation)
{
	m_translation = translation;
	m_rotation = mat3::Identity();
}

Transform::Transform(const mat3& rotation)
{
	m_translation = vec3(0.0f, 0.0f, 0.0f);
	m_rotation = rotation;
}

Transform::Transform(const Transform& transform)
{
	m_translation = transform.m_translation;
	m_rotation = transform.m_rotation;
}

// Destructor
Transform::~Transform(void)
{
}

// Member functions
void Transform::Identity()
{
	m_translation = vec3(0.0f, 0.0f, 0.0f);
	m_rotation = mat3::Identity();
}

Transform& Transform::operator = (const Transform& source)
{
	m_translation = source.m_translation;
	m_rotation = source.m_rotation;
	return *this;
}

Transform Transform::Lerp(const float fPerc, const Transform& t0, const Transform& t1)
{
	Transform result;
	result.m_translation = t0.m_translation * (1.0f - fPerc) + t1.m_translation * fPerc;

	Quaternion q0, q1, q;
	q0.FromRotation(t0.m_rotation);
	q1.FromRotation(t1.m_rotation);
	float d = Quaternion::Dot(q0, q1);
	if (d < 0)
		q1 = -q1;
	q = Quaternion::Slerp(fPerc, q0, q1);
	result.m_rotation = q.ToRotation();

	return result;
}

//************************************************************************
// Functions you need to implement
//************************************************************************

//========================================================================
// 3D Matrix

//////////////////////////////////////////////////////////////////////////
// Convert a rotation matrix to Euler angles in ZXY rotation order
// Euler angles are stored to angleRad in radians
// Return true if there is no Gimbol lock, otherwise false
bool mat3::ToEulerAnglesZXY(vec3& angleRad) const
{
	float x, y, z;
	x = asin(v[2][1]);
	if ( abs(cos(x)) < EPSILON )
	{ return false; }
	else
	{
		y = acos(v[2][2]/cos(x));
		z = acos(v[1][1]/cos(x));
		vec3 V(x,y,z);
		angleRad = V;
		return true;
	}
}

//////////////////////////////////////////////////////////////////////////
// Convert Euler angles in ZXY rotation order to rotation matrix
// The input Euler angles are in angleRad in radians
// The returning mat3 is the corresponding rotation matrix
mat3 mat3::FromEulerAnglesZXY(const vec3& angleRad)
{
	float x, y, z;
	x = angleRad[VX]; y = angleRad[VY]; z = angleRad[VZ];
	vec3 v1(cos(z)*cos(y)-sin(z)*sin(x)*sin(y), -1*sin(z)*cos(x), cos(z)*sin(y)+sin(z)*sin(x)*cos(y));
	vec3 v2(sin(z)*cos(y)+cos(z)*sin(x)*sin(y), cos(z)*cos(x), sin(z)*sin(y)-cos(z)*sin(x)*cos(y));
	vec3 v3(-1*cos(x)*sin(y), sin(x), cos(x)*cos(y));
	v[0] = v1; v[1] = v2; v[2] = v3;
	mat3 M(v1, v2, v3);
	return M;
}

//////////////////////////////////////////////////////////////////////////
// Convert rotation matrix to Quaternion
// Return the corresponding Quaternion
Quaternion mat3::ToQuaternion() const 
{
	float W, X, Y, Z;
	float test = v[0][0] + v[1][1] + v[2][2];
	if( test > 0 ) 
	{
		float s = 0.5f / sqrtf(test+ 1.0f);
		W = 0.25f / s;
		X = ( v[2][1] - v[1][2] )*s;
		Y = ( v[0][2] - v[2][0] )*s;
		Z = ( v[1][0] - v[0][1] )*s;
	}
	else 
	{
		if ( v[0][0] > v[1][1] && v[0][0] > v[2][2] ) 
		{
			float s = 2.0f * sqrtf( 1.0f + v[0][0] - v[1][1] - v[2][2]);
			W = (v[2][1] - v[1][2] )/s;
			X = 0.25f * s;
			Y = (v[0][1] + v[1][0] )/s;
			Z = (v[0][2] + v[2][0] )/s;
		} 
		else if (v[1][1] > v[2][2]) 
		{
			float s = 2.0f * sqrtf( 1.0f + v[1][1] - v[0][0] - v[2][2]);
			W = (v[0][2] - v[2][0] )/s;
			X = (v[0][1] + v[1][0] )/s;
			Y = 0.25f * s;
			Z = (v[1][2] + v[2][1] )/s;
		} 
		else 
		{
			float s = 2.0f * sqrtf( 1.0f + v[2][2] - v[0][0] - v[1][1] );
			W = (v[1][0] - v[0][1] )/s;
			X = (v[0][2] + v[2][0] )/s;
			Y = (v[1][2] + v[2][1] )/s;
			Z = 0.25f * s;
		}
	}
	Quaternion q(W,X,Y,Z);
	q.Normalize();
	return q;
}

//////////////////////////////////////////////////////////////////////////
// Convert Quaternion to rotation matrix
// Input is the Quaternion for conversion
void mat3::FromQuaternion(const Quaternion& q)
{
	float s, x, y, z;
	s = q.W(); x = q.X(); y = q.Y(); z = q.Z();
	vec3 v1(1-2*(y*y+z*z), 2*(x*y-s*z), 2*(x*z+s*y));
	vec3 v2(2*(x*y+s*z), 1-2*(x*x+z*z), 2*(y*z-s*x));
	vec3 v3(2*(x*z-s*y), 2*(y*z+s*x), 1-2*(x*x+y*y));
	mat3 M(v1,v2,v3);
	(*this) = M;
}

//========================================================================
// Quaternion

//////////////////////////////////////////////////////////////////////////
// Convert Quaternion to rotation matrix
// Return the corresponding matrix
mat3 Quaternion::ToRotation () const
{
	float s, x, y, z;
	s = n[VW]; x = n[VX]; y = n[VY]; z = n[VZ];
	vec3 v1(1-2*(y*y+z*z), 2*(x*y-s*z), 2*(x*z+s*y));
	vec3 v2(2*(x*y+s*z), 1-2*(x*x+z*z), 2*(y*z-s*x));
	vec3 v3(2*(x*z-s*y), 2*(y*z+s*x), 1-2*(x*x+y*y));
	mat3 M(v1,v2,v3);
	return M;
}

//////////////////////////////////////////////////////////////////////////
// Convert a rotation matrix to Quaternion
// Input is the rotation matrix
// Return the corresponding Quaternion
// You need to handle the case when S is close to zero
void Quaternion::FromRotation (const mat3& rot) 
{
	mat3 v = rot;
	float W, X, Y, Z;
	float test = v[0][0] + v[1][1] + v[2][2]; 
	if( test > 0 ) 
	{
		float s = 0.5f / sqrtf(test + 1.0f);
		W = 0.25f / s;
		X = ( v[2][1] - v[1][2] )*s;
		Y = ( v[0][2] - v[2][0] )*s;
		Z = ( v[1][0] - v[0][1] )*s;
	} 
	else 
	{
		if ( v[0][0] > v[1][1] && v[0][0] > v[2][2] ) 
		{
			float s = 2.0f * sqrtf( 1.0f + v[0][0] - v[1][1] - v[2][2]);
			W = (v[2][1] - v[1][2] )/s;
			X = 0.25f * s;
			Y = (v[0][1] + v[1][0] )/s;
			Z = (v[0][2] + v[2][0] )/s;
		} 
		else if (v[1][1] > v[2][2]) 
		{
			float s = 2.0f * sqrtf( 1.0f + v[1][1] - v[0][0] - v[2][2]);
			W = (v[0][2] - v[2][0] )/s;
			X = (v[0][1] + v[1][0] )/s;
			Y = 0.25f * s;
			Z = (v[1][2] + v[2][1] )/s;
		} 
		else 
		{
			float s = 2.0f * sqrtf( 1.0f + v[2][2] - v[0][0] - v[1][1] );
			W = (v[1][0] - v[0][1] )/s;
			X = (v[0][2] + v[2][0] )/s;
			Y = (v[1][2] + v[2][1] )/s;
			Z = 0.25f * s;
		}
	}

	n[VW] = W; n[VX] = X; n[VY] = Y; n[VZ] = Z;
	Normalize();
}

//////////////////////////////////////////////////////////////////////////
// Slerp interpolation
// Input are: time = t, from Quaternion q0, to Quaternion q1
// Return the Quaternion that is the SLERP(t, q0, q1)
Quaternion Quaternion::Slerp(float t, const Quaternion& q0, const Quaternion& q1)
{
	float omega = acos(Quaternion::Dot(q0,q1));
	float f = 1.0/sin(omega);
	Quaternion q = q0*sin((1-t)*omega) + q1*sin(omega*t);
	q = f*q;
	q.Normalize();
	return q;
}

//////////////////////////////////////////////////////////////////////////
// Compute the intermediate Quaternion for SQUAD
// Input are three quaternions from frame(i-1), frame (i) and frame(i+1)
// Return the intermediate Quaternion for frame(i)
Quaternion Quaternion::Intermediate (const Quaternion& q0, const Quaternion& q1, const Quaternion& q2)
{
	Quaternion q2prime = Double(q0, q1);
	Quaternion q2star = Bisect(q2prime, q2);
	Quaternion q = Slerp(0.333, q1, q2star);
	q.Normalize();
	return q;
}

//////////////////////////////////////////////////////////////////////////
// Squad interpolation
// Compute the Squad interpolation
// Inputs are: time = t, from Quaternion q0, its intermediate Quaternion a,
//                       to Quaternion q1, its intermediate Quaternion b
// Return the Quaternion that is Squad(t, q0, a, b, q1)
Quaternion Quaternion::Squad(float t, const Quaternion& q0, const Quaternion& a, const Quaternion& b, const Quaternion& q1)
{
	Quaternion b0 = q0;
	Quaternion b1 = a;
	Quaternion b2 = b;
	Quaternion b3 = q1;
	Quaternion result = b0*pow(1-t,3) + b1*3*t*pow(1-t,2) 
						+ b2*3*pow(t,2)*(1-t) + b3*pow(t,3);
	result.Normalize();
	return result;
}

//=======================================================================
// Transform

//////////////////////////////////////////////////////////////////////////
// Inverse of a transformation
// Return the inverse of current transformation
Transform Transform::Inverse() const
{
	mat3 R = m_rotation.Transpose();
	vec3 D = -1 * R * m_translation;
	Transform tmp(D, R);
	return tmp;
}

//////////////////////////////////////////////////////////////////////////
// * operator for Transform
// Return the Transform that equals to transform1 * transform2
Transform operator * (const Transform& t1, const Transform& t2)
{
	mat3 R = t1.m_rotation * t2.m_rotation;
	vec3 D = t1.m_rotation*t2.m_translation + t1.m_translation;
	Transform tmp(D,R);
	return tmp;
}

Quaternion Double(const Quaternion& a, const Quaternion& b)
{
	return b*2*Quaternion::Dot(a,b) - a;
}
Quaternion Bisect(const Quaternion& a, const Quaternion& b)
{
	Quaternion result = a + b;
	result = result/result.Length();
	return result;
}

