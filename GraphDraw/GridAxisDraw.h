/*
 * GridAxisDraw.h
 *
 *  Created on: 6 avr. 2012
 *      Author: didier
 */

#ifndef GRIDAXISDRAW_H_
#define GRIDAXISDRAW_H_


#include "TickMark.h"

namespace GraphDraw_ns
{

	// ============================
	//    GridAxisDraw   CLASS
	// ============================
	enum class AxisTextFormat{
		FORMAT_STD,
		FORMAT_LOG,
		FORMAT_DATE,
		FORMAT_TIME,
	} ;

	class GridAxisDraw : public GraphElement
	{
	public:
		typedef GraphElement  _B;
		typedef GridAxisDraw  CLASSNAME;

		struct StyleGE : ChStyle<StyleGE> {
				GraphElement::GEBaseStyle geBase;
				int       axisWidth;
				Color     axisColor;
				Font      axisTextFont;
				Color     axisTextColor;
				Color     axisTickColor;
				Color     gridColor;
				int       gridThickness;
				String    gridDash;
				Function<TickMark* ()> primaryTickFactory;
				Function<TickMark* ()> secondaryTickFactory;
		};

		
		static const StyleGE& StyleGEDefault();  // default for X1 & Y1
		static const StyleGE& StyleGEDefault2(); // default for X2,Y2, X3,Y3, ....
		GridAxisDraw&  SetStyleGE(const StyleGE& s) {
			style = &s;
			_tickMarks[0] = style->primaryTickFactory();
			_tickMarks[1] = style->secondaryTickFactory();
			return *this;
		}

	protected:
		const StyleGE *style;
		
	public:
		
	protected:
		CoordinateConverter& _coordConverter;
		GridStepManager _gridStepManager;

		enum {NB_TICKMARKS = 2 };
		One<TickMark> _tickMarks[NB_TICKMARKS]; // One<>  used for ownership (manages delete)
		TypeFormatTextCbk _formatTextCbk;
		Sizef _meanTickTextsz;
		Sizef _tmpTextSize;
		unsigned int _nbMeanValues;


	public:
		GridAxisDraw(CoordinateConverter& coordConv)
		: _coordConverter( coordConv )
		, _gridStepManager( coordConv )
		, _formatTextCbk(THISBACK(FormatAsDouble))
		, _meanTickTextsz(10,10)
		, _tmpTextSize(10,10)
		, _nbMeanValues(0)
		{
			SetStyleGE(StyleGEDefault());
			_B::DisablePos(FLOAT_OVER_GRAPH);
			PrePaint(1);
		}
		
		GE_NOT_COPYABLE_MOVEABLE(GridAxisDraw)

	public:
		virtual ~GridAxisDraw() {}
		
		virtual void PrePaint( int scale );
		virtual void SetElementPos(ElementPosition v);
		virtual void FitToData(FitToDataStrategy fitStrategy);

		inline GridStepManager& GetGridStepManager()         { return _gridStepManager; }
		inline CoordinateConverter& GetCoordConverter()      { return _coordConverter;  }

		GridAxisDraw& SetAxisInverted(bool v=true)              { _coordConverter.SetInverted(v); _gridStepManager.UpdateGridSteps(); return *this; }
		bool IsAxisInverted() const                             { return _coordConverter.IsInverted(); }

		GridAxisDraw& setMajorTickMark(TickMark* v)             { _tickMarks[0] = v; return *this;  }
		GridAxisDraw& setMinorTickMark(TickMark* v)             { _tickMarks[1] = v; return *this;  }
		GridAxisDraw& setAxisTextFormat(TypeFormatTextCbk v)    { _formatTextCbk = v; return *this;  }

		GridAxisDraw& setAxisTextFormat(AxisTextFormat v) {
			switch(v) {
				case AxisTextFormat::FORMAT_STD:  resetAxisTextFormat() ; break;
				case AxisTextFormat::FORMAT_LOG:  setAxisLogFormat(); break;
				case AxisTextFormat::FORMAT_DATE: setAxisDateFormat(); break;
				case AxisTextFormat::FORMAT_TIME: setAxisTimeFormat(); break;
				default:
					ASSERT_(false, "UNVALID_VALUE");
			}
			return *this;
		}
		
		GridAxisDraw& resetAxisTextFormat();
		GridAxisDraw& setAxisLogFormat(TypeFormatTextCbk cbk=TypeFormatTextCbk());
		GridAxisDraw& setAxisDateFormat( TypeFormatTextCbk cbk=TypeFormatTextCbk() );
		GridAxisDraw& setAxisTimeFormat( TypeFormatTextCbk cbk=TypeFormatTextCbk() );
  
		inline int  GetMajorTickLength()                  { return _tickMarks[0]->GetTickLength(); }
		inline void SetMajorTickLength(int v)             { _tickMarks[0]->SetTickLength(v); }
		inline int  GetMinorTickLength()                  { return _tickMarks[1]->GetTickLength(); }
		inline void SetMinorTickLength(int v)             { _tickMarks[1]->SetTickLength(v); }

		inline       GridStepIterator GridStepBegin(void) { return  _gridStepManager.Begin(); }
		inline const_GridStepIterator GridStepEnd(void)   { return  _gridStepManager.End(); }

		void FormatAsDouble( const const_GridStepIterator& iter, String& output );
		void FormatAsLog10( const const_GridStepIterator& iter, String& output );
		void FormatAsDate( const const_GridStepIterator& value, String& output );
		void FormatAsTime( const const_GridStepIterator& value, String& output );

		void UpdateTickTextData( int scale );

		void PaintTickText(Draw& dw,  const ElementPosition ePos, const const_GridStepIterator& value, TypeScreenCoord x, TypeScreenCoord y, const Color color, const Font scaledFont, int scale);
		virtual void PaintAxisLeft(Draw& dw, const int scale, const_GridStepIterator iter, const_GridStepIterator endIter);
		virtual void PaintAxisRight(Draw& dw, const int scale, const_GridStepIterator iter, const_GridStepIterator endIter);
		virtual void PaintAxisBottom(Draw& dw, const int scale, const_GridStepIterator iter, const_GridStepIterator endIter);
		virtual void PaintAxisTop(Draw& dw, const int scale, const_GridStepIterator iter, const_GridStepIterator endIter);
		virtual void PaintVGrid(Draw& dw, const int scale, int xRange, const_GridStepIterator iter, const_GridStepIterator endIter);
		virtual void PaintHGrid(Draw& dw, const int scale, int yRange, const_GridStepIterator iter, const_GridStepIterator endIter);
		virtual void PaintOnPlot_underData(Draw& dw, int otherWidth, int scale);
		virtual void PaintElement(Draw& dw, int scale);
	};
}


#endif /* GRIDAXISDRAW_H_ */
