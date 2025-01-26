#ifndef _GraphCtrl_GraphFunctions_h_
#define _GraphCtrl_GraphFunctions_h_


namespace GraphDraw_ns
{
	void DrawLine(Draw &w, double x0, double y0, double x1, double y1, double width, const Color &color);
	void DrawLine(Painter &w, double x0, double y0, double x1, double y1, double width, const Color &color);
	void DrawRectangle(Draw &w, double x0, double y0, double x1, double y1, double scale, 
						double width, const Color &color);
	void DrawRectangle(Painter &w, double x0, double y0, double x1, double y1, double scale, 
						double width, const Color &color);
	template <class T>
	void DrawRectangle(T &w, const Rectf &rect, double scale, double width, const Color &color) {
		DrawRectangle(w, rect.left, rect.top, rect.right, rect.bottom, scale, width, color);
	}
	void FillRectangle(Draw &w, double x0, double y0, double x1, double y1, const Color &color) ;
	void FillRectangle(Painter &w, double x0, double y0, double x1, double y1, const Color &color);
	template <class T>
	void FillRectangle(T &w, const Rectf &rect, const Color &color) {
		FillRectangle(w, rect.left, rect.top, rect.right, rect.bottom, color);
	}					
	void DrawLineOpa(Draw& w, double x0, double y0, double x1, double y1, double scale, double opacity, double thick, const Color &_color, String pattern, const Color &background = Null);	
	void DrawLineOpa(Painter& w, double x0, double y0, double x1, double y1, double scale, double opacity, double thick, const Color &_color, String pattern, const Color &background = Null);	
	void DrawCircleOpa(Draw& w, double x, double y, double r, double scale, double opacity, double thick, const Color &_color, String pattern, const Color &background = Null);	
	void DrawCircleOpa(Painter& w, double x, double y, double r, double scale, double opacity, double thick, const Color &_color, String pattern, const Color &background = Null);	
	void FillRectangleOpa(Draw &w, double x0, double y0, double x1, double y1, double opacity, const Color &background, const Color &color);
	void FillRectangleOpa(Painter &w, double x0, double y0, double x1, double y1, double opacity, const Color &background, const Color &color);
	void DrawPolylineOpa(Draw& w, const Vector<Pointf> &p, double scale, double opacity, double thick, const Color &color, String pattern = "", const Color &background = Null);
	void DrawPolylineOpa(Painter& w, const Vector<Pointf> &p, double scale, double opacity, double thick, const Color &color, String pattern = "", const Color &background = Null);
	void FillPolylineOpa(Draw& w, const Vector<Pointf> &p, double scale, double opacity, const Color &background, const Color &fillColor);
	void FillPolylineOpa(Painter& w, const Vector<Pointf> &p, double scale, double opacity, const Color &background, const Color &fillColor);
	void DrawVArrow(Draw &w, double x0, double y0, double x1, double y1, double width, double aWidth, double aHeight, const Color &color);
	void DrawVArrow(Painter &w, double x0, double y0, double x1, double y1, double width, double aWidth, double aHeight, const Color &color);
	void DrawHArrow(Draw &w, double x0, double y0, double x1, double y1, double width, double aWidth, double aHeight, const Color &color);
	void DrawHArrow(Painter &w, double x0, double y0, double x1, double y1, double width, double aWidth, double aHeight, const Color &color);
	void DrawText(Draw &w, double x, double y, int angle, const String &text, Upp::Font font, Color color);
	void DrawText(Painter &w, double x, double y, int angle, const String &text, Upp::Font font, Color color);
//	void Clip(Draw &w, double x, double y, double cx, double cy);
//	void Clip(Painter &w, double x, double y, double cx, double cy);
//	void ClipEnd(Draw &w);
//	void ClipEnd(Painter &w);
	double GetDashLength(const char *dash);
	
	Size GetTextSizeSpace(const String& text, Font font);

	// ===========================================================

	// LINE/LINE
	template <class POINT, class POINT2>
	bool DetectLineCrossing(POINT p1a, POINT p1b, POINT2 p2a, POINT2 p2b)
	{
		// calculate the direction of the lines
		float uA = ((p2b.x-p2a.x)*(p1a.y-p2a.y) - (p2b.y-p2a.y)*(p1a.x-p2a.x)) / ((p2b.y-p2a.y)*(p1b.x-p1a.x) - (p2b.x-p2a.x)*(p1b.y-p1a.y));
		float uB = ((p1b.x-p1a.x)*(p1a.y-p2a.y) - (p1b.y-p1a.y)*(p1a.x-p2a.x)) / ((p2b.y-p2a.y)*(p1b.x-p1a.x) - (p2b.x-p2a.x)*(p1b.y-p1a.y));
		
		// if uA and uB are between 0-1, lines are colliding
		return (uA >= 0 & uA <= 1 & uB >= 0 & uB <= 1);
//		if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) return true;
//		return false;
	}


//#define  USE_LINECROSSING


	template <class POINT, class RECT>
	bool DetectSCrossing( POINT p1, POINT p2, RECT rect)
	{
		if (p1.x>p2.x) Swap(p1,p2);
#ifdef USE_LINECROSSING
		if ( DetectLineCrossing(p1, p2, rect.TopLeft(), rect.BottomRight()) ) return true;
		if ( DetectLineCrossing(p1, p2, rect.TopRight(), rect.BottomLeft()) ) return true;
		return false;
#else
		
		if (p1.x<p2.x) {
			if ((p2.x<rect.left) || (rect.right<p1.x)) return false;
		}
		else {
			if ((p1.x<rect.left) || (rect.right<p2.x)) return false;
		}
	
		if (p1.y<p2.y) {
			if ((p1.y>rect.bottom) || (rect.top>p2.y)) return false;
		}
		else {
			if ((p2.y>rect.bottom) || (rect.top>p1.y)) return false;
		}

		auto pente = (p2.y-p1.y)/(p2.x-p1.x);
		auto dXmin = pente*(rect.left-p1.x)+p1.y;
		auto dXmax = pente*(rect.right-p1.x)+p1.y;
		return ( ((dXmin-rect.top)*(dXmax-rect.bottom) < 0)
		         | ((dXmin-rect.bottom)*(dXmax-rect.top) < 0) );
//		if ( ((dXmin-rect.top)*(dXmax-rect.bottom) < 0)
//		   ||((dXmin-rect.bottom)*(dXmax-rect.top) < 0) )
//		{
//			return true;
//		}
//		return false;
#endif
	}


	template <class POINT, class RECT>
	bool DetectSCrossing_XinRange(POINT p1, POINT p2, RECT rect)
	{
//		if (p1.x>p2.x) Swap(p1,p2);

#ifdef USE_LINECROSSING
		if ( DetectLineCrossing(p1, p2, rect.TopLeft(), rect.BottomRight()) ) return true;
		if ( DetectLineCrossing(p1, p2, rect.TopRight(), rect.BottomLeft()) ) return true;
		return false;
#else
		// We know X is in valid range ==> no need to test
		if (p1.y<p2.y) {
			if ((p1.y>rect.bottom) || (rect.top>p2.y)) return false;
		}
		else {
			if ((p2.y>rect.bottom) || (rect.top>p1.y)) return false;
		}

		auto pente = (p2.y-p1.y)/(p2.x-p1.x);
		auto dXmin = pente*(rect.left-p1.x)+p1.y;
		auto dXmax = pente*(rect.right-p1.x)+p1.y;
		
		return ( ((dXmin-rect.top)*(dXmax-rect.bottom) < 0)
		       | ((dXmin-rect.bottom)*(dXmax-rect.top) < 0) );
//		if ( ((dXmin-rect.top)*(dXmax-rect.bottom) < 0)
//		   ||((dXmin-rect.bottom)*(dXmax-rect.top) < 0) )
//		{
//			return true;
//		}
//		return false;
#endif
	}


};


#endif
