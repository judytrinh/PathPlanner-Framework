#include "stdafx.h"
#include "Environment.h"
#include <queue>

Environment::Environment(int cellsize) : m_cellsize(cellsize)
{
	m_worldWidth = 80.0f;
	m_worldHeight = 80.0f;
	m_width = (int) m_worldWidth / cellsize;
	m_height = (int) m_worldHeight / cellsize;

	// set up global occupancy map
	//m_occupancyMap = vector<vector<bool>>();
	/*for (unsigned int i = 0; i < m_width; ++i) {
		vector<bool> col;
		for (unsigned int j = 0; j < m_height; ++j) {
			col.push_back(false);
		}
		m_occupancyMap.push_back(col);
	}*/

	// set up global cell map
	m_cellMap = vector<vector<cell>>();
	for (unsigned int i = 0; i < m_width; ++i) {
		vector<cell> col;
		for (unsigned int j = 0; j < m_height; ++j) {
			cell currCell;
			currCell.i = i;
			currCell.j = j;
			currCell.iP = -1; // no parent
			currCell.jP = -1;
			currCell.G = 0;
			currCell.H = 0;
			currCell.open = false; // not on open list
			currCell.closed = false; // not on closed list
			currCell.occupied = false;
			col.push_back(currCell);
		}
		m_cellMap.push_back(col);
	}
}

Environment::~Environment()
{
}

unsigned int Environment::numRows() const
{
    return m_height;
}

unsigned int Environment::numCols() const
{
    return m_width;
}

// given the coordinates of a cell (i,j), return the center of 
// the cell (x, 0, z) in world coordinates
void Environment::cellToPos(int i, int j, float& x, float& z)
{
	x = i * m_cellsize - (m_worldWidth/2.0f) + (m_cellsize/2.0f);
	z = j * m_cellsize - (m_worldHeight/2.0f) + (m_cellsize/2.0f);
}

// given world coordinates (x,0,z) return the coordinates of the cell (i,j)
void Environment::posToCell(float x, float z, int& i, int& j)
{
	i = (int)((x + (m_worldWidth/2.0f)) / m_cellsize);// (int)(x + (m_worldWidth/2.0f));
	j = (int)((z + (m_worldHeight/2.0f)) / m_cellsize);// (int)(z + (m_worldHeight/2.0f));
}

// return true if cell (i,j) cannot be traversed
bool Environment::isOccupied(int i, int j)
{
	if (m_cellMap[i][j].occupied) return true;
	return false;
}

// set the cell (i,j) as traversable or not
void Environment::setOccupied(int i, int j, bool b)
{
	m_cellMap[i][j].occupied = b;
}

// empty all cells -> make entire environment traversable
void Environment::clearObstacles()
{
	for (unsigned int i = 0; i < m_width; ++i) {
		for (unsigned int j = 0; j < m_height; ++j) {
			m_cellMap[i][j].occupied = false;
		}
	}
}

bool insertInOrder(vector<cell>& list, cell& c) {
	// don't insert if already in list
	if (c.open) return false;
	// don't insert if we're already done with this
	if (c.closed) return false;

	int cF = c.G + c.H;
	for (vector<cell>::iterator it = list.begin(); it != list.end(); ++it) {
		cell a = *it;
		int aF = a.G + a.H;
		// maintain ordered list
		if (cF <= aF) {
			c.open = true;
			list.insert(it, c);
			return true;
		}
	}

	// if we've gone through the loop without an insertion, this must mean
	// the cell F is larger than any F in the list. thus we push_back at the end
	c.open = true;
	list.push_back(c);
	return true;
}

// given a start position and a target position, return a path from start to
// target as a list of vectors. The implementation should use A*
std::list<vec3> Environment::findPath(const vec3& start, const vec3& target)
{

	vector<cell> openList;
	vector<cell> closedList;
	bool pathFound = false;

	//----------------------------------------------------------------------------------
	//- GRAB i,j OF START AND TARGET ---------------------------------------------------
	// get i,j of start
	int iStart;
	int jStart;
	posToCell(start[0], start[2], iStart, jStart);
	// get i,j of target
	int iEnd;
	int jEnd;
	posToCell(target[0], target[2], iEnd, jEnd);

	//----------------------------------------------------------------------------------
	//- HANDLE STARTING CELL -----------------------------------------------------------
	// add cell at i,j to open list. set dist from itself to 0. this is like the beginning of iterative bfs
	cell& startCell = m_cellMap[iStart][jStart];
	startCell.G = 0;
	// manhattan dist from curr to target
	int hDist = abs(startCell.i - iEnd);
	int vDist = abs(startCell.j - jEnd);
	startCell.H = (hDist + vDist) * 10;
	startCell.open = true;
	startCell.closed = false;
	openList.push_back(startCell);

	// for each cell in the open list
	while(!openList.empty()) {
		cell front = openList.front();
		cell& currCell = m_cellMap[front.i][front.j];
		currCell.open = false;
		currCell.closed = true;
		closedList.push_back(currCell);
		// remove cell we're visiting from open list (pop from the front)
		openList.erase(openList.begin());

		// if we've FINALLY ADDED TARGET CELL TO CLOSED LIST
		if (currCell.i == iEnd && currCell.j == jEnd) {
			// WE'RE DONE
			pathFound = true;
			break;
		}

		// check out all adjacent neighbors of the current cell
		for (unsigned int k = 0; k < 3; ++k) {
			for (unsigned int l = 0; l < 3; ++l) {

				// top left of surrounding cells
				int itopLeft = currCell.i-1;
				int jtopLeft = currCell.j-1;

				// get global i,j of current neighbor we're checking out
				int iNeigh = itopLeft + k;
				int jNeigh = jtopLeft + l;
				
				//----------------------------------------------------------------------------------
				//- DISREGARD STUFF ----------------------------------------------------------------
				// disregard if out of cell index range
				if (iNeigh < 0 || iNeigh > m_width - 1 || jNeigh < 0 || jNeigh > m_height - 1) continue;
				// disregard space if it's occupied
				if (m_cellMap[iNeigh][jNeigh].occupied) continue;
				// disregard if we're looking at the center piece
				if (iNeigh == currCell.i && jNeigh == currCell.j) continue;
				// disregard if CLOSED DUH
				if (m_cellMap[iNeigh][jNeigh].closed) continue;

				// get curr neighbor from cell map
				cell& neighbor = m_cellMap[iNeigh][jNeigh];

				//----------------------------------------------------------------------------------
				//- CHECK IF ON OPEN LIST, IF SO, SPECIAL TREATMENT --------------------------------
				if (neighbor.open) {
					int newG = currCell.G;
					newG += (iNeigh == currCell.i || jNeigh == currCell.j) ? 10 : 14;
					// if it's better! do stuff
					if (newG < neighbor.G) {
						// set new parent to current cell
						neighbor.iP = currCell.i;
						neighbor.jP = currCell.j;
						neighbor.G = newG;
						// find where cell is in open list. remove it if found.
						for (vector<cell>::iterator it = openList.begin(); it != openList.end(); ++it) {
							cell c = *it;
						
							if (c.i == neighbor.i && c.j == neighbor.j) {
								openList.erase(it);
								neighbor.open = false;
								break;
							}
						}
						// re insert in order
						bool INSERTED = insertInOrder(openList, neighbor);

					} else {
						continue; // do nuthin
					}
					continue; // don't execute rest of loop
				}
				//----------------------------------------------------------------------------------
				//- ELSE, DO NORMAL STUFF ----------------------------------------------------------

				// assign current i,j as parent
				neighbor.iP = currCell.i;
				neighbor.jP = currCell.j;

				//----------------------------------------------------------------------------------
				//- CALCULATE G --------------------------------------------------------------------
				// if cell if diag from parent, set G to 14, else set to 10
				neighbor.G = currCell.G;
				neighbor.G += (iNeigh == currCell.i || jNeigh == currCell.j) ? 10 : 14;
				//----------------------------------------------------------------------------------
				//- CALCULATE H --------------------------------------------------------------------
				// manhattan dist from curr to target
				int horizDist = abs(neighbor.i - iEnd);
				int vertDist = abs(neighbor.j - jEnd);
				neighbor.H = (horizDist + vertDist) * 10;

				//----------------------------------------------------------------------------------
				//- ADD NEIGHBOR TO OPENLIST -------------------------------------------------------
				bool INSERTED = insertInOrder(openList, neighbor);

			} // end for (int j....)
		} // end for (int k....)

	} // end of while(!openList.empty()) ...

	std::list<vec3> path;
	//----------------------------------------------------------------------------------
	//- IF PATH IS FOUND, TRAVERSE VIA PARENTS AND RETURN IT LATER ---------------------
	if (pathFound) {
		cell& endCell = m_cellMap[iEnd][jEnd];
		cell curr = endCell;		
		float x, z;
		cellToPos(curr.i, curr.j, x, z);
			// add initial target cell
		path.push_back(vec3(x,0,z));
		// while current is not the start, keep traversing through parent
		while (!(curr.i == iStart && curr.j == jStart)) {
			curr = m_cellMap[curr.iP][curr.jP];
			cellToPos(curr.i, curr.j, x, z);
			path.push_front(vec3(x,0,z));
		}
	}

	//----------------------------------------------------------------------------------
	//- RESET CELLS AND STUFF ----------------------------------------------------------
	for (unsigned int i = 0; i < m_width; ++i) {
		for (unsigned int j = 0; j < m_height; ++j) {
			cell& c = m_cellMap[i][j];
			c.iP = -1, c.jP = -1;
			c.G = 0;
			c.H = 0;
			c.open = false;
			c.closed = false;
		}
	}

	return path;

}
	 
void Environment::saveMap(const char* filename)
{ 
	std::ofstream ofile(filename);
    if (!ofile.good()) return;

    for (unsigned int i = 0; i < numRows(); i++)
    {
        for (unsigned int j = 0; j < numCols(); j++)
        {
            if (isOccupied(i,j))
            {
                ofile << i << " " << j << std::endl;
            }
        }
    }
}