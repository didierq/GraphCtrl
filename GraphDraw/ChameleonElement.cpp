#include "GraphDraw.h"

namespace Upp {
namespace GraphDraw_ns {

// =============================================
//  BlankAreaElement
// =============================================
CH_STYLE(BlankAreaElement, StyleGE, StyleGEDefault) {
	geBase.lmntBackgnd = Null;
}

// =============================================
//  LabelElement
// =============================================
CH_STYLE(LabelElement, StyleGE, StyleGEDefault) {
	geBase.lmntBackgnd = Null;
	labelFont   = StdFont(15).Bold();
	labelColor  = SColorText();
}

CH_STYLE(LabelElement, StyleGE, StyleGETitleDefault) {
	geBase.lmntBackgnd = Null;
	labelFont   = StdFont(20).Bold().Underline();
	labelColor  = SColorMark();
}

CH_STYLE(LabelElement, StyleGE, StyleGEXAxisDefault) {
	geBase.lmntBackgnd = Null;
	labelFont   = StdFont(15).Bold();
	labelColor  = SColorMark();
}

CH_STYLE(LabelElement, StyleGE, StyleGEYAxisDefault) {
	geBase.lmntBackgnd = Null;
	labelFont = StdFont(15).Bold();
	labelColor = SColorMark();
}

// =============================================
//  LegendElement
// =============================================
CH_STYLE(LegendElement, StyleGE, StyleGEDefault) {
	geBase.lmntBackgnd    = Null;
	lgdFont        = StdFont();
	lgdTxtColor    = SColorText();  // if NULL : uses series color by default
	lgdXSeparation = 20; // separation between two legends
	lgdStyleLength = 23;
	lgdFloatBackgnd= GraphDrawImg::LEGEND_FLOAT_STYLE();
	ldgStyle_SerieSelected = GraphDrawImg::GSERIE_SELECTED();
	ldgStyle_SerieDataSelected = GraphDrawImg::GSERIE_DATA_SELECTED();
	ldgTextSelect  = SColorText();
}


// =============================================
//  MarkerElement
// =============================================
CH_STYLE(MarkerElement, StyleGE, StyleGEDefault) {
	geBase.lmntBackgnd  = Null;
	mrkLineColor = SRed();
	mrkTickColor = SRed();
	mrkLineWidth = 1;
}

// =============================================
//  MarkerElement
// =============================================
// Style for X1, Y1
CH_STYLE(GridAxisDraw, StyleGE, StyleGEDefault) {
	geBase.lmntBackgnd   = Null;
	axisWidth     = 2;
	axisColor     = SBlue();
	axisTextFont  = StdFont();
	axisTextColor = SColorText();
	axisTextFont  = StdFont();
	axisTickColor = SColorText();
	gridColor     = SGray();
	gridThickness = 1;
	gridDash      = "";
	primaryTickFactory    << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(3); return t; };
	secondaryTickFactory  << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(1); return t; };
}

// Style for X2, X3 .... Y2, Y3, ....
CH_STYLE(GridAxisDraw, StyleGE, StyleGEDefault2) {
	geBase.lmntBackgnd   = Null;
	axisWidth     = 2;
	axisColor     = SBlue();
	axisTextFont  = StdFont();
	axisTextColor = SColorText();
	axisTextFont  = StdFont();
	axisTickColor = SColorText();
	gridColor     = Null;     
	gridThickness = 1;
	gridDash      = "";
	primaryTickFactory    << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(3); return t; };
	secondaryTickFactory  << []() ->TickMark* { TickMark* t = new LineTickMark();  t->SetTickLength(1); return t; };
}

} // namespace GraphDraw_ns
} // namespace Upp
