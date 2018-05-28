#ifndef _BSP_TREE
#define _BSP_TREE

#define 

class BSPNode {
public:
	tVector3 v1,v2;
	BSPNode left_tree,right_tree;
	//face left_face, right_face;
	//box bounding_box;
	bool terminal_node; 
	//face terminal_node_faces[]
};

#endif