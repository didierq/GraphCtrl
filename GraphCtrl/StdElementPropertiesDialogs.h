#ifndef _GraphCtrl_StdElementPropertiesDialogs_h_
#define _GraphCtrl_StdElementPropertiesDialogs_h_


//class Ctrl;



template <class ELEMENT, class STYL>
class ElementCommonPropertiesDlg : public WithElementBaseLayout<ElementPropertiesDlgInterface> {
	public:
	CtrlRetriever r1;
	ELEMENT*      elem;
	int           pos;
	int           elementWidth;
	bool          hide;
	int           stackPrio;

	public:
	typedef ElementCommonPropertiesDlg<ELEMENT, STYL>  CLASSNAME;
	typedef WithElementBaseLayout<ElementPropertiesDlgInterface> _B;

	
	ElementCommonPropertiesDlg() : elem(nullptr), pos(100) {
//		CtrlLayoutOKCancel(*this, "");
		SetLayout_ElementBaseLayout(*this, true);
		 Size sz = _B::GetLayoutSize();
		 _B::SetMinSize(sz);
		 _B::SetRect(sz);
	}
	virtual ~ElementCommonPropertiesDlg() {}

	
	void InitDlg(ELEMENT& element, STYL* styl=nullptr) {
		//_B::Title(element.GetElementName());
		elem = &element;
		bPosition.SetVertical();
		bPosition.Add(FLOAT_OVER_GRAPH, t_("FLOAT") );
		bPosition.Add(TOP_OF_GRAPH, t_("TOP") );
		bPosition.Add(BOTTOM_OF_GRAPH, t_("BOTTOM") );
		bPosition.Add(LEFT_OF_GRAPH, t_("LEFT") );
		bPosition.Add(RIGHT_OF_GRAPH, t_("RIGHT") );

		for (int c=0; c<bPosition.GetCases().GetCount(); ++c) {
			 const Switch::Case& caseData = bPosition.GetCases()[c];
			if ((elem->GetAllowedPosMask() & caseData.value.To<int>()) == 0 ) bPosition.DisableValue(caseData.value);
		}

		pos = elem->GetElementPos();
		elementWidth = elem->GetElementWidth();
		hide = elem->IsHidden();
		stackPrio = elem->GetStackingPriority();

		r1( bWidth, elementWidth)
		  ( bHide, hide)
		  ( bStackingPrio, stackPrio)
		  ( bPosition, pos )
		  ;
	}
	
	virtual void Retrieve() {
		r1.Retrieve();
		elem->SetElementPos(static_cast<ElementPosition>(pos));
		elem->SetElementWidth(elementWidth);
		elem->Hide(hide);
		elem->SetStackingPriority(stackPrio);
		elem->_parent->RefreshFromChild( REFRESH_FULL );
	}
};
// ============================================================================================

template <class ELEMENTDRAW, class STYL>
class BlankAreaPropertiesDlg : public WithBlankAreaLayout<ElementPropertiesDlgInterface> {
	public:
	typedef BlankAreaPropertiesDlg<ELEMENTDRAW, STYL>  CLASSNAME;
	typedef WithBlankAreaLayout<ElementPropertiesDlgInterface>     _B;
	
	BlankAreaPropertiesDlg() {
		SetLayout_BlankAreaLayout(*this, true);
		 Size sz = _B::GetLayoutSize();
		 _B::SetMinSize(sz);
		 _B::SetRect(sz);
	}
	
	virtual ~BlankAreaPropertiesDlg() {}

	void InitDlg(ELEMENTDRAW& gda, STYL* styl=nullptr) {}
	virtual void Retrieve() {}
};

// ============================================================================================

template <class LABELDRAW, class STYL>
class LabelPropertiesDlg : public WithLabelPropertiesDlgLayout<ElementPropertiesDlgInterface > {
	public:
	CtrlRetriever r2;
	
	public:
	typedef LabelPropertiesDlg<LABELDRAW, STYL>  CLASSNAME;
	typedef WithLabelPropertiesDlgLayout<ElementPropertiesDlgInterface > _B;
	
	LabelPropertiesDlg() {
		SetLayout_LabelPropertiesDlgLayout(*this, true);
		 Size sz = _B::GetLayoutSize();
		 _B::SetMinSize(sz);
		 _B::SetRect(sz);
	}
	
	virtual ~LabelPropertiesDlg() {}

	void InitDlg(LABELDRAW& gda, STYL* styl=nullptr) {
		if (styl) {
			r2( _B::textColor, styl->labelColor)
			  ( _B::textFont,  styl->labelFont)
			  ;
		}
		r2 ( _B::labelText, gda._label);

		labelBox.SetLabel( gda.GetElementName() );
	}
		
	virtual void Retrieve() {
		r2.Retrieve();
	}
};

// ============================================================================================

template <class MARKERDRAW, class STYL>
class MarkerPropertiesDlg : public WithMarkerPropertiesDlgLayout<ElementPropertiesDlgInterface> {
	public:
		CtrlRetriever r2;

	public:
		typedef MarkerPropertiesDlg CLASSNAME;
		typedef WithMarkerPropertiesDlgLayout<ElementPropertiesDlgInterface > _B;

		MarkerPropertiesDlg() {
			SetLayout_MarkerPropertiesDlgLayout(*this, true);
			 Size sz = _B::GetLayoutSize();
			 _B::SetMinSize(sz);
			 _B::SetRect(sz);
		}

	virtual ~MarkerPropertiesDlg() {}
	
	void InitDlg(MARKERDRAW& gda, STYL* styl=nullptr) {
		if (styl) {
			r2( _B::lineColor, styl->mrkLineColor)
//			  ( _B::lineDash,  styl->mrkLineDash)
			  ( _B::lineWidth, styl->mrkLineWidth)
			  ( _B::tickColor, styl->mrkTickColor)
			  ;
		}
	}
		
	virtual void Retrieve() {
		r2.Retrieve();
	}
	
};


// ============================================================================================

template <class GRIDAXISDRAW, class STYL>
class GridAxisPropertiesDlg : public WithGenericGridAxisPropertiesLayout< ElementPropertiesDlgInterface >
{
	public:
	int iscaleType;
	CoordinateConverter* converter;
	GridAxisDraw* gridAxisDraw;
	bool invertAxis;
	CtrlRetriever r2;
	double gMin;
	double gMax;
	
	public:
	typedef GridAxisPropertiesDlg<GRIDAXISDRAW, STYL>  CLASSNAME;
	typedef WithGenericGridAxisPropertiesLayout<ElementPropertiesDlgInterface > _B;
	

	GridAxisPropertiesDlg() : converter(nullptr), gridAxisDraw(nullptr)  {
		SetLayout_GenericGridAxisPropertiesLayout(*this, true);
		 Size sz = _B::GetLayoutSize();
		 _B::SetMinSize(sz);
		 _B::SetRect(sz);
		 _B::scaleType.SetVertical();
		 _B::scaleFormat.SetVertical();
		 _B::max << THISBACK(WhenMinMaxChange);
		 _B::min << THISBACK(WhenMinMaxChange);
	}
	
	virtual ~GridAxisPropertiesDlg() {}

	void WhenMinMaxChange() {
		_B::range = _B::max - _B::min;
	}

	void InitDlg(GRIDAXISDRAW& gda, CoordinateConverter& conv, STYL* styl=nullptr) {
		converter = &conv;
		gridAxisDraw = &gda;
		gMin = converter->getGraphMin();
		gMax = converter->getGraphMax();
		iscaleType = converter->GetScaleType();
		invertAxis = gridAxisDraw->IsAxisInverted();
		

		_B::scaleType.Add(CoordinateConverter::AXIS_SCALE_STD,   t_("Std") );
		_B::scaleType.Add(CoordinateConverter::AXIS_SCALE_LOG,   t_("Log") );
		_B::scaleType.Add(CoordinateConverter::AXIS_SCALE_POW10, t_("Pow10") );
		if ( gMin <= 0) {
			_B::scaleType.DisableValue( CoordinateConverter::AXIS_SCALE_LOG);
		}
		
		if (styl) {
			r2( _B::axisLineColor,        styl->gdStyle.axisColor)
			  ( _B::axisTextColor,        styl->gdStyle.axisTextColor)
			  ( _B::axisTickColor,        styl->gdStyle.axisTickColor)
			  ( _B::axisLineThickness,    styl->gdStyle.axisWidth)
			  ( _B::gridColor,            styl->gdStyle.gridColor)
			  ( _B::gridLineThickness,    styl->gdStyle.gridThickness)
			  ( _B::gridLineDash,         styl->gdStyle.gridDash)
			  ;
		}
		r2   ( _B::min, gMin)
			  ( _B::max, gMax)
			  ( _B::scaleType, iscaleType)
			  ( _B::axisInvert, invertAxis)
			  ;

		  WhenMinMaxChange();
	}
		
	virtual void Retrieve() {
		r2.Retrieve();
		converter->SetScaleType(iscaleType);
		gridAxisDraw->SetAxisInverted(invertAxis);
		converter->UpdateGraphSize(gMin, gMax);
	}
};


// ============================================================================================

template <class LEGENDDRAW, class STYL>
class LegendPropertiesDlg : public WithSeriesLegendLayout<ElementPropertiesDlgInterface> {
	private:
		GraphSeriesDecoratorVector* series;
		CtrlRetriever r2;
		
	public:
	typedef LegendPropertiesDlg<LEGENDDRAW, STYL>  CLASSNAME;
	typedef WithSeriesLegendLayout<ElementPropertiesDlgInterface>     _B;
	
	LegendPropertiesDlg() : series(0) {
		SetLayout_SeriesLegendLayout(*this, true);
		 Size sz = _B::GetLayoutSize();
		 _B::SetMinSize(sz);
		 _B::SetRect(sz);
	}
	
	virtual ~LegendPropertiesDlg() {}

	void InitDlg(LEGENDDRAW& gda, GraphSeriesDecoratorVector& s, STYL* styl=nullptr) {
		series = &s;
		
		if (styl) {
			r2( _B::textFont,        styl->lgdFont)
			  ( _B::textColor,   styl->lgdTxtColor)
			  ;
		}
	}
	virtual void Retrieve() {
		r2.Retrieve();
	}
};

// ============================================================================================


#endif
