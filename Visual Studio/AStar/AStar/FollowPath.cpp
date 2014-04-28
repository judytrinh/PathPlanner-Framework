#include "stdafx.h"
#include "FollowPath.h"

FollowPath::FollowPath() : Seek(vec3(0,0,0))
{
}
FollowPath::FollowPath(vec3 target) : Seek(target)
{
}

FollowPath::FollowPath(const FollowPath& orig) : Seek(orig)
{
}

Behavior* FollowPath::Clone() const
{
    return new FollowPath(*this);
}

FollowPath::~FollowPath()
{
}

void FollowPath::SetPath(const std::list<vec3>& path)
{
    m_path = path;
    if (m_path.size() > 0)
	{
		m_nextLocIt = m_path.begin()++;
		WalkTowards(*m_path.begin());
	}
}

vec3 FollowPath::CalculateDesiredVelocity(Actor& actor)
{
    // Walk along current path
	if (m_path.size() > 0 && m_nextLocIt != m_path.end() && Arrived(actor))
	{
		WalkTowards(*m_nextLocIt);
		++m_nextLocIt;
	}

    return Seek::CalculateDesiredVelocity(actor);
}


bool FollowPath::Arrived(Actor& actor)
{
	vec3 agentPos = actor.globalPosition;
	vec3 seekPos = m_pTarget;

	double distance = (agentPos - seekPos).Length();
	return (distance < 1.0);
}

void FollowPath::WalkTowards(const vec3 pos)
{
	m_pTarget = pos;
}

