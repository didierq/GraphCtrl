#ifndef _GraphCtrl_GrapCtrl_h
#define _GraphCtrl_GrapCtrl_h


/*

ceci est un commentaire

*/
#include <GraphDraw/GraphDraw.h>

#include <CtrlLib/CtrlLib.h>
#include <GridCtrl/GridCtrl.h>

#include <DropLineDash/DropLineDash.h>
#include <DropFont/DropFont.h>
#include <AutoScroller/AutoScroller.h>

namespace Upp {

INITIALIZE(GraphCtrl);

#define LAYOUTFILE <GraphCtrl/GraphCtrl.lay>
#include <CtrlCore/lay.h>
#define IMAGECLASS GraphCtrlImg
#define IMAGEFILE <GraphCtrl/GraphCtrl.iml>
#include <Draw/iml_header.h>

namespace GraphDraw_ns {

// ===============================================================================================================================
// ===============================================================================================================================


#include "PropertiesDlgBase.h"
#include "GSeriesCtrl.h"
#include "GraphCtrlBase.h"
#include "StdElementPropertiesDialogs.h"
#include "ElementCtrlBase.h"
#include "StdElementCtrls.h"



	template<class TYPES, class DERIVED>
	class GD_XYLTMM_GraphCtrl   : public GraphCtrl_Base< TYPES, DERIVED, CRTP_EmptyGraphDraw<TYPES, DERIVED> >
	{
		public:
			typedef GD_XYLTMM_GraphCtrl<TYPES, DERIVED> CLASSNAME;
			typedef TYPES Types;
			typedef GraphCtrl_Base< TYPES, DERIVED, CRTP_EmptyGraphDraw<TYPES, DERIVED> > _B;
	
			typedef typename TYPES::X1_TypeCoordConverter TypeCoordConverterX1;
			typedef typename TYPES::X1_TypeGridAxisDraw   TypeGridAxisX1;
			typedef typename TYPES::TypeLabelElement      TypeLabelX1;
			typedef typename TYPES::Y1_TypeCoordConverter TypeCoordConverterY1;
			typedef typename TYPES::Y1_TypeGridAxisDraw   TypeGridAxisY1;
			typedef typename TYPES::TypeLabelElement      TypeLabelY1;
			typedef typename TYPES::TypeLegendElement     TypeLegend;
			typedef typename TYPES::TypeLabelElement      TypeLabelTitle;
			typedef typename TYPES::TypeMarkerElement     TypeMarkerX1;
			typedef typename TYPES::TypeMarkerElement     TypeMarkerY1;
			
			struct Style : ChStyle<Style> {
				typename _B::StyleGD                 gdStyle;
				typename _B::StyleGC                 gcStyle;
				typename     TypeGridAxisX1::StyleGE x1AxisStyle;
				typename     TypeLabelX1   ::StyleGE x1LabelStyle;
				typename     TypeGridAxisY1::StyleGE y1AxisStyle;
				typename     TypeLabelY1   ::StyleGE y1LabelStyle;
				typename     TypeLegend    ::StyleGE legendStyle;
				typename     TypeLabelTitle::StyleGE titleStyle;
				typename     TypeMarkerX1  ::StyleGE x1MarkerStyle;
				typename     TypeMarkerY1  ::StyleGE y1MarkerStyle;
			};

		protected:
			const Style*  style;
			TypeCoordConverterX1  _x1Converter;
			TypeGridAxisX1        _x1GridDraw;
			TypeLabelX1           _x1Label;
			TypeCoordConverterY1  _y1Converter;
			TypeGridAxisY1        _y1GridDraw;
			TypeLabelY1           _y1Label;
			TypeLegend            _legend;
			TypeLabelTitle        _title;
			TypeMarkerX1          _x1MarkerGraphElement;
			TypeMarkerY1          _y1MarkerGraphElement;

		public:
			DERIVED& setGraphSize(Rectf r) {
				_x1Converter.UpdateGraphSize(r.TopLeft().x, r.BottomRight().x);
				_y1Converter.UpdateGraphSize(r.TopLeft().y, r.BottomRight().y);
				_B::updateSizes();
				return *static_cast<DERIVED*>(this);
			}
	
			DERIVED& setGraphSize(TypeGraphCoord x0, TypeGraphCoord x1, TypeGraphCoord y0, TypeGraphCoord y1) {
				_x1Converter.UpdateGraphSize( x0, x1);
				_y1Converter.UpdateGraphSize( y0, y1);
				_B::updateSizes();
				return *static_cast<DERIVED*>(this);
			}

		public:
			virtual ~GD_XYLTMM_GraphCtrl() {}
			
			GD_XYLTMM_GraphCtrl()
			: _x1Converter(*this)
			, _x1GridDraw(_x1Converter)
			, _y1Converter(*this)
			, _y1GridDraw(_y1Converter)
			, _x1MarkerGraphElement(_x1Converter)
			, _y1MarkerGraphElement(_y1Converter)
			{
				SetStyle( static_cast<DERIVED*>(this)->StyleDefault() );
				
				_B::AddXConverter(&_x1Converter);
				_B::AddBottomElement(_x1GridDraw, 20);
				_B::AddBottomElement(30, _x1Label, 25);
				_x1GridDraw.SetElementName( t_("X Axis grid") );
				_x1GridDraw.SetElementWidth(25);
				_x1Label.SetElementName( t_("X Axis label") );
				_x1Label.SetLabel("X Axis label");
	
				_B::AddYConverter(&_y1Converter);
				_B::AddLeftElement(_y1GridDraw, 20);
				_B::AddLeftElement(30, _y1Label, 25);
				_y1GridDraw.SetElementName( t_("Y Axis grid") );
				_y1GridDraw.SetElementWidth(40);
				_y1Label.SetElementName( t_("Y Axis label") );
				_y1Label.SetLabel("Y Axis label");
				
				_legend.SetElementName(t_("Legend"));
				_legend.SetFloatFrame(RectScreen(PointScreen(40,20), Size(80, 30)));
				_B::AddFloatElement(30, _legend, 150);
				
				_B::AddTopElement(40, _title, 200);
				_title.SetElementName( t_("Graph Title") );
				_title.SetLabel("TITLE");
	
				_B::AddTopElement(30, _x1MarkerGraphElement, -1);
				_x1MarkerGraphElement.SetAllowedPosMask(BOTTOM_OF_GRAPH | TOP_OF_GRAPH);
	
				_B::AddRightElement(30, _y1MarkerGraphElement, -1);
				_y1MarkerGraphElement.SetAllowedPosMask(LEFT_OF_GRAPH | RIGHT_OF_GRAPH);
			}
	
			const Style& GetStyle() { return *style; }
			
			DERIVED&  SetStyle(const Style& s) {
				_B::OverrideLocalChStyle(s);
				style = &s;
				_B::SetStyleGD(style->gdStyle);
				_B::SetStyleGC(style->gcStyle);
				_title.               SetStyleGE(style->titleStyle);
				_legend.              SetStyleGE(style->legendStyle);
				_x1GridDraw.          SetStyleGE(style->x1AxisStyle);
				_x1Label.             SetStyleGE(style->x1LabelStyle);
				_x1MarkerGraphElement.SetStyleGE(style->x1MarkerStyle);
				_y1GridDraw.          SetStyleGE(style->y1AxisStyle);
				_y1Label.             SetStyleGE(style->y1LabelStyle);
				_y1MarkerGraphElement.SetStyleGE(style->y1MarkerStyle);
				return *static_cast<DERIVED*>(this);
			}

			GD_ELEM_FN_TITLE;
			GD_ELEM_FN_AXIS(X1,x1);
			GD_ELEM_FN_LABEL(X1,x1);
			GD_ELEM_FN_AXIS(Y1,y1);
			GD_ELEM_FN_LABEL(Y1,y1);
			GD_ELEM_FN_LEGEND;
			GD_ELEM_FN_MARKER(X1,x1);
			GD_ELEM_FN_MARKER(Y1,y1);

			GD_LAYOUTFN_BASE;
			GD_ELEM_LAYOUTFN_TITLE;
			GD_ELEM_LAYOUTFN_LEGEND;
			GC_ELEM_LAYOUTFN_AXIS   (X1, x1);
			GC_ELEM_LAYOUTFN_AXIS   (Y1, y1);
			GD_ELEM_LAYOUTFN_LABEL  (X1, x1);
			GD_ELEM_LAYOUTFN_LABEL  (Y1, y1);
			GD_ELEM_LAYOUTFN_MARKER (X1, x1);
			GD_ELEM_LAYOUTFN_MARKER (Y1, y1);

			virtual void AddAllPropertiesTabs(ElementPropertiesDlgInterface::VList& elemPropDlgList, TabCtrl& tabs, Style& styl) {
				_B::AddPropertiesTab( elemPropDlgList, tabs, "Global", GetElementTitle()         , styl.titleStyle   );
				_B::AddPropertiesTab( elemPropDlgList, tabs, "Legend", GetElementLegend()        , styl.legendStyle  );

				_B::AddPropertiesTab( elemPropDlgList, tabs, "--X--", GetElementX1Label()        , styl.x1LabelStyle
				                                             , GetElementX1GridAxisDraw() , styl.x1AxisStyle
				                                             , GetElementX1Markers()      , styl.x1MarkerStyle
				                                             );
				_B::AddPropertiesTab( elemPropDlgList, tabs, "--Y--", GetElementY1Label()       , styl.y1LabelStyle
				                                             , GetElementY1GridAxisDraw(), styl.y1AxisStyle
				                                             , GetElementY1Markers()     , styl.y1MarkerStyle
				                                             );
			}
	};



	template<class TYPES, class DERIVED>
	class GD_XYY2LTMM_GraphCtrl   : public GraphCtrl_Base< TYPES, DERIVED, CRTP_EmptyGraphDraw<TYPES, DERIVED> >
	{
		public:
			typedef GD_XYY2LTMM_GraphCtrl<TYPES, DERIVED> CLASSNAME;
			typedef GraphCtrl_Base< TYPES, DERIVED, CRTP_EmptyGraphDraw<TYPES, DERIVED> > _B;
			typedef TYPES Types;
	
			typedef typename TYPES::TypeLabelElement      TypeLabelTitle;
			typedef typename TYPES::TypeLegendElement     TypeLegend;
			typedef typename TYPES::X1_TypeCoordConverter TypeCoordConverterX1;
			typedef typename TYPES::X1_TypeGridAxisDraw   TypeGridAxisX1;
			typedef typename TYPES::TypeLabelElement      TypeLabelX1;
			typedef typename TYPES::TypeMarkerElement     TypeMarkerX1;
			typedef typename TYPES::Y1_TypeCoordConverter TypeCoordConverterY1;
			typedef typename TYPES::Y1_TypeGridAxisDraw   TypeGridAxisY1;
			typedef typename TYPES::TypeLabelElement      TypeLabelY1;
			typedef typename TYPES::TypeMarkerElement     TypeMarkerY1;
			typedef typename TYPES::Y2_TypeCoordConverter TypeCoordConverterY2;
			typedef typename TYPES::Y2_TypeGridAxisDraw   TypeGridAxisY2;
			typedef typename TYPES::TypeLabelElement      TypeLabelY2;
			typedef typename TYPES::TypeMarkerElement     TypeMarkerY2;
			
			struct Style : ChStyle<Style> {
				typename _B::StyleGD                 gdStyle;
				typename _B::StyleGC                 gcStyle;
				typename     TypeLabelTitle::StyleGE titleStyle;
				typename     TypeLegend    ::StyleGE legendStyle;
				typename     TypeGridAxisX1::StyleGE x1AxisStyle;
				typename     TypeLabelX1   ::StyleGE x1LabelStyle;
				typename     TypeGridAxisY1::StyleGE y1AxisStyle;
				typename     TypeLabelY1   ::StyleGE y1LabelStyle;
				typename     TypeGridAxisY2::StyleGE y2AxisStyle;
				typename     TypeLabelY2   ::StyleGE y2LabelStyle;
				typename     TypeMarkerX1  ::StyleGE x1MarkerStyle;
				typename     TypeMarkerY1  ::StyleGE y1MarkerStyle;
				typename     TypeMarkerY2  ::StyleGE y2MarkerStyle;
			};

		protected:
			const Style*  style;
			TypeLabelTitle       _title;
			TypeLegend           _legend;
			TypeCoordConverterX1 _x1Converter;
			TypeGridAxisX1       _x1GridDraw;
			TypeLabelX1          _x1Label;
			TypeMarkerX1         _x1MarkerGraphElement;
			TypeCoordConverterY1 _y1Converter;
			TypeGridAxisY1       _y1GridDraw;
			TypeLabelY1          _y1Label;
			TypeMarkerY1         _y1MarkerGraphElement;
			TypeCoordConverterY2 _y2Converter;
			TypeGridAxisY2       _y2GridDraw;
			TypeLabelY2          _y2Label;
			TypeMarkerY1         _y2MarkerGraphElement;

		private:
			// forbid usage of following methods in this case
			DERIVED& setGraphSize(Rectf r) = delete;
			DERIVED& setGraphSize(TypeGraphCoord x0, TypeGraphCoord x1, TypeGraphCoord y0, TypeGraphCoord y1) = delete;
			
		public:
			DERIVED& setGraphSize(TypeGraphCoord x0, TypeGraphCoord x1, TypeGraphCoord y0, TypeGraphCoord y1, TypeGraphCoord y20, TypeGraphCoord y21 )
			{
				_x1Converter.UpdateGraphSize( x0, x1);
				_y1Converter.UpdateGraphSize( y0, y1);
				_y2Converter.UpdateGraphSize( y20, y21);
				_B::updateSizes();
				return *static_cast<DERIVED*>(this);
			}

		public:
			virtual ~GD_XYY2LTMM_GraphCtrl() {}
			
			GD_XYY2LTMM_GraphCtrl()
			: _x1Converter(*this)
			, _x1GridDraw(_x1Converter)
			, _x1MarkerGraphElement(_x1Converter)
			, _y1Converter(*this)
			, _y1GridDraw(_y1Converter)
			, _y1MarkerGraphElement(_y1Converter)
			, _y2Converter(*this)
			, _y2GridDraw(_y2Converter)
			, _y2MarkerGraphElement(_y2Converter)
			{
				SetStyle( static_cast<DERIVED*>(this)->StyleDefault() );
				
				_B::AddXConverter(&_x1Converter);
				_B::AddBottomElement(_x1GridDraw, 20);
				_B::AddBottomElement(30, _x1Label, 25);
				_x1GridDraw.SetElementName( t_("X axis grid") );
				_x1GridDraw.SetElementWidth(25);
				_x1Label.SetElementName( t_("X Axis label") );
				_x1Label.SetLabel("X Axis label");
	
				_B::AddYConverter(&_y1Converter);
				_B::AddLeftElement(_y1GridDraw, 20);
				_B::AddLeftElement(30, _y1Label, 25);
				_y1GridDraw.SetElementName( t_("Y Axis grid") );
				_y1GridDraw.SetElementWidth(40);
				_y1Label.SetElementName( t_("Y Axis label") );
				_y1Label.SetLabel("Y Axis label");

				_B::AddYConverter(&_y2Converter);
				_B::AddRightElement(_y2GridDraw, 20);
				_B::AddRightElement(30, _y2Label, 25);
				_y2GridDraw.SetElementName( t_("Y2 Axis grid") );
				_y2GridDraw.SetElementWidth(40);
				_y2Label.SetElementName( t_("Y2 Axis label") );
				_y2Label.SetLabel("Y2 Axis label");
				
				_legend.SetElementName(t_("Legend"));
				_legend.SetFloatFrame(RectScreen(PointScreen(40,20), Size(80, 30)));
				_B::AddFloatElement(30, _legend, 150);
				
				_B::AddTopElement(40, _title, 200);
				_title.SetElementName( t_("Graph Title") );
				_title.SetLabel("TITLE");
	
				_B::AddTopElement(30, _x1MarkerGraphElement, -1);
				_x1MarkerGraphElement.SetAllowedPosMask(BOTTOM_OF_GRAPH | TOP_OF_GRAPH);
	
				_B::AddRightElement(30, _y1MarkerGraphElement, -1);
				_y1MarkerGraphElement.SetAllowedPosMask(LEFT_OF_GRAPH | RIGHT_OF_GRAPH);
			}
	
			const Style& GetStyle() { return *style; }
			
			DERIVED&  SetStyle(const Style& s) {
				_B::OverrideLocalChStyle(s);
				style = &s;
				_B::SetStyleGD(style->gdStyle);
				_B::SetStyleGC(style->gcStyle);
				_title.               SetStyleGE(style->titleStyle);
				_legend.              SetStyleGE(style->legendStyle);
				_x1GridDraw.          SetStyleGE(style->x1AxisStyle);
				_x1Label.             SetStyleGE(style->x1LabelStyle);
				_x1MarkerGraphElement.SetStyleGE(style->x1MarkerStyle);
				_y1GridDraw.          SetStyleGE(style->y1AxisStyle);
				_y1Label.             SetStyleGE(style->y1LabelStyle);
				_y1MarkerGraphElement.SetStyleGE(style->y1MarkerStyle);
				_y2GridDraw.          SetStyleGE(style->y2AxisStyle);
				_y2Label.             SetStyleGE(style->y2LabelStyle);
				_y2MarkerGraphElement.SetStyleGE(style->y2MarkerStyle);
				return *static_cast<DERIVED*>(this);
			}

			GD_ELEM_FN_TITLE;
			GD_ELEM_FN_LEGEND;
			GD_ELEM_FN_AXIS(X1,x1);
			GD_ELEM_FN_LABEL(X1,x1);
			GD_ELEM_FN_MARKER(X1,x1);
			GD_ELEM_FN_AXIS(Y1,y1);
			GD_ELEM_FN_LABEL(Y1,y1);
			GD_ELEM_FN_MARKER(Y1,y1);
			GD_ELEM_FN_AXIS(Y2,y2);
			GD_ELEM_FN_LABEL(Y2,y2);
			GD_ELEM_FN_MARKER(Y2,y2);

			GD_LAYOUTFN_BASE;
			GD_ELEM_LAYOUTFN_TITLE;
			GD_ELEM_LAYOUTFN_LEGEND;
			GC_ELEM_LAYOUTFN_AXIS   (X1, x1);
			GD_ELEM_LAYOUTFN_LABEL  (X1, x1);
			GD_ELEM_LAYOUTFN_MARKER (X1, x1);
			GC_ELEM_LAYOUTFN_AXIS   (Y1, y1);
			GD_ELEM_LAYOUTFN_LABEL  (Y1, y1);
			GD_ELEM_LAYOUTFN_MARKER (Y1, y1);
			GC_ELEM_LAYOUTFN_AXIS   (Y2, y2);
			GD_ELEM_LAYOUTFN_LABEL  (Y2, y2);
			GD_ELEM_LAYOUTFN_MARKER (Y2, y2);

			virtual void AddAllPropertiesTabs(ElementPropertiesDlgInterface::VList& elemPropDlgList, TabCtrl& tabs, Style& styl) {
				_B::AddPropertiesTab( elemPropDlgList, tabs, "Global", GetElementTitle()         , styl.titleStyle   );
				_B::AddPropertiesTab( elemPropDlgList, tabs, "Legend", GetElementLegend()        , styl.legendStyle  );
				_B::AddPropertiesTab( elemPropDlgList, tabs, "--X--", GetElementX1Label()        , styl.x1LabelStyle
				                                             , GetElementX1GridAxisDraw() , styl.x1AxisStyle
				                                             , GetElementX1Markers()      , styl.x1MarkerStyle
				                                             );
				_B::AddPropertiesTab( elemPropDlgList, tabs, "--Y--", GetElementY1Label()        , styl.y1LabelStyle
				                                             , GetElementY1GridAxisDraw() , styl.y1AxisStyle
				                                             , GetElementY1Markers()      , styl.y1MarkerStyle
				                                             );
				_B::AddPropertiesTab( elemPropDlgList, tabs, "--Y2--", GetElementY2Label()       , styl.y2LabelStyle
				                                              , GetElementY2GridAxisDraw(), styl.y2AxisStyle
				                                              , GetElementY2Markers()     , styl.y2MarkerStyle
				                                             );
			}
	};

};


// ===============================================================================================================================
// ===============================================================================================================================
struct GraphCtrlDefaultTypes {
		typedef GraphDraw_ns::CoordinateConverter X1_TypeCoordConverter;
		typedef GraphDraw_ns::CoordinateConverter X2_TypeCoordConverter;
		typedef GraphDraw_ns::CoordinateConverter Y1_TypeCoordConverter;
		typedef GraphDraw_ns::CoordinateConverter Y2_TypeCoordConverter;
		typedef GraphDraw_ns::StdGridAxisECtrl    X1_TypeGridAxisDraw;
		typedef GraphDraw_ns::StdGridAxisECtrl    X2_TypeGridAxisDraw;
		typedef GraphDraw_ns::StdGridAxisECtrl    Y1_TypeGridAxisDraw;
		typedef GraphDraw_ns::StdGridAxisECtrl    Y2_TypeGridAxisDraw;
		typedef GraphDraw_ns::StdLabelECtrl       TypeLabelElement;
		typedef GraphDraw_ns::StdLegendECtrl      TypeLegendElement;
		typedef GraphDraw_ns::StdBlankAreaECtrl   TypeBlankElement;
		typedef GraphDraw_ns::StdMarkerECtrl      TypeMarkerElement;
};


class XYLTMM_GraphCtrl : public GraphDraw_ns::GD_XYLTMM_GraphCtrl< GraphCtrlDefaultTypes, XYLTMM_GraphCtrl > {
	public:
		typedef XYLTMM_GraphCtrl  CLASSNAME;
		typedef GraphDraw_ns::GD_XYLTMM_GraphCtrl< GraphCtrlDefaultTypes, CLASSNAME > _B;
		
		XYLTMM_GraphCtrl() { _B::SetStyle( StyleDefault() ); }
		virtual ~XYLTMM_GraphCtrl() {}
		
		static const Style& StyleDefault();
};

class XYY2LTMM_GraphCtrl : public GraphDraw_ns::GD_XYY2LTMM_GraphCtrl< GraphCtrlDefaultTypes, XYY2LTMM_GraphCtrl > {
	public:
		typedef XYY2LTMM_GraphCtrl  CLASSNAME;
		typedef GraphDraw_ns::GD_XYY2LTMM_GraphCtrl< GraphCtrlDefaultTypes, CLASSNAME > _B;
		
		XYY2LTMM_GraphCtrl() {  _B::SetStyle( StyleDefault() ); }
		virtual ~XYY2LTMM_GraphCtrl() {}
		
		static const Style& StyleDefault();
};

class XY_GraphCtrl : public XYLTMM_GraphCtrl {
	public:
		typedef XY_GraphCtrl  CLASSNAME;
		typedef XYLTMM_GraphCtrl _B;
		
		XY_GraphCtrl() {
			DisableGE(GetElementLegend());
			DisableGE(GetElementTitle());
			DisableGE(GetElementX1Markers());
			DisableGE(GetElementY1Markers());
		}
		virtual ~XY_GraphCtrl() {}
};

class XYLT_GraphCtrl : public XYLTMM_GraphCtrl {
	public:
		typedef XYLT_GraphCtrl  CLASSNAME;
		typedef XYLTMM_GraphCtrl _B;
		
		XYLT_GraphCtrl() {
			DisableGE( GetElementX1Markers() );
			DisableGE( GetElementY1Markers() );
		}
		virtual ~XYLT_GraphCtrl() {}
};

class XYLTM_GraphCtrl : public XYLTMM_GraphCtrl {
	public:
		typedef XYLTM_GraphCtrl  CLASSNAME;
		typedef XYLTMM_GraphCtrl _B;
		
		XYLTM_GraphCtrl() {
			DisableGE( GetElementY1Markers() );
		}
		virtual ~XYLTM_GraphCtrl() {}
};

class XYY2LT_GraphCtrl : public XYY2LTMM_GraphCtrl {
	public:
		typedef XYY2LT_GraphCtrl   CLASSNAME;
		typedef XYY2LTMM_GraphCtrl _B;
		
		XYY2LT_GraphCtrl() {
			DisableGE( GetElementX1Markers() );
			DisableGE( GetElementY1Markers() );
			DisableGE( GetElementY2Markers() );
		}
		virtual ~XYY2LT_GraphCtrl() {}
};


}
#endif
