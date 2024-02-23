#ifndef _GraphDraw_GraphDrawMixinLayers_h_
#define _GraphDraw_GraphDrawMixinLayers_h_


namespace GraphDraw_ns
{

#define GD_LAYOUTFN_BASE \
	CLASSNAME& SetPlotBackgroundStyle(const Value& v) { _B::template GetLocalChStyle<Style>().gdStyle.plotBckgndStyle = v; _B::_CtrlBackgroundImage.Clear(); return *this; }\
	CLASSNAME& SetCtrlBackgroundStyle(const Value& v) { _B::template GetLocalChStyle<Style>().gdStyle.ctrlBckgndStyle = v; _B::_CtrlBackgroundImage.Clear(); return *this; }\
	CLASSNAME& SetRectSelectStyle(Value v)     { _B::template GetLocalChStyle<Style>().gdStyle.rectSelectStyle = v;                                   return *this; }
	
		


#define GD_ELEM_FN_AXIS( XYZ, xyz) \
	COMBINE(TypeCoordConverter, XYZ)& COMBINE(GetCoordConverter, XYZ)()      { return COMBINE3(_, xyz, Converter);}\
	COMBINE(TypeGridAxis, XYZ)& COMBINE3(GetElement, XYZ, GridAxisDraw)()    { return COMBINE3(_, xyz, GridDraw); }\
	DERIVED& COMBINE3(Hide, XYZ, Axis) (bool v=true)                         { COMBINE3(_, xyz, GridDraw).Hide(v);                   return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Show, XYZ, Axis) (bool v=true)                         { COMBINE3(_, xyz, GridDraw).Hide(!v);                  return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Set, XYZ, AxisRectWidth)(int v)                        { COMBINE3(_, xyz, GridDraw).SetElementWidth(v);        return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Set, XYZ, ScaleType)(int v)                            { COMBINE3(_, xyz, Converter).SetScaleType(v);          return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Set, XYZ, AxisFormatType)(AxisTextFormat v)            { COMBINE3(_, xyz, GridDraw).setAxisTextFormat(v);      return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Set, XYZ, Min)(double v)                               { COMBINE3(_, xyz, Converter).SetGraphMin(v);           return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Set, XYZ, Max)(double v)                               { COMBINE3(_, xyz, Converter).SetGraphMax(v);           return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Set, XYZ, MinRangeLimit)(double v)                     { COMBINE3(_, xyz, Converter).setGraphMinRangeLimit(v); return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Set, XYZ, MaxRangeLimit)(double v)                     { COMBINE3(_, xyz, Converter).setGraphMaxRangeLimit(v); return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Invert, XYZ, Axis)(bool v=true)                        { COMBINE3(_, xyz, GridDraw).SetAxisInverted(v);        return *static_cast<DERIVED*>(this); }\
	TypeGraphCoord COMBINE3(Get, XYZ, Min)()                                 { return ( COMBINE3(_, xyz, Converter).getGraphMin()); }\
	TypeGraphCoord COMBINE3(Get, XYZ, Max)()                                 { return ( COMBINE3(_, xyz, Converter).getGraphMax()); }\
	Value COMBINE3(Get, XYZ, MinRangeLimit)()                                { return ( COMBINE3(_, xyz, Converter).getGraphMinRangeLimit()); }\
	Value COMBINE3(Get, XYZ, MaxRangeLimit)()                                { return ( COMBINE3(_, xyz, Converter).getGraphMaxRangeLimit()); }

#define GD_ELEM_LAYOUTFN_AXIS( XYZ, xyz) \
	CLASSNAME& COMBINE3(Set, XYZ, AxisBackGroundStyle)(const Value& v)       { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).geBase.lmntBackgnd  =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, GridColor    )(const Color v)              { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gridColor    =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisGridColor)(const Color v)              { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gridColor    =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, GridThickness)(const int v)                { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gridThickness=v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, GridDash     )(const String& v)            { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gridDash     =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisWidth    )(int v)                      { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).axisWidth    =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisColor    )(const Color v)              { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).axisColor    =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisTextColor)(const Color v)              { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).axisTextColor=v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisTextFont )(const Font v)               { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).axisTextFont =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisTickColor)(const Color v)              { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).axisTickColor=v; return *this; }

#define GC_ELEM_LAYOUTFN_AXIS( XYZ, xyz) \
	CLASSNAME& COMBINE3(Set, XYZ, AxisBackGroundStyle)(const Value& v)       { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gdStyle.geBase.lmntBackgnd  =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, GridColor    )(const Color v)              { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gdStyle.gridColor    =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisGridColor)(const Color v)              { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gdStyle.gridColor    =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, GridThickness)(const int v)                { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gdStyle.gridThickness=v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, GridDash     )(const String& v)            { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gdStyle.gridDash     =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisWidth    )(int v)                      { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gdStyle.axisWidth    =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisColor    )(const Color v)              { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gdStyle.axisColor    =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisTextColor)(const Color v)              { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gdStyle.axisTextColor=v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisTextFont )(const Font v)               { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gdStyle.axisTextFont =v; return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, AxisTickColor)(const Color v)              { _B::template GetLocalChStyle<Style>().COMBINE(xyz, AxisStyle ).gdStyle.axisTickColor=v; return *this; }


#define GD_ELEM_FN_LABEL( XYZ, xyz) \
	COMBINE(TypeLabel, XYZ)& COMBINE3(GetElement, XYZ, Label)()   { return COMBINE3(_, xyz, Label); }\
	DERIVED& COMBINE3(Hide, XYZ, Label)(bool v=true)              { COMBINE3(_, xyz, Label).Hide(v);             return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Show, XYZ, Label)(bool v=true)              { COMBINE3(_, xyz, Label).Hide(!v);            return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Set,  XYZ, LabelWidth)(int v)               { COMBINE3(_, xyz, Label).SetElementWidth(v);  return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Set,  XYZ, Label)(const String& v)          { COMBINE3(_, xyz, Label).SetLabel(v);         return *static_cast<DERIVED*>(this); }

#define GD_ELEM_LAYOUTFN_LABEL( XYZ, xyz) \
	CLASSNAME& COMBINE3(Set, XYZ, LabelBackGroundStyle)(const Value& v) { _B::template GetLocalChStyle<Style>().COMBINE(xyz, LabelStyle ).geBase.lmntBackgnd=v;  return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, LabelFont    )(const Font v)          { _B::template GetLocalChStyle<Style>().COMBINE(xyz, LabelStyle ).labelFont  =v;  return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, LabelColor   )(const Color v)         { _B::template GetLocalChStyle<Style>().COMBINE(xyz, LabelStyle ).labelColor =v;  return *this; }




#define GD_ELEM_FN_TITLE \
	TypeLabelTitle& GetElementTitle()                   { return _title; }\
	DERIVED& HideTitle(bool v=true)                     { _title.Hide(v);              return *static_cast<DERIVED*>(this); }\
	DERIVED& SetTitleWidth(int v)                       { _title.SetElementWidth(v);   return *static_cast<DERIVED*>(this); }\
	DERIVED& SetTitle(const String& v)                  { _title.SetLabel(v);          return *static_cast<DERIVED*>(this); }\
	DERIVED& SetTitlePosition(const ElementPosition v)  { _title.SetElementPos(v);     return *static_cast<DERIVED*>(this); }

#define GD_ELEM_LAYOUTFN_TITLE \
	CLASSNAME& SetTitleBackGroundStyle(const Value& v)  { _B::template GetLocalChStyle<Style>().titleStyle.geBase.lmntBackgnd=v;  return *this; }\
	CLASSNAME& SetTitleFont  (const Font v)             { _B::template GetLocalChStyle<Style>().titleStyle.labelFont  =v;  return *this; }\
	CLASSNAME& SetTitleColor (const Color v)            { _B::template GetLocalChStyle<Style>().titleStyle.labelColor =v;  return *this; }




#define GD_ELEM_FN_LEGEND \
	TypeLegend& GetElementLegend()                      { return _legend; }\
	DERIVED& HideLegend(bool v=true)                    { _legend.Hide(v);  return *static_cast<DERIVED*>(this); }\
	DERIVED& ShowLegend(bool v=true)                    { _legend.Hide(!v); return *static_cast<DERIVED*>(this); }\
	DERIVED& SetLegendPosition(const ElementPosition v) { _legend.SetElementPos(v); return *static_cast<DERIVED*>(this); }\
	DERIVED& SetLegendWidth(int v)                      { _legend.SetElementWidth(v); return *static_cast<DERIVED*>(this); }\
	DERIVED& SetLegendXSize(int v)                      { RectScreen r = _legend.GetFloatFrame();r.right = r.left+v; _legend.SetFloatFrame(r);               return *static_cast<DERIVED*>(this); }\
	DERIVED& SetLegendYSize(int v)                      { RectScreen r = _legend.GetFloatFrame();r.bottom = r.top+v; _legend.SetFloatFrame(r);               return *static_cast<DERIVED*>(this); }\
	DERIVED& SetLegendXPos(int v)                       { RectScreen r = _legend.GetFloatFrame();r.right = v+r.Width(); r.left=v; _legend.SetFloatFrame(r);  return *static_cast<DERIVED*>(this); }\
	DERIVED& SetLegendYPos(int v)                       { RectScreen r = _legend.GetFloatFrame();r.bottom = v+r.Height(); r.top=v; _legend.SetFloatFrame(r); return *static_cast<DERIVED*>(this); }

#define GD_ELEM_LAYOUTFN_LEGEND \
	CLASSNAME& SetLegendBackGroundStyle(const Value& v)      { _B::template GetLocalChStyle<Style>().legendStyle.geBase.lmntBackgnd=v;      return *this; }\
	CLASSNAME& SetLegendFloatBackGroundStyle(const Value& v) { _B::template GetLocalChStyle<Style>().legendStyle.lgdFloatBackgnd=v;  return *this; }\
	CLASSNAME& SetLegendTxtColor(const Color v)              { _B::template GetLocalChStyle<Style>().legendStyle.lgdTxtColor=v;      return *this; }\
	CLASSNAME& SetLegendFont(const Font v)                   { _B::template GetLocalChStyle<Style>().legendStyle.lgdFont=v;          return *this; }
	
	
	



#define GD_ELEM_FN_MARKER( XYZ, xyz) \
	COMBINE(TypeMarker, XYZ)& COMBINE3(GetElement, XYZ, Markers)()         { return COMBINE3(_, xyz, MarkerGraphElement); }\
	DERIVED& COMBINE3(Hide, XYZ, Markers)(bool v=true)                     { COMBINE3(_, xyz, MarkerGraphElement).Hide(v);             return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Show, XYZ, Markers)(bool v=true)                     { COMBINE3(_, xyz, MarkerGraphElement).Hide(!v);            return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Set,  XYZ, MarkerWidth)(int v)                       { COMBINE3(_, xyz, MarkerGraphElement).SetElementWidth(v);  return *static_cast<DERIVED*>(this); }\
	DERIVED& COMBINE3(Set,  XYZ, MarkerPosition)(const ElementPosition v)  { COMBINE3(_, xyz, MarkerGraphElement).SetElementPos(v);    return *static_cast<DERIVED*>(this); }


#define GD_ELEM_LAYOUTFN_MARKER( XYZ, xyz) \
	CLASSNAME& COMBINE3(Set, XYZ, MarkerBackgroundStyle )(const Value& v)  { _B::template GetLocalChStyle<Style>().COMBINE(xyz, MarkerStyle ).geBase.lmntBackgnd  =v;  return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, MarkerLineColor )(const Color v)         { _B::template GetLocalChStyle<Style>().COMBINE(xyz, MarkerStyle ).mrkLineColor =v;  return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, MarkerTickColor )(const Color v)         { _B::template GetLocalChStyle<Style>().COMBINE(xyz, MarkerStyle ).mrkTickColor =v;  return *this; }\
	CLASSNAME& COMBINE3(Set, XYZ, MarkerLineWidth )(int v)                 { _B::template GetLocalChStyle<Style>().COMBINE(xyz, MarkerStyle ).mrkLineWidth =v;  return *this; }

	// ==================================================================================================================================
	// ==================================================================================================================================

}; // namespace GraphDraw_ns



#endif
