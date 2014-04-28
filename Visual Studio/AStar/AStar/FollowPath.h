#ifndef FollowPath_H_
#define FollowPath_H_

#include "Seek.h"
#include <list>

class FollowPath : public Seek
{
public:
	FollowPath();
    FollowPath(vec3 target);
    FollowPath(const FollowPath& orig);
    virtual Behavior* Clone() const;
	virtual ~FollowPath();

    virtual vec3 CalculateDesiredVelocity(Actor& actor);
    virtual void SetPath(const std::list<vec3>& path);
	virtual bool Arrived(Actor& agent);
	virtual void WalkTowards(const vec3 pos);

protected:
	std::list<vec3> m_path;
	std::list<vec3>::iterator m_nextLocIt;
};

#endif