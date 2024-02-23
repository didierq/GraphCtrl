#include "SimpleJobSerie.h"

namespace Upp {

#define LAYOUTFILE <GraphSeries/SimpleJobSerie/SimpleJobSerieLayout.lay>
#include <CtrlCore/lay.h>

namespace GraphDraw_ns {


class SimpleJobSerieEditor : public WithJobPropertiesLayout<Ctrl>
{
	CtrlRetriever retr;
	
public:
	SimpleJobSerieEditor() = delete;
	SimpleJobSerieEditor(SimpleJobSerie::StyleGS& styl) {
		CtrlLayout(*this);
//		retr(markWidth, styl.markWidth)
//		    (markColor, styl.markColor)
//		    (lineDash, styl.dash)
//		    (lineThickness, styl.thickness)
//		    (lineColor, styl.color)
//		    (opacity, styl.opacity)
//		    (fillColor, styl.fillColor)
////		    (, styl.markPlot)
////		    (, styl.seriesPlot)
//		    ;

//		lineDash.WhenAction = WhenAction.Proxy();
//		lineThickness.WhenAction = WhenAction.Proxy();
//		lineColor.WhenAction = WhenAction.Proxy();
//		opacity.WhenAction = WhenAction.Proxy();
//		fillColor.WhenAction = WhenAction.Proxy();
//	
//		//markstyle.WhenAction = WhenAction.Proxy();
//		markWidth.WhenAction = WhenAction.Proxy();
//		markColor.WhenAction = WhenAction.Proxy();
	}
	virtual ~SimpleJobSerieEditor() {
		retr.Reset();
	}
	
	void Retrieve() {
		retr.Retrieve();
	}
};



void InitGraphSerieSimpleJobSerie() {
	RLOG("INIT InitGraphSerieSimpleJobSerie()"); 
	Function<GraphSerieEditorInterface*(SimpleJobSerie::StyleGS&)> makeEditorFct = [] (SimpleJobSerie::StyleGS& styl)->GraphSerieEditorInterface* {
			SimpleJobSerieEditor* dlg = new SimpleJobSerieEditor(styl);
			GraphSerieEditorInterface* gei = GraphSerieEditorInterface::Create(dlg, styl);
			return gei;
		};
	SimpleJobSerie::SetDefaultMakeEditorFct(makeEditorFct);
}

}}
