#include "include/UFDSet.h"
#include <vector>
#include <iostream>
#include "include/Pixel.h"

int main()
{
	UFDSet set(16, 4);	// 16 pixels aka 4x4 image
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			set.makeSet(Pixel(i,j,255));
		}
	}

	//set.selfDisplay();

	set.link(Pixel(0,0,255), Pixel(1,1,255));
	set.link(Pixel(0,0,255), Pixel(2,2,255));
	set.selfDisplay();

	return 0;
}
