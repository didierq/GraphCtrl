#ifndef _GraphCtrl_StdElementCtrls_h_
#define _GraphCtrl_StdElementCtrls_h_


// ============================
//    GriDAxis Ctrl   CLASS
// ============================
struct StdGridAxisDrawECtrl_GEStyle {
	struct StyleGE : ChStyle<StyleGE> {
		GridAxisDraw::StyleGE gdStyle;
		Value vSelectStyle;
		Value vAxisSelectStyle;
		Value hSelectStyle;
		Value hAxisSelectStyle;

		StyleGE& operator=(const GridAxisDraw::StyleGE& gad) {
			gdStyle = gad;
			return *this;
		}
	};

	static const StyleGE& StyleGEDefault();  //X, Y
	static const StyleGE& StyleGEDefault2(); // X2, Y2, X3, Y3, ...
};


#define GD_LAYDESIGN_TStdGridAxisECtrl(CLASS, STYL) \
	CLASS& SetVSelectStyle(Value p)     { STYL.vSelectStyle = p; return *this; } \
	CLASS& SetVAxisSelectStyle(Value p) { STYL.vAxisSelectStyle = p; return *this; }\
	CLASS& SetHSelectStyle(Value p)     { STYL.hSelectStyle = p; return *this; }\
	CLASS& SetHAxisSelectStyle(Value p) { STYL.hAxisSelectStyle = p; return *this; }

template <class BASE_GRIDAXISDRAW>
class TStdGridAxisECtrl : public GraphElementCtrl_Base<BASE_GRIDAXISDRAW >
{
	public:
		typedef TStdGridAxisECtrl<BASE_GRIDAXISDRAW>       CLASSNAME;
		typedef GraphElementCtrl_Base<BASE_GRIDAXISDRAW > _B;
	
		typedef StdGridAxisDrawECtrl_GEStyle::StyleGE StyleGE;

		void SetStyleGE(const StyleGE& s) {
			_B::SetStyleGE(s.gdStyle);
			styleEC = &s;
		}
		
		static const StyleGE& StyleGEDefault()  { return StdGridAxisDrawECtrl_GEStyle::StyleGEDefault(); }
		static const StyleGE& StyleGEDefault2() { return StdGridAxisDrawECtrl_GEStyle::StyleGEDefault2(); }

	protected:
		const StyleGE* styleEC;

	private:
		PointScreen prevMousePoint;
		PointScreen selectOriginPoint, selectEndPoint;
		RectScreen selectRect;
		bool useLocalSelectLoop;
		Value currSelectStyle;
		
		UpdateCounter<CoordinateConverter> linkStatusCounter;
		typedef Index<CLASSNAME*> LinkedAxisList;
		LinkedAxisList linkedAxis;
	
		void _updateLinkedGraphs() {
			if (linkedAxis.GetCount() == 0) return;
			TypeGraphCoord min = _B::GetCoordConverter().getGraphMin();
			TypeGraphCoord max = _B::GetCoordConverter().getGraphMax();
			for (int c=(linkedAxis.GetCount()-1); c>=0; --c) {
				if ( linkedAxis[c]->linkStatusCounter != linkStatusCounter) {
					linkedAxis[c]->linkStatusCounter = linkStatusCounter;
					linkedAxis[c]->GetCoordConverter().UpdateGraphSize(min, max);
					linkedAxis[c]->_parent->RefreshFromChild( GraphDraw_ns::REFRESH_FAST );
				}
			}
		}
	
		void updateLinkedGraphs() {
			_B::GetCoordConverter().linkStatusCounter.Inc();
			_B::_parent->RequestLinksUpdate( _B::GetCoordConverter() );
		}
	
		void onAxisRangeUpdated() {
			whenRange( _B::GetCoordConverter().getGraphMin(), _B::GetCoordConverter().getGraphMax() );
			updateLinkedGraphs();
		}
		
	public:
		template<class COORDCONV>
		TStdGridAxisECtrl( COORDCONV& conv)
		: _B(conv)
		, useLocalSelectLoop(true)
		{
			SetStyleGE(StyleGEDefault());
			const StyleGE** pStyleEC = &styleEC;
			_B::openPropertiesDlgCB = [this, pStyleEC]() ->void {	_B::TOpenPropertiesDlg(*this, pStyleEC); };
			_B::makePropertiesCtrl = [=](Value& v) ->ElementPropertiesDlgInterface* { return _B::template TMakePropertiesCtrl<CLASSNAME>(v); };
			makeGEEditorCB = GetDefaultMakeEditorCB();
			currSelectStyle = Null;
		}
	
		Callback2<TypeGraphCoord, TypeGraphCoord>  whileScroll;
		Callback2<TypeGraphCoord, TypeGraphCoord>  whenRange;
	
	private:
		TStdGridAxisECtrl( TStdGridAxisECtrl& p)
		: _B(p)
		, useLocalSelectLoop(p.useLocalSelectLoop)
		{}
		
		
	public:
		virtual ~TStdGridAxisECtrl() {}


	public:
		typedef Function< ElementPropertiesDlgInterface* (CLASSNAME& , typename CLASSNAME::StyleGE&) > MakeGEEditorCB;
		static void SetDefaultMakeEditorFct(MakeGEEditorCB f) { GetDefaultMakeEditorCB() = f; }
		void SetMakeGEEditorCB(MakeGEEditorCB f) { makeGEEditorCB = f; }
		static MakeGEEditorCB& GetDefaultMakeEditorCB() { static MakeGEEditorCB defaultMakeEditorFct; return defaultMakeEditorFct;	}
		MakeGEEditorCB makeGEEditorCB;

	public:
		
	void ExecuteWithAxisUndo(Callback cb) {
		UndoStackData undo;
		CoordinateConverter& converter = _B::GetCoordConverter();
		undo.undoAction << converter.MakeRestoreAxisMinMaxCB();
		cb();
		undo.redoAction << converter.MakeRestoreAxisMinMaxCB();
		_B::_parent->AddUndoAction(undo);
		_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_FAST );
	}


	void FitToDataRefresh(FitToDataStrategy fitStrategy = GraphDraw_ns::ALL_SERIES) {
		_B::FitToData(fitStrategy);
		onAxisRangeUpdated();
		_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_FULL );
	}

	virtual void ContextMenu(Bar& bar) {
		//;
		bar.Add(t_("Edit properties"),     THISBACK (OpenPropertiesDlg));
		bar.Add(t_("Fit To Data"),         THISBACK1(ExecuteWithAxisUndo, THISBACK1(FitToDataRefresh, GraphDraw_ns::ALL_SERIES)) );
		bar.Add(t_("Fit To Visible Data"), THISBACK1(ExecuteWithAxisUndo, THISBACK1(FitToDataRefresh, GraphDraw_ns::VISIBLE_SERIES_ONLY)) );
	}

	void UseLocalSelectLoop(bool p = true) {
		useLocalSelectLoop = p;
	}

	void Link(CLASSNAME* gridAxisCtrl) {
		if (gridAxisCtrl == nullptr)  return;
		if (linkedAxis.Find(gridAxisCtrl) >= 0) return;
		linkedAxis.Add( gridAxisCtrl );
		gridAxisCtrl->Link(this);
	}

	void Link(CLASSNAME& gridAxisCtrl) { Link(&gridAxisCtrl); }

	bool IsLinkedTo(CLASSNAME* gridAxisCtrl) const {
		return (linkedAxis.Find(gridAxisCtrl) >= 0);
	}

	void Unlink(CLASSNAME* gridAxisCtrl) {
		if (gridAxisCtrl == nullptr)  return;
		if ( linkedAxis.Find(gridAxisCtrl) < 0) return;
		linkedAxis.RemoveKey(gridAxisCtrl);
		gridAxisCtrl->Unlink(this);
	}

	void UnLinkAll() {
		while ( linkedAxis.GetCount() > 0 ) {
			Unlink(linkedAxis[0]);
		}
	}



	virtual Image  CursorImage(PointScreen p, dword keyflags) {
		if (  TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_AXIS_ZOOM) ) {
			if (!_B::GetCoordConverter().IsAxisZoomAllowed())    return GraphCtrlImg::CROSS();
			if (_B::IsVertical() ) return GraphCtrlImg::AXIS_ZOOM_Y();
			else                   return GraphCtrlImg::AXIS_ZOOM_X();
		}
		else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_ZOOM)) {
			if (!_B::GetCoordConverter().IsAxisZoomAllowed())    return GraphCtrlImg::CROSS();
			if (_B::IsVertical() ) return GraphCtrlImg::ZOOM_Y();
			else                   return GraphCtrlImg::ZOOM_X();
		}
		else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_AXIS_SCROLL)) {
			if (!_B::GetCoordConverter().IsAxisScrollAllowed())  return GraphCtrlImg::CROSS();
			if (_B::IsVertical() ) return GraphCtrlImg::AXIS_SCROLL_Y();
			else                   return GraphCtrlImg::AXIS_SCROLL_X();
		}
		else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_SCROLL)) {
			if (!_B::GetCoordConverter().IsAxisScrollAllowed())  return GraphCtrlImg::CROSS();
			if (_B::IsVertical() ) return GraphCtrlImg::SCROLL_Y();
			else                   return GraphCtrlImg::SCROLL_X();
		}
		return GraphCtrlImg::CROSS();
	}

	virtual void MouseWheel (PointScreen p, int delta, dword keyflags) {
		CoordinateConverter& converter = _B::GetCoordConverter();
		int zdelta = 1;

		if (  TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_AXIS_ZOOM) ||  TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_ZOOM) )
		{
			if (!_B::GetCoordConverter().IsAxisZoomAllowed()) return;

			if (delta<0)  zdelta = converter.getScreenRange()*(1 -     GraphCtrl_Constants::ZOOM_STEP_FACTOR);
			else          zdelta = converter.getScreenRange()*(1 - 1.0/GraphCtrl_Constants::ZOOM_STEP_FACTOR);
			if (_B::IsHorizontal())  zdelta = -zdelta;
			zdelta = (zdelta+0.5)/2;

			UndoStackData undo;
			undo.undoAction << converter.MakeRestoreAxisMinMaxCB();
			if (  TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_AXIS_ZOOM) )
			{
				// => ZOOM on wheel (this axis only)
				converter.UpdateGraphSize( converter.toGraph( converter.getScreenMin() - zdelta ),
				                           converter.toGraph( converter.getScreenMax() + zdelta ));
			}
			else //if (  TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_ZOOM) )
			{
				// => ZOOM on wheel ( ALL CoordConverter of axis not only the current one )
				if (_B::IsVertical() ) {
					_B::_parent->ZoomY(converter.getScreenMax() + zdelta, converter.getScreenMin() - zdelta);
				} else {
					_B::_parent->ZoomX(converter.getScreenMin() - zdelta, converter.getScreenMax() + zdelta);
				}
			}
			undo.redoAction << _B::_parent->MakeRestoreGraphSizeCB();
			_B::_parent->AddUndoAction(undo);
			_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_FAST );
			onAxisRangeUpdated();
		}
		else if (  TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_AXIS_SCROLL) || TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_SCROLL) )
		{
			if (delta < 0) zdelta = -1;
			if (_B::IsHorizontal())  zdelta = -zdelta;
			zdelta *= abs(converter.getScreenRange()) * (1-GraphCtrl_Constants::ZOOM_STEP_FACTOR);

			if (!_B::GetCoordConverter().IsAxisScrollAllowed()) return;
			UndoStackData undo;
			undo.undoAction << converter.MakeRestoreAxisMinMaxCB();
			if (  TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_AXIS_SCROLL) )
			{
				// => SCROLL on wheel ( on axis )
				converter.UpdateGraphSize( converter.toGraph( converter.getScreenMin() - zdelta ),
				                           converter.toGraph( converter.getScreenMax() - zdelta ));
			}
			else  // if (  TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_SCROLL) )
			{
				// => SCROLL on wheel ( ALL vertical OR horizontal axis )
				if (_B::IsVertical() ) {
					_B::_parent->ScrollY(zdelta);
				} else {
					_B::_parent->ScrollX(zdelta);
				}
			}
			undo.redoAction << converter.MakeRestoreAxisMinMaxCB();
			_B::_parent->AddUndoAction(undo);
			_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_FAST );
			onAxisRangeUpdated();
		}
	}

	virtual void  LeftDrag(PointScreen p, dword keyflags) {
		prevMousePoint = p;
		selectOriginPoint = p-_B::GetFrame().TopLeft();
		selectEndPoint = selectOriginPoint;

		CoordinateConverter& converter = _B::GetCoordConverter();
		Ctrl* parentCtrl = _B::_parent->GetParentCtrl().template To<Ctrl*>();
		RectTracker tracker(*parentCtrl);
		tracker.Dashed().Animation();
		tracker.SetColor(Cyan()).Width(1);

		UndoStackData undo;
		undo.undoAction << _B::_parent->MakeRestoreGraphSizeCB();

		if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_AXIS_ZOOM) ) // AXIS ZOOM --ONLY THIS AXIS--
		{
			if (!_B::GetCoordConverter().IsAxisZoomAllowed()) return;
			if (_B::IsVertical() ) {
				if ( useLocalSelectLoop ) {
					currSelectStyle = styleEC->vAxisSelectStyle;
					_B::_parent->DoLocalLoop( THISBACK( _selectZoomLoop ) );
				} else {
					selectRect = tracker.Track(RectScreen(PointScreen(_B::GetFrame().TopLeft().x, p.y), Size(_B::GetFrame().GetSize().cx, 2)), ALIGN_CENTER, ALIGN_NULL ) - _B::GetFrame().TopLeft();
				}
				converter.UpdateGraphSize( converter.toGraph( selectRect.bottom ), converter.toGraph( selectRect.top ));
			} else {
				if ( useLocalSelectLoop ) {
					currSelectStyle = styleEC->hAxisSelectStyle;
					_B::_parent->DoLocalLoop( THISBACK( _selectZoomLoop ) );
				} else {
					selectRect = tracker.Track(RectScreen(PointScreen(p.x, _B::GetFrame().TopLeft().y), Size(2,_B::GetFrame().GetSize().cy)), ALIGN_NULL, ALIGN_CENTER) - _B::GetFrame().TopLeft();
				}
				converter.UpdateGraphSize( converter.toGraph( selectRect.left ), converter.toGraph( selectRect.right ));
			}
			currSelectStyle = Null;
			_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_FAST );
			
			if (p != (_B::_parent->GetParentCtrl().template To<Ctrl*>())->GetMouseViewPos()) {
				undo.redoAction << _B::_parent->MakeRestoreGraphSizeCB();
				_B::_parent->AddUndoAction(undo);
				onAxisRangeUpdated();
			}
		}
		else if (TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_ZOOM) ) // GRAPH ZOOM   // TODO_ZOOM
		{
			if (!_B::GetCoordConverter().IsAxisZoomAllowed()) return;
			if (_B::IsVertical() ) {
				if ( useLocalSelectLoop ) {
					currSelectStyle = styleEC->vSelectStyle;
					_B::_parent->DoLocalLoop( THISBACK( _selectZoomLoop ) );
				}
				else {
					selectRect = tracker.Track(RectScreen(PointScreen(_B::GetFrame().TopLeft().x, p.y), Size(_B::GetFrame().GetSize().cx, 2)), ALIGN_CENTER, ALIGN_NULL ) - _B::GetFrame().TopLeft();
				}
				_B::_parent->ZoomY( selectRect.top, selectRect.bottom );
			} else {
				if ( useLocalSelectLoop ) {
					currSelectStyle = styleEC->hSelectStyle;
					_B::_parent->DoLocalLoop( THISBACK( _selectZoomLoop ) );
				}
				else {
					selectRect = tracker.Track(RectScreen(PointScreen(p.x, _B::GetFrame().TopLeft().y), Size(2,_B::GetFrame().GetSize().cy)), ALIGN_NULL, ALIGN_CENTER) - _B::GetFrame().TopLeft();
				}
				_B::_parent->ZoomX(selectRect.left, selectRect.right );
			}
			currSelectStyle = Null;
			_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_FAST );

			if (p != (_B::_parent->GetParentCtrl().template To<Ctrl*>())->GetMouseViewPos()) {
				undo.redoAction << _B::_parent->MakeRestoreGraphSizeCB();
				_B::_parent->AddUndoAction(undo);
				onAxisRangeUpdated();
			}
		}
		else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_AXIS_SCROLL ) ) // AXIS SCROLL --ONLY THIS AXIS--
		{
			if (!_B::GetCoordConverter().IsAxisScrollAllowed()) return;
			_B::_parent->DoLocalLoop( THISBACK( _AxisScrollLoop ) );

			if (p != (_B::_parent->GetParentCtrl().template To<Ctrl*>())->GetMouseViewPos()) {
				undo.redoAction << _B::_parent->MakeRestoreGraphSizeCB();
				_B::_parent->AddUndoAction(undo);
				onAxisRangeUpdated();
			}
		}
		else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_SCROLL )) // GRAPH SCROLL
		{
			if (!_B::GetCoordConverter().IsAxisScrollAllowed()) return;
			_B::_parent->DoLocalLoop( THISBACK( _ScrollLoop ) );

			if (p != (_B::_parent->GetParentCtrl().template To<Ctrl*>())->GetMouseViewPos()) {
				undo.redoAction << _B::_parent->MakeRestoreGraphSizeCB();
				_B::_parent->AddUndoAction(undo);
				onAxisRangeUpdated();
			}
		}
	}

	private:
	virtual void PaintOnPlot_overData(Draw& dw, int otherWidth, int scale) {
		_B::PaintOnPlot_overData(dw, otherWidth, scale);
		if ( useLocalSelectLoop && !currSelectStyle.IsNull() ) {
			if (_B::IsVertical() ) {
				if (selectOriginPoint.y<=selectEndPoint.y) { selectRect = RectScreen(PointScreen(0, selectOriginPoint.y), PointScreen(otherWidth, selectEndPoint.y) );    }
				else                                       { selectRect = RectScreen(PointScreen(0, selectEndPoint.y),    PointScreen(otherWidth, selectOriginPoint.y) ); }
			} else {
				if (selectOriginPoint.x<=selectEndPoint.x) { selectRect = RectScreen(PointScreen(selectOriginPoint.x, 0), PointScreen(selectEndPoint.x, otherWidth) );    }
				else                                       { selectRect = RectScreen(PointScreen(selectEndPoint.x, 0),    PointScreen(selectOriginPoint.x, otherWidth) ); }
			}
			ChPaint(dw, selectRect, currSelectStyle);
		}
	}

	void _selectZoomLoop (PointScreen p, dword keyflags) {
		selectEndPoint = p-_B::GetFrame().TopLeft();
		_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_KEEP_DATA );
	}

	void _ScrollLoop (PointScreen p, dword keyflags) {
		if (_B::IsVertical() ) { _B::_parent->ScrollY(p.y-prevMousePoint.y); }
		else                   { _B::_parent->ScrollX(p.x-prevMousePoint.x); }
		prevMousePoint = p;
		_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_FAST );
	}

	void _AxisScrollLoop (PointScreen p, dword keyflags) {
		int delta=0;
		if (_B::IsVertical() ) { delta = p.y-prevMousePoint.y; }
		else                   { delta = p.x-prevMousePoint.x; }
		_B::_coordConverter.Scroll( delta );
		prevMousePoint = p;
		_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_FAST );
	}

	public:
	virtual void MouseMove (PointScreen p, dword keyflags) {
	}
};



// ============================
//    LegendElement Ctrl   
// ============================

template<class LEGENDDRAW>
class TStdLegendECtrl : public GraphElementCtrl_FloatMoveResize<GraphElementCtrl_Base<LEGENDDRAW > > {
	public:
		typedef TStdLegendECtrl<LEGENDDRAW>  CLASSNAME;
		typedef GraphElementCtrl_FloatMoveResize<GraphElementCtrl_Base<LEGENDDRAW > >  _B;
		TStdLegendECtrl() {
			const typename CLASSNAME::StyleGE** pStyleEC = & CLASSNAME::GetStyleGE();
			_B::openPropertiesDlgCB = [this, pStyleEC]() ->void {	_B::TOpenPropertiesDlg(*this, pStyleEC); };
			_B::makePropertiesCtrl = [=](Value& v) ->ElementPropertiesDlgInterface* { return _B::template TMakePropertiesCtrl<CLASSNAME>(v); };
			makeGEEditorCB = GetDefaultMakeEditorCB();
		}
		
		TStdLegendECtrl(TStdLegendECtrl& p) : GraphElementCtrl_FloatMoveResize<LEGENDDRAW>(p) {
			makeGEEditorCB = p.makeGEEditorCB;
		}
		virtual ~TStdLegendECtrl() {}

	public:
		typedef Function< ElementPropertiesDlgInterface* (CLASSNAME& , typename CLASSNAME::StyleGE&) > MakeGEEditorCB;
		static void SetDefaultMakeEditorFct(MakeGEEditorCB f) { GetDefaultMakeEditorCB() = f; }
		void SetMakeGEEditorCB(MakeGEEditorCB f) { makeGEEditorCB = f; }
		static MakeGEEditorCB& GetDefaultMakeEditorCB() { static MakeGEEditorCB defaultMakeEditorFct; return defaultMakeEditorFct;	}
		MakeGEEditorCB makeGEEditorCB;
		
		virtual void LeftDown(PointScreen p, dword keyflags) {
			PointScreen p2 = p - _B::_frame.TopLeft();
			if (_B::IsFloat()) p2 = p - _B::_floatFrame.TopLeft();
				
			int nbLabels = (*_B::g_series).GetCount(); //_B::seriesLabelRectVector.GetCount();
			for (int c=0; c<nbLabels; ++c) {
				GraphSerieDecorator& gsd = (*_B::g_series)[c];
				if ((gsd.IsShow()==false) || gsd.IsShowLegend() == false ) { continue; }
				if (_B::seriesLabelRectVector[c].Contains(p2)) return; // if in labelRect ==> do not call _B::LeftDown(p, keyflags);
			}
			_B::LeftDown(p, keyflags);
		}

		virtual void LeftUp(PointScreen p, dword keyflags) {
			int nbLabels = (*_B::g_series).GetCount();
			bool inLabelRect = false;
			PointScreen p2 = p - _B::_frame.TopLeft();
			if (_B::IsFloat()) { 
				p2 = p - _B::_floatFrame.TopLeft();
			}
				
			for (int c=0; c<nbLabels; ++c) {
				GraphSerieDecorator& gsd = (*_B::g_series)[c];
				if ((gsd.IsShow()==false) || gsd.IsShowLegend() == false ) { continue; }
				if (_B::seriesLabelRectVector[c].Contains(p2)) {
					gsd.SelectSerie(! gsd.IsSerieSelected() );
					inLabelRect = true;
				}
			}
			if (inLabelRect) _B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_KEEP_DATA );
			else             _B::LeftUp(p, keyflags);
		}
		
		virtual Image  CursorImage(PointScreen p, dword keyflags) {
			PointScreen p2 = p - _B::_frame.TopLeft();
			if (_B::IsFloat()) p2 = p - _B::_floatFrame.TopLeft();
				
			int nbLabels = (*_B::g_series).GetCount(); //_B::seriesLabelRectVector.GetCount();
			for (int c=0; c<nbLabels; ++c) {
				GraphSerieDecorator& gsd = (*_B::g_series)[c];
				if ((gsd.IsShow()==false) || gsd.IsShowLegend() == false ) { continue; }
				if (_B::seriesLabelRectVector[c].Contains(p2)) {
					return Image::Hand();
				}
			}
			return _B::CursorImage(p, keyflags);
		}
};


// ============================
//    Label Ctrl   CLASS
// ============================

template<class LABELDRAW>
class TStdLabelECtrl : public  GraphElementCtrl_Base< LABELDRAW > {
	public:
	typedef TStdLabelECtrl<LABELDRAW>  CLASSNAME;
	typedef GraphElementCtrl_Base< LABELDRAW > _B;
	
	TStdLabelECtrl() {
		_B::DisablePos(GraphDraw_ns::FLOAT_OVER_GRAPH);
		const typename _B::StyleGE** pStyleEC = & _B::GetStyleGE();
		_B::openPropertiesDlgCB = [this, pStyleEC]() ->void {	_B::TOpenPropertiesDlg(*this, pStyleEC); };
		_B::makePropertiesCtrl = [=](Value& v) ->ElementPropertiesDlgInterface* { return _B::template TMakePropertiesCtrl<CLASSNAME>(v); };
		makeGEEditorCB = GetDefaultMakeEditorCB();
	}

	public:
		typedef Function< ElementPropertiesDlgInterface* (CLASSNAME& , typename CLASSNAME::StyleGE&) > MakeGEEditorCB;
		static void SetDefaultMakeEditorFct(MakeGEEditorCB f) { GetDefaultMakeEditorCB() = f; }
		void SetMakeGEEditorCB(MakeGEEditorCB f) { makeGEEditorCB = f; }
		static MakeGEEditorCB& GetDefaultMakeEditorCB() { static MakeGEEditorCB defaultMakeEditorFct; return defaultMakeEditorFct; }
		MakeGEEditorCB makeGEEditorCB;
};




// ============================
//    BlankArea Ctrl   CLASS
// ============================

template<class ELEMENTDRAW>
class TStdBlankAreaECtrl : public  GraphElementCtrl_Base< ELEMENTDRAW > {
	public:
		typedef TStdBlankAreaECtrl<ELEMENTDRAW>  CLASSNAME;
		typedef GraphElementCtrl_Base< ELEMENTDRAW > _B;
	
		TStdBlankAreaECtrl() {
			//_B::openPropertiesDlgCB = THISBACK( _B::template TOpenPropertiesDlg<BlankAreaPropertiesDlg> );
			makeGEEditorCB = GetDefaultMakeEditorCB();
		}

	public:
		typedef Function< ElementPropertiesDlgInterface* (CLASSNAME& , typename CLASSNAME::StyleGE&) > MakeGEEditorCB;
		static void SetDefaultMakeEditorFct(MakeGEEditorCB f) { GetDefaultMakeEditorCB() = f; }
		void SetMakeGEEditorCB(MakeGEEditorCB f) { makeGEEditorCB = f; }
		static MakeGEEditorCB& GetDefaultMakeEditorCB() { static MakeGEEditorCB defaultMakeEditorFct; return defaultMakeEditorFct; }
		MakeGEEditorCB makeGEEditorCB;
};


// ============================
//    DynamicMArker Ctrl   CLASS
// ============================
typedef Callback3< const MarkerPosList& /*list*/, int /*markerID*/, void* /*dynMarkerCtrl*/> TypeMarkerMoveCbk;

class DynamicMarkerECtrl : public  GraphElementCtrl_Base< GraphDraw_ns::MarkerElement > {
	public:
	typedef DynamicMarkerECtrl  CLASSNAME;
	typedef GraphElementCtrl_Base< GraphDraw_ns::MarkerElement > _B;
	
	protected:
	UpdateCounter<CLASSNAME> linkStatusCounter;
	
	typedef Index<CLASSNAME*> LinkedElementsList;
	LinkedElementsList linkedElements;
	
	PointScreen prevMousePoint;
	TypeScreenCoord selectOffset;
	
	MarkerPosList::Iterator currMarkerPos; // marker selected for MOVE action
	
	GraphDraw_ns::MarkerElementData::TypeMarkerUpdateCbk _whenMarkerUpdatedFromLink;

	public:
		typedef Function< ElementPropertiesDlgInterface* (CLASSNAME& , typename CLASSNAME::StyleGE&) > MakeGEEditorCB;
		static void SetDefaultMakeEditorFct(MakeGEEditorCB f) { GetDefaultMakeEditorCB() = f; }
		void SetMakeGEEditorCB(MakeGEEditorCB f) { makeGEEditorCB = f; }
		static MakeGEEditorCB& GetDefaultMakeEditorCB() { static MakeGEEditorCB defaultMakeEditorFct; return defaultMakeEditorFct;	}
		MakeGEEditorCB makeGEEditorCB;

	public:
	TypeMarkerMoveCbk whenMarkerMove;
	TypeMarkerMoveCbk whenMarkerUpdated;
	TypeMarkerMoveCbk whenMarkerSelected;
	TypeMarkerMoveCbk whenMarkerReleased;
		

	DynamicMarkerECtrl(CoordinateConverter& coordconv)
	: _B(coordconv)
	, _whenMarkerUpdatedFromLink(THISBACK(_ProcessWhenMarkerUpdatedFromLink))
	, whenMarkerUpdated( Proxy( whenMarkerMove ) )
	{
		const typename _B::StyleGE** pStyleEC = & _B::GetStyleGE();
		_B::openPropertiesDlgCB = [this, pStyleEC]() ->void {	_B::TOpenPropertiesDlg(*this, pStyleEC); };
		_B::makePropertiesCtrl = [=](Value& v) ->ElementPropertiesDlgInterface* { return _B::template TMakePropertiesCtrl<CLASSNAME>(v); };
		makeGEEditorCB = GetDefaultMakeEditorCB();
	}

	~DynamicMarkerECtrl() {
		UnLinkAll();
	}
	
	
	private:
	virtual void ContextMenu(Bar& bar) {
		bar.Add(t_("Edit properties"),  THISBACK (OpenPropertiesDlg));
		bar.Add(t_("Reset marker positions"),    THISBACK(ResetMarkers));
	}

	void _MoveMarker (PointScreen p, dword keyflags) {
		if (keyflags & K_MOUSELEFT)
		{
			if (_B::IsVertical() ) {
				// Vertical drag
				(*currMarkerPos) =  _B::_coordConverter.toGraph(p.y+selectOffset);
			} else {
				// Horizontal drag
				(*currMarkerPos) =  _B::_coordConverter.toGraph(p.x+selectOffset);
			}
			prevMousePoint = p;
			whenMarkerMove(_B::markers, currMarkerPos->GetID(), this);
			_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_KEEP_DATA );
		}
	}
	
	void _ProcessWhenMarkerUpdatedFromLink(int markerID, void* dynMarkerCtrl) {
		DynamicMarkerECtrl* dynMarkCtrl = (DynamicMarkerECtrl*)dynMarkerCtrl;
		whenMarkerUpdated(dynMarkCtrl->markers, markerID, dynMarkerCtrl);
	}
	
	void _UpdateLinkedMarkers() {
		if ( linkedElements.IsEmpty() ) return;
		
		// Update marker directly linked
		for (int m=(_B::markers.GetCount()-1); m>=0; --m) {
			_B::markers[m].UpdateLinked( _whenMarkerUpdatedFromLink );
		}
		
		// Update marker in-directly linked
		for (int e=(linkedElements.GetCount()-1); e>=0; --e) {
			if (linkedElements[e]->linkStatusCounter != linkStatusCounter) {
				linkedElements[e]->linkStatusCounter = linkStatusCounter;
				linkedElements[e]->_UpdateLinkedMarkers();
			}
		}
	}
	
	void _RefreshLinkedMarkerElements2() {
		for (int m=(linkedElements.GetCount()-1); m>=0; --m) {
			linkedElements[m]->_parent->RefreshFromChild( GraphDraw_ns::REFRESH_KEEP_DATA );
			if (linkedElements[m]->linkStatusCounter != linkStatusCounter) {
				linkedElements[m]->linkStatusCounter = linkStatusCounter;
				linkedElements[m]->_RefreshLinkedMarkerElements2();
			}
		}
	}

	void _RefreshLinkedMarkerElements() {
		if ( linkedElements.IsEmpty() ) return;
		linkStatusCounter.Inc();
		_RefreshLinkedMarkerElements2();
	}
	
	void _CleanLinks() {
		// Remove elements that have no more linked markers
		int l = linkedElements.GetCount()-1;
		while (l>=0) {
			if ( IsLinkedTo( linkedElements[l] ) == false) {
				CLASSNAME* otherMarkerElement = linkedElements[l];
				linkedElements.Remove( l );
				otherMarkerElement->_CleanLinks();
				l = linkedElements.GetCount()-1;
			}
			else --l;
		}
	}
	
	public:
	
	void Link(CLASSNAME* dynMarker, int thisId, int otherId) {
		if (dynMarker == nullptr)  return;
		_B::markers.Get(thisId).Link(dynMarker->markers.Get(otherId));
		if (linkedElements.Find(dynMarker) >= 0) return;
		linkedElements.Add( dynMarker );
		dynMarker->Link(this, otherId, thisId);
	}
	inline void Link(CLASSNAME& dynMarker, int thisId, int otherId) { Link(&dynMarker, thisId, otherId); }
	inline void Link(int thisId, CLASSNAME* dynMarker, int otherId) { Link( dynMarker, thisId, otherId); }
	inline void Link(int thisId, CLASSNAME& dynMarker, int otherId) { Link(&dynMarker, thisId, otherId); }
	inline void Link(int thisId, CLASSNAME* dynMarker) { Link( dynMarker, thisId, thisId); }
	inline void Link(int thisId, CLASSNAME& dynMarker) { Link(&dynMarker, thisId, thisId); }

	bool IsLinkedTo(CLASSNAME* dynMarker) const {
		for (int l=(_B::markers.GetCount()-1); l>=0; --l) {
			for (int o=(dynMarker->markers.GetCount()-1); o>=0; --o) {
				if (_B::markers[l].IsLinkedTo( dynMarker->markers[o]) ) {
					return true;
				}
			}
		}
		return false;
	}

	void Unlink(CLASSNAME* otherDynMarker, int thisId, int otherId) {
		//GDLOGBLOCK("DynamicMarkerECtrl::Unlink(" << thisId << " , " << otherId << ")  REQUESTED");
		if (otherDynMarker == nullptr)  return;
		if ( linkedElements.Find(otherDynMarker) < 0) return;
		if (( _B::markers.Find(thisId) < 0 ) || (otherDynMarker->markers.Find(otherId) < 0)) return;
		//LOG("DynamicMarkerECtrl::Unlink(" << thisId << " , " << otherId << ")   removing link     count = " << linkedElements.GetCount() );
		_B::markers.Get(thisId).Unlink(otherDynMarker->markers.Get(otherId) );
		_CleanLinks();
		otherDynMarker->Unlink(this, otherId, thisId);
		//LOG("DynamicMarkerECtrl::Unlink(" << thisId << " , " << otherId << ")   links cleaned     count = " << linkedElements.GetCount() );
	}
	inline void Unlink(CLASSNAME& dynMarker, int thisId, int otherId) { Unlink(&dynMarker, thisId, otherId); }
	inline void Unlink(int thisId, CLASSNAME* dynMarker, int otherId) { Unlink( dynMarker, thisId, otherId); }
	inline void Unlink(int thisId, CLASSNAME& dynMarker, int otherId) { Unlink(&dynMarker, thisId, otherId); }
	inline void Unlink(int thisId, CLASSNAME* dynMarker) { Unlink( dynMarker, thisId, thisId); }
	inline void Unlink(int thisId, CLASSNAME& dynMarker) { Unlink(&dynMarker, thisId, thisId); }

	void UnLinkAll() {
		for (int l=(_B::markers.GetCount()-1); l>=0; --l) {
			_B::markers[l].UnlinkAll();
		}
		_CleanLinks();
	}

	void ResetMarkers() {
		MarkerPosList::Iterator iter = _B::markers.Begin();
		MarkerPosList::ConstIterator endIter = _B::markers.End();
		TypeGraphCoord step = _B::_coordConverter.getSignedGraphRange()/ (_B::markers.GetCount()+1);
		TypeGraphCoord currVal = _B::_coordConverter.getGraphMin();
		while ( iter != endIter ) {
			currVal += step;
			(*iter) = currVal;
			whenMarkerMove(_B::markers, (*iter).GetID(), this);
			++iter;
		}
		_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_KEEP_DATA );
		linkStatusCounter.Inc();
		_UpdateLinkedMarkers();
		_RefreshLinkedMarkerElements();
	}


	void SetMarkerPos(int markerID, TypeGraphCoord pos ) {
		_B::markers.Get(markerID) = pos;
		linkStatusCounter.Inc();
		_UpdateLinkedMarkers();
		_RefreshLinkedMarkerElements();
	}


	int MarkerContains(PointScreen p) const {// ============================
//    DynamicMArker Ctrl   CLASS
// ============================
typedef Callback3< const MarkerPosList& /*list*/, int /*markerID*/, void* /*dynMarkerCtrl*/> TypeMarkerMoveCbk;

		if (_B::_frame.Contains(p)) {
			MarkerPosList::ConstIterator iter = _B::markers.Begin();
			MarkerPosList::ConstIterator endIter = _B::markers.End();
	
			while ( iter != endIter ) {
				const MarkerElementData& markerData = *iter;
				if (_B::_coordConverter.IsInGraphVisibleRange(markerData)) {
					switch( _B::GetElementPos() ) {
						case GraphDraw_ns::LEFT_OF_GRAPH:
							if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(), _B::GetElementPos(), _B::GetElementWidth(), _B::_coordConverter.toScreen(markerData))) return markerData.GetID();
							break;
						case GraphDraw_ns::BOTTOM_OF_GRAPH:
							if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(), _B::GetElementPos(), _B::_coordConverter.toScreen(markerData), 0 ))                    return markerData.GetID();
							break;
						case GraphDraw_ns::TOP_OF_GRAPH:
							if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(), _B::GetElementPos(), _B::_coordConverter.toScreen(markerData), _B::GetElementWidth())) return markerData.GetID();
							break;
						case GraphDraw_ns::RIGHT_OF_GRAPH:
							if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(), _B::GetElementPos(), 0, _B::_coordConverter.toScreen(markerData)))                     return markerData.GetID();
							break;
						case GraphDraw_ns::FLOAT_OVER_GRAPH:
							break;
					}
				}
				++iter;
			}
		}
		return MarkerElementData::INVALID_MARKER_ID;
	}

	virtual void  LeftDown(PointScreen p, dword keyflags) {
		prevMousePoint = p;

		MarkerPosList::Iterator iter = _B::markers.End();
		MarkerPosList::ConstIterator endIter = _B::markers.Begin();
		while ( iter != endIter ) {
			--iter;
			MarkerElementData& markerData = *iter;
			if (_B::_coordConverter.IsInGraphVisibleRange(markerData)) {
				switch( _B::GetElementPos() ) {
					case GraphDraw_ns::LEFT_OF_GRAPH:
						if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(),  _B::GetElementPos(), _B::GetElementWidth(), _B::_coordConverter.toScreen(markerData) )) {
							currMarkerPos = iter;
							selectOffset = _B::_coordConverter.toScreen(markerData) - p.y;
							whenMarkerSelected(_B::markers, currMarkerPos->GetID(), this);
							_B::_parent->DoLocalLoop( THISBACK( _MoveMarker ) );
							whenMarkerReleased(_B::markers, currMarkerPos->GetID(), this);
							linkStatusCounter.Inc();
							_UpdateLinkedMarkers();
							_RefreshLinkedMarkerElements();
						}
						break;
					case GraphDraw_ns::BOTTOM_OF_GRAPH:
						if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(), _B::GetElementPos(), _B::_coordConverter.toScreen(markerData), 0)) {
							currMarkerPos = iter;
							selectOffset = _B::_coordConverter.toScreen(markerData) - p.x;
							whenMarkerSelected(_B::markers, currMarkerPos->GetID(), this);
							_B::_parent->DoLocalLoop( THISBACK( _MoveMarker ) );
							whenMarkerReleased(_B::markers, currMarkerPos->GetID(), this);
							linkStatusCounter.Inc();
							_UpdateLinkedMarkers();
							_RefreshLinkedMarkerElements();
						}
						break;
					case GraphDraw_ns::TOP_OF_GRAPH:
						if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(), _B::GetElementPos(),  _B::_coordConverter.toScreen(markerData), _B::GetElementWidth() )) {
							currMarkerPos = iter;
							selectOffset = _B::_coordConverter.toScreen(markerData) - p.x;
							whenMarkerSelected(_B::markers, currMarkerPos->GetID(), this);
							_B::_parent->DoLocalLoop( THISBACK( _MoveMarker ) );
							whenMarkerReleased(_B::markers, currMarkerPos->GetID(), this);
							linkStatusCounter.Inc();
							_UpdateLinkedMarkers();
							_RefreshLinkedMarkerElements();
						}
						break;
					case GraphDraw_ns::RIGHT_OF_GRAPH:
						if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(), _B::GetElementPos(), 0, _B::_coordConverter.toScreen(markerData) )) {
							currMarkerPos = iter;
							selectOffset = _B::_coordConverter.toScreen(markerData) - p.y;
							whenMarkerSelected(_B::markers, currMarkerPos->GetID(), this);
							_B::_parent->DoLocalLoop( THISBACK( _MoveMarker ) );
							whenMarkerReleased(_B::markers, currMarkerPos->GetID(), this);
							linkStatusCounter.Inc();
							_UpdateLinkedMarkers();
							_RefreshLinkedMarkerElements();
						}
						break;
					case GraphDraw_ns::FLOAT_OVER_GRAPH:
						break;
				}
			}
		}
	}


	virtual Image  CursorImage(PointScreen p, dword keyflags) {
		MarkerPosList::Iterator iter = _B::markers.Begin();
		MarkerPosList::ConstIterator endIter = _B::markers.End();

		while ( iter != endIter ) {
			MarkerElementData& markerData = *iter;
			if (_B::_coordConverter.IsInGraphVisibleRange(markerData)) {
				switch( _B::GetElementPos() ) {
					case GraphDraw_ns::LEFT_OF_GRAPH:
						if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(), _B::GetElementPos(), _B::GetElementWidth(), _B::_coordConverter.toScreen(markerData) ) ) return GraphCtrlImg::SCROLL_Y_FINGER();
						break;
					case GraphDraw_ns::BOTTOM_OF_GRAPH:
						if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(), _B::GetElementPos(), _B::_coordConverter.toScreen(markerData), 0 )) return GraphCtrlImg::SCROLL_X_FINGER();
						break;
					case GraphDraw_ns::TOP_OF_GRAPH:
						if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(), _B::GetElementPos(), _B::_coordConverter.toScreen(markerData), _B::GetElementWidth() )) return GraphCtrlImg::SCROLL_X_FINGER();
						break;
					case GraphDraw_ns::RIGHT_OF_GRAPH:
						if ( markerData.GetTickMark().Contains(p, _B::GetFrame().TopLeft(), _B::GetElementPos(), 0, _B::_coordConverter.toScreen(markerData) ) ) return GraphCtrlImg::SCROLL_Y_FINGER();
						break;
					case GraphDraw_ns::FLOAT_OVER_GRAPH:
						return _B::CursorImage(p,keyflags);
						break;
				}
			}
			++iter;
		}
		return _B::CursorImage(p,keyflags);
	}
};



// ============================
//    DynamicMarkerContains Ctrl   CLASS
// ============================
typedef Callback3< const MarkerPosList& /*list*/, int /*markerID*/, void* /*dynMarkerCtrl*/> TypeMarkerMoveCbk;

class DynamicMarkerCtrl_MarkerContains : public  DynamicMarkerECtrl {
	public:
	typedef DynamicMarkerCtrl_MarkerContains  CLASSNAME;
	typedef DynamicMarkerECtrl _B;

	DynamicMarkerCtrl_MarkerContains(CoordinateConverter& coordconv)
	: _B(coordconv)
	{
		const typename _B::StyleGE** pStyleEC = & _B::GetStyleGE();
		_B::openPropertiesDlgCB = [this, pStyleEC]() ->void {	_B::TOpenPropertiesDlg(*this, pStyleEC); };
		_B::makePropertiesCtrl = [=](Value& v) ->ElementPropertiesDlgInterface* { return _B::template TMakePropertiesCtrl<CLASSNAME>(v); };
		makeGEEditorCB = GetDefaultMakeEditorCB();
	}

	~DynamicMarkerCtrl_MarkerContains() {}

	public:
		typedef Function< ElementPropertiesDlgInterface* (CLASSNAME& , typename CLASSNAME::StyleGE&) > MakeGEEditorCB;
		static void SetDefaultMakeEditorFct(MakeGEEditorCB f) { GetDefaultMakeEditorCB() = f; }
		void SetMakeGEEditorCB(MakeGEEditorCB f) { makeGEEditorCB = f; }
		static MakeGEEditorCB& GetDefaultMakeEditorCB() { static MakeGEEditorCB defaultMakeEditorFct; return defaultMakeEditorFct;	}
		MakeGEEditorCB makeGEEditorCB;

	virtual bool Contains(PointScreen p) const {
		return ( _B::MarkerContains(p) != MarkerElementData::INVALID_MARKER_ID );
	}
};


	typedef TStdGridAxisECtrl< GridAxisDraw >     StdGridAxisECtrl;
	typedef TStdLabelECtrl   < LabelElement>      StdLabelECtrl;
	typedef TStdLegendECtrl  < LegendElement>     StdLegendECtrl;
	typedef TStdBlankAreaECtrl<BlankAreaElement>  StdBlankAreaECtrl;
	typedef DynamicMarkerECtrl                    StdMarkerECtrl;

	void InitGraphElementCtrls();

#endif
