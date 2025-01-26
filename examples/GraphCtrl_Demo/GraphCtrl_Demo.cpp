// https://github.com/SaschaWillems/Vulkan/blob/master/examples/renderheadless/renderheadless.cpp

// ===================================
// ===================================
//
//     GT 9600  +  Q6600
//
// ===================================
// ===================================

//  Use shared libs
// GCC     -O3 -ffunction-sections 
 
// ============== TIMING STATS ==================
// paint() > Max=985.044567ms   Min=2.585503ms   Average=79.9070829047619ms   ( count:42 )   Current=14.78064ms
// paintBckGnd() > Max=136.421719ms   Min=0.79223ms   Average=5.52855507142857ms   ( count:42 )   Current=7.414448ms
// initBackGndPaint() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_chPaint() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_copyImage() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_paintImage() > Max=10.123214ms   Min=0.789158ms   Average=1.41763347619048ms   ( count:42 )   Current=7.411516ms
// _preparePaintPlotPointsListTiming() > Max=11.063079ms   Min=6.711261ms   Average=8.1327915ms   ( count:6 )   Current=6.711261ms
// _fullPaintPlotDataTiming() > Max=476.838408ms   Min=388.679044ms   Average=425.5401815ms   ( count:6 )   Current=399.362978ms
// fastPaintPlotDataTiming() > Max=11.57729ms   Min=7.301243ms   Average=9.52202679411765ms   ( count:34 )   Current=10.800004ms
// totalFullPaintPlotDataTiming() > Max=929.909418ms   Min=801.78314ms   Average=867.534436ms   ( count:3 )   Current=801.78314ms
// paintPlotDataGlobalTiming() > Max=933.405315ms   Min=0.798586ms   Average=73.4578389047619ms   ( count:42 )   Current=5.895565ms
// ===============================================

// ===================================
// ===================================
//
//      GT 9600  +  RYZEN 2700
//
// ===================================
// ===================================
 
// ------------------------------------------------------------------------------------------------------------------------------------
//   svn.14449
// ------------------------------------------------------------------------------------------------------------------------------------
//  Use shared libs
// CLANG     -O3 -ffunction-sections 
// 
// ============== TIMING STATS ==================
// paint() > Max=253.213722ms   Min=219.279984ms   Average=232.872180333333ms   ( count:9 )   Current=221.786316ms
// paintBckGnd() > Max=0.003997ms   Min=0.002204ms   Average=0.00261711111111111ms   ( count:9 )   Current=0.002625ms
// initBackGndPaint() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_chPaint() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_copyImage() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_paintImage() > Max=0.003427ms   Min=0.001633ms   Average=0.00206522222222222ms   ( count:9 )   Current=0.001954ms
// _preparePaintPlotPointsListTiming() > Max=2.862029ms   Min=0.894217ms   Average=1.07707348148148ms   ( count:27 )   Current=0.908975ms
// _fullPaintPlotDataTiming() > Max=87.898566ms   Min=70.754233ms   Average=76.3348122962963ms   ( count:27 )   Current=71.837685ms
// fastPaintPlotDataTiming() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// totalFullPaintPlotDataTiming() > Max=252.63105ms   Min=218.594528ms   Average=232.241960222222ms   ( count:9 )   Current=221.153318ms
// paintPlotDataGlobalTiming() > Max=253.043353ms   Min=219.002964ms   Average=232.650830444444ms   ( count:9 )   Current=221.604374ms
// ===============================================

// 
// ------------------------------------------------------------------------------------------------------------------------------------
//   svn.14515
// ------------------------------------------------------------------------------------------------------------------------------------
// CLANG     -O3 -ffunction-sections -fdata-sections
// Use shared libs
// svn.14515
// ============== TIMING STATS ==================
// paint() > Max=233.946719ms   Min=213.401665ms   Average=220.001335272727ms   ( count:11 )   Current=233.946719ms
// paintBckGnd() > Max=0.005811ms   Min=0.002014ms   Average=0.00319145454545455ms   ( count:11 )   Current=0.005811ms
// initBackGndPaint() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_chPaint() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_copyImage() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_paintImage() > Max=0.00517ms   Min=0.001502ms   Average=0.00256836363636364ms   ( count:11 )   Current=0.00517ms
// _preparePaintPlotPointsListTiming() > Max=2.285337ms   Min=0.864933ms   Average=1.03087933333333ms   ( count:33 )   Current=0.868088ms
// _fullPaintPlotDataTiming() > Max=84.49567ms   Min=67.860559ms   Average=72.1033823939394ms   ( count:33 )   Current=71.240609ms
// fastPaintPlotDataTiming() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// totalFullPaintPlotDataTiming() > Max=233.31284ms   Min=212.799205ms   Average=219.408837727273ms   ( count:11 )   Current=233.31284ms
// paintPlotDataGlobalTiming() > Max=233.729392ms   Min=213.148921ms   Average=219.780807181818ms   ( count:11 )   Current=233.729392ms
// ===============================================

// ===================================
// ===================================
//    SAPPHIRE  RX580  +  RYZEN 2700
// ===================================
// ===================================

// ------------------------------------------------------------------------------------------------------------------------------------
//   svn.14557
// ------------------------------------------------------------------------------------------------------------------------------------
// CLANG     -O3 -ffunction-sections -fdata-sections
// Use shared libs
// svn.14515

// ============== TIMING STATS ==================
// paint() > Max=221.241955ms   Min=216.823786ms   Average=218.420374875ms   ( count:8 )   Current=220.558707ms
// paintBckGnd() > Max=0.005311ms   Min=0.001717ms   Average=0.003756125ms   ( count:8 )   Current=0.004203ms
// initBackGndPaint() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_chPaint() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_copyImage() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// paintBackGndTiming_paintImage() > Max=0.004702ms   Min=0.001378ms   Average=0.00322225ms   ( count:8 )   Current=0.003664ms
// _preparePaintPlotPointsListTiming() > Max=3.349448ms   Min=0.640797ms   Average=1.04246704166667ms   ( count:24 )   Current=0.666445ms
// _fullPaintPlotDataTiming() > Max=76.646966ms   Min=69.970102ms   Average=71.5641109166667ms   ( count:24 )   Current=73.39436ms
// fastPaintPlotDataTiming() > Max=0ms   Min=1e21ms   Average=?ms   ( count:0 )   Current=0ms
// totalFullPaintPlotDataTiming() > Max=220.656029ms   Min=216.186433ms   Average=217.824811625ms   ( count:8 )   Current=219.974628ms
// paintPlotDataGlobalTiming() > Max=221.010871ms   Min=216.61855ms   Average=218.20926475ms   ( count:8 )   Current=220.34818ms
// ===============================================



// ------------------------------------------------------------------------------------------------------------------------------------
// Upp GIT version : a79380bc2fb0bfa69b462b415eb84a5b2a86ff6c   Fri Jan 10 15:28:13 2025 +0100
// ------------------------------------------------------------------------------------------------------------------------------------
// -DflagMT -DflagGD_TIMINGS -DflagCLANG -DflagSHARED -DflagBLITZ -DflagPOSIX -DflagLINUX  -fexceptions -O3 -ffunction-sections -fdata-sections -x c++ -std=c++17 -Wno-logical-op-parentheses

// 3 * 100 000 points of data
//============== TIMING STATS ==================
//paint()                                    > ( count:32 )  	Average=227.541047125ms  	Max=237.865329ms  	Min=0.206689ms  	Current=0.206689ms
//  paintBckGnd                              > ( count:32 )  	Average=0.00688453125ms  	Max=0.015529ms  	Min=0.004468ms  	Current=0.004468ms
//    initBackGndPaint                       > ( count:0 )  	Average=ms  				Max=0ms  			Min=1e21ms  		Current=0ms
//    paintBackGndTiming_chPaint             > ( count:0 )  	Average=ms  				Max=0ms 			Min=1e21ms  		Current=0ms
//    paintBackGndTiming_copyImage           > ( count:0 )  	Average=ms  				Max=0ms  			Min=1e21ms  		Current=0ms
//    paintBackGndTiming_paintImage          > ( count:32 )  	Average=0.00672890625ms  	Max=0.015369ms  	Min=0.004308ms  	Current=0.004308ms
//    AllSeries PaintPlotData                > ( count:0 )  	Average=ms  				Max=0ms  			Min=1e21ms  		Current=0ms
//    paintPlotDataGlobal                    > ( count:32 )  	Average=227.302745375ms  	Max=237.617843ms  	Min=0.001764ms  	Current=0.001764ms
//      fastPaintPlotData                    > ( count:0 )  	Average=ms  				Max=0ms  			Min=1e21ms  		Current=0ms
//      fullPaintPlotData                    > ( count:0 )  	Average=ms  				Max=0ms  			Min=1e21ms  		Current=0ms
//        preparePaintPlotPointsList         > ( count:0 )  	Average=ms  				Max=0ms  			Min=1e21ms  		Current=0ms
//    PaintSelectedPlotData                  > ( count:32 )  	Average=0.00067134375ms  	Max=0.005571ms  	Min=0.00027ms  		Current=0.00027ms
//    PaintGraphElements                     > ( count:32 )  	Average=0.202327ms  		Max=0.252675ms  	Min=0.171763ms  	Current=0.176923ms
//===============================================

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//                    DATA SIZE CHAGE !!
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// 3 * 300 000 points of data
//============== TIMING STATS ==================
//paint()                                    > ( count:32 )  	Average=566.79212678125ms  	Max=712.630136ms  	Min=0.439256ms  	Current=0.57399ms
//  paintBckGnd                              > ( count:32 )  	Average=0.00892709375ms  	Max=0.022603ms  	Min=0.004909ms  	Current=0.007755ms
//    initBackGndPaint                       > ( count:0 )  	Average=ms  	Max=0ms  	Min=1e21ms  	Current=0ms
//    paintBackGndTiming_chPaint             > ( count:0 )  	Average=ms  	Max=0ms  	Min=1e21ms  	Current=0ms
//    paintBackGndTiming_copyImage           > ( count:0 )  	Average=ms  	Max=0ms  	Min=1e21ms  	Current=0ms
//    paintBackGndTiming_paintImage          > ( count:32 )  	Average=0.00873121875ms  	Max=0.022152ms  	Min=0.004799ms  	Current=0.007494ms
//    AllSeries PaintPlotData                > ( count:0 )  	Average=ms  	Max=0ms  	Min=1e21ms  	Current=0ms
//    paintPlotDataGlobal                    > ( count:32 )  	Average=566.445215ms  	Max=712.416034ms  	Min=0.00513ms  	Current=0.00513ms
//      fastPaintPlotData                    > ( count:0 )  	Average=ms  	Max=0ms  	Min=1e21ms  	Current=0ms
//      fullPaintPlotData                    > ( count:0 )  	Average=ms  	Max=0ms  	Min=1e21ms  	Current=0ms
//        preparePaintPlotPointsList         > ( count:0 )  	Average=ms  	Max=0ms  	Min=1e21ms  	Current=0ms
//    PaintSelectedPlotData                  > ( count:32 )  	Average=0.00061684375ms  	Max=0.001002ms  	Min=0.000341ms  	Current=0.000591ms
//    PaintGraphElements                     > ( count:32 )  	Average=0.30421715625ms  	Max=2.896591ms  	Min=0.160101ms  	Current=0.502034ms
//===============================================

#include "GraphCtrl_Demo.h"

using namespace Upp::GraphDraw_ns;

namespace Upp {
	#define IMAGECLASS GraphCtrl_DemoImg
	#define IMAGEFILE <examples/GraphCtrl_Demo/GraphCtrl_Demo.iml>
	#include <Draw/iml_source.h>
}


namespace Upp {


class ExclusionAreaDraw : public GraphElement
{
	private:
	CoordinateConverter& _x1Converter;
	CoordinateConverter& _y1Converter;
	typedef  GraphElement _B;

	public:
	typedef ExclusionAreaDraw   CLASSNAME;
	ExclusionAreaDraw(CoordinateConverter& xConv, CoordinateConverter& yConv) :  _x1Converter(xConv), _y1Converter(yConv) {};
	~ExclusionAreaDraw() {};


	virtual void PaintElement(Draw& dw, int scale) { /* do noting */}
	virtual void PaintOnPlot_underData(Draw& dw, int otherWidth, int scale)
	{
		int xMin = _x1Converter.getScreenMin();
		int xMax = _x1Converter.getScreenMax();
		int yMin = _y1Converter.getScreenMin();
		int yMax = _y1Converter.getScreenMax();

		Rect a(_x1Converter.toScreen(_x1Converter.getGraphMin()), _y1Converter.toScreen(_y1Converter.getGraphMax()), _x1Converter.toScreen(5), _y1Converter.toScreen(4));
		Rect b(_x1Converter.toScreen(7), _y1Converter.toScreen(8), _x1Converter.toScreen(_x1Converter.getGraphMax()), _y1Converter.toScreen(_y1Converter.getGraphMin()));
		a.Normalize();
		b.Normalize();
		dw.DrawRect(a, Color(148, 235, 242));
		dw.DrawRect(b, Color(250, 150, 150));

	}
};



Pointf opara1(double t) {return Pointf(0.5*cos(2*M_PI*t), 0.5*sin(2*M_PI*t));}

void para1(Pointf& xy, double t) {xy = Pointf(cos(2*M_PI*t), sin(2*M_PI*t));}
void para2(Pointf& xy, double t) {xy = Pointf(0.5*cos(6*M_PI*t)+3*t-1, 1.5+0.5*sin(6*M_PI*t));}
void para3(Pointf& xy, double t) {xy = Pointf(3+(0.5+t)*cos(6*M_PI*t), (0.5+t)*sin(6*M_PI*t));}
void para4(Pointf& xy, double t) {xy = Pointf(0, -0.25+0.5*t);}
void para5(Pointf& xy, double t) {xy = Pointf(-0.25+0.5*t, 0);}

void para1p(Pointf& xy, double t, double a, double b) 	{xy = Pointf(a*cos(2*M_PI*t),b*sin(2*M_PI*t));}
void para3p(Pointf& xy, double t, double a) 			{xy = Pointf(a+(0.5+t)*cos(6*M_PI*t),(0.5+t)*sin(6*M_PI*t));}


double funct1(double x)	{return 3;}
double funct2(double x)	{return (x*x-5);}
double funct3(double x)	{return (-x*x-5);}
void   vfunct1(double& y, double x) {y = 0;}
void   vfunct2(double& y, double x) {y = x*x;}
void   vfunct3(double& y, double x) {y = -x*x;}

void   vfunct1_(double& y, double x) {y = (x-1000100);}



void paraXY(Pointf& xy, double t) {xy = Pointf(0.5*cos(6*M_PI*t)+3*t-1, 1.5+0.5*sin(6*M_PI*t));}
double functx(double t)	{return (0.5*cos(6*M_PI*t)+3*t-1); }
double functy(double t)	{return (1.5+0.5*sin(6*M_PI*t) ); }



typedef DynamicMarkerECtrl  MarkerElementType;
typedef DynamicMarkerECtrl  MarkerElementType2;

#define LINKED_MARKER_ID1 101
#define LINKED_MARKER_ID2 102
#define LINKED_MARKER_ID3 103

#define MARKER_X1_ID 125
#define MARKER_X2_ID 126
#define MARKER_Y1_ID 45000
#define MARKER_Y2_ID 1000


MarkerElementType& SetDynMarkerGraph(XY_GraphCtrl& g) {
	g.SetCtrlBackgroundStyle(GraphCtrl_DemoImg::CTRL_BACKGND() );
	g.GetCoordConverterX1().UpdateGraphSize(-5,5);
	g.GetCoordConverterY1().UpdateGraphSize(-20,20);

	MarkerElementType& markerElem = g.CreateElement1< MarkerElementType , TOP_OF_GRAPH>(30, -1, g.GetCoordConverterX1() );
	SmartTextTickMark& marker = markerElem.AddMarker(LINKED_MARKER_ID1, "\1[ [ [*0 Linked]]]" );
	marker.SetBackGroundStyle(GraphCtrl_DemoImg::MARKER_BACKGND());
	
	g.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&funct1).PlotStyle<LineSeriesPlot>().Legend("3");
	g.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&funct2).PlotStyle<LineSeriesPlot>().Legend("x*x-5");
	g.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&vfunct3).PlotStyle<LineSeriesPlot>().Legend("y = -x*x");
	
	return markerElem;
}



void GraphCtrl_Demo::onXMarkerMoveCBK( const GraphDraw_ns::MarkerPosList& markers, int ID,  void* m) {
	if (ID >=0) { tabFullDemo.xMarkerPos.SetData(markers.Get(ID).GetPos()); }
}

void GraphCtrl_Demo::onXMarkerSelectCBK( const GraphDraw_ns::MarkerPosList& markers, int ID,  void* m) {
	//if (ID == MARKER_X1_ID)	{ tabFullDemo.xMarkerPos.SetStyle(markerActiveStyle); }
	tabFullDemo.xMarkerPos.SetStyle(markerActiveStyle);
}

void GraphCtrl_Demo::onXMarkerReleaseCBK( const GraphDraw_ns::MarkerPosList& markers, int ID,  void* m) {
	tabFullDemo.xMarkerPos.SetStyle(EditField::StyleDefault());
}

void GraphCtrl_Demo::onY1MarkerMoveCBK( const GraphDraw_ns::MarkerPosList& markers, int ID,  void* m) {
	if (ID >=0) { tabFullDemo.y1MarkerPos.SetData(markers.Get(ID).GetPos()); }
}

void GraphCtrl_Demo::onY2MarkerMoveCBK( const GraphDraw_ns::MarkerPosList& markers, int ID,  void* m) {
	if (ID >=0) { tabFullDemo.y2MarkerPos.SetData(markers.Get(ID).GetPos()); }
}


void GraphCtrl_Demo::onMarkerMoveCBK_tabDyn( const GraphDraw_ns::MarkerPosList& markers, int ID, void* elemnt )
{
	if (ID >=0) {
		tabDynMarker.markerPos.SetData(markers.Get(ID).GetPos());
	}
}

void GraphCtrl_Demo::DoDrawPerfTest() {
	tabBigData.graph.DoDataDrawPerfTest(30);
}



bool DoNothing() {
	return false;
}

GraphCtrl_Demo::GraphCtrl_Demo()
{
	VALIDATE_IML(GraphCtrl_DemoImg);
	
	
	markerActiveStyle = EditField::StyleDefault();
	markerActiveStyle.disabled = Color(255, 255, 0);

	CtrlLayout(*this, "GraphCtrl DEMO");
	Sizeable();
	MinimizeBox();
	MaximizeBox();
	
	addAsTab(tabFullDemo, "Full Demo");
	addAsTab(tabOpenGL, "OpenGL 1");
	addAsTab(tabOpenGL, "OpenGL 2");
	addAsTab(tabBigData, "Big Data Set");
	addAsTab(tab1DataPoint, "1 Data PointPoint");
	addAsTab(tabDynMarker, "Dynamic Markers");
	addAsTab(tabLinkedGraphs, "Linked Graphs");
	addAsTab(tabScatterCompat, "ScatterDraw comptibility");
	addAsScatterTab(tabScatterCompat.tabBasic, "Basic");
	addAsScatterTab(tabScatterCompat.tabFunctions, "Functions");
	addAsScatterTab(tabScatterCompat.tabParam, "Parametric");
	addAsScatterTab(tabScatterCompat.tabTrendLines, "Trend Lines");

	
	// ====================================================
	// FULL DEMO
	// ====================================================
	{
		XYY2LTMM_GraphCtrl* g2 = &(tabFullDemo.graph);
		tabFullDemo.butStyleDefault << [g2]() ->void { GraphCtrl_Demo::SetStyleDefault(*g2); };
		tabFullDemo.butStyle0 << [g2]() ->void { GraphCtrl_Demo::SetStyle0(*g2); };
		tabFullDemo.butStyle1 << [g2]() ->void { GraphCtrl_Demo::SetStyle1(*g2); };
		tabFullDemo.butStyle2 << [g2]() ->void { GraphCtrl_Demo::SetStyle2(*g2); };
		tabFullDemo.butStyle3 << [g2]() ->void { GraphCtrl_Demo::SetStyle3(*g2); };
		tabFullDemo.butThemeFlip << []() ->void { SwapDarkLight(); };

		tabFullDemo.butResetStats << [g2]() ->void { g2->ResetTimingStats(); };
		tabFullDemo.butPrintStats << [g2]() ->void { g2->PrintTimingStats(); };
		
		

		{
			Option* opt = &(tabFullDemo.butInvertX);
			(*opt) << [this, g2, opt]() ->void { g2->InvertX1Axis(opt->GetData()); g2->RefreshFromChild(REFRESH_FULL); };
		}
			
		{
			Option* opt = &(tabFullDemo.butInvertY);
			(*opt) << [g2, opt]() ->void { g2->InvertY1Axis(opt->GetData()); g2->RefreshFromChild(REFRESH_FULL); };
		}
			
		{
			Option* opt = &(tabFullDemo.butInvertY2);
			(*opt) << [g2, opt]() ->void { g2->InvertY2Axis(opt->GetData()); g2->RefreshFromChild(REFRESH_FULL); };
		}


		{	Option* opt = &(tabFullDemo.butDisableAxisScroll);  (*opt) << [g2, opt]() ->void { g2->DisableAxisScroll(opt->GetData()); };	}
		{	Option* opt = &(tabFullDemo.butDisableAxisZoom);    (*opt) << [g2, opt]() ->void { g2->DisableAxisZoom(opt->GetData()); };	}
		{	Option* opt = &(tabFullDemo.butDisableGraphScroll); (*opt) << [g2, opt]() ->void { g2->DisableGraphScroll(opt->GetData()); };	}
		{	Option* opt = &(tabFullDemo.butDisableGraphZoom);   (*opt) << [g2, opt]() ->void { g2->DisableGraphZoom(opt->GetData()); };	}

		{	Option* opt = &(tabFullDemo.butDisableXScroll);     (*opt) << [g2, opt]() ->void { g2->DisableXScroll(opt->GetData()); };	}
		{	Option* opt = &(tabFullDemo.butDisableXZoom);       (*opt) << [g2, opt]() ->void { g2->DisableXZoom(opt->GetData()); };	}
		{	Option* opt = &(tabFullDemo.butDisableYScroll);     (*opt) << [g2, opt]() ->void { g2->DisableYScroll(opt->GetData()); };	}
		
		{	Option* opt = &(tabFullDemo.butDisableYZoom);       (*opt) << [g2, opt]() ->void { g2->DisableYZoom(opt->GetData()); };	}
		{	Option* opt = &(tabFullDemo.butZoomProportional);   (*opt) << [g2, opt]() ->void { g2->SetZoomProportional(opt->GetData()); };	}
		
//		Upp::GraphDraw_ns::SimpleJobSerie simpleJobSerie
		simpleJobSerie[0].Init(0,  100,  0, 0.5, GraphCtrl_DemoImg::FW_IMG() );
		simpleJobSerie[1].Init(10,  80, 10, 0.5, GraphCtrl_DemoImg::FW_IMG() );
		simpleJobSerie[2].Init(20, 110, 20, 0.5, GraphCtrl_DemoImg::FW_IMG() );
		simpleJobSerie[3].Init(25, 350, 30, 0.5, GraphCtrl_DemoImg::FW_IMG() );
		simpleJobSerie[4].Init(30, 130, 40, 0.5, GraphCtrl_DemoImg::FW_IMG() );
		simpleJobSerie[5].Init(40, 180, 50, 0.5, GraphCtrl_DemoImg::FW_IMG() );
		

		fullDemo_points << Pointf(0.5,1) << Pointf(1, 3.5)<< Pointf(2,1.8)<< Pointf(4, 3)<< Pointf(5.5, 2.5) << Pointf(6,7) << Pointf(7, 9)<< Pointf(8,10)<< Pointf(10, 15)<< Pointf(15, 15);
		fullDemo_points1b << Pointf(0.5,1) << Pointf(1, 3.5)<< Pointf(2,1.8)<< Pointf(4, 3)<< Pointf(5.5, 2.5) << Pointf(6,7) << Pointf(7, 9)<< Pointf(8,10)<< Pointf(10, 15)<< Pointf(15, 15);
		
		fullDemo_points2 << Pointf(0,2) << Pointf(1, 3)<< Pointf(2,4)<< Pointf(4, 4)<< Pointf(5.5, 5) << Pointf(6,6) << Pointf(7, 7)<< Pointf(8,11)<< Pointf(10, 10)<< Pointf(15, 9);
		fullDemo_points2b << Pointf(0,1) << Pointf(1, 2)<< Pointf(2,3)<< Pointf(4, 3)<< Pointf(5.5, 4) << Pointf(6,5) << Pointf(7, 6)<< Pointf(8,10)<< Pointf(10, 9)<< Pointf(15, 8);

		//g4.debugTrace = true;
		XYY2LTMM_GraphCtrl& g4 = tabFullDemo.graph;
		g4.AddGraphSerie( simpleJobSerie );
		
		//g4.debugTrace = true;
//		g4.CreateElement2<ExclusionAreaDraw, FLOAT_OVER_GRAPH>(0, 0, g4.GetCoordConverterX1(), g4.GetCoordConverterY1() );
		{
			auto& markerGElem = g4.GetElementX1Markers();
			markerGElem.whenMarkerMove = THISBACK(onXMarkerMoveCBK);
			markerGElem.whenMarkerSelected = THISBACK(onXMarkerSelectCBK);
			markerGElem.whenMarkerReleased = THISBACK(onXMarkerReleaseCBK);

			markerGElem.AddMarker(MARKER_X1_ID, "\1[ [ [*@4;1  X1 ]]]", 3.5);
			markerGElem.AddMarker(MARKER_X2_ID, "\1[ [ [*@4;1  X2 ]]]", 7.0);
		}
		{
//			MarkerElementType2& markerElem = g4.CreateElement1< MarkerElementType2, LEFT_OF_GRAPH>(30, g4.GetElementY1GridAxisDraw().GetStackingPriority()+1, g4.GetCoordConverterY1() );
			MarkerElementType& markerElem = g4.GetElementY1Markers();
//			markerGElem.SetStackingPriority()
			markerElem.SetOverlapPrevious(true);
			markerElem.whenMarkerMove = THISBACK(onY1MarkerMoveCBK);
			SmartTextTickMark& mark1 = markerElem.AddMarker(MARKER_Y1_ID, 8.5);
			mark1.SetText("\1[ [ [*@(0.0.255)1  Y1 ]]]");
		}
		{
//			MarkerElementType2& markerElem = g4.CreateElement1< MarkerElementType2, RIGHT_OF_GRAPH>(40, -1, g4.GetCoordConverterY2() );
			auto& markerElem = g4.GetElementY2Markers();
			markerElem.Hide(false);
			markerElem.whenMarkerMove = THISBACK(onY2MarkerMoveCBK);
			markerElem.SetOverlapPrevious(true);
			SmartTextTickMark& mark1 = markerElem.AddMarker<SmartTextTickMark>(MARKER_Y2_ID, 6.5);
			mark1.SetText("\1[ [ [*@6;1  Y2 ]]]");
		}
	
		g4.GetCoordConverterX1().SetFormatCbk( [] (TypeGraphCoord v) { return FormatDouble(v,5) << " Sec"; } );
		g4.GetCoordConverterY1().SetFormatCbk( [] (TypeGraphCoord v) { return FormatDouble(v,5) << " Watt"; } );
		g4.GetCoordConverterY2().SetFormatCbk( [] (TypeGraphCoord v) { return FormatDouble(v,5) << " T/m"; } );

		g4.SetCurrentYConverter(0); // set Y1 as current Y axis
		g4.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(fullDemo_points).PlotStyle<LineSeriesPlot>().MarkStyle<XMarkPlot>().MarkWidth(3).Legend("S1");//.Fill(Color(28, 255, 200)).Opacity(.5);
		g4.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(fullDemo_points1b).LineColor(Yellow()).LineThickness(3).MarkWidth(5).Legend("S1b");

		g4.SetCurrentYConverter(1); // set Y2 as current Y axis

		g4.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(fullDemo_points2b).LineColor(Green()).LineThickness(2).MarkWidth(3).NoMark().Legend("S2b");
		g4.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(fullDemo_points2).PlotStyle<LineSeriesPlot>().NoMark().Legend("S2"); // tied to last X/Y  coordConverters ==> X / Y2
	
		g4.SetCtrlBackgroundStyle(GraphCtrl_DemoImg::CTRL_BACKGND3() );
		g4.SetPlotBackgroundStyle(GraphCtrl_DemoImg::PLOT_BACKGND2() );
		g4.SetLegendBackGroundStyle(GraphCtrl_DemoImg::LEGEND_BACKGND3new());
		g4.GetElementLegend().SetElementWidth(28);
		//g4.GetYGridAxisDraw().SetBackGroundStyle(GraphCtrl_DemoImg::LEGEND_BACKGND4());
		//g4.GetElementY1GridAxisDraw().SetVSelectStyle(GraphCtrl_DemoImg::VSELECT());
		g4.FitToData(); // TODO  ==> Prendre en compte avec CustomSeries
//		g4.GetElementX1Markers().ResetMarkers();
		g4.Refresh();
	}
	
	// ====================================================
	// BIG DATA
	// ====================================================

	double y;
	const int NB_POINTS_G3 = 300000;
	for (int t = 0; t < NB_POINTS_G3; ++t) {
		y = 20.0*sin(2.0*M_PI*t/100000);
		// create a "cloud" of points around the main line
		s1 <<Pointf(t, y);
		s2 <<Pointf(t, y + (Upp::Randomf()*5.0)-2.5);
		s3 <<Pointf(t, y+10);
	}
	tabBigData.graph.SetCtrlBackgroundStyle(GraphCtrl_DemoImg::CTRL_BACKGND() );
	tabBigData.graph.SetLegendBackGroundStyle( GraphCtrl_DemoImg::MARKER_BACKGND());
	tabBigData.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(s3).SetSequential(false).MarkStyle<FastMarkPlot>().NoPlot().Legend("S3 NOT sequential");
	tabBigData.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(s2).SetSequential(true).MarkStyle<FastMarkPlot>().NoPlot().Legend("S2 sequential");
	tabBigData.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(s1).SetSequential(true).MarkStyle<FastMarkPlot>().NoPlot().Legend("S1 sequential");
	tabBigData.graph.FitToData();
	tabBigData.doPerfTest.WhenPush << THISBACK(DoDrawPerfTest);
	MarkerElementType& tabBigData_markerElem_1 = tabBigData.graph.CreateElement1< AutoHideElementCtrl<MarkerElementType>, TOP_OF_GRAPH>(30, -1, tabBigData.graph.GetCoordConverterX1() );
	{	
		MarkerElementType& markerElem = tabBigData_markerElem_1;
		// TODO markerElem.SetBackGroundStyle(GraphCtrl_DemoImg::LEGEND_BACKGND());
		SmartTextTickMark* mark;

		mark = &markerElem.AddMarker<SmartTextTickMark>(LINKED_MARKER_ID1);
		mark->SetText("\1[ [ [*0 Linked]]]");
		mark->SetBackGroundStyle(GraphCtrl_DemoImg::MARKER_BACKGND());

		mark = &markerElem.AddMarker<SmartTextTickMark>(LINKED_MARKER_ID3);
		mark->SetText("\1[ [ [*0 Not Linked]]]");
		mark->SetBackGroundStyle(GraphCtrl_DemoImg::MARKER_BACKGND());
	}

	tabBigData.graph.debugTraceTimings = true;


	// ====================================================
	// 1 Data Point
	// ====================================================
	sOne.Clear();
	sOne << Pointf(GetSysDate().Get(), 10);
	sOne << Pointf(GetSysDate().Get()+10, 15);
	
	tab1DataPoint.graph.SetCtrlBackgroundStyle(GraphCtrl_DemoImg::CTRL_BACKGND() );
	tab1DataPoint.graph.SetY1AxisBackGroundStyle( GraphCtrl_DemoImg::HeatGradient_1());
	tab1DataPoint.graph.SetLegendBackGroundStyle( GraphCtrl_DemoImg::LEGEND_BACKGND());
	{
		auto& serie = tab1DataPoint.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(sOne);
		serie.PlotStyle<LineSeriesPlot>()
		     .Fill(Color(28, 255, 200))
		     .Opacity(.4)
		     .Legend("y = (x-1000100)");
	}
	tab1DataPoint.graph.SetY1Min(0.).SetY1Max(720);
	tab1DataPoint.graph.FitToData();
//	tab1DataPoint.graph.SetX1Min(1000098.643); //GetSysTime().Get());
//	tab1DataPoint.graph.SetX1Max(1000107.684); //GetSysTime().Get() + 60*60*24*90);
	
	// ====================================================
	// LOG  &  TIME SCALE
	// ====================================================
	
	tabLogTimeScale.graph.SetCtrlBackgroundStyle(GraphCtrl_DemoImg::CTRL_BACKGND() );
	tabLogTimeScale.graph.SetY1AxisBackGroundStyle( GraphCtrl_DemoImg::HeatGradient_1());
	tabLogTimeScale.graph.SetLegendBackGroundStyle( GraphCtrl_DemoImg::LEGEND_BACKGND());
	tabLogTimeScale.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&vfunct1_).PlotStyle<LineSeriesPlot>().Fill(Color(28, 255, 200)).Opacity(.4).Legend("y = (x-1000100)");
	tabLogTimeScale.graph.SetY1Min(0.000001).SetY1Max(720);
	tabLogTimeScale.graph.SetX1Min(1000098.643); //GetSysTime().Get());
	tabLogTimeScale.graph.SetX1Max(1000107.684); //GetSysTime().Get() + 60*60*24*90);
	
	// ====================================================
	// SCATTER CTRL COMPAT : BASIC
	// ====================================================
	{
		scatterBasic_s1 << Pointf(10, 26) << Pointf(20, 37) << Pointf(30, 31) << Pointf(40, 33) << Pointf(50, 28);
		tabScatterCompat.tabBasic.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(scatterBasic_s1).Legend("Series 1").PlotStyle<LineSeriesPlot>().Opacity(0.3).Fill();
		
		scatterBasic_s2y[0] = 22; scatterBasic_s2y[1] = 33; scatterBasic_s2y[2] = 27; scatterBasic_s2y[3] = 29; scatterBasic_s2y[4] = 24;
		tabScatterCompat.tabBasic.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(scatterBasic_s2y, 5, 10, 10).Legend("Series 2").PlotStyle<LineSeriesPlot>()
						.Dash("").MarkColor(Red()).Fill().Opacity(0.5);
		
		scatterBasic_s3y[0] = 18; scatterBasic_s3y[1] = 29; scatterBasic_s3y[2] = 23; scatterBasic_s3y[3] = 25; scatterBasic_s3y[4] = 20;
		scatterBasic_s3x[0] = 10; scatterBasic_s3x[1] = 20; scatterBasic_s3x[2] = 30; scatterBasic_s3x[3] = 40; scatterBasic_s3x[4] = 50;
		tabScatterCompat.tabBasic.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(scatterBasic_s3x, scatterBasic_s3y, 5).Legend("Series 3").PlotStyle<LineSeriesPlot>();
		
		scatterBasic_s4y << 14 << 25 << 19 << 21 << 16;
		scatterBasic_s4x << 10 << 20 << 30 << 40 << 50;
		tabScatterCompat.tabBasic.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(scatterBasic_s4x, scatterBasic_s4y).Legend("Series 4").PlotStyle<StaggeredSeriesPlot>().Dash("").NoMark().Fill().Stroke(3, LtRed());
		
		scatterBasic_s5.Add(10, 10);
		scatterBasic_s5.Add(20, 21);
		scatterBasic_s5.Add(30, 15);
		scatterBasic_s5.Add(40, 16);
		scatterBasic_s5.Add(50, 12);
		tabScatterCompat.tabBasic.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(scatterBasic_s5).Legend("Series 5").PlotStyle<BarSeriesPlot>().Dash("").NoMark().Fill();
		tabScatterCompat.tabBasic.graph.setGraphSize(0,60,0,50);
	}

	// ====================================================
	// SCATTER CTRL COMPAT : FUNCTIONS
	// ====================================================
	
	tabScatterCompat.tabFunctions.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&funct1).PlotStyle<LineSeriesPlot>().Legend("0");
	tabScatterCompat.tabFunctions.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&funct2).PlotStyle<LineSeriesPlot>().Legend("x*x-5");
	tabScatterCompat.tabFunctions.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&funct3).PlotStyle<LineSeriesPlot>().Legend("-x*x-5");
	tabScatterCompat.tabFunctions.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&vfunct1).PlotStyle<LineSeriesPlot>().Legend("y = 0");
	tabScatterCompat.tabFunctions.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&vfunct2).PlotStyle<LineSeriesPlot>().Legend("y = x*x");
	tabScatterCompat.tabFunctions.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&vfunct3).PlotStyle<LineSeriesPlot>().Legend("y = -x*x");
	
	// ====================================================
	// SCATTER CTRL COMPAT : PARAMETER
	// ====================================================
	
	tabScatterCompat.tabParam.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&opara1, 20).Legend("Circle 1").NoMark().PlotStyle<LineSeriesPlot>();
	tabScatterCompat.tabParam.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(STDBACK(para1), 100).Legend("Circle 2").NoMark().PlotStyle<LineSeriesPlot>();
	tabScatterCompat.tabParam.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(STDBACK(para2), 100).Legend("Coil").NoMark().PlotStyle<LineSeriesPlot>().Fill(Color(28, 255, 255)).Opacity(.3);
	tabScatterCompat.tabParam.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(STDBACK(para3), 150).Legend("Spiral 1").NoMark().PlotStyle<LineSeriesPlot>().Fill(Color(0, 0, 0)).Opacity(.2);
	tabScatterCompat.tabParam.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(STDBACK1(para3p, 2.5), 150, 0, 1).Legend("Spiral 2").NoMark().PlotStyle<LineSeriesPlot>();
	tabScatterCompat.tabParam.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(STDBACK(para4), 2).Legend("VLine").NoMark().PlotStyle<LineSeriesPlot>();
	tabScatterCompat.tabParam.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(STDBACK(para5), 2).Legend("HLine").NoMark().PlotStyle<LineSeriesPlot>();
	tabScatterCompat.tabParam.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(STDBACK2(para1p, 4.0, 0.25), 50, 0, 1).Legend("Ellipse 1").NoMark().PlotStyle<LineSeriesPlot>().Fill(Color(113, 42, 0)).Opacity(.2);
	tabScatterCompat.tabParam.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(STDBACK2(para1p, 2.0, 0.5), 50, 0, 1).Legend("Ellipse 2").NoMark().PlotStyle<LineSeriesPlot>();

	// ====================================================
	// SCATTER CTRL COMPAT : TREND LINES
	// ====================================================
	
	trendLine_s1x << -3.067E0 << -2.981E0 << -2.921E0 << -2.912E0 << -2.840E0 << -2.797E0 << -2.702E0 << -2.699E0 << -2.633E0 << -2.481E0 << -2.363E0  << -2.322E0  << -1.501E0  << -1.460E0  << -1.274E0  << -1.212E0  << -1.100E0  << -1.046E0 << -0.915E0 << -0.714E0 << -0.566E0 << -0.545E0 << -0.400E0 << -0.309E0 << -0.109E0 << -0.103E0 << 0.010E0 << 0.119E0 << 0.377E0 << 0.790E0 << 0.963E0 << 1.006E0 << 1.115E0 << 1.572E0 << 1.841E0 << 2.047E0 << 2.200E0;
	trendLine_s1y << 80.574E0 << 84.248E0 << 87.264E0 << 87.195E0 << 89.076E0 << 89.608E0 << 89.868E0 << 90.101E0 << 92.405E0 << 95.854E0 << 100.696E0 << 101.060E0 << 401.672E0 << 390.724E0 << 567.534E0 << 635.316E0 << 733.054E0 << 759.087E0 << 894.206E0 << 990.785E0 << 1090.109E0 << 1080.914E0 << 1122.643E0 << 1178.351E0 << 1260.531E0 << 1273.514E0 << 1288.339E0 << 1327.543E0 << 1353.863E0 << 1414.509E0 << 1425.208E0 << 1421.384E0 << 1442.962E0 << 1464.350E0 << 1468.705E0 << 1447.894E0 << 1457.628E0;		
	{
		double l_r2, p2_r2, p4_r2, f_r2, exp_r2, rat1_r2;
		VectorXY vs1(trendLine_s1x, trendLine_s1y);
		linear.Fit(vs1, l_r2);
		poly2.SetDegree(2);
		poly2.Fit(vs1, p2_r2);
		poly4.SetDegree(4);
		poly4.Fit(vs1, p4_r2);
		fourier.SetDegree(3);
		fourier.Fit(vs1, f_r2);
		exponential.Fit(vs1, exp_r2);
		rational1.Fit(vs1, rat1_r2);
	}
	
	tabScatterCompat.tabTrendLines.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(trendLine_s1x, trendLine_s1y).Legend("Series 1").MarkStyle<RhombMarkPlot>().MarkWidth(10).NoPlot();
	tabScatterCompat.tabTrendLines.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(linear).Legend(linear.GetFullName()).NoMark().Stroke(2).PlotStyle<LineSeriesPlot>();
	tabScatterCompat.tabTrendLines.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(poly2).Legend(poly2.GetFullName()).NoMark().Stroke(4).PlotStyle<LineSeriesPlot>();
	tabScatterCompat.tabTrendLines.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(poly4).Legend(poly4.GetFullName()).NoMark().Stroke(2).PlotStyle<LineSeriesPlot>();
	tabScatterCompat.tabTrendLines.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(fourier).Legend(fourier.GetFullName()).NoMark().Stroke(3).PlotStyle<LineSeriesPlot>();
	tabScatterCompat.tabTrendLines.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(exponential).Legend(exponential.GetFullName()).NoMark().Stroke(2).PlotStyle<LineSeriesPlot>();
	tabScatterCompat.tabTrendLines.graph.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(rational1).Legend(rational1.GetFullName()).NoMark().Stroke(2).PlotStyle<LineSeriesPlot>();
	tabScatterCompat.tabTrendLines.graph.FitToData();

	// ====================================================
	// DYNAMIC MARKER
	// ====================================================
	
	MarkerElementType& g1MarkerElem = SetDynMarkerGraph(tabDynMarker.g1);
	g1MarkerElem.whenMarkerMove = THISBACK(onMarkerMoveCBK_tabDyn);
	MarkerElementType& g2MarkerElem = SetDynMarkerGraph(tabDynMarker.g2);
	MarkerElementType& g3MarkerElem = SetDynMarkerGraph(tabDynMarker.g3);
//	MarkerElementType& g4MarkerElem = SetDynMarkerGraph(tabDynMarker.g4);
//	MarkerElementType& g5MarkerElem = SetDynMarkerGraph(tabDynMarker.g5);
	
	g1MarkerElem.Link(LINKED_MARKER_ID1, g2MarkerElem, LINKED_MARKER_ID1 );
	g2MarkerElem.Link(LINKED_MARKER_ID1, g3MarkerElem, LINKED_MARKER_ID1 );
//	g3MarkerElem.Link(LINKED_MARKER_ID1, g4MarkerElem, LINKED_MARKER_ID1 );
//	g4MarkerElem.Link(LINKED_MARKER_ID1, g5MarkerElem, LINKED_MARKER_ID1 );
//	g5MarkerElem.Link(LINKED_MARKER_ID1, g1MarkerElem, LINKED_MARKER_ID1 );
	
	{
		XYLT_GraphCtrl& g5 = tabDynMarker.g5;
		MarkerElementType& markerElemG5_1 = g5.CreateElement1< MarkerElementType, TOP_OF_GRAPH >(30, 0, g5.GetCoordConverterX1() );
		markerElemG5_1.AddMarker<SmartTextTickMark>(1, 3.8).SetText("\1[ [ [*_@6$(28.255.150)+59 M1]]]");
		
		MarkerElementType& markerElemG5_2 = g5.CreateElement1< MarkerElementType, RIGHT_OF_GRAPH >(40, 0, g5.GetCoordConverterY1() );
		markerElemG5_2.AddMarker<SmartTextTickMark>(2, 3.8).SetText("\1[ [ [*_@6$(28.255.150)+59 M2]]]");
		
		MarkerElementType& markerElemG5_3 = g5.CreateElement1< MarkerElementType, BOTTOM_OF_GRAPH >(30, 0, g5.GetCoordConverterX1() );
		SmartTextTickMark& sttm = markerElemG5_3.AddMarker<SmartTextTickMark>(3, 3.8);
			sttm.SetText("\1[ [ [@6$(255.255.192)2 `-`-][*_$(255.255.192)2 M3][@6$(255.255.192)2 `-`-]]]");
			sttm.SetBackGroundStyle(GraphCtrl_DemoImg::BACKGND());
		
		MarkerElementType& markerElemG5_4 = g5.CreateElement1< MarkerElementType, LEFT_OF_GRAPH >(40, 0, g5.GetCoordConverterY1() );
		SmartTextTickMark& sttm4 = markerElemG5_4.AddMarker<SmartTextTickMark>(4, 3.8);
			sttm4.SetText("---M4---");
			sttm4.SetBackGroundStyle(GraphCtrl_DemoImg::BACKGND());
	}

	{
		XYLT_GraphCtrl& g4 = tabDynMarker.g4;
			//MarkerElementType& markerElem = g4.CreateElement1< AutoHideElementCtrl<MarkerElementType>, TOP_OF_GRAPH>(30, 1, g4.GetCoordConverterX1() );
		MarkerElementType& markerElemG5_1 = g4.CreateElement1< AutoHideElementCtrl<MarkerElementType>, TOP_OF_GRAPH >(30, -1, g4.GetCoordConverterX1() );
		//TODO markerElemG5_1.SetBackGroundStyle(GraphCtrl_DemoImg::LEGEND_BACKGND4());
		markerElemG5_1.AddMarker<SmartTextTickMark>(1, 3.8).SetText("\1[ [ [*_@6$(28.255.150)+59 M1]]]");
		
		MarkerElementType& markerElemG5_2 = g4.CreateElement1< AutoHideElementCtrl<MarkerElementType>, RIGHT_OF_GRAPH >(40, -1, g4.GetCoordConverterY1() );
		//TODO markerElemG5_2.SetBackGroundStyle(GraphCtrl_DemoImg::LEGEND_BACKGND4());
		markerElemG5_2.AddMarker<SmartTextTickMark>(2, 3.8).SetText("\1[ [ [*_@6$(28.255.150)+59 M2]]]");
		
		MarkerElementType& markerElemG5_3 = g4.CreateElement1< AutoHideElementCtrl<MarkerElementType>, BOTTOM_OF_GRAPH >(30, -1, g4.GetCoordConverterX1() );
		//TODO markerElemG5_3.SetBackGroundStyle(GraphCtrl_DemoImg::LEGEND_BACKGND4());
		SmartTextTickMark& sttm = markerElemG5_3.AddMarker<SmartTextTickMark>(3, 3.8);
			sttm.SetText("\1[ [ [@6$(255.255.192)2 `-`-][*_$(255.255.192)2 M3][@6$(255.255.192)2 `-`-]]]");
			sttm.SetBackGroundStyle(GraphCtrl_DemoImg::BACKGND());
		
		MarkerElementType& markerElemG5_4 = g4.CreateElement1< AutoHideElementCtrl<MarkerElementType>, LEFT_OF_GRAPH >(40, -1, g4.GetCoordConverterY1() );
		// TODO markerElemG5_4.SetBackGroundStyle(GraphCtrl_DemoImg::LEGEND_BACKGND4());
		SmartTextTickMark& sttm4 = markerElemG5_4.AddMarker<SmartTextTickMark>(4, 3.8);
			sttm4.SetText("---M4---");
			sttm4.SetBackGroundStyle(GraphCtrl_DemoImg::BACKGND());
	}

	// ====================================================
	// LINKED GRAPHS
	// ====================================================
	#define T_MIN 0
	#define T_MAX 10
	tabLinkedGraphs.gxy.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(STDBACK(paraXY), 10000, T_MIN, T_MAX).Legend("Coil").NoMark().PlotStyle<LineSeriesPlot>();//.Fill(Color(28, 255, 255)).Opacity(.3);
	tabLinkedGraphs.gx.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&functx).Legend("X(t) Coil").NoMark().PlotStyle<LineSeriesPlot>();//.Fill(Color(28, 255, 255)).Opacity(.3);
	tabLinkedGraphs.gy.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&functy).Legend("Y(t) Coil").NoMark().PlotStyle<LineSeriesPlot>();//.Fill(Color(28, 255, 255)).Opacity(.3);
	tabLinkedGraphs.gx2.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&functx).Legend("X(t) Coil").NoMark().PlotStyle<LineSeriesPlot>();//.Fill(Color(28, 255, 255)).Opacity(.3);
	tabLinkedGraphs.gy2.CreateGraphSerie<ScatterGraphSeries>().SetSerieData(&functy).Legend("Y(t) Coil").NoMark().PlotStyle<LineSeriesPlot>();//.Fill(Color(28, 255, 255)).Opacity(.3);

	tabLinkedGraphs.gxy.SetCtrlBackgroundStyle(GraphCtrl_DemoImg::CTRL_BACKGND() );
	//tabLinkedGraphs.gx.SetCtrlBackgroundStyle(GraphCtrl_DemoImg::CTRL_BACKGND() );
	//tabLinkedGraphs.gy.SetCtrlBackgroundStyle(GraphCtrl_DemoImg::CTRL_BACKGND() );

	tabLinkedGraphs.gxy.Link( tabLinkedGraphs.gxy.GetCoordConverterX1(), tabLinkedGraphs.gx.GetCoordConverterY1());
	tabLinkedGraphs.gxy.Link( tabLinkedGraphs.gxy.GetCoordConverterY1(), tabLinkedGraphs.gy.GetCoordConverterY1());
	tabLinkedGraphs.gx.Link( tabLinkedGraphs.gx.GetCoordConverterX1(), tabLinkedGraphs.gy.GetCoordConverterX1());

	tabLinkedGraphs.gx2.Link( tabLinkedGraphs.gx2.GetCoordConverterX1(), tabLinkedGraphs.gx.GetCoordConverterX1());
	tabLinkedGraphs.gx2.Link( tabLinkedGraphs.gx2.GetCoordConverterY1(), tabLinkedGraphs.gx.GetCoordConverterY1());

	tabLinkedGraphs.gy2.Link( tabLinkedGraphs.gy2.GetCoordConverterX1(), tabLinkedGraphs.gy.GetCoordConverterX1());
	tabLinkedGraphs.gy2.Link( tabLinkedGraphs.gy2.GetCoordConverterY1(), tabLinkedGraphs.gy.GetCoordConverterY1());
	
	// Set limits and default range for each type of axis (once per type)
	tabLinkedGraphs.gx.SetX1Min(3).SetX1MinRangeLimit(T_MIN).SetX1Max(7).SetX1MaxRangeLimit(T_MAX);
	tabLinkedGraphs.gxy.SetX1Min(0).SetX1MinRangeLimit(-10).SetX1Max(30).SetX1MaxRangeLimit(40);
	tabLinkedGraphs.gxy.SetY1Min(1).SetY1MinRangeLimit(0).SetY1Max(3).SetY1MaxRangeLimit(4);

	// propagate axis config to all other axis !!
	tabLinkedGraphs.gxy.ForceUpdateAllLinks( LINK_UPDATE_RANGE_LIMITS );
	tabLinkedGraphs.gx.ForceUpdateAllLinks( LINK_UPDATE_RANGE_LIMITS );

}


// ============================================================================================
// ============================================================================================
void GLGraphCtrl::GLPaint() {
	StdView();

	double t = 13 * point.x;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glPushMatrix();
		glTranslatef(0, 0, -6);
		glRotated(t / 30.0, 0, 1, 0);
		glRotated(t / 40.0, 1, 0, 0);
		glRotated(t / 5.0, 0, 0, 1);
		glBegin(GL_TRIANGLE_FAN);
			glColor4d(0.8, 0.4, 0.2, 1);
			glVertex3f(0.0f, 0.0f, 0.0f);
			for(int i = 0; i < 50; i++) {
				double u = M_2PI * i / 49;
				glColor4d(i / 50.0, 0.5 + i / 100.0, 0.7 - i / 150.0, 1);
				glVertex3d(sin(u), cos(u), 1.0f);
			}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
			glColor4d(0.8, 0.4, 0.2, 1);
			glVertex3f(0.0f, 0.0f, 3.0f);
			for(int i = 0; i < 50; i++) {
				double u = M_2PI * i / 49;
				glColor4d(0.7, 0.5 - i / 100.0, 0.7 + i / 150.0, 1);
				glVertex3d(sin(u), cos(u), 1.0f);
			}
		glEnd();
	glPopMatrix();
	t = 13 * point.y;
	float sn = (float)sin(t / 300);
	float cs = (float)cos(t / 300);
	glTranslatef(sn + cs, sn, -6 - cs);
	glRotated(t / 12.0, 0, 0, 1);
	glRotated(t / 15.0, 0, 1, 0);
	glRotated(t / 17.0, 1, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor4d(1, 0, 0, 0.5);
		glVertex3d(-1, 0, 0);
		glVertex3d(1, 0, 0);
		glVertex3d(0, 0.87, 0);
		glColor4d(0, 1, 0, 0.5);
		glVertex3d(0, 0, 1.67);
	glEnd();
}

void GLGraphCtrl::GLResize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void GLGraphCtrl::MouseMove(Point p, dword) {
	point = p;
	Refresh();
}

};