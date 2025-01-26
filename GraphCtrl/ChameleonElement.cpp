#include "GraphCtrl.h"

namespace Upp {
namespace GraphDraw_ns {

CH_STYLE(StdGridAxisDrawECtrl_GEStyle, StyleGE, StyleGEDefault) {
	// GED - GraphElementDraw
	gdStyle = GridAxisDraw::StyleGEDefault();

	// GEC - GraphElementCtrl
	vSelectStyle     = GraphCtrlImg::VSELECT();
	vAxisSelectStyle = GraphCtrlImg::VAXISSELECT();
	hSelectStyle     = GraphCtrlImg::HSELECT();
	hAxisSelectStyle = GraphCtrlImg::HAXISSELECT();
}

CH_STYLE( StdGridAxisDrawECtrl_GEStyle, StyleGE, StyleGEDefault2 ) {
	// GED - GraphElementDraw
	gdStyle = GridAxisDraw::StyleGEDefault2();

	// GEC - GraphElementCtrl
	vSelectStyle     = GraphCtrlImg::VSELECT();
	vAxisSelectStyle = GraphCtrlImg::VAXISSELECT();
	hSelectStyle     = GraphCtrlImg::HSELECT();
	hAxisSelectStyle = GraphCtrlImg::HAXISSELECT();
}

}; // namespace GraphDraw_ns
}; // namespace Upp
