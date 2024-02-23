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

	template <class POINT, class RECT>
	bool DetectSCrossing(const POINT p1, const POINT p2, const RECT rect)
	{
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
		if ( ((dXmin-rect.top)*(dXmax-rect.bottom) < 0)
		   ||((dXmin-rect.bottom)*(dXmax-rect.top) < 0) )
		{
			return true;
		}
		return false;
	}


	template <class POINT, class RECT>
	bool DetectSCrossing_XinRange(const POINT p1, const POINT p2, const RECT rect)
	{
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
		if ( ((dXmin-rect.top)*(dXmax-rect.bottom) < 0)
		   ||((dXmin-rect.bottom)*(dXmax-rect.top) < 0) )
		{
			return true;
		}
		return false;
	}


};


#endif
