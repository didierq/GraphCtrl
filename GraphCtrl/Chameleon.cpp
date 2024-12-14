#include "GraphCtrl.h"


namespace Upp {


// ===========================================================================================
// ===========================================================================================
//                     GraphDraw Classes
// ===========================================================================================


namespace GraphDraw_ns {

	CH_STYLE(CH_GraphCtrl_Base, StyleGC, StyleGCDefault) {
		propDlg.separator.width = 1;
		propDlg.SmallSepDist     = 3;
		propDlg.LargeSepDist     = 12;
		//propDlg.separator.style  = Null;
		measureTool.lineColor    = SColorMark;
		measureTool.lineWidth    = 2;
		measureTool.textColor    = SColorMark;
		measureTool.textBackGnd  = GraphCtrlImg::MEASURE_BACKGND();
	}
}

using namespace GraphDraw_ns;

CH_STYLE(XYLTMM_GraphCtrl, Style, StyleDefault) {
	gdStyle        = CH_EmptyGraphDraw::StyleGDDefault();
	gcStyle        = CH_GraphCtrl_Base::StyleGCDefault();
	x1LabelStyle   = XYLTMM_GraphCtrl::TypeLabelX1::StyleGEXAxisDefault();
	x1AxisStyle    = XYLTMM_GraphCtrl::TypeGridAxisX1::StyleGEDefault();
	y1LabelStyle   = XYLTMM_GraphCtrl::TypeLabelY1::StyleGEYAxisDefault();
	y1AxisStyle    = XYLTMM_GraphCtrl::TypeGridAxisY1::StyleGEDefault();
	titleStyle     = XYLTMM_GraphCtrl::TypeLabelTitle::StyleGETitleDefault();
	legendStyle    = XYLTMM_GraphCtrl::TypeLegend::StyleGEDefault();
	x1MarkerStyle  = XYLTMM_GraphCtrl::TypeMarkerX1::StyleGEDefault();
	y1MarkerStyle  = XYLTMM_GraphCtrl::TypeMarkerY1::StyleGEDefault();
}

CH_STYLE(XYY2LTMM_GraphCtrl, Style, StyleDefault) {
	gdStyle        = CH_EmptyGraphDraw::StyleGDDefault();
	gcStyle        = CH_GraphCtrl_Base::StyleGCDefault();
	x1LabelStyle   = XYY2LTMM_GraphCtrl::TypeLabelX1::StyleGEXAxisDefault();
	x1AxisStyle    = XYY2LTMM_GraphCtrl::TypeGridAxisX1::StyleGEDefault();
	y1LabelStyle   = XYY2LTMM_GraphCtrl::TypeLabelY1::StyleGEYAxisDefault();
	y1AxisStyle    = XYY2LTMM_GraphCtrl::TypeGridAxisY1::StyleGEDefault();
	y2LabelStyle   = XYY2LTMM_GraphCtrl::TypeLabelY2::StyleGEYAxisDefault();
	y2AxisStyle    = XYY2LTMM_GraphCtrl::TypeGridAxisY2::StyleGEDefault2();
	titleStyle     = XYY2LTMM_GraphCtrl::TypeLabelTitle::StyleGETitleDefault();
	legendStyle    = XYY2LTMM_GraphCtrl::TypeLegend::StyleGEDefault();
	x1MarkerStyle  = XYY2LTMM_GraphCtrl::TypeMarkerX1::StyleGEDefault();
	y1MarkerStyle  = XYY2LTMM_GraphCtrl::TypeMarkerY1::StyleGEDefault();
	y2MarkerStyle  = XYY2LTMM_GraphCtrl::TypeMarkerY2::StyleGEDefault();
}

} // namespace Upp
