	#ifndef _GraphCtrl_Demo_GraphCtrl_Demo_h
#define _GraphCtrl_Demo_GraphCtrl_Demo_h

#include <CtrlLib/CtrlLib.h>
#include <GraphCtrl/GraphCtrl.h>
#include <GraphSeries/ScatterSeries/ScatterSeries.h>
#include <GraphSeries/SimpleJobSerie/SimpleJobSerie.h>

#include <GLCtrl/GLCtrl.h>

using namespace Upp::GraphDraw_ns;

namespace Upp {
	#define IMAGECLASS GraphCtrl_DemoImg
	#define IMAGEFILE <examples/GraphCtrl_Demo/GraphCtrl_Demo.iml>
	#include <Draw/iml_header.h>
	
	
	struct GLGraphCtrl : GLCtrl {
		Point point;
		virtual void GLPaint();
		virtual void GLResize(int w, int h);
		virtual void MouseMove(Point p, dword);
	};
	
	#define LAYOUTFILE <examples/GraphCtrl_Demo/GraphCtrl_Demo.lay>
	#include <CtrlCore/lay.h>

	INITIALIZE(GraphCtrl_Demo);
}


namespace Upp {

class GraphCtrl_Demo : public WithGraphCtrl_DemoLayout<TopWindow> {
private:
	EditField::Style markerActiveStyle;
	
	static void SetStyleDefault(XYY2LTMM_GraphCtrl& g);
	static void SetStyle0(XYY2LTMM_GraphCtrl& g);
	static void SetStyle1(XYY2LTMM_GraphCtrl& g);
	static void SetStyle2(XYY2LTMM_GraphCtrl& g);
	static void SetStyle3(XYY2LTMM_GraphCtrl& g);
	
	WithTabFullDemo<Ctrl> tabFullDemo;
	WithTabDynamicMarkerLayout<Ctrl> tabDynMarker;
	WithTabBigDataLayout<Ctrl> tabBigData;
	WithTabOpenGL<Ctrl> tabOpenGL;
	WithTabOpenGL<Ctrl> tabOpenGL2;
	WithTabScatterCompatLayout<Ctrl> tabScatterCompat;
	WithTabLinkedGraphsLayout<Ctrl> tabLinkedGraphs;
	WithTabLogTimeScaleLayout<Ctrl> tabLogTimeScale;
	WithTabLogTimeScaleLayout<Ctrl> tab1DataPoint;
	
public:
	typedef GraphCtrl_Demo CLASSNAME;
	GraphCtrl_Demo();
	virtual ~GraphCtrl_Demo() {}

	
	template<class T>
	void addAsTab(T& ctrl, const char *text="") {
		CtrlLayout( ctrl );
		tabs.Add(ctrl, text);
		ctrl.SizePos();
	}

	template<class T>
	void addAsScatterTab(T& ctrl, const char *text="") {
		CtrlLayout( ctrl );
		tabScatterCompat.tabs.Add(ctrl, text);
		ctrl.SizePos();
		
		ctrl.graph.SetCtrlBackgroundStyle(GraphCtrl_DemoImg::CTRL_BACKGND2() );
		ctrl.graph.SetPlotBackgroundStyle(GraphCtrl_DemoImg::PLOT_BACKGND() );
		ctrl.graph.SetLegendBackGroundStyle( GraphCtrl_DemoImg::MARKER_BACKGND() ); //GraphCtrl_DemoImg::LEGEND_BACKGND2());
		ctrl.graph.AddBlanklArea(GraphDraw_ns::RIGHT_OF_GRAPH, 10, 10);
	}

	Vector<Pointf> s1;
	Vector<Pointf> s2;
	Vector<Pointf> s3;
	Vector<Pointf> sOne;

	Vector<Pointf> scatterBasic_s1;
	double scatterBasic_s2y[5];
	double scatterBasic_s3x[5], scatterBasic_s3y[5];
	Vector<double> scatterBasic_s4x, scatterBasic_s4y;
	VectorMap<double, double> scatterBasic_s5;

	Vector<Pointf> fullDemo_points;
	Vector<Pointf> fullDemo_points1b;
	Vector<Pointf> fullDemo_points2;
	Vector<Pointf> fullDemo_points2b;

	Vector<double> trendLine_s1x, trendLine_s1y;
	Vector<double> trendLine_s2;
	LinearEquation linear;
	PolynomialEquation poly2, poly4;
	FourierEquation fourier;
	ExponentialEquation exponential;
	Rational1Equation rational1;
	
	Upp::GraphDraw_ns::SimpleJobSerie simpleJobSerie;
	

	void onXMarkerMoveCBK( const GraphDraw_ns::MarkerPosList& markers, int ID,  void* m );
	void onXMarkerSelectCBK( const GraphDraw_ns::MarkerPosList& markers, int ID,  void* m );
	void onXMarkerReleaseCBK( const GraphDraw_ns::MarkerPosList& markers, int ID,  void* m );
	
	void onY1MarkerMoveCBK( const GraphDraw_ns::MarkerPosList& markers, int ID,  void* m );
	void onY2MarkerMoveCBK( const GraphDraw_ns::MarkerPosList& markers, int ID,  void* m );
	void onMarkerMoveCBK_tabDyn( const GraphDraw_ns::MarkerPosList& markers, int ID,  void* m );
	void DoDrawPerfTest();
	
};

};

#endif
