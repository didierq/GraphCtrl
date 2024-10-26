/*
 * GraphElement.h
 *
 *  Created on: 6 avr. 2012
 *      Author: didier
 */
#include "logging.h"

#ifndef GRAPHELEMENT_H_
#define GRAPHELEMENT_H_
namespace GraphDraw_ns
{
	typedef enum ElementPosition {
		LEFT_OF_GRAPH    = 0x001,
		RIGHT_OF_GRAPH   = 0x002,
		TOP_OF_GRAPH     = 0x010,
		BOTTOM_OF_GRAPH  = 0x020,
		FLOAT_OVER_GRAPH = 0x100
	} ElementPosition;

	enum {
		VERTICAL_MASK   = 0x00F,
		HORIZONTAL_MASK = 0x0F0,
		FLOAT_MASK      = 0xF00
	};

	typedef enum {
		ELEMENT_BORDER_NONE   = 0x0,
		
		ELEMENT_BORDER_LEFT   = LEFT_OF_GRAPH,
		ELEMENT_BORDER_RIGHT  = RIGHT_OF_GRAPH,
		ELEMENT_BORDER_TOP    = TOP_OF_GRAPH,
		ELEMENT_BORDER_BOTTOM = BOTTOM_OF_GRAPH,
		
		ELEMENT_BORDER_CENTER = 0x200,

		ELEMENT_BORDER_TOP_LEFT     = ELEMENT_BORDER_LEFT | ELEMENT_BORDER_TOP,
		ELEMENT_BORDER_TOP_RIGHT    = ELEMENT_BORDER_RIGHT | ELEMENT_BORDER_TOP,
		ELEMENT_BORDER_BOTTOM_RIGHT = ELEMENT_BORDER_RIGHT | ELEMENT_BORDER_BOTTOM,
		ELEMENT_BORDER_BOTTOM_LEFT  = ELEMENT_BORDER_LEFT | ELEMENT_BORDER_BOTTOM
	} ElementBorderPosition;

	ElementBorderPosition GetElementSubArea( PointScreen p, RectScreen r, int borderWidth );



	typedef enum RefreshStrategy {
			REFRESH_DEFAULT = 0,
			REFRESH_FAST,
			REFRESH_FULL,
			REFRESH_KEEP_DATA
	} RefreshStrategy;

	typedef enum FitToDataStrategy {
		ALL_SERIES,
		VISIBLE_SERIES_ONLY
	} FitToDataStrategy;

	 typedef enum {
		MD_DRAW		   = -1,
		MD_ANTIALIASED = MODE_ANTIALIASED,
		MD_NOAA        = MODE_NOAA,
		MD_SUBPIXEL    = MODE_SUBPIXEL
	} DrawMode;



	typedef Callback2< PointScreen, dword >  MouseLocalLoopCB;

	class GraphElementParent {
		public:
			typedef GraphElementParent CLASSNAME;
			virtual void ScrollX( TypeScreenCoord xOffset, bool doRefresh = true) = 0;
			virtual void ScrollY( TypeScreenCoord yOffset, bool doRefresh = true) = 0;
			virtual void ZoomX(TypeScreenCoord left, TypeScreenCoord right) = 0;
			virtual void ZoomY(TypeScreenCoord top, TypeScreenCoord bottom) = 0;
			virtual void RefreshFromChild( RefreshStrategy doFastPaint ) = 0;
			virtual GraphSeriesDecoratorVector& GetGSeries() = 0;
			virtual Value GetParentCtrl() = 0;
			virtual void AddUndoAction(Upp::UndoStackData& CB) = 0;
			virtual Callback MakeRestoreGraphSizeCB() = 0;
			virtual DrawMode GetDrawMode() = 0;
			virtual void RequestLinksUpdate(CoordinateConverter& p) = 0;
			virtual void RequestChStyleLocal() = 0;
			
			virtual void DoLocalLoop(MouseLocalLoopCB  CB, Image cursorOverrideImg = Null) = 0;

			GraphElementParent() {}
			virtual ~GraphElementParent() {}
			
			// GraphElements are NOT COPYABLE nor MOVEABLE
			GraphElementParent(GraphElementParent&&) = delete;
			GraphElementParent(const GraphElementParent&&) = delete;
			GraphElementParent(GraphElementParent& ) = delete;
			GraphElementParent(const GraphElementParent& ) = delete;
	};


	// ============================
	//    GraphElement   CLASS
	// ============================
	// GraphElements are NOT COPYABLE nor MOVEABLE
	#define GE_NOT_COPYABLE_MOVEABLE(classe) \
	classe(classe&&) = delete; \
	classe(const classe&&) = delete;\
	classe(classe& ) = delete;\
	classe(const classe& ) = delete;

	class GraphElement {
		protected:
			RectScreen      _frame;     // Frame on which element is painted (absolute position in complete ctrl area)
			RectScreen      _floatFrame;// Frame size used as SCALE=1 reference frame  when element is FLOATING
			int             _width;     // width of GraphElement (in screen size)
			ElementPosition _pos;       // position in plot area
			int             _allowedPosMask; // mask that enables only the authorized _pos values
			bool            _hide;      // true: is not drawn
			int             _stackingPriority; //
			bool            _overlapPreviousElement; // if true, then this element will overlap previous element ==> it will have SAME SIZE and  SAME POSITION as the previous element
			String          _name;


		public:
			struct GEBaseStyle {
				Value     lmntBackgnd;
			};

			GraphElementParent* _parent;

			GraphElement()
			: _frame( 0, 0, 5, 5 )
			, _floatFrame(_frame)
			, _width(5)
			, _pos(LEFT_OF_GRAPH)
			, _allowedPosMask(LEFT_OF_GRAPH | RIGHT_OF_GRAPH| BOTTOM_OF_GRAPH | TOP_OF_GRAPH | FLOAT_OVER_GRAPH )
			, _hide(false)
			, _stackingPriority(100)
			, _overlapPreviousElement(false)
			, _name("NAME NOT SET")
			, _parent(nullptr)
			{}
			
			GraphElement(GraphElement* p)
			: _frame( 0, 0, 5, 5 )
			, _floatFrame(p->_floatFrame)
			, _width(p->_width)
			, _pos(LEFT_OF_GRAPH)
			, _allowedPosMask(p->_allowedPosMask)
			, _hide(p->_hide)
			, _stackingPriority(p->_stackingPriority)
			, _overlapPreviousElement(false)
			, _name("NAME NOT SET")
			, _parent(p->_parent)
			{}
			
			GE_NOT_COPYABLE_MOVEABLE(GraphElement)

			String   ToString() const {
				String r;
				r << "GraphElement::  " << _name << "   width:"<< _width << "   Prio:" << _stackingPriority << "   Pos:" << (int)_pos << "     " << _frame;
				return r;
			}

			void AdjustToPlotRect(const RectScreen& plotRect)
			{
				if ( !IsFloat() ) {
					if ( IsHorizontal() ) {
						_frame.left = plotRect.left;
						_frame.right = plotRect.right;
					}
					else {
						_frame.top = plotRect.top;
						_frame.bottom = plotRect.bottom;
					}
				}
			}

			virtual ~GraphElement() {}
			
			inline GraphElementParent* GetParent() { return _parent; }


			inline void SetElementName(const char* name) { _name = name; };
			inline String& GetElementName() { return _name; };
			
			inline void SetFrame(RectScreen v) { _frame = v; }
			inline const RectScreen& GetFrame() const { return _frame; }

			inline void SetFloatFrame(RectScreen v) { _floatFrame = v; }
			inline const RectScreen& GetFloatFrame() const { return _floatFrame; }
			inline const RectScreen GetFloatFrame(int scale) const { RectScreen f=_floatFrame; f.Set(f.TopLeft()*scale, f.BottomRight()*scale) ; return f; }

			virtual void SetElementWidth(int v)  { _width = v; }
			inline int   GetElementWidth() const { return _width; }

			inline void SetStackingPriority( int v ) { _stackingPriority = v; }
			inline int  GetStackingPriority() const  { return _stackingPriority; }

			inline void SetOverlapPrevious( bool v ) { _overlapPreviousElement = v; }
			inline bool GetOverlapPrevious() const   { return _overlapPreviousElement; }
			
			virtual void  SetElementPos(ElementPosition v) { _pos = v; }
			inline ElementPosition GetElementPos() const { return _pos; }
			inline void DisablePos( int v ) { _allowedPosMask &= ~v; }
			inline void SetAllowedPosMask( int v ) { _allowedPosMask = v; }
			inline int GetAllowedPosMask() { return _allowedPosMask; }

			inline bool IsVertical() const { return ((_pos & GraphDraw_ns::VERTICAL_MASK)!=0); }
			inline bool IsHorizontal() const { return ((_pos & GraphDraw_ns::HORIZONTAL_MASK)!=0); }
			inline bool IsFloat() const { return ((_pos & GraphDraw_ns::FLOAT_MASK)!=0); }
			inline bool IsHidden() const { return _hide; }
			inline void Hide( bool v=true ) { _hide = v; }
			
			bool operator<(const GraphElement& b) const { return (_stackingPriority < b._stackingPriority); };
			bool operator>(const GraphElement& b) const { return (_stackingPriority > b._stackingPriority); };


			virtual bool Contains(PointScreen p) const { return _frame.Contains(p); }

			
			inline void PaintElementBckGround(Draw& dw, Size sz, const Value& backGnd) {
				if ( !(backGnd.IsNull()) )   ChPaint(dw, sz, backGnd );
			}

			// Do general painting prepapration actions : update, recalculations, ...
			virtual void PrePaint( int scale ) {};

            // Paint element somewhere inside the graph area as a FLOATING element (legend, ...)
			// Offset and clipping are set with the '_floatFrame' settings
			virtual void PaintFloatElement(Draw& dw, int scale) { };

			// Paint the element in his own area
			// There is no clipping ==> drawing can overlap plot or other elements
			virtual void PaintElement(Draw& dw, int scale) = 0;

			// Paint additionnal element stuff on PLOT AREA : grids, square zones,  anything you wan't
			// Painting zone is clipped so nothing can be drawn outside
			virtual void PaintOnPlot_underData(Draw& dw, int otherWidth, int scale) {}
			virtual void PaintOnPlot_overData(Draw& dw, int otherWidth, int scale) {}

			virtual void MouseEnter (PointScreen p, dword keyflags) { }
			virtual void MouseLeave ()                              { }
			virtual void MouseMove  (PointScreen p, dword keyflags) { }
			virtual void MouseWheel (PointScreen p, int zdelta, dword keyflags) { }

			virtual Image  CursorImage(PointScreen p, dword keyflags) { return GraphDrawImg::CROSS(); }
			
			virtual void LeftDown   (PointScreen p, dword keyflags) { }
			virtual void LeftUp     (PointScreen p, dword keyflags) { }
			virtual void LeftDouble (PointScreen p, dword keyflags) { }
			virtual void LeftTriple (PointScreen p, dword keyflags) { }
			virtual void LeftRepeat (PointScreen p, dword keyflags) { }
			virtual void LeftDrag   (PointScreen p, dword keyflags) { }
			virtual void LeftHold   (PointScreen p, dword keyflags) { }
			
			virtual void RightDown  (PointScreen p, dword keyflags) { }
			virtual void RightUp    (PointScreen p, dword keyflags) { }
			virtual void RightDouble(PointScreen p, dword keyflags) { }
			virtual void RightTriple(PointScreen p, dword keyflags) { }
			virtual void RightRepeat(PointScreen p, dword keyflags) { }
			virtual void RightDrag  (PointScreen p, dword keyflags) { }
			virtual void RightHold  (PointScreen p, dword keyflags) { }

			virtual void MiddleDown  (PointScreen p, dword keyflags) { }
			virtual void MiddleUp    (PointScreen p, dword keyflags) { }
			virtual void MiddleDouble(PointScreen p, dword keyflags) { }
			virtual void MiddleTriple(PointScreen p, dword keyflags) { }
			virtual void MiddleRepeat(PointScreen p, dword keyflags) { }
			virtual void MiddleDrag  (PointScreen p, dword keyflags) { }
			virtual void MiddleHold  (PointScreen p, dword keyflags) { }

			
			virtual void FitToData(FitToDataStrategy fitStrategy) {}

	};

	inline bool compareGraphElementPriority(const GraphElement* a, const GraphElement* b) {
		return *a < *b;
	}
}

#endif /* GRAPHELEMENT_H_ */
