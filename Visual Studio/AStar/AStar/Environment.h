#ifndef Environment_H_
#define Environment_H_

#include <list>
#include <map>
#include <fstream>
#include <vector>
#include "Transformation.h"

struct cell {
  //vec2 ij; // index
  int i;
  int j;
  //vec2 ijP; // parent
  int iP;
  int jP;
  int G;
  int H;
  bool open; // open list
  bool closed; // closed list
  bool occupied;
} ;

// Environment discretizes the ground plane into a 2D occupancy grid
// which supports A* search.  The public interface must be implemented
// for the environment to work correctly with out framework

class Environment
{
public:

    // Our visuals assume our gridsize is 1, but we may want to 
    // change this for different environments
	Environment(int cellsize = 1);
	virtual ~Environment();

    // Get the number of rows in our grid
    virtual unsigned int numRows() const;

    // Get the number of cols in our grid
    virtual unsigned int numCols() const;

    // Given a cell (i,j), return a planar world coordinate (x,z)
	virtual void cellToPos(int i, int j, float& x, float& z);

    // Given a planar world coordinate (x,z), return a cell (i,j)
    virtual void posToCell(float x, float z, int& i, int& j);

    // Return true if the cell (i,j) is occupied, e.g. agents cannot
    // move through this cell
	virtual bool isOccupied(int i, int j);

    // Set the cell (i,j) as occupied
	virtual void setOccupied(int i, int j, bool b);

    // Clear all obstacles.  Resets the map to its starting state
	virtual void clearObstacles();

	// Given the target, returns a path that will get us there
	virtual std::list<vec3> findPath(const vec3& start, const vec3& target);

	void saveMap(const char* filename);

protected:
	int m_width;
	int m_height;
	int m_cellsize;
	float m_worldWidth;
	float m_worldHeight;
	//std::vector<std::vector<bool>> m_occupancyMap;
	std::vector<std::vector<cell>> m_cellMap;
};

#endif
