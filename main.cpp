#include "include/UFDSet.h"
#include <vector>
#include <iostream>
#include "include/Pixel.h"
#include "include/CTree.h"

#include "libtim/Common/Types.h"
#include "libtim/Common/Image.h"

using namespace LibTIM;

int main()
{
	/*UFDSet set(16, 4);	// 16 pixels aka 4x4 image
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
	set.selfDisplay();*/

	Image<U8> img;
	img.load("lena.pgm", img);

	CTree ct(img);
	ct.buildComponentTree();

	return 0;
}
