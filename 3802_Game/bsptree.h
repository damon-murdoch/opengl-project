#ifndef INCLUDE_BSP_TREE
#define INCLUDE_BSP_TREE

#include <fstream.h>

#include "common.h"

// http://collaboration.cmc.ec.gc.ca/science/rpn/biblio/ddj/Website/articles/DDJ/1995/9507/9507d/9507d.htm

class BSP_Node_List;
class BSP_Node{
private:
	unsigned short index;
	BSP_Node *FrontNode,*BackNode;
	short Point_Count;
	tVector3 * point_list;
	tVector3 center;
	tVector3 normal;
	float D;

	unsigned long Split_Poly(BSP_Node *Plane,tVector3*split_points);

	void Compute_Center(void);
	void Compute_Normal(void);
	void ComputeD(void);
public:
};

#endif // INCLUDE_BSP_TREE