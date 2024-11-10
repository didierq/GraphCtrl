#ifndef _GraphCtrl_StdElementPropertiesDialogs_h_
#define _GraphCtrl_StdElementPropertiesDialogs_h_




template <class ELEMENTDRAW, class STYL>
class BlankAreaPropertiesDlg : public WithBlankAreaLayout<GEPropertiesDlgInterface> {
	public:
	typedef BlankAreaPropertiesDlg<ELEMENTDRAW, STYL>  CLASSNAME;
	typedef WithBlankAreaLayout<GEPropertiesDlgInterface>     _B;
	
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
class LabelPropertiesDlg : public WithLabelPropertiesDlgLayout<GEPropertiesDlgInterface > {
	public:
	CtrlRetriever r2;
	
	public:
	typedef LabelPropertiesDlg<LABELDRAW, STYL>  CLASSNAME;
	typedef WithLabelPropertiesDlgLayout<GEPropertiesDlgInterface > _B;
	
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
class MarkerPropertiesDlg : public WithMarkerPropertiesDlgLayout<GEPropertiesDlgInterface> {
	public:
		CtrlRetriever r2;

	public:
		typedef MarkerPropertiesDlg CLASSNAME;
		typedef WithMarkerPropertiesDlgLayout<GEPropertiesDlgInterface > _B;

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
class GridAxisPropertiesDlg : public WithGenericGridAxisPropertiesLayout< GEPropertiesDlgInterface >
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
	typedef WithGenericGridAxisPropertiesLayout<GEPropertiesDlgInterface > _B;
	

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
class LegendPropertiesDlg : public WithSeriesLegendLayout<GEPropertiesDlgInterface> {
	private:
		GraphSeriesDecoratorVector* series;
		CtrlRetriever r2;
		
	public:
	typedef LegendPropertiesDlg<LEGENDDRAW, STYL>  CLASSNAME;
	typedef WithSeriesLegendLayout<GEPropertiesDlgInterface>     _B;
	
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
