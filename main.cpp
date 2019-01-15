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
	Image<U8> img;
	img.load("buffalo.pgm", img);

	CTree ct(img);
	ct.buildComponentTree();
	ct.saveDOT("graph.dot");

	return 0;
}
