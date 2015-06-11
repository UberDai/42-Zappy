#include "Pathfinding.hpp"

Pathfinding::Pathfinding()
{

}

Pathfinding::Pathfinding(Pathfinding const &model)
{
	*this = model;
}

Pathfinding::~Pathfinding()
{

}

std::string	Pathfinding::toString() const
{
	return "Pathfinding";
}

Pathfinding&	Pathfinding::operator=(Pathfinding const &copy)
{
	if (this != &copy)
		(void)copy;
	return *this;
}

std::ostream	&operator<<(std::ostream &o, Pathfinding const &i)
{
	o << i.toString();
	return o;
}

int Pathfinding::getTotalCase(int k)
{
	return (2 * k + 1) * (2 * k + 1);
}

int Pathfinding::getNbcircle(int n)
{
	int i;

	for (i = 0; getTotalCase(i) <= n; i++)
		;
	return i;
}

int Pathfinding::getCirclePos(int n)
{
	int circle = getNbcircle(n);
	return ((8 * circle + (n - getTotalCase(circle)) + 1)) % (8 * circle);
}

void Pathfinding::getOffset(int circle, int pos, int XY[2])
{
	int q = pos / (2 * circle);
	int r = pos - q * 2 * circle;

	switch (q)
	{
		case 0:
		XY[0] += 0;
		XY[1] += r;
		break;
		case 1:
		XY[1] += 2 * circle;
		XY[0] += r;
		break;
		case 2:
		XY[0] += 2 * circle;
		XY[1] += 2 * circle - r;
		break;
		default:
		XY[1] += 0;
		XY[0] += 2 * circle - r;
		break;
	}
}

void Pathfinding::Pos(int n, int XY[2])
{
	int circle = getNbcircle(n);
	int pos = getCirclePos(n);

	XY[0] = -circle;
	XY[1] = -circle;
	getOffset(circle, pos, XY);
}