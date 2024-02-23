#include "SimpleJobSerie.h"

#define IMAGECLASS SimpleJobImg
#define IMAGEFILE <GraphSeries/SimpleJobSerie/SimpleJob.iml>
#include <Draw/iml_header.h>

#define IMAGECLASS SimpleJobImg
#define IMAGEFILE <GraphSeries/SimpleJobSerie/SimpleJob.iml>
#include <Draw/iml_source.h>


namespace Upp {
namespace GraphDraw_ns {
	

	// =========================================================
	//    CustomData_Job
	// =========================================================
	bool CustomData_Job::Contains(const PointGraph& pt) const
	{
//				RLOG("CustomData_Job::Contains()["<< priorite << "]="<< rectGraphBound.Contains(pt) << " : " << pt << "  -- "  << rectGraphBound);
		return rectGraphBound.Contains(pt);
	}

	bool CustomData_Job::Intersects(const RectGraph& rect) const
	{
		//RLOG( "CustomData_Job::Intersects()=" << rect.Intersects(rectGraphBound) << " : "<< rect <<  "  --  " << rectGraphBound);
		if ( !rectGraphBound.IsNullInstance() || !rectGraphBound.IsEmpty() ) return rect.Intersects(rectGraphBound);
		return false;
	}

	bool CustomData_Job::Contained(const RectGraph& rect) const
	{
		//RLOG( "CustomData_Job::Contained()=" << rect.Intersects(rectGraphBound) << " : "<< rect <<  "  --  " << rectGraphBound);
		if ( !rectGraphBound.IsNullInstance() || !rectGraphBound.IsEmpty() ) return rect.Contains(rectGraphBound);
		return false;
	}
	
	
	void CustomData_Job::PaintDataPoint(BufferPainter& dw, int scale, int style, const MCoordinateConverter& coordConv ) const {
		Rect r = coordConv.ToScreen(rectGraphBound);
		ChPaint(dw, r, rectStyle);
		if (style == DataPaintingStyle::HIGHLIGHT_STYLE) {
			r.Inflate(5);
			DrawFatFrame(dw, r, Color(255, 44, 252), 3);
		}
	}
	
	
	// =========================================================
	//    SimpleJobSerie
	// =========================================================
	SimpleJobSerie::MakeEditorFunction& SimpleJobSerie::GetDefaultMakeEditorCB() {
		static MakeEditorFunction defaultMakeEditorFct;
		return defaultMakeEditorFct;
	}

	SimpleJobSerie::SimpleJobSerie() {
		SetSelectable(true);
		SetCtrlable(true);
		SetLegend("WF");
		makeEditorFct = GetDefaultMakeEditorCB();
	}

	
	Image SimpleJobSerie::MakeSerieIcon( Size sz, const int scale ) const {
		RGBA bckgColor;   bckgColor.r = 0; bckgColor.g = 0; bckgColor.b = 0; bckgColor.a = 0;
		int width = sz.cx;
		int height = sz.cy;
		ImageBuffer ib( sz );
		Upp::Fill( ib.Begin(), bckgColor, ib.GetLength() );
		BufferPainter dw(ib);
		ChPaint(dw, sz, SimpleJobImg::LegendIcon() );
		return ib;
	}

	RectGraph SimpleJobSerie::GetMinMaxGraphRect() const {
		RectGraph r = data[0].rectGraphBound;
		
		for (int c=1; c<GetCount(); ++c) {
			r.left =   min( data[c].rectGraphBound.left, r.left);
			r.right =  max( data[c].rectGraphBound.right, r.right);
			r.top =    min( data[c].rectGraphBound.top, r.top);
			r.bottom = max( data[c].rectGraphBound.bottom, r.bottom);
		}
		return r;
	}


	bool SimpleJobSerie::LeftDouble (unsigned int pIndex, PointGraph p, dword keyflags) {
		RLOG( "SimpleJobSerie::LeftDouble() [" << pIndex << "] : " << data[pIndex].dateDebut);
		return true;
	}
	
	bool SimpleJobSerie::CursorImage(unsigned int pIndex, PointGraph p, dword keyflags, Image& outImg ) const {
		outImg = GraphDrawImg::CROSS();
		return true;
	}

};
};