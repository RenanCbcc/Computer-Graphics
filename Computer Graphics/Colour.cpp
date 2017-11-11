#include "Colour.h"


bool Colour::operator!=(const Colour &colour) const
{
	return ((colour.r != this->r) || (colour.g != this->g) || (colour.b != this->b));
}
