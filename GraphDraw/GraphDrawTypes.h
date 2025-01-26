/*
 * GraphDrawTypes.h
 *
 *  Created on: 25 mai 2012
 *      Author: didier
 */

#ifndef GRAPHDRAWTYPES_H_
#define GRAPHDRAWTYPES_H_


namespace GraphDraw_ns {

	// Physical screen data types
	typedef int                     TypeScreenCoord;
	typedef Point_<TypeScreenCoord> PointScreen;
	typedef Rect_<TypeScreenCoord>  RectScreen;
	

	// Logical graph data types
	typedef double                  TypeGraphCoord;
	typedef Point_<TypeGraphCoord>  PointGraph;
	typedef Rect_<TypeGraphCoord>   RectGraph;
};

#endif /* GRAPHDRAWTYPES_H_ */
