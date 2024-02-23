#include "ScatterSeries.h"

namespace Upp {
namespace GraphDraw_ns {

	MarkPlot* GetNewMarkPlot(int id)
	{
		switch(id) {
		case 0:	return new CircleMarkPlot();
		case 1:	return new SquareMarkPlot();
		case 2:	return new TriangleMarkPlot();
		case 3:	return new CrossMarkPlot();
		case 4:	return new XMarkPlot();
		case 5:	return new RhombMarkPlot();
		}
		return new CircleMarkPlot();
	}
	
	SeriesPlot* GetNewPlotStyle(int id) {
		return new LineSeriesPlot();
	}

	
	Color GetNewColor(int id)
	{
		switch(id) {
			case 0:  return LtBlue();
			case 1:  return LtRed();
			case 2:  return LtGreen();
			case 3:  return Black();
			case 4:  return LtGray();
			case 5:  return Brown();
			case 6:  return Blue();
			case 7:  return Red();
			case 8:  return Green();
			case 9:  return Gray();
			case 10: return LtBlue();
			case 11: return LtRed();
			case 12: return LtGreen();
			case 13: return Black();
			case 14: return LtGray();
			case 15: return Brown();
			case 16: return Blue();
			case 17: return Red();
			case 18: return Green();
			case 19: return Gray();
		}
		return Color((int)Random(), (int)Random(), (int)Random());
	}
	
	String GetNewDash(int id)
	{
		switch(id) {
			case 0:		return LINE_SOLID;
			case 1:		return LINE_DOTTED;
			case 2:		return LINE_DASHED;
			case 3:		return LINE_DASH_DOT;
			case 4:		return LINE_SOLID;
			case 5:		return LINE_DOTTED;
			case 6:		return LINE_DASHED;
			case 7:		return LINE_DASH_DOT;
			case 8:		return LINE_SOLID;
			case 9:		return LINE_DOTTED;
			case 10:	   return LINE_DASHED;
			case 11:	   return LINE_DASH_DOT;
		}
		dword r = Random();
		if (r < 8000)
			r += 2000;
		String ret = FormatInt((int)r).Right(4);
		String space = " ";
		return ret.Mid(0, 1) + space + ret.Mid(1, 1) + space + ret.Mid(2, 1) + space + ret.Mid(3, 1);
	}

}
}