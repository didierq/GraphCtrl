#ifndef _GraphDraw_StdElements_h_
#define _GraphDraw_StdElements_h_


#include "GraphElement.h"
#include "TickMark.h"

namespace GraphDraw_ns
{
	
	class BlankAreaElement : public GraphElement
	{
	public:
		typedef BlankAreaElement CLASSNAME;
		typedef GraphElement _B;

		struct StyleGE : ChStyle<StyleGE> {
			GraphElement::GEBaseStyle geBase;
		};
		static const StyleGE& StyleGEDefault();

		BlankAreaElement() {}
		GE_NOT_COPYABLE_MOVEABLE(BlankAreaElement)
		
		virtual ~BlankAreaElement() {}
		virtual void PaintElement(Draw& dw, int scale) { /* do noting */ }
	};


	
	// ============================
	//    LabelElement   CLASS
	// ============================
	class LabelElement : public GraphElement
	{
	public:
		typedef LabelElement CLASSNAME;
		typedef GraphElement _B;
		
		struct StyleGE : ChStyle<StyleGE> {
			GraphElement::GEBaseStyle geBase;
			Font        labelFont;
			Color       labelColor;
		};

		static const StyleGE& StyleGEDefault();
		static const StyleGE& StyleGETitleDefault();
		static const StyleGE& StyleGEXAxisDefault();
		static const StyleGE& StyleGEYAxisDefault();

		const StyleGE*& GetStyleGE() { return styleGE; }
		void SetStyleGE(const StyleGE& s) { styleGE = &s; }
		
	protected:
		const StyleGE* styleGE;
			
	public:
		Upp::String _label;

		LabelElement() { styleGE = &StyleGEDefault(); }
		GE_NOT_COPYABLE_MOVEABLE(LabelElement)
		virtual ~LabelElement() {}

		template<class T>	inline LabelElement& SetLabel(T& v) { _label = v; return *this; }
		inline const Upp::String& GetLabel() const { return _label; }
		virtual void PaintElement(Draw& dw, int scale);
	};

//	// ============================
//	//    LabelElement   CLASS
//	// ============================

// QTFDisplay

//	class RichLabelElement : public GraphElement
//	{
//		private:
//		RichText    _label;
//		Color       _bckGndcolor;
//		typedef RichLabelElement                          CLASSANME;
//		typedef GraphElement _B;
//
//		public:
//		RichLabelElement() : _bckGndcolor(Null) {}
//		RichLabelElement(RichLabelElement& p) : _B(p), _bckGndcolor(p._bckGndcolor) {}
//		virtual ~RichLabelElement() {}
//
//		virtual CLASSANME* Clone() { return new CLASSANME(*this); };
//
//		template<class T>
//		inline void SetLabel(T& v) { _label = ParseQTF(v); }
////		inline const Upp::String& GetLabel() const { return _label.; }
//
//		virtual void PaintElement(Draw& dw, int scale)
//		{
//			if ( !_bckGndcolor.IsNullInstance() )
//				dw.DrawRect( 0, 0, _B::GetFrame().GetWidth(), _B::GetFrame().GetHeight(), _bckGndcolor);
//
//			//Size sz(0,0);
//			switch(_B::GetElementPos()){
//				case LEFT_OF_GRAPH:
//
//					//dw.DrawText( _B::GetElementWidth()*scale/2-sz.cy/2, _B::GetFrame().GetHeight()/2+sz.cx/2 , 900, _label, _font, _color);
//					break;
//				case BOTTOM_OF_GRAPH:
//					//dw.DrawText( _B::GetFrame().GetWidth()/2-sz.cx/2, _B::GetElementWidth()*scale/2-sz.cy/2 , _label, _font, _color);
//					break;
//				case TOP_OF_GRAPH:
//					_label.Paint(dw, 0, 0, 1000);
//					//dw.DrawText( _B::GetFrame().GetWidth()/2-sz.cx/2, _B::GetElementWidth()*scale/2-sz.cy/2 , _label, _font, _color);
//					break;
//				case RIGHT_OF_GRAPH:
//					//dw.DrawText( _B::GetElementWidth()*scale/2+sz.cy/2, _B::GetFrame().GetHeight()/2-sz.cx/2 , 2700, _label, _font, _color);
//					break;
//			}
//		}
//	};



	// ============================
	//    LegendElement   CLASS
	// ============================
	class LegendElement : public GraphElement
	{
	public:
		typedef LegendElement CLASSNAME;
		typedef GraphElement _B;

		struct StyleGE : ChStyle<StyleGE> {
			GraphElement::GEBaseStyle geBase;
			Font   lgdFont;
			Color  lgdTxtColor;
			int    lgdXSeparation; // separation between two legends
			int    lgdStyleLength;
			Value  lgdFloatBackgnd;
			Value  ldgLabelSelect; // style applied to label when serie is selected
			Value  ldgTextSelect;  // style applied to label when serie is selected
		};
		
		static const StyleGE& StyleGEDefault();
		const StyleGE*& GetStyleGE() { return style; }
		void SetStyleGE(const StyleGE& s) { style = &s; }
		
	protected:
		const StyleGE *style;
		String _legend;
		int    _legendWidth;
		GraphSeriesDecoratorVector* g_series;
		Vector<RectScreen> seriesLabelRectVector; // Screen Rect occupied by each label (needed for label selecttion)

	public:

		LegendElement()	: g_series(nullptr)	{ style = &StyleGEDefault(); }
		GE_NOT_COPYABLE_MOVEABLE(LegendElement)
		virtual ~LegendElement() {}

		CLASSNAME& SetLegend(String v) { _legend = v; return *this; }

		virtual void PaintElement(Draw& dw, int scale);
		virtual void PaintFloatElement(Draw& dw, int scale);
		virtual void PrePaint( int scale );
		void DrawLegend(Draw& w, const int scale);
	};

	
	// ============================
	//    MarkerElementData   CLASS
	// ============================

	class MarkerElementData : Moveable<MarkerElementData> {
	public:
		typedef Function< void(int /*markerID*/, void*) > TypeMarkerUpdateCbk;


	private:
		TickMark* tickMark;
		TypeGraphCoord pos;
		int ID;
		Index<MarkerElementData*> linkedMarkers;
		void* owner;
		
		MarkerElementData(const MarkerElementData& p) : tickMark(nullptr), pos(p.pos), ID(INVALID_MARKER_ID) {} // explicitally forbidden
		
	public:
		enum { INVALID_MARKER_ID = std::numeric_limits<decltype(ID)>::max() };

		MarkerElementData() : tickMark(0), ID(INVALID_MARKER_ID), owner(0) {}
		~MarkerElementData() {
			//GDLOGBLOCK("MarkerElementData::~MarkerElementData");
			UnlinkAll();
			if (tickMark) delete tickMark;
			tickMark = nullptr;
			ID = INVALID_MARKER_ID;
		}
		
		inline TickMark& GetTickMark() const { return *tickMark; }
		inline operator TickMark&()    const { return *tickMark; }

		inline TypeGraphCoord GetPos()   const { return pos; }
		inline operator TypeGraphCoord() const { return pos; }
		
		void SetPos(TypeGraphCoord v) { pos = v; }
		MarkerElementData& operator=( const TypeGraphCoord v ) { pos = v; return *this; }
		MarkerElementData& operator=( const MarkerElementData v ) { pos = v.pos; return *this; }
		MarkerElementData& operator=( const MarkerElementData* v ) { pos = v->pos; return *this; }

		inline int GetID() const { return ID; }
		
		template <class T>
		T& CreateMarker(int id, void* own) // Only valid ID values allowed
		{
			owner = own;
			ID = id;
			if (tickMark) delete tickMark;
			T& tick = * new T();
			tickMark = &tick;
			return tick;
		}
		
		inline bool IsLinkedTo(MarkerElementData* m) const { return ((linkedMarkers.Find(m)  >= 0) ? true : false ); }
		inline bool IsLinkedTo(MarkerElementData& m) const { return ((linkedMarkers.Find(&m) >= 0) ? true : false ); }
		
		void Link(MarkerElementData* m);
		inline void Link(MarkerElementData& m) { Link(&m); }
	
		void Unlink(MarkerElementData* m);
		inline void Unlink(MarkerElementData& m) { Unlink(&m); }
	
		void UnlinkAll();
		void UpdateLinked(TypeMarkerUpdateCbk& cbk);
	};

	// ============================
	//    MarkerPosList
	// ============================
	typedef ArrayMap<int, MarkerElementData> MarkerPosList;

	// ============================
	//    MarkerElement   CLASS
	// ============================
	class MarkerElement : public GraphElement
	{
	public:
		typedef GraphElement  _B;
		typedef MarkerElement  CLASSNAME;

		struct StyleGE : ChStyle<StyleGE> {
			GraphElement::GEBaseStyle geBase;
			Color       mrkLineColor;
			int         mrkLineWidth;
			//int         mrkLineDash;
			Color       mrkTickColor;
			//Function<TickMark* ()> markerFactory;
		};
		
		static const StyleGE& StyleGEDefault();
		
		const StyleGE*& GetStyleGE() { return styleGE; }
		void SetStyleGE(const StyleGE& s) { styleGE = &s; }

	protected:
		const StyleGE* styleGE;
		
	public:
		CoordinateConverter& _coordConverter;
		MarkerPosList markers;

		MarkerElement(CoordinateConverter& coordconv)
		: _coordConverter(coordconv)
		{
			styleGE = &StyleGEDefault();
			_B::DisablePos(FLOAT_OVER_GRAPH);
		}
		
		GE_NOT_COPYABLE_MOVEABLE(MarkerElement)
		virtual ~MarkerElement() {}

		inline const MarkerElementData& GetMarker(int ID) const { return markers.Get(ID); }
		
		template <class MARKER_TYPE>
		MARKER_TYPE&  AddMarker(int markerId, const String txt, TypeGraphCoord pos=0.0) {
			MarkerElementData& markData = markers.Add(markerId);
			markData = pos;
			MARKER_TYPE& m = markData.CreateMarker<MARKER_TYPE>(markerId, this);
			m.SetText(txt);
			return m;
		}

		template <class MARKER_TYPE>
		MARKER_TYPE&  AddMarker(int markerId, TypeGraphCoord pos=0.0) {
			MarkerElementData& markData = markers.Add(markerId);
			markData = pos;
			return markData.CreateMarker<MARKER_TYPE>(markerId, this);
		}

		SmartTextTickMark&  AddMarker(int markerId, TypeGraphCoord pos=0.0);
		SmartTextTickMark&  AddMarker(int markerId, const String txt, TypeGraphCoord pos=1.0);
		void ClearMarkers() { markers.Clear();	}
		void  SetElementPos(ElementPosition v);
		void PaintHLine(Draw& dw, int range);
		void PaintVLine(Draw& dw, int range);
		void PaintElement(Draw& dw, int scale);
		void PaintOnPlot_overData(Draw& dw, int otherWidth, int scale);
	};
}
#endif
