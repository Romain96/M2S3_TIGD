#include "include/UFDSet.h"
#include <vector>
#include <iostream>
#include "include/Pixel.h"
#include "include/CTree.h"

#include "libtim/Common/Types.h"
#include "libtim/Common/Image.h"
#include "libtim/Algorithms/Thresholding.h"

using namespace LibTIM;

int main()
{
	Image<U8> img;
	img.load("test2_100_100.pgm", img);
	//img.load("test.pgm", img);

	CTree ct(img);
	ct.buildComponentTree();
	ct.saveDOT("graph.dot");

	return 0;
}
