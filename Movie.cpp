#include "stdafx.h"
#include "Movie.h"

Movie::Movie()
{
}

Movie::Movie(std::string tTitle, int tYear, int tMinutes)
{
	mTitle = tTitle;
	mYear = tYear;
	mMinutes = tMinutes;
}



Movie::~Movie()
{
}
