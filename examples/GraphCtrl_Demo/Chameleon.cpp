#include "GraphCtrl_Demo.h"

using namespace Upp::GraphDraw_ns;

namespace Upp {



#define MAKE_SET_STYLE_METH(GRAPHTYPE, STYLE_NAME)\
GRAPHTYPE::Style MakeStyle_##STYLE_NAME(GRAPHTYPE& g);\
void GraphCtrl_Demo::SetStyle##STYLE_NAME(GRAPHTYPE& g) {\
	static const GRAPHTYPE::Style s = MakeStyle_##STYLE_NAME(g); \
	g.SetStyle(s);\
	g.RefreshLayoutDeep();\
}\
GRAPHTYPE::Style MakeStyle_##STYLE_NAME(GRAPHTYPE& g)




Image MakeVGradientImage(const Size sz, const Color topColor, const Color bottomColor, const int offset, const int alpha = 255) {
	Image topImg = CreateImage(sz, topColor);
	Image botImg = CreateImage(sz, bottomColor);
	Image alphaImg = CreateImage(sz, alpha*Color(0,0,0) );
	if (alpha < 255) return Premultiply( AssignAlpha( VertBlend( topImg, botImg, offset, sz.cy-offset), alphaImg) );
	return VertBlend( topImg, botImg, offset, sz.cy-offset);
}

Image MakeHGradientImage(const Size sz, const Color leftColor, const Color rightColor, const int offset, const int alpha = 255) {
	Image leftImg = CreateImage(sz, leftColor);
	Image rightImg = CreateImage(sz, rightColor);
	Image alphaImg = CreateImage(sz, alpha*Color(0,0,0) );
	if (alpha < 255) return Premultiply( AssignAlpha( HorzBlend( leftImg, rightImg, offset, sz.cy-offset), alphaImg ) );
	return HorzBlend( leftImg, rightImg, offset, sz.cy-offset);
}

Image MakeVGradientButton(int radius, Color topColor, Color bottomColor, double border_width, Color border_color, dword corner  = 0xff) {
	const int off = (int)(border_width + radius);
	Size sz(DPI(16 + off), DPI(16+off));
	Image img = MakeVGradientImage(sz, topColor, bottomColor, off);
	img = MakeElement(sz, radius, img, border_width, border_color, [&](Painter& w, const Rectf& r) { RoundedRect(w, r, radius, radius, corner); } );
	SetHotSpots(img, Point(off,off), Rect(img.GetSize()-1).BottomRight() - Point(off,off));
	return img;
}


MAKE_SET_STYLE_METH(XYY2LTMM_GraphCtrl, Default) {
	return XYY2LTMM_GraphCtrl::StyleDefault();
}

MAKE_SET_STYLE_METH(XYY2LTMM_GraphCtrl, 0) {
	XYY2LTMM_GraphCtrl::Style s = XYY2LTMM_GraphCtrl::StyleDefault();
	s.gdStyle.plotBckgndStyle = GraphCtrl_DemoImg::PLOT_BACKGND2();
	s.gdStyle.ctrlBckgndStyle = GraphCtrl_DemoImg::CTRL_BACKGND3();
	return s;
}


MAKE_SET_STYLE_METH(XYY2LTMM_GraphCtrl, 1) {
	XYY2LTMM_GraphCtrl::Style s = XYY2LTMM_GraphCtrl::StyleDefault();

//	s.gdStyle.plotBckgndStyle = MakeButton(0, SLtGray(), 1, SColorDkShadow());
	s.gdStyle.plotBckgndStyle = MakeVGradientButton(5, SColorFace(), SLtGray(), 1, SColorDkShadow());
	s.gdStyle.ctrlBckgndStyle = Null;// SColorFace();

	s.x1LabelStyle.labelFont = StdFont(15).Bold();
	s.x1LabelStyle.labelColor = SGreen();
	s.x1LabelStyle.geBase.lmntBackgnd = Null;
	s.x1AxisStyle.gdStyle.axisWidth     = 2;
	s.x1AxisStyle.gdStyle.axisColor     = SBlue();
	s.x1AxisStyle.gdStyle.axisTextFont  = StdFont();
	s.x1AxisStyle.gdStyle.axisTextColor = SRed();
	s.x1AxisStyle.gdStyle.axisTickColor = SRed();
	s.x1AxisStyle.gdStyle.gridColor     = SGray();
	s.x1AxisStyle.gdStyle.gridThickness = 1;
	s.x1AxisStyle.gdStyle.gridDash      = "";
	s.x1AxisStyle.gdStyle.primaryTickFactory    << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(3); return t; };
	s.x1AxisStyle.gdStyle.secondaryTickFactory  << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(1); return t; };
	s.x1AxisStyle.gdStyle.geBase.lmntBackgnd = Null;
	
	s.y1LabelStyle.labelFont = StdFont(15).Bold();
	s.y1LabelStyle.labelColor = SGreen();
	s.y1LabelStyle.geBase.lmntBackgnd = Null;
	s.y1AxisStyle.gdStyle.axisWidth     = 2;
	s.y1AxisStyle.gdStyle.axisColor     = SBlue();
	s.y1AxisStyle.gdStyle.axisTextFont  = StdFont();
	s.y1AxisStyle.gdStyle.axisTextColor = SRed();
	s.y1AxisStyle.gdStyle.axisTickColor = SRed();
	s.y1AxisStyle.gdStyle.gridColor     = SGray();
	s.y1AxisStyle.gdStyle.gridThickness = 1;
	s.y1AxisStyle.gdStyle.gridDash      = "";
	s.y1AxisStyle.gdStyle.primaryTickFactory    << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(3); return t; };
	s.y1AxisStyle.gdStyle.secondaryTickFactory  << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(1); return t; };
	s.y1AxisStyle.gdStyle.geBase.lmntBackgnd = Null;
	
	s.x1MarkerStyle.mrkLineColor = Green();
	s.x1MarkerStyle.mrkTickColor = Green();
	s.x1MarkerStyle.mrkLineWidth = 2;
	s.y1MarkerStyle.mrkLineColor = Cyan();
	s.y1MarkerStyle.mrkTickColor = Red();
	s.y1MarkerStyle.mrkLineWidth = 4;

	s.legendStyle.lgdFont = StdFont();
	s.legendStyle.lgdTxtColor = Null;
	s.legendStyle.lgdXSeparation = 20;
	s.legendStyle.lgdStyleLength = 23;
	s.legendStyle.geBase.lmntBackgnd = Null;
	s.legendStyle.lgdFloatBackgnd = GraphCtrl_DemoImg::MARKER_BACKGND();
	s.legendStyle.ldgStyle_SerieSelected     = GraphDrawImg::GSERIE_SELECTED(); // TODO  use the right image
	s.legendStyle.ldgStyle_SerieDataSelected = GraphDrawImg::GSERIE_DATA_SELECTED(); // TODO  use the right image
	
	
	s.legendStyle.ldgTextSelect  = Black(); // TODO  use the right image

	s.titleStyle.geBase.lmntBackgnd = Null;
	s.titleStyle.labelColor = SRed();
	s.titleStyle.labelFont = StdFont(20).Bold().Underline();

	return s;
}

MAKE_SET_STYLE_METH(XYY2LTMM_GraphCtrl, 2) {
	static XYY2LTMM_GraphCtrl::Style s = XYY2LTMM_GraphCtrl::StyleDefault();

	s.gdStyle.plotBckgndStyle = SBlack();

	//Image MakeButton(int radius, Color face, double border_width, Color border_color, dword corner)
	s.gdStyle.ctrlBckgndStyle = MakeButton(4, Blend(SColorShadow(), SColorPaper(), 190), 2, SColorDkShadow());

	s.x1LabelStyle.labelFont = StdFont(10).Bold();
	s.x1LabelStyle.labelColor = SColorText();
	s.x1LabelStyle.geBase.lmntBackgnd = Null;
	s.x1AxisStyle.gdStyle.axisWidth     = 2;
	s.x1AxisStyle.gdStyle.axisColor     = SBlue();
	s.x1AxisStyle.gdStyle.axisTextFont  = StdFont();
	s.x1AxisStyle.gdStyle.axisTextColor = SColorInfoText();
	s.x1AxisStyle.gdStyle.axisTickColor = SRed();
	s.x1AxisStyle.gdStyle.gridColor     = SWhiteGray();
	s.x1AxisStyle.gdStyle.gridThickness = 1;
	s.x1AxisStyle.gdStyle.gridDash      = "";
	s.x1AxisStyle.gdStyle.primaryTickFactory    << []() ->TickMark* { TickMark* t = new TriangleTickMark();  t->SetTickLength(10); return t; };
	s.x1AxisStyle.gdStyle.secondaryTickFactory  << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(1); return t; };
	s.x1AxisStyle.gdStyle.geBase.lmntBackgnd = Null;

	s.y1LabelStyle.labelFont = StdFont(15).Bold();
	s.y1LabelStyle.labelColor = SGreen();
	s.y1LabelStyle.geBase.lmntBackgnd = Null;
	s.y1AxisStyle.gdStyle.axisWidth     = 2;
	s.y1AxisStyle.gdStyle.axisColor     = SBlue();
	s.y1AxisStyle.gdStyle.axisTextFont  = StdFont();
	s.y1AxisStyle.gdStyle.axisTextColor = SRed();
	s.y1AxisStyle.gdStyle.axisTickColor = SRed();
	s.y1AxisStyle.gdStyle.gridColor     = SGray();
	s.y1AxisStyle.gdStyle.gridThickness = 1;
	s.y1AxisStyle.gdStyle.gridDash      = "";
	s.y1AxisStyle.gdStyle.primaryTickFactory    << []() ->TickMark* { TickMark* t = new RoundTickMark();  t->SetTickLength(8); return t; };
	s.y1AxisStyle.gdStyle.secondaryTickFactory  << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(1); return t; };
	s.y1AxisStyle.gdStyle.geBase.lmntBackgnd = GraphCtrl_DemoImg::MARKER_BACKGND();

	s.x1MarkerStyle.mrkLineColor = Yellow();
	s.x1MarkerStyle.mrkTickColor = Red();
	s.x1MarkerStyle.mrkLineWidth = 1;
	s.y1MarkerStyle.mrkLineColor = Cyan();
	s.y1MarkerStyle.mrkTickColor = Red();
	s.y1MarkerStyle.mrkLineWidth = 1;
	
	s.legendStyle.lgdFont = StdFont();
	s.legendStyle.lgdTxtColor = Null;
	s.legendStyle.lgdXSeparation = 20;
	s.legendStyle.lgdStyleLength = 23;
	s.legendStyle.geBase.lmntBackgnd = SYellow();
	s.legendStyle.lgdFloatBackgnd = SYellow();
	s.legendStyle.ldgStyle_SerieSelected = GraphDrawImg::GSERIE_SELECTED(); // TODO  use the right image
	s.legendStyle.ldgStyle_SerieDataSelected = GraphDrawImg::GSERIE_DATA_SELECTED(); // TODO  use the right image
	
	
	s.legendStyle.ldgTextSelect  = Black(); // TODO  use the right image
	
	s.titleStyle.geBase.lmntBackgnd = SColorFace();
	s.titleStyle.labelColor = SColorText();
	s.titleStyle.labelFont = StdFont(20).Bold().Underline();

	return s;
}

MAKE_SET_STYLE_METH(XYY2LTMM_GraphCtrl, 3) {
	static XYY2LTMM_GraphCtrl::Style s = XYY2LTMM_GraphCtrl::StyleDefault();

	s.gdStyle.plotBckgndStyle = GraphCtrl_DemoImg::PLOT_BACKGND();
	s.gdStyle.ctrlBckgndStyle = GraphCtrl_DemoImg::CTRL_BACKGND2();

	s.x1LabelStyle.labelFont = StdFont(15).Bold();
	s.x1LabelStyle.labelColor = SGreen();
	s.x1LabelStyle.geBase.lmntBackgnd = Null;
	s.x1AxisStyle.gdStyle.axisWidth     = 2;
	s.x1AxisStyle.gdStyle.axisColor     = SBlue();
	s.x1AxisStyle.gdStyle.axisTextFont  = StdFont();
	s.x1AxisStyle.gdStyle.axisTextColor = SRed();
	s.x1AxisStyle.gdStyle.axisTickColor = SRed();
	s.x1AxisStyle.gdStyle.gridColor     = SGray();
	s.x1AxisStyle.gdStyle.gridThickness = 1;
	s.x1AxisStyle.gdStyle.gridDash      = "";
	s.x1AxisStyle.gdStyle.primaryTickFactory    << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(3); return t; };
	s.x1AxisStyle.gdStyle.secondaryTickFactory  << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(1); return t; };
	s.x1AxisStyle.gdStyle.geBase.lmntBackgnd = Null;

	s.y1LabelStyle.labelFont = StdFont(15).Bold();
	s.y1LabelStyle.labelColor = SGreen();
	s.y1LabelStyle.geBase.lmntBackgnd = Null;
	s.y1AxisStyle.gdStyle.axisWidth     = 2;
	s.y1AxisStyle.gdStyle.axisColor     = SBlue();
	s.y1AxisStyle.gdStyle.axisTextFont  = StdFont();
	s.y1AxisStyle.gdStyle.axisTextColor = SRed();
	s.y1AxisStyle.gdStyle.axisTickColor = SRed();
	s.y1AxisStyle.gdStyle.gridColor     = SGray();
	s.y1AxisStyle.gdStyle.gridThickness = 1;
	s.y1AxisStyle.gdStyle.gridDash      = "";
	s.y1AxisStyle.gdStyle.primaryTickFactory    << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(3); return t; };
	s.y1AxisStyle.gdStyle.secondaryTickFactory  << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(1); return t; };
	s.y1AxisStyle.gdStyle.geBase.lmntBackgnd = Null;
	
	s.x1MarkerStyle.mrkLineColor = Cyan();
	s.x1MarkerStyle.mrkTickColor = Red();
	s.x1MarkerStyle.mrkLineWidth = 4;
	s.y1MarkerStyle.mrkLineColor = Cyan();
	s.y1MarkerStyle.mrkTickColor = Red();
	s.y1MarkerStyle.mrkLineWidth = 1;

	s.legendStyle.lgdFont = StdFont();
	s.legendStyle.lgdTxtColor = Null;
	s.legendStyle.lgdXSeparation = 20;
	s.legendStyle.lgdStyleLength = 23;
	s.legendStyle.geBase.lmntBackgnd = Null;
	s.legendStyle.lgdFloatBackgnd = SYellow();
	s.legendStyle.ldgStyle_SerieSelected = GraphDrawImg::GSERIE_SELECTED(); // TODO  use the right image
	s.legendStyle.ldgStyle_SerieDataSelected = GraphDrawImg::GSERIE_DATA_SELECTED(); // TODO  use the right image
	s.legendStyle.ldgTextSelect  = Black(); // TODO  use the right image

	s.titleStyle.geBase.lmntBackgnd = Yellow();
	s.titleStyle.labelColor = SRed();
	s.titleStyle.labelFont = StdFont(20).Bold().Underline();

	return s;
}

};