#ifndef SEEK_H_
#define SEEK_H_

#include "Behavior.h"

class Seek : public Behavior
{
public:
	Seek(vec3& target);
    Seek(const Seek& orig);
    virtual Behavior* Clone() const;
	virtual ~Seek();

	virtual vec3 CalculateDesiredVelocity(Actor& actor);

protected:
    vec3 m_pTarget;
};


#endif
