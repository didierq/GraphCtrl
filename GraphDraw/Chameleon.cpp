#include "GraphDraw.h"


namespace Upp {

namespace GraphDraw_ns {

	CH_STYLE(CH_EmptyGraphDraw, StyleGD, StyleGDDefault) {
		plotBckgndStyle = Blend(SColorShadow(), SColorPaper(), 190); //SLtGray();
		ctrlBckgndStyle = SColorPaper();
		rectSelectStyle = GraphDrawImg::GSELECT();
	}

}


CH_STYLE(XYLTMM_GraphDraw, Style, StyleDefault) {
	gdStyle        = XYLTMM_GraphDraw::CH_EmptyGraphDraw::StyleGDDefault();
	x1LabelStyle   = XYLTMM_GraphDraw::TypeLabelX1::StyleGEXAxisDefault();
	x1AxisStyle    = XYLTMM_GraphDraw::TypeGridAxisX1::StyleGEDefault();
	y1LabelStyle   = XYLTMM_GraphDraw::TypeLabelY1::StyleGEYAxisDefault();
	y1AxisStyle    = XYLTMM_GraphDraw::TypeGridAxisY1::StyleGEDefault();
	titleStyle     = XYLTMM_GraphDraw::TypeLabelTitle::StyleGETitleDefault();
	legendStyle    = XYLTMM_GraphDraw::TypeLegend::StyleGEDefault();
	x1MarkerStyle  = XYLTMM_GraphDraw::TypeMarkerX1::StyleGEDefault();
	y1MarkerStyle  = XYLTMM_GraphDraw::TypeMarkerY1::StyleGEDefault();
}

CH_STYLE(XYY2LTMM_GraphDraw, Style, StyleDefault) {
	gdStyle        = XYY2LTMM_GraphDraw::CH_EmptyGraphDraw::StyleGDDefault();
	x1LabelStyle   = XYY2LTMM_GraphDraw::TypeLabelX1::StyleGEXAxisDefault();
	x1AxisStyle    = XYY2LTMM_GraphDraw::TypeGridAxisX1::StyleGEDefault();
	y1LabelStyle   = XYY2LTMM_GraphDraw::TypeLabelY1::StyleGEYAxisDefault();
	y1AxisStyle    = XYY2LTMM_GraphDraw::TypeGridAxisY1::StyleGEDefault();
	y2LabelStyle   = XYY2LTMM_GraphDraw::TypeLabelY2::StyleGEYAxisDefault();
	y2AxisStyle    = XYY2LTMM_GraphDraw::TypeGridAxisY2::StyleGEDefault2();
	titleStyle     = XYY2LTMM_GraphDraw::TypeLabelTitle::StyleGETitleDefault();
	legendStyle    = XYY2LTMM_GraphDraw::TypeLegend::StyleGEDefault();
	x1MarkerStyle  = XYY2LTMM_GraphDraw::TypeMarkerX1::StyleGEDefault();
	y1MarkerStyle  = XYY2LTMM_GraphDraw::TypeMarkerY1::StyleGEDefault();
	y2MarkerStyle  = XYY2LTMM_GraphDraw::TypeMarkerY2::StyleGEDefault();
}

//} // namespace GraphDraw_ns
} // namespace Upp
