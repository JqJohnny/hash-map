#pragma once
#include <string>
#include <iostream>
#include <sstream>

class Movie
{
	std::string mTitle;
	int mYear;
	int mMinutes;

public:
	Movie(std::string tTitle, int tYear, int tMinutes);
	Movie();
	~Movie();

	struct Hashor
	{
		// Remember, you can't use this ascii * 37 loop from the slides.  It only gets a 64 anyway.  (Higher - more unique is better.)
		//int operator()(const Movie &tWhat) //Default Hashor
		//{
		//	int tRunningTotal = 0;
		//	for( int i = 0; i < tWhat.mTitle.size(); i++ )
		//		tRunningTotal = (int)tWhat.mTitle[i] + 37 * tRunningTotal;

		//	std::cout << tWhat.mTitle << " : " << tRunningTotal;// Naughty to have console in class.  This is debugging

		//	return tRunningTotal;
		//}
		int operator()(const Movie& tWhat)
		{
			int tRunningTotal = 0;
			for( int i = 0; i < tWhat.mTitle.size(); i++ )
				tRunningTotal = (int)tWhat.mTitle[i] + tRunningTotal;
			std::string minutes = std::to_string(tWhat.mMinutes);
			std::reverse(minutes.begin(), minutes.end());
			std::stringstream time(minutes);
			tRunningTotal *= tWhat.mMinutes;
			int x = 0;
			time >> x;
			tRunningTotal *= x;
			std::string year = std::to_string(tWhat.mYear);
			std::reverse(year.begin(), year.end());
			std::stringstream year_reversed(year);
			year_reversed >> x;
			tRunningTotal *= tWhat.mYear;
			tRunningTotal *= x;
			std::cout << tWhat.mTitle << " : ";
			return tRunningTotal;
		}


	};
	struct Equalitor
	{
		bool operator()(const Movie &tLHS, const Movie &tRHS)
		{
			if (tLHS.mTitle == tRHS.mTitle)
				if (tLHS.mYear == tRHS.mYear)
					if (tLHS.mMinutes == tRHS.mMinutes)
						return true;

			return false;
		}
	};
};

