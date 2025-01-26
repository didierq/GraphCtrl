#ifndef _GraphDraw_GrapDraw_h
#define _GraphDraw_GrapDraw_h


#include <Core/Core.h>
#include <Draw/Draw.h>
#include <Painter/Painter.h>

#include <RichText/RichText.h>

#ifdef flagGD_TIMINGS
#include <TimingPolicies/TimingPolicies.h>
#endif

#define IMAGECLASS GraphDrawImg
#define IMAGEFILE <GraphDraw/GraphDraw.iml>
#include <Draw/iml_header.h>


#include <UndoStack/UndoStack.h>

#include "logging.h"

//#define GD_DEPRECATED(MSG) [[deprecated(MSG)]]
#define GD_DEPRECATED(MSG)

namespace Upp {

namespace GraphDraw_ns
{
	Size GetSmartTextSize(const char *text, const Font scaledFont, int scale=1, int cx=INT_MAX);
	int GetSmartTextHeight(const char *s, int cx, const Font font, int scale=1);
	void DrawSmartText(Draw& draw, int x, int y, int cx, const char *text, const Font scaledFont, Color ink, int scale);
};

#define VALIDATE_IMG(img) \
	{\
		int pix=0;\
		for(const RGBA *s = img.begin(); s != img.End(); ++s, ++pix) {\
			if ( !(s->r <= s->a && s->g <= s->a && s->b <= s->a )) {\
				RLOG("PIXEL [" << pix << "/" << img.GetLength() << "] *s =" << *s << "    " <<  IML_NAME::GetId(c));\
			}\
		}\
	}

#define VALIDATE_IML(IML_NAME) \
	for (int c=0; c<IML_NAME::GetCount(); ++c)	{\
		Image img = IML_NAME::Get(c);\
		int pix=0;\
		for(const RGBA *s = img.begin(); s != img.End(); ++s, ++pix) {\
			if ( !(s->r <= s->a && s->g <= s->a && s->b <= s->a )) {\
				RLOG("PIXEL [" << pix << "/" << img.GetLength() << "] *s =" << *s << "    " <<  IML_NAME::GetId(c));\
			}\
		}\
	}




#include "UpdateCounter.h"
#include "GraphDrawTypes.h"
#include "CoordinateConverter.h"
#include "GraphFunctions.h"
#include "GraphSeries.h"
#include "GraphSeriesGroup.h"
#include "GridStepManager.h"
#include "StdGraphElements.h"
#include "GridAxisDraw.h"
#include "GraphDrawBase.h"
#include "GraphDrawMixinLayers.h"




namespace GraphDraw_ns
{
	struct GraphDrawDefaultTypes {
			typedef GraphDraw_ns::CoordinateConverter          X1_TypeCoordConverter;
			typedef GraphDraw_ns::CoordinateConverter          X2_TypeCoordConverter;
			typedef GraphDraw_ns::CoordinateConverter          Y1_TypeCoordConverter;
			typedef GraphDraw_ns::CoordinateConverter          Y2_TypeCoordConverter;

			typedef GraphDraw_ns::GridAxisDraw                 X1_TypeGridAxisDraw;
			typedef GraphDraw_ns::GridAxisDraw                 X2_TypeGridAxisDraw;
			typedef GraphDraw_ns::GridAxisDraw                 Y1_TypeGridAxisDraw;
			typedef GraphDraw_ns::GridAxisDraw                 Y2_TypeGridAxisDraw;

			typedef LabelElement                               TypeLabelElement;
			typedef LegendElement                              TypeLegendElement;
			typedef BlankAreaElement                           TypeBlankElement;
			typedef MarkerElement                              TypeMarkerElement;
	};





template<class TYPES, class DERIVED>
class GD_XYLTMM_GraphDraw : public CRTP_EmptyGraphDraw< GraphDrawDefaultTypes, DERIVED >
	{
		public:
			typedef GD_XYLTMM_GraphDraw<TYPES, DERIVED> CLASSNAME;
			typedef CRTP_EmptyGraphDraw< GraphDrawDefaultTypes, DERIVED > _B;
			typedef TYPES Types;
	
			typedef typename Types::X1_TypeCoordConverter TypeCoordConverterX1;
			typedef typename Types::X1_TypeGridAxisDraw   TypeGridAxisX1;
			typedef typename Types::TypeLabelElement      TypeLabelX1;
			typedef typename Types::Y1_TypeCoordConverter TypeCoordConverterY1;
			typedef typename Types::Y1_TypeGridAxisDraw   TypeGridAxisY1;
			typedef typename Types::TypeLabelElement      TypeLabelY1;
			typedef typename Types::TypeLegendElement     TypeLegend;
			typedef typename Types::TypeLabelElement      TypeLabelTitle;
			typedef typename Types::TypeMarkerElement     TypeMarkerX1;
			typedef typename Types::TypeMarkerElement     TypeMarkerY1;
			
			struct Style : ChStyle<Style> {
				typename     _B::StyleGD             gdStyle;
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
			virtual ~GD_XYLTMM_GraphDraw() {}
			
			GD_XYLTMM_GraphDraw()
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
				
				_legend.SetElementName(t_("Graph Legend"));
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
			static const Style& StyleDefault();
			
			DERIVED& SetStyle(const Style& s) {
				_B::OverrideLocalChStyle(s);
				style = &s;
				_B::SetStyleGD(style->gdStyle);
				_x1GridDraw.          SetStyleGE(style->x1AxisStyle);
				_x1Label.             SetStyleGE(style->x1LabelStyle);
				_y1GridDraw.          SetStyleGE(style->y1AxisStyle);
				_y1Label.             SetStyleGE(style->y1LabelStyle);
				_legend.              SetStyleGE(style->legendStyle);
				_title.               SetStyleGE(style->titleStyle);
				_x1MarkerGraphElement.SetStyleGE(style->x1MarkerStyle);
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
			GD_ELEM_LAYOUTFN_AXIS   (X1, x1);
			GD_ELEM_LAYOUTFN_AXIS   (Y1, y1);
			GD_ELEM_LAYOUTFN_LABEL  (X1, x1);
			GD_ELEM_LAYOUTFN_LABEL  (Y1, y1);
			GD_ELEM_LAYOUTFN_MARKER (X1, x1);
			GD_ELEM_LAYOUTFN_MARKER (Y1, y1);

	};





	template<class TYPES, class DERIVED>
	class GD_XYY2LTMM_GraphDraw : public CRTP_EmptyGraphDraw< TYPES, DERIVED >
	{
		public:
			typedef GD_XYY2LTMM_GraphDraw< TYPES, DERIVED > CLASSNAME;
			typedef CRTP_EmptyGraphDraw< TYPES, DERIVED > _B;
			typedef GraphDrawDefaultTypes Types;
	
			typedef typename Types::TypeLabelElement      TypeLabelTitle;
			typedef typename Types::TypeLegendElement     TypeLegend;
			typedef typename Types::X1_TypeCoordConverter TypeCoordConverterX1;
			typedef typename Types::X1_TypeGridAxisDraw   TypeGridAxisX1;
			typedef typename Types::TypeLabelElement      TypeLabelX1;
			typedef typename Types::TypeMarkerElement     TypeMarkerX1;
			typedef typename Types::Y1_TypeCoordConverter TypeCoordConverterY1;
			typedef typename Types::Y1_TypeGridAxisDraw   TypeGridAxisY1;
			typedef typename Types::TypeLabelElement      TypeLabelY1;
			typedef typename Types::TypeMarkerElement     TypeMarkerY1;
			typedef typename Types::Y2_TypeCoordConverter TypeCoordConverterY2;
			typedef typename Types::Y2_TypeGridAxisDraw   TypeGridAxisY2;
			typedef typename Types::TypeLabelElement      TypeLabelY2;
			typedef typename Types::TypeMarkerElement     TypeMarkerY2;
			
			struct Style : ChStyle<Style> {
				typename     _B::StyleGD             gdStyle;
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
				_x1Converter.UpdateGraphSize( x0, x1 );
				_y1Converter.UpdateGraphSize( y0, y1 );
				_y2Converter.UpdateGraphSize( y20, y21 );
				_B::updateSizes();
				return *static_cast<DERIVED*>(this);
			}

		public:
			virtual ~GD_XYY2LTMM_GraphDraw() {}
			
			GD_XYY2LTMM_GraphDraw()
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

				_B::AddYConverter(&_y2Converter);
				_B::AddRightElement(_y2GridDraw, 20);
				_B::AddRightElement(30, _y2Label, 25);
				_y2GridDraw.SetElementName( t_("Y2 Axis grid") );
				_y2GridDraw.SetElementWidth(40);
				_y2Label.SetElementName( t_("Y2 Axis label") );
				_y2Label.SetLabel("Y2 Axis label");
				
				_legend.SetElementName(t_("Graph Legend"));
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
			GD_ELEM_LAYOUTFN_AXIS   (X1, x1);
			GD_ELEM_LAYOUTFN_LABEL  (X1, x1);
			GD_ELEM_LAYOUTFN_MARKER (X1, x1);
			GD_ELEM_LAYOUTFN_AXIS   (Y1, y1);
			GD_ELEM_LAYOUTFN_LABEL  (Y1, y1);
			GD_ELEM_LAYOUTFN_MARKER (Y1, y1);
			GD_ELEM_LAYOUTFN_AXIS   (Y2, y2);
			GD_ELEM_LAYOUTFN_LABEL  (Y2, y2);
			GD_ELEM_LAYOUTFN_MARKER (Y2, y2);

	};
}; // namespace GraphDraw

class XYLTMM_GraphDraw : public GraphDraw_ns::GD_XYLTMM_GraphDraw< GraphDraw_ns::GraphDrawDefaultTypes, XYLTMM_GraphDraw >
{
	public:
		typedef XYLTMM_GraphDraw  CLASSNAME;
		typedef GraphDraw_ns::GD_XYLTMM_GraphDraw< GraphDraw_ns::GraphDrawDefaultTypes, XYLTMM_GraphDraw > _B;

		XYLTMM_GraphDraw() { _B::SetStyle( StyleDefault() ); }
		virtual ~XYLTMM_GraphDraw() {}
	
		static const Style& StyleDefault();
};


class XYY2LTMM_GraphDraw : public GraphDraw_ns::GD_XYY2LTMM_GraphDraw< GraphDraw_ns::GraphDrawDefaultTypes, XYY2LTMM_GraphDraw >
{
	public:
		typedef XYY2LTMM_GraphDraw  CLASSNAME;
		typedef GraphDraw_ns::GD_XYY2LTMM_GraphDraw< GraphDraw_ns::GraphDrawDefaultTypes, XYY2LTMM_GraphDraw > _B;

		XYY2LTMM_GraphDraw() { _B::SetStyle( StyleDefault() ); }
		virtual ~XYY2LTMM_GraphDraw() {}
	
		static const Style& StyleDefault();
};


}

#endif
