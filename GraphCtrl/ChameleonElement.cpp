#include "GraphCtrl.h"

namespace Upp {
namespace GraphDraw_ns {

#define MAKE_STYLE_METH(KLASS, STYLETYPE, STYLENAME)\
KLASS::STYLETYPE Make__##KLASS##__##STYLENAME##___##STYLETYPE();\
const KLASS::STYLETYPE& KLASS::STYLENAME() {\
	static const KLASS::STYLETYPE s = Make__##KLASS##__##STYLENAME##___##STYLETYPE(); \
	return s;\
}\
KLASS::STYLETYPE Make__##KLASS##__##STYLENAME##___##STYLETYPE()


MAKE_STYLE_METH( StdGridAxisDrawECtrl_GEStyle, StyleGE, StyleGEDefault ) {
	StdGridAxisDrawECtrl_GEStyle::StyleGE s;
	const GridAxisDraw::StyleGE& gad  = GridAxisDraw::StyleGEDefault();

	// GED - GraphElementDraw
	s = gad;

	// GEC - GraphElementCtrl
	s.vSelectStyle     = GraphCtrlImg::VSELECT();
	s.vAxisSelectStyle = GraphCtrlImg::VAXISSELECT();
	s.hSelectStyle     = GraphCtrlImg::HSELECT();
	s.hAxisSelectStyle = GraphCtrlImg::HAXISSELECT();
	return s;
}

MAKE_STYLE_METH( StdGridAxisDrawECtrl_GEStyle, StyleGE, StyleGEDefault2 ) {
	StdGridAxisDrawECtrl_GEStyle::StyleGE s;
	const GridAxisDraw::StyleGE& gad  = GridAxisDraw::StyleGEDefault2();

	// GED - GraphElementDraw
	s = gad;

	// GEC - GraphElementCtrl
	s.vSelectStyle     = GraphCtrlImg::VSELECT();
	s.vAxisSelectStyle = GraphCtrlImg::VAXISSELECT();
	s.hSelectStyle     = GraphCtrlImg::HSELECT();
	s.hAxisSelectStyle = GraphCtrlImg::HAXISSELECT();
	return s;
}

}; // namespace GraphDraw_ns
}; // namespace Upp
