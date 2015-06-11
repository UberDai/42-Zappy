#ifndef PATHFINDING_HEADER
#define PATHFINDING_HEADER

#include <string>
#include <iostream>

class Pathfinding
{
public:
	Pathfinding();
	Pathfinding(Pathfinding const &);
	virtual ~Pathfinding();
	std::string	toString() const;

	Pathfinding&	operator=(Pathfinding const &);


	
int			getTotalCase(int k);
int			getNbcircle(int n);
int			getCirclePos(int n);
void		getOffset(int circle, int pos, int XY[2]);
void		Pos(int n, int XY[2]);
	
};

std::ostream	&operator<<(std::ostream &o, Pathfinding const &i);

#endif /*PATHFINDING_HEADER*/