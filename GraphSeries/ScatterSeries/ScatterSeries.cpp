#include "ScatterSeries.h"

namespace Upp {


INITBLOCK {
	MarkPlot::Register<GraphDraw_ns::FastMarkPlot>("FastMark");
}

namespace GraphDraw_ns {

ScatterGraphSeries::MakeEditorFunction& ScatterGraphSeries::GetDefaultMakeEditorCB() {
	static MakeEditorFunction defaultMakeEditorFct;
	return defaultMakeEditorFct;
}

ScatterGraphSeries::ScatterGraphSeries()
{
	SetSelectable(true);
	SetDataSelectable(true);
//	SetCtrlable(true);

	owns = false;
	pD = 0;
	xConverter = 0;
	yConverter = 0;
	
	if ( ! GetDefaultMakeEditorCB() ) RLOG("makeEditorFct is NULL");
	makeEditorFct = GetDefaultMakeEditorCB();
	
	sequential = true;
	sequentialPointsRangeMin = 0;
	sequentialPointsRangeMax = 0;
	nbVisiblePoints = 0;
	NoDash();
	NoMark();
	style.seriesPlot = new LineSeriesPlot();
//				markPlot;  // = new CircleMarkPlot();
	style.color = Null;
	style.thickness = 1;
	style.opacity = 0.3;
	style.markWidth = 8;
	style.markColor = Null;
	style.fillColor = Null;
}

ScatterGraphSeries::~ScatterGraphSeries() { if(pD && owns) delete pD; pD = 0; }

bool ScatterGraphSeries::Contains(PointGraph p, unsigned int& pIndexOut) const {
	RLOG("ScatterGraphSeries[" << GetLegend() << "]::Contains(" << p << ")");
	return false;
}


bool ScatterGraphSeries::Intersects(const RectGraph rect, unsigned int& pIndexOut) const {
	RLOG("ScatterGraphSeries[" << GetLegend() << "]::Intersects(" << rect << ")");
	return false; // TODO
}

void ScatterGraphSeries::SetAutoColor(int id, Color colorHint)
{
	// TODO  use colorHint
	autoColorId = id;
	style.color = GetNewColor(autoColorId);
	style.markColor = Color(max(style.color.GetR()-30, 0), max(style.color.GetG()-30, 0), max(style.color.GetB()-30, 0));
	//PlotStyle();
	//NoDash();
	//NoMark();

//	dash = GetNewDash(id);
//	markPlot = GetNewMarkPlot(id);
//	seriesPlot = new LineSeriesPlot();
}


ScatterGraphSeries& ScatterGraphSeries::Stroke(double pthickness, Color pcolor) {
	if (IsNull(pcolor) ) {
		if ( IsNull(style.color) ) pcolor = GetNewColor(autoColorId);
		else                 pcolor = style.color;
	}
	style.color = pcolor;
	style.thickness = pthickness;
	//series[id].dash = GetNewDash(id);
	return *this;
}

ScatterGraphSeries& ScatterGraphSeries::SetFillColor(Color fcolor) {
	if (IsNull(fcolor)) {
		if (IsNull(style.color)) {
			fcolor = GetNewColor(autoColorId);
		}
		else {
			fcolor = style.color;
		}
		fcolor = Color(min(fcolor.GetR()+30, 255), min(fcolor.GetG()+30, 255), min(fcolor.GetB()+30, 255));
	}
	style.fillColor = fcolor;
	return *this;
}

ScatterGraphSeries& ScatterGraphSeries::SetMarkColor(Color c) {
	if (IsNull(c)) {
		c = GetNewColor(autoColorId);
		c = Color(max(c.GetR()-30, 0), max(c.GetG()-30, 0), max(c.GetB()-30, 0));
	}
	style.markColor = c;
	return *this;
}


// ===========================================
//  PaintSerie()
// ===========================================
void ScatterGraphSeries::_PaintSerie(bool paintSelected, BufferPainter& dw, const bool _doFastPaint, int scale, const MCoordinateConverter& coordConv ) {
	DataSource& dataSrc = GetDataSource();
	const CoordinateConverter& xConverter = *coordConv.GetXCoordConverter();
	const CoordinateConverter& yConverter = *coordConv.GetYCoordConverter();

	if ( !style.seriesPlot && !style.markPlot ) return;


	if ((nbVisiblePoints==0)  &&  ( ! dataSrc.IsExplicit())) {
			nbVisiblePoints = (decltype(nbVisiblePoints))(dataSrc.GetCount());
	}
	
	// ============================================
	//     CREATE  LIST  OF  POINTS  TO  DRAW
	// ============================================
	int inc = 1;
	Upp::int64 nbVisiblePts = 0;
	int imin=0, imax=0;
	double dmin=0, dmax=0;
	
	// =================================
	// figure out data-range
	Rectf logicalRect(xConverter.getGraphMin(), yConverter.getGraphMin(), xConverter.getGraphMax(), yConverter.getGraphMax()); 
	if (dataSrc.IsParam()) {             // It is a param function : x=F(t)  y=G(t)
		imin = 0;
		imax = (decltype(imax)) (dataSrc.GetCount()-1);
	} else if ( dataSrc.IsExplicit() ) { // It is a function :  y=f(x)
		dmin = xConverter.getGraphMin();
		dmax = xConverter.getGraphMax();
	} else {
	    imin = 0;
	    imax = (decltype(imax)) (dataSrc.GetCount()-1);
	    if (sequential) {
			imin = FindIndexX(&dataSrc, imin, imax, xConverter.getGraphMin())-1;
			if (imin < 0) imin=0;
			
			int imax2 = FindIndexX(&dataSrc, imin, imax, xConverter.getGraphMax())+1;
			if (imax2>imax) imax2 = imax;
			imax = imax2;
		}
	}
	// =================================
	
	p1.Trim(0);
	p1.Reserve(imax-imin+1);
	PointGraph prevPoint = Null;
	bool prevPointIsVisible = true;
	TypeGraphCoord x;
	TypeGraphCoord y;
	
	if ( !_doFastPaint )  // DRAW ALL DATA (no partial draw)
	{
		nbVisiblePts = 0;
		bool isSeriesFilled = false;
		if ( !style.seriesPlot.IsEmpty() && !style.fillColor.IsNullInstance() ) {
			isSeriesFilled = true;
		}

		if (dataSrc.IsParam())
		{
			const int xmax = imax+1;
			if (!style.seriesPlot.IsEmpty()) // lines & points will be drawn
			{
				for (double cx=imin; cx<=xmax; ++cx)
				{
					x = dataSrc.x(cx);
					y = dataSrc.y(cx);
					p1.AddPick(PointScreen(xConverter.toScreen( x ), yConverter.toScreen( y )));
					++nbVisiblePts;
				}
			}
			else  // only points will be drawn
			{
				for (double cx=imin; cx<xmax; ++cx)
				{
					x = dataSrc.x(cx);
					y = dataSrc.y(cx);
					if ( logicalRect.Contains(x,y) ) {
						p1.AddPick(PointScreen(xConverter.toScreen( x ), yConverter.toScreen( y )));
						++nbVisiblePts;
					}
				}
			}
		}
		else if ( dataSrc.IsExplicit() )
		{
			double dx = double(dmax - dmin)/(double)xConverter.getScreenRange(); // one point per X pixel
			dmax = dmax+dx;
			double yy, xx;
			if (!style.seriesPlot.IsEmpty()) // lines & points will be drawn
			{
				for (xx = dmin-dx; xx < dmax; xx += dx)
				{
					yy = dataSrc.f(xx);
					p1.AddPick(PointScreen(xConverter.toScreen( xx ), yConverter.toScreen( yy )));
					++nbVisiblePts;
				}
			}
			else // only points will be drawn
			{
				for ( xx = dmin-dx; xx < dmax; xx += dx)
				{
					yy = dataSrc.f(xx);
					if ( yConverter.IsInGraphVisibleRange(yy) )	{
						p1.AddPick(PointScreen(xConverter.toScreen( xx ), yConverter.toScreen( yy )));
						++nbVisiblePts;
					}
				}
			}
		}
		else
		{
			if (sequential)
			{
				int64 c=imin;
				if (!style.seriesPlot.IsEmpty())  // lines & points will be drawn
				{
					prevPoint.x = dataSrc.x(c);
					prevPoint.y = dataSrc.y(c);
					for ( ; c<=imax; ++c)
					{
						x = dataSrc.x(c);
						y = dataSrc.y(c);
						addToFullPointsList_withLine( DetectSCrossing_XinRange, p1, x, y, xConverter, yConverter, nbVisiblePts, prevPoint, prevPointIsVisible, isSeriesFilled, logicalRect);
					}
				}
				else // only points will be drawn
				{
					for ( ; c<=imax; ++c)
					{
						x = dataSrc.x(c);
						y = dataSrc.y(c);
						if ( yConverter.IsInGraphVisibleRange(y) )	{
							p1.AddPick(PointScreen(xConverter.toScreen( x ), yConverter.toScreen( y )));
							++nbVisiblePts;
						}
					}
				}
			}
			else
			{
				if (!style.seriesPlot.IsEmpty()) // lines & points will be drawn
				{
					for (Upp::int64 c=imin; c<=imax; c+=inc)
					{
						x = dataSrc.x(c);
						y = dataSrc.y(c);
						addToFullPointsList_withLine( DetectSCrossing, p1, x, y, xConverter, yConverter, nbVisiblePts, prevPoint, prevPointIsVisible, isSeriesFilled, logicalRect);
					}
				}
				else // only points will be drawn
				{
					for (Upp::int64 c=imin; c<=imax; c+=inc)
					{
						x = dataSrc.x(c);
						y = dataSrc.y(c);
						if ( logicalRect.Contains(x,y) ) {
							p1.AddPick(PointScreen(xConverter.toScreen( x ), yConverter.toScreen( y )));
							++nbVisiblePts;
						}
					}
				}
			}
		}
		nbVisiblePoints = (decltype(nbVisiblePoints)) nbVisiblePts;
	}
	else  // DO FAST DRAW : display 800 points maximum per series
	{
		if (dataSrc.IsParam()) {
			const double xmax = imax+1;
			double x, y;
			double dx = Upp::max(double(xmax - imin)/800. , 1.0);
			for (double cx=imin; cx<=xmax; cx+=dx)
			{
				x = dataSrc.x(cx);
				y = dataSrc.y(cx);
				p1 << PointScreen(xConverter.toScreen( x ), yConverter.toScreen( y ));
			}
		} else if (dataSrc.IsExplicit() ) {
			double dx = double(dmax - dmin)/800.;
			dmax = dmax+dx;
			if (xConverter.getScreenRange()<800.) dx = double(dmax - dmin)/xConverter.getScreenRange();

			for (double xx = dmin; xx < dmax; xx += dx) {
				double yy = dataSrc.f(xx);
				p1 << PointScreen(xConverter.toScreen( xx ), yConverter.toScreen( yy ));
			}
		} else {
			inc = fceil((imax-imin)/800.0);
			if (inc==0) ++inc;
			
			imin -= imin%inc;
			
			for ( Upp::int64 c=imin; c<=imax; c+=inc)
			{
				p1 << PointScreen( xConverter.toScreen( dataSrc.x(c)) , yConverter.toScreen( dataSrc.y(c)) );
			}
		}
	}
	
	Color selectColor = Color(255, 0, 255); // TODO add to Style management
	// Draw lines
	if ( !style.seriesPlot.IsEmpty() && (p1.GetCount()>0))
		style.seriesPlot->Paint(dw,
                        p1,
                        scale,
                        style.opacity,
                        (paintSelected ? (style.thickness<=4 ? 6 : style.thickness +2) : style.thickness),
                        (paintSelected ? selectColor : style.color ),
                        style.dash,
                        Null, //style->plotBckgndStyle,
                        style.fillColor,
                        xConverter.getScreenRange() / xConverter.getGraphRange(),
                        yConverter.getScreenRange() / yConverter.getGraphRange(),
                        int(yConverter.getScreenRange() * (1 + yConverter.getGraphMin() / yConverter.getGraphRange())),
                        10,
                        false
		);
	// Draw marks
	if (style.markWidth >= 1 && style.markPlot && !(style.markColor.IsNullInstance()) )
	{
		if ( !style.markPlot.IsEmpty() ) {
			for (int c=0; c<p1.GetCount(); ++c)
			{
				style.markPlot->Paint(dw,
                            scale,
                            p1[c],
                            style.markWidth+ ( paintSelected ? 3 : 0 ),
                            (paintSelected ? selectColor : style.markColor ),
                            style.markWidth,
                            (paintSelected ? selectColor : style.markColor )
                            );
			}
		}
	}
}




Image ScatterGraphSeries::MakeSerieIcon( Size sz, const int scale ) const {
		RGBA bckgColor;   bckgColor.r = 0; bckgColor.g = 0; bckgColor.b = 0; bckgColor.a = 0;
		int width = sz.cx;
		int height = sz.cy;
		ImageBuffer ib( sz );
		Upp::Fill( ib.Begin(), bckgColor, ib.GetLength() );

		Vector< PointGraph > pts;
		int painterMode = MODE_ANTIALIASED;
		if ( !style.seriesPlot.IsEmpty() && !style.color.IsNullInstance() ) {
			// draw multiple points ONLY if lines are drawn
			pts << PointScreen((width*2)/32,(height*2)/32) << PointScreen((width*10)/32,(height*20)/32) << PointScreen((width*20)/32,(height*12)/32) << PointScreen((width*30)/32,(height*30)/32);
		}
		else {
			// lines not drawn ==> only one point in serie ( CENTERED )
			pts << PointScreen(width/2,height/2);
			painterMode = MODE_SUBPIXEL;
		}

		BufferPainter dw(ib, painterMode );
		
		// Draw lines
		if ( !style.seriesPlot.IsEmpty() ) {
			style.seriesPlot->Paint(dw,
                              pts,
                              scale,
                              style.opacity,
                              fround(style.thickness),
                              style.color,
                              style.dash,
                              Null,
                              style.fillColor,
                              1,
                              1,
                              32,
			                     10, false);
		}
		// Draw marks
		if ( style.markWidth >= 1 && style.markPlot && !style.markPlot.IsEmpty()) {
			for (int c=0; c<pts.GetCount(); ++c)
			{
				style.markPlot->Paint(dw,
                               scale,
                               pts[c],
                               style.markWidth,
                               style.markColor,
                               style.markWidth,
                               style.markColor);
			}
		}
		return ib;
	}



}
}