#include "ScatterSeriesEditors.h"

#include <DropFont/DropFont.h>
#include <DropLineDash/DropLineDash.h>
#include <GraphSeries/ScatterSeries/ScatterSeries.h>

namespace Upp {

#define LAYOUTFILE <GraphSeries/ScatterSeriesEditors/ScatterSeriesEditors.lay>
#include <CtrlCore/lay.h>

namespace GraphDraw_ns {


class ScatterPropertiesEditorDlg : public WithScatterSerieEditor<Ctrl> {
	CtrlRetriever retr;
	
public:
	ScatterPropertiesEditorDlg() = delete;
	ScatterPropertiesEditorDlg(ScatterGraphSeries::StyleGS& styl) {
		CtrlLayout(*this);
		retr(markWidth, styl.markWidth)
		    (markColor, styl.markColor)
		    (lineDash, styl.dash)
		    (lineThickness, styl.thickness)
		    (lineColor, styl.color)
		    (opacity, styl.opacity)
		    (fillColor, styl.fillColor)
//		    (, styl.markPlot)
//		    (, styl.seriesPlot)
		    ;

		lineDash.WhenAction = WhenAction.Proxy();
		lineThickness.WhenAction = WhenAction.Proxy();
		lineColor.WhenAction = WhenAction.Proxy();
		opacity.WhenAction = WhenAction.Proxy();
		fillColor.WhenAction = WhenAction.Proxy();
	
		//markstyle.WhenAction = WhenAction.Proxy();
		markWidth.WhenAction = WhenAction.Proxy();
		markColor.WhenAction = WhenAction.Proxy();
	}
	virtual ~ScatterPropertiesEditorDlg() {
		retr.Reset();
	}
	
	void Retrieve() {
		retr.Retrieve();
	}
};


void InitGrapSerieScatterEditors() {
	Function<GraphSerieEditorInterface*(ScatterGraphSeries::StyleGS&)> f = [] (ScatterGraphSeries::StyleGS& styl)->GraphSerieEditorInterface* {
			ScatterPropertiesEditorDlg* dlg = new ScatterPropertiesEditorDlg(styl);
			GraphSerieEditorInterface* gei = GraphSerieEditorInterface::Create(dlg, styl);
			return gei;
		};
	ScatterGraphSeries::SetDefaultMakeScatterEditorFct(f);
}

}
}
