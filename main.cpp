#include "include/UFDSet.h"
#include <vector>
#include <iostream>
#include "include/Pixel.h"
#include "include/CTree.h"

#include "libtim/Common/Types.h"
#include "libtim/Common/Image.h"
#include "libtim/Algorithms/Thresholding.h"

using namespace LibTIM;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "usage : " << argv[0] << " binary_pgm_image dot_graph_name" << std::endl;
		exit(1);
	}

	// repositories
	std::string images_repo = "images/";
	std::string graphs_repo = "graphs/";

	// loading binary PGM image
	std::cout << "loading image : " << images_repo << argv[1] << std::endl;
	Image<U8> img;
	img.load((images_repo + argv[1]).c_str(), img);

	// building component tree
	CTree ct(img);
	ct.buildComponentTree();

	// saving component tree in DOT format
	std::cout << "saving DOT graph in " << graphs_repo + argv[2] << std::endl;
	ct.saveDOT((graphs_repo + argv[2]).c_str());

	return 0;
}
