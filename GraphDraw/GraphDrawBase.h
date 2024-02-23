#ifndef _GraphDraw_GraphDrawBase_h_
#define _GraphDraw_GraphDrawBase_h_


#ifndef __TimingPolicies_H__
class TimingStub
{
	public:
		TimingStub(const char* prefix) {}
		inline void beginTiming(void) {};
		inline void endTiming(void)  {};
		inline void reset(void) {};
		template <class STREAM> STREAM& printStats(STREAM& str)	{ return str; }
		
		Upp::String  ToString() const {
			return String("Class TimingStub ");
		}
};
#endif



namespace GraphDraw_ns
{
	
	
	// ------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//            G r a p h D r a  w    C l a s s e s
	//
	// ------------------------------------------------------------------------------------------------------------------------------------------------------


	// ============================
	// LocalStyle   CLASS
	// ============================
	class LocalStyle {
		template<typename DERIVED>
		friend class BASE;
			
		private:
			void* style;
			Function<void (void)> deletor;
		
		public:
			LocalStyle() : style(nullptr) {}
			~LocalStyle() {
				Clear();
			}
		
		private:
			LocalStyle(const LocalStyle& c) {}
		
		public:
			bool IsEmpty() const { return (style == nullptr); }
			bool IsSameStyle(const void* styleAddr) const { return (style == styleAddr);}
			
			template <class T>
			T& GetLocalStyle() {
				if (style == nullptr) {
					T* st = new T();
					style = (void*)(st);
					deletor << [&]() {
					                   if (this->style != nullptr) { delete (T*) (this->style); }
					                   this->style=nullptr;
					                   this->deletor.Clear();
					                 };
				}
				return *((T*)(style));
			}
			
			void Clear() { deletor(); }
	};


	// ============================
	// CH_EmptyGraphDraw   CLASS
	// ============================
	class CH_EmptyGraphDraw {
		public:
			struct StyleGD : ChStyle<StyleGD> {
				Value    plotBckgndStyle;
				Value    ctrlBckgndStyle;
				Value    rectSelectStyle;
			};
		
			static const StyleGD& StyleGDDefault();
			
			CH_EmptyGraphDraw() {
				styleGD = &StyleGDDefault();
			}
		
		protected:
		const StyleGD *styleGD;

	};
	

	// ============================
	// CRTP_EmptyGraphDraw   CLASS
	// ============================
	template<class TYPES, class DERIVED>
	class CRTP_EmptyGraphDraw : public GraphSeriesGroup< DERIVED >, public GraphElementParent, public CoordinateConverterOwner, public CH_EmptyGraphDraw
	{
	private:
		LocalStyle localChStyle;

	public:
		typedef CRTP_EmptyGraphDraw<TYPES, DERIVED> CLASSNAME;
		typedef GraphSeriesGroup< DERIVED >  _B;

		virtual void SetStyleGD(const StyleGD& s) {
			styleGD = &s;
			ClearPlotDrawImg();
			ClearCtrlBackGndImg();
		}

		
		template <typename T>
		T& GetLocalChStyle() {
			bool doInit = localChStyle.IsEmpty();
			T& t = localChStyle. template GetLocalStyle<T>();
			if (doInit) {
				DERIVED& der = *static_cast<DERIVED*>(this);
				t = der.GetStyle(); // copy values
				der.SetStyle(t);
			}
			return t;
		}

		virtual void RequestChStyleLocal() {
			GetLocalChStyle<typename DERIVED::Style>();
		}

	protected:
		template <typename STYLE>
		void OverrideLocalChStyle(const STYLE& st) {
			if ( !localChStyle.IsEmpty() && !(localChStyle.IsSameStyle(&st) ) ) {
				localChStyle.Clear();
				DERIVED& der = *static_cast<DERIVED*>(this);
				der.SetStyle( st );
			}
		}

	protected:
		// graph elements drawn around the graph
		Vector< GraphElement* >  _drawElements;
		Vector< GraphElement* >  _createdElements; // the elements in this list were dynamically created by GraphDraw and are owned by GrapDraw
		Vector< CoordinateConverter* > _xConverters;
		Vector< CoordinateConverter* > _yConverters;
		

		RectScreen  _ctrlRect;  // whole graph screen Rect
		RectScreen  _plotRect;
		DrawMode    _drawMode;
		bool        _doFastPaint;

		typename TYPES::TypeBlankElement topMargin;
		typename TYPES::TypeBlankElement bottomMargin;
		typename TYPES::TypeBlankElement leftMargin;
		typename TYPES::TypeBlankElement rightMargin;
		
		UndoStack _undoManager;
		Image     _PlotDrawImage;
		Image     _CtrlBackgroundImage;
		Image     _PlotSelectImage;
		
		RectScreen  _selectRect;
		Vector< PointGraph > p1;
		
	public:


		template <class T>
		bool IsDisabledGE(const T& ge) const {
			const GraphElement* pge = &ge;
			return IsDisabledGE( pge );
		}

		bool IsDisabledGE(const GraphElement* ge) const {
			for (int c=0; c<_drawElements.GetCount(); ++c) {
				if (_drawElements[c] == ge) {
					return false;
					break;
				}
			}
			return true;
		}

		template <class T>
		void DisableGE(const T& ge) {
			const GraphElement* pge = &ge;
			DisableGE( pge );
		}

		void DisableGE(const GraphElement* ge) {
			for (int c=0; c<_drawElements.GetCount(); ++c) {
				if (_drawElements[c] == ge) {
					_drawElements.Remove(c);
					break;
				}
			}
		}
		
#ifndef __TimingPolicies_H__
		typedef TimingStub TimingType;
#else
		typedef NamedTimings< TimingPolicies_ns::MinMaxAverageTiming > TimingType;
		typedef NamedTimings< TimingPolicies_ns::NoTiming > NullTimingType;
		//typedef NamedTimings< TimingPolicies_ns::NoTiming >  TimingType;
		
#endif
		
		TimingType _paintTiming;
		TimingType _fastPaintPlotDataTiming;
		TimingType _totalFullPaintPlotDataTiming;
		TimingType _paintPlotDataGlobalTiming;
		TimingType _paintBackGndTiming;
		TimingType _initBackGndPaintTiming;
		TimingType _paintBackGndTiming_chPaint;
		TimingType _paintBackGndTiming_paintImage;
		TimingType _paintBackGndTiming_copyImage;
		TimingType _preparePlotPointsListTiming;
		TimingType _fullPaintPlotDataTiming;

		inline void ClearPlotDrawImg()    { _PlotDrawImage.Clear(); _PlotSelectImage.Clear(); }
		inline void ClearCtrlBackGndImg() {	_CtrlBackgroundImage.Clear(); }
		
		// helper method
		void AppendElementToRect(GraphElement& element, RectScreen& fromRect, const int scale) const
		{
//			RLOGBLOCK_STR( debugTrace, "CRTP_EmptyGraphDraw::AppendElementToRect()   GraphElem:" << element);
			RectScreen res = fromRect;
			switch(element.GetElementPos()) {
				case TOP_OF_GRAPH:
					res.bottom = res.top+element.GetElementWidth()*scale;
					fromRect.top = res.bottom;
					element.SetFrame(res);
					break;
				case BOTTOM_OF_GRAPH:
					res.top = res.bottom-element.GetElementWidth()*scale;
					fromRect.bottom = res.top;
					element.SetFrame(res);
					break;
				case LEFT_OF_GRAPH:
					res.right = res.left+element.GetElementWidth()*scale;
					fromRect.left = res.right;
					element.SetFrame(res);
					break;
				case RIGHT_OF_GRAPH:
					res.left = res.right-element.GetElementWidth()*scale;
					fromRect.right = res.left;
					element.SetFrame(res);
					break;
				case FLOAT_OVER_GRAPH:
					res = element.GetFloatFrame();
					res = RectScreen( res.TopLeft()*scale, res.Size()*scale );
					element.SetFrame(res);
					break;
			}
//			RLOG_STR( debugTrace, "modified plotRect:(" << fromRect << ")");
//			RLOG_STR( debugTrace, "element:(" << element << ")");
		}

		void updateSizesOnSide( Vector< GraphElement* >& elementsList, RectScreen& tmpRect, RectScreen& plotRect, const int scale = 1 ) const {
//			RLOGBLOCK_STR( debugTrace, "CRTP_EmptyGraphDraw::updateSizesOnSide(" << plotRect << ")");

			int j = elementsList.GetCount()-1;

			for (; j>=1; --j)
			{
				tmpRect = plotRect;
				if ( elementsList[j]->GetOverlapPrevious() ) {
					elementsList[j]->SetElementWidth(0);
					AppendElementToRect(*(elementsList[j]), tmpRect, scale);
					AppendElementToRect(*(elementsList[j-1]), tmpRect, scale);
					if ( elementsList[j-1]->GetStackingPriority() >=0 ) plotRect = tmpRect;
					elementsList[j]->SetElementWidth( elementsList[j-1]->GetElementWidth());
					elementsList[j]->SetFrame( elementsList[j-1]->GetFrame() );
					--j;
					if (j==0) --j;
				}
				else
				{
					AppendElementToRect(*(elementsList[j]), tmpRect, scale);
					if ( elementsList[j]->GetStackingPriority() >=0 ) plotRect = tmpRect;
				}
			}

			if (j==0) {
				tmpRect = plotRect;
				AppendElementToRect(*(elementsList[j]), tmpRect, scale);
				if ( elementsList[j]->GetStackingPriority() >=0 ) plotRect = tmpRect;
			}
		}

		void updateSizes( const int scale = 1 )
		{
//			RLOGBLOCK_STR( debugTrace, "CRTP_EmptyGraphDraw::updateSizes(" << _plotRect << ")");
			RectScreen svg = _plotRect;
			_plotRect = _ctrlRect;
//			RLOG_STR( debugTrace, "INPUT   plotRect:(" << _plotRect << ")");

			StableSort(_drawElements, compareGraphElementPriority);

			Vector< GraphElement* >  topSideElements;
			Vector< GraphElement* >  bottomSideElements;
			Vector< GraphElement* >  leftSideElements;
			Vector< GraphElement* >  rightSideElements;
			Vector< GraphElement* >  floatSideElements;
			for (int j=0; j<_drawElements.GetCount(); ++j) {
				if (!_drawElements[j]->IsHidden()) {
					switch(_drawElements[j]->GetElementPos()) {
						case LEFT_OF_GRAPH:
							leftSideElements.Add(_drawElements[j]);
							break;
						case BOTTOM_OF_GRAPH:
							bottomSideElements.Add(_drawElements[j]);
							break;
						case FLOAT_OVER_GRAPH:
							floatSideElements.Add(_drawElements[j]);
							break;
						case RIGHT_OF_GRAPH:
							rightSideElements.Add(_drawElements[j]);
							break;
						case TOP_OF_GRAPH:
							topSideElements.Add(_drawElements[j]);
							break;
					}
				}
			}

			RectScreen tmpRect = _plotRect;
			
			updateSizesOnSide(topSideElements,   tmpRect, _plotRect, scale);
			updateSizesOnSide(bottomSideElements,tmpRect, _plotRect, scale);
			updateSizesOnSide(leftSideElements,  tmpRect, _plotRect, scale);
			updateSizesOnSide(rightSideElements, tmpRect, _plotRect, scale);
			updateSizesOnSide(floatSideElements, tmpRect, _plotRect, scale);
		
			if (_plotRect != svg) {
				_CtrlBackgroundImage.Clear();
				ClearPlotDrawImg();
			}

			for (int j = 0; j < _drawElements.GetCount(); ++j) {
				if (!_drawElements[j]->IsHidden()) {
					_drawElements[j]->AdjustToPlotRect( _plotRect );
				}
			}

			for (int j = 0; j < _xConverters.GetCount(); ++j) {
				_xConverters[j]->UpdateScreenSize( 0, _plotRect.GetWidth() );
			}

			for (int j = 0; j < _yConverters.GetCount(); ++j) {
				_yConverters[j]->UpdateScreenSize( _plotRect.GetHeight(), 0  );
			}
		}

		public:

		bool debugTrace;
		bool debugTraceTimings;
		
		CRTP_EmptyGraphDraw()
		: _ctrlRect(0,0,100,100)
		, _plotRect(0,0,100,100)
		, _drawMode( MD_DRAW )
		, _doFastPaint(false)
		, _paintTiming                  ("paint()                                   ")
		, _paintBackGndTiming           ("  paintBckGnd()                           ")
		, _initBackGndPaintTiming       ("    initBackGndPaint()                    ")
		, _paintBackGndTiming_chPaint   ("    paintBackGndTiming_chPaint()          ")
		, _paintBackGndTiming_paintImage("    paintBackGndTiming_paintImage()       ")
		, _paintBackGndTiming_copyImage ("    paintBackGndTiming_copyImage()        ")
		, _totalFullPaintPlotDataTiming ("    AllSeries PaintPlotDataTiming()       ")
		, _paintPlotDataGlobalTiming    ("    paintPlotDataGlobalTiming()           ")
		, _fastPaintPlotDataTiming      ("      fastPaintPlotDataTiming()           ")
		, _fullPaintPlotDataTiming      ("      fullPaintPlotDataTiming()           ")
		, _preparePlotPointsListTiming  ("        preparePaintPlotPointsListTiming()")
		, debugTrace(false)
		, debugTraceTimings(false)
		{
			SetStyleGD( StyleGDDefault() );
			_selectRect.Clear();
			setScreenSize( Size(100,100) ); // set default size
			
			topMargin.SetElementName("Top Margin");
			bottomMargin.SetElementName("Bottom Margin");
			leftMargin.SetElementName("Left Margin");
			rightMargin.SetElementName("Right Margin");

			AddElement(TOP_OF_GRAPH,    3, topMargin,    INT_MAX);
			AddElement(BOTTOM_OF_GRAPH, 3, bottomMargin, INT_MAX);
			AddElement(RIGHT_OF_GRAPH,  3, rightMargin,  INT_MAX);
			AddElement(LEFT_OF_GRAPH,   3, leftMargin,   INT_MAX);
		};

		virtual ~CRTP_EmptyGraphDraw() {
			for (int j = 0; j < _createdElements.GetCount(); j++)
			{
				delete ( _createdElements[j] );
			}
			_createdElements.Clear();
			
			PrintTimingStats(false);
		}


#ifdef flagGD_TIMINGS
		void PrintTimingStats(bool forcePrint=true) {
			if (forcePrint || debugTraceTimings) {
				VppLog() << "============== TIMING STATS ==================\n";
				_paintTiming.printStats( VppLog() );
				_paintBackGndTiming.printStats(VppLog() );
				  _initBackGndPaintTiming.printStats( VppLog() );
				  _paintBackGndTiming_chPaint.printStats( VppLog() );
				  _paintBackGndTiming_copyImage.printStats( VppLog() );
				  _paintBackGndTiming_paintImage.printStats( VppLog() );
				_totalFullPaintPlotDataTiming.printStats( VppLog() );
				  _paintPlotDataGlobalTiming.printStats( VppLog() );
				    _fastPaintPlotDataTiming.printStats( VppLog() );
				    _fullPaintPlotDataTiming.printStats( VppLog() );
				      _preparePlotPointsListTiming.printStats( VppLog() );
				VppLog() << "===============================================\n\n";
			}
		}

		void ResetTimingStats() {
			_paintTiming.reset();
			  _paintBackGndTiming.reset();
			    _initBackGndPaintTiming.reset();
			    _paintBackGndTiming_chPaint.reset();
			    _paintBackGndTiming_copyImage.reset();
			    _paintBackGndTiming_paintImage.reset();
			_totalFullPaintPlotDataTiming.reset();
			  _paintPlotDataGlobalTiming.reset();
			    _fastPaintPlotDataTiming.reset();
			    _fullPaintPlotDataTiming.reset();
			      _preparePlotPointsListTiming.reset();
		}
		
		private:
		void DoDataDrawPerfTest2(unsigned int refreshCount ) {
			if (refreshCount) {
				--refreshCount;
				RefreshFromChild(REFRESH_FULL);
				PostCallback(THISBACK1(DoDataDrawPerfTest2, refreshCount));
			}
			else PostCallback(THISBACK1(PrintTimingStats, true));
		}
		public:
		void DoDataDrawPerfTest(unsigned int nbDraws = 10 ) {
			ResetTimingStats();
			PostCallback(THISBACK1(DoDataDrawPerfTest2, nbDraws));
		}

#else
		inline void PrintTimingStats(bool forcePrint=true) {}
		inline void ResetTimingStats() {}
		inline void DoDataDrawPerfTest(unsigned int nbDraws = 10 ) {}
#endif
		
		virtual void SetGDModify() {}
		
		virtual GraphSeriesDecoratorVector& GetGSeries() {
			return _B::graphSeriesProxyList;
		}

		virtual Value GetParentCtrl() {
			ASSERT_(0, "CRTP_EmptyGraphDraw::GetParentCtrl()  was CALLED");
			return Null;
		}

		virtual void AddUndoAction(UndoStackData& CB) {
			_undoManager.AddUndoAction(CB);
		}
		
		void Undo() {
			if (_undoManager.Undo()) RefreshFromChild( GraphDraw_ns::REFRESH_FULL );
		}

		void Redo() {
			if (_undoManager.Redo()) RefreshFromChild( GraphDraw_ns::REFRESH_FULL );
		}
		
		void FitToData(FitToDataStrategy fitStrategy=ALL_SERIES) {
			for (int j = _drawElements.GetCount()-1; j>=0; j--) {
				_drawElements[j]->FitToData(fitStrategy);
			}
			RefreshFromChild( GraphDraw_ns::REFRESH_FULL );
			UpdateAllLinks();
		}
		

		CoordinateConverter& GetXCoordConverter(int c) {
			if (c<0) {
				ASSERT(_B::_currentXConverter!=nullptr);
				return *_B::_currentXConverter;
			}
			CoordinateConverter& coord = *_xConverters[c];
			return (coord);
		}
		
		CoordinateConverter& GetYCoordConverter(int c) {
			if (c <0 ) {
				ASSERT(_B::_currentYConverter!=nullptr);
				return *_B::_currentYConverter;
			}
			CoordinateConverter& coord = *_yConverters[c];
			return (coord);
		}
// ====================== LINKING ======================

	virtual void RefreshWhenLinkUpdate() {
		//Refresh(); //GraphDraw_ns::REFRESH_FAST);
		RefreshFromChild(GraphDraw_ns::REFRESH_FULL);
	}

	virtual void RequestLinksUpdate(CoordinateConverter& p) {
		p.UpdateLinks(LINK_UPDATE_RANGE);
	}

	void UpdateAllLinks(LinkUpdateStrategy strategy = LINK_UPDATE_RANGE) {
		for (int j = 0; j < _xConverters.GetCount(); j++) {
			_xConverters[j]->UpdateLinks(strategy);
		}

		for (int j = 0; j < _yConverters.GetCount(); j++) {
			_yConverters[j]->UpdateLinks(strategy);
		}
	}

	void ForceUpdateAllLinks(LinkUpdateStrategy strategy = LINK_UPDATE_RANGE) {
		for (int j = 0; j < _xConverters.GetCount(); j++) {
			_xConverters[j]->linkStatusCounter.Inc();
		}

		for (int j = 0; j < _yConverters.GetCount(); j++) {
			_yConverters[j]->linkStatusCounter.Inc();
		}
		
		UpdateAllLinks(strategy);
	}

	static void Link(CoordinateConverter& local, CoordinateConverter& other) {
		if (local.Link(other) ) {
			other.Link(local);
		}
	}
	
	static void Unlink(CoordinateConverter& local, CoordinateConverter& other) {
		local.Unlink(other);
	}
// ======================

		DERIVED& SetDrawMode(DrawMode m) { _drawMode = m; return *static_cast<DERIVED*>(this); }
		DERIVED& SetDrawMode(int m) {
			if ((MD_DRAW<=m) && (m<=MD_SUBPIXEL)) _drawMode = (DrawMode)m;
			return *static_cast<DERIVED*>(this);
		}
		virtual DrawMode GetDrawMode() { return _drawMode; }

		
		DERIVED& SetTopMargin(int v)    { topMargin.SetElementWidth(v);    return *static_cast<DERIVED*>(this); }
		DERIVED& SetBottomMargin(int v) { bottomMargin.SetElementWidth(v); return *static_cast<DERIVED*>(this); }
		DERIVED& SetLeftMargin(int v)   { leftMargin.SetElementWidth(v);   return *static_cast<DERIVED*>(this); }
		DERIVED& SetRightMargin(int v)  { rightMargin.SetElementWidth(v);  return *static_cast<DERIVED*>(this); }

		DERIVED& setScreenSize(RectScreen r, const int scale=1)	{
//			RLOGBLOCK_STR( debugTrace, "setScreenSize(" << r << " , " << scale << ")");
			if (r!=_ctrlRect || scale != 1) {
				_ctrlRect = r;
				ClearPlotDrawImg();
				_CtrlBackgroundImage.Clear();
				updateSizes(scale);
			}
			return *static_cast<DERIVED*>(this);
		}

		inline DERIVED& setScreenSize( const int scale=1 )	{
			return setScreenSize(_ctrlRect, scale);
		}

		virtual void AddXConverter(CoordinateConverter* conv) {
			_xConverters.Add() = conv;
			_B::_currentXConverter = conv;
		}

		virtual void AddYConverter(CoordinateConverter* conv) {
			_yConverters.Add() = conv;
			_B::_currentYConverter = conv;
		}

		void AddXConverter(CoordinateConverter& conv) {
			AddXConverter(&conv);
		}

		void AddYConverter(CoordinateConverter& conv) {
			AddYConverter(&conv);
		}
		
		void SetCurrentXConverter(int n) {
			ASSERT( n < _xConverters.GetCount() );
			_B::_currentXConverter =  _xConverters[n];
		}

		void SetCurrentYConverter(int n) {
			ASSERT( n < _yConverters.GetCount() );
			_B::_currentYConverter =  _yConverters[n];
		}

		bool IsValidForZoom(RectScreen r)
		{
			static const TypeGraphCoord rangeMin = std::numeric_limits<TypeGraphCoord>::epsilon() * 1000.0;
			for (int j = 0; j < _xConverters.GetCount(); j++)
			{
				if ( tabs(_xConverters[j]->toGraph( r.left ) - _xConverters[j]->toGraph( r.right )) < rangeMin ) return false;
			}

			for (int j = 0; j < _yConverters.GetCount(); j++)
			{
				if ( tabs(_yConverters[j]->toGraph( r.bottom ) - _yConverters[j]->toGraph( r.top )) < rangeMin) return false;
			}
			return true;
		}

		virtual Callback MakeRestoreGraphSizeCB() {
			Callback action;
			for (int j = 0; j < _xConverters.GetCount(); j++) { action << _xConverters[j]->MakeRestoreAxisMinMaxCB(); }
			for (int j = 0; j < _yConverters.GetCount(); j++) { action << _yConverters[j]->MakeRestoreAxisMinMaxCB(); }
			return 	action;
		}

		virtual void ZoomX(TypeScreenCoord left, TypeScreenCoord right)
		{
			bool isModified = false;
			for (int j = 0; j < _xConverters.GetCount(); j++)
			{
				if (_xConverters[j]->IsZoomAllowed()) {
					_xConverters[j]->UpdateGraphSize( _xConverters[j]->toGraph( left ),
					                                  _xConverters[j]->toGraph( right ));
					_xConverters[j]->linkStatusCounter.Inc();
					isModified = true;
				}
			}
			if (isModified) {
				ClearPlotDrawImg();
				Refresh();
			}
		}

		virtual void ZoomY(TypeScreenCoord top, TypeScreenCoord bottom)
		{
			bool isModified = false;
			for (int j = 0; j < _yConverters.GetCount(); j++)
			{
				if (_yConverters[j]->IsZoomAllowed()) {
					_yConverters[j]->UpdateGraphSize( _yConverters[j]->toGraph( bottom ),
					                                  _yConverters[j]->toGraph( top ));
					_yConverters[j]->linkStatusCounter.Inc();
					isModified = true;
				}
			}
			if (isModified) {
				ClearPlotDrawImg();
				Refresh();
			}
		}

		void ZoomOnRect(RectScreen r)
		{
			if ( IsValidForZoom(r) )
			{
				ZoomX(r.left, r.right);
				ZoomY(r.top, r.bottom);
				Refresh();
			}
		}

		void ApplyInvZoomFactor( double zoom, PointScreen zoomCenter = Null )
		{
			ApplyZoomFactor( 1.0/zoom, zoomCenter);
		}

		void ApplyZoomFactor( double zoom, PointScreen zoomCenter = Null )
		{
			double xDelta = _plotRect.GetWidth() * (1.0 - zoom) + .5;
			double yDelta = _plotRect.GetHeight() * (1.0 - zoom) + .5;
			RectScreen r( (TypeScreenCoord)(-xDelta/2.0),
					(TypeScreenCoord)(-yDelta/2.0),
					(TypeScreenCoord)(_plotRect.GetWidth() +xDelta - xDelta/2.0),
					(TypeScreenCoord)(_plotRect.GetHeight() +yDelta - yDelta/2.0) );
			if (! zoomCenter.IsNullInstance()) {
				r.Offset( (zoomCenter - r.CenterPoint())*( zoom -1.0 ) );
			}
			ZoomOnRect(r);
		}


		virtual void ScrollX( TypeScreenCoord xOffset, bool doRefre = true)
		{
			if (xOffset == 0) return;
			bool isModified = false;
			for (int j = 0; j < _xConverters.GetCount(); j++)
			{
				if (_xConverters[j]->IsScrollAllowed()) {
					_xConverters[j]->Scroll( xOffset );
					_xConverters[j]->linkStatusCounter.Inc();
					isModified=true;
				}
			}
			if (isModified) {
				ClearPlotDrawImg();
				if (doRefre) Refresh();
			}
		}

		virtual void ScrollY( TypeScreenCoord yOffset, bool doRefre = true)
		{
			if (yOffset == 0) return;
			bool isModified = false;
			for (int j = 0; j < _yConverters.GetCount(); j++)
			{
				if (_yConverters[j]->IsScrollAllowed()) {
					_yConverters[j]->Scroll( yOffset );
					_yConverters[j]->linkStatusCounter.Inc();
					isModified=true;
				}
			}
			if (isModified) {
				ClearPlotDrawImg();
				if (doRefre) Refresh();
			}
		}

		DERIVED& Scroll( TypeScreenCoord xOffset, TypeScreenCoord yOffset)
		{
			ScrollX(xOffset, false);
			ScrollY(yOffset, false);
			Refresh();
			return *static_cast<DERIVED*>(this);
		}

		template<class T, int POS_OF_GRAPH>
		T& AddElement(T& v, int stackPrio) {
			v._parent = this;
			v.SetStackingPriority(stackPrio);
			v.SetElementPos((ElementPosition)POS_OF_GRAPH);
			_drawElements.Add(&v);
			StableSort(_drawElements, compareGraphElementPriority);
			return v;
		}

		template<class T>
		T& AddElement(ElementPosition pos, T& v, int stackPrio) {
			v._parent = this;
			v.SetStackingPriority(stackPrio);
			v.SetElementPos(pos);
			_drawElements.Add(&v);
			StableSort(_drawElements, compareGraphElementPriority);
			return v;
		}

		template<class T, int POS_OF_GRAPH>
		T& AddElement(int elementWidth, T& v, int stackPrio) {
				v.SetElementWidth(elementWidth);
				return AddElement<T, POS_OF_GRAPH>(v, stackPrio);
		}

		template<class T>
		T& AddElement(ElementPosition pos, int elementWidth, T& v, int stackPrio) {
				v.SetElementWidth(elementWidth);
				return AddElement<T>(pos, v, stackPrio);
		}

		template<class T>  T& AddLeftElement(T& v, int stackPrio)   { return AddElement<T, LEFT_OF_GRAPH>(v, stackPrio); }
		template<class T>  T& AddRightElement(T& v, int stackPrio)  { return AddElement<T, RIGHT_OF_GRAPH>(v, stackPrio); }
		template<class T>  T& AddTopElement(T& v, int stackPrio)    { return AddElement<T, TOP_OF_GRAPH>(v, stackPrio); }
		template<class T>  T& AddBottomElement(T& v, int stackPrio) { return AddElement<T, BOTTOM_OF_GRAPH>(v, stackPrio); }
		template<class T>  T& AddFloatElement(T& v, int stackPrio)  { return AddElement<T, FLOAT_OVER_GRAPH>(v, stackPrio); }

		template<class T>  T& AddLeftElement(int elementWidth, T& v, int stackPrio)   { return AddElement<T, LEFT_OF_GRAPH>(elementWidth, v, stackPrio); }
		template<class T>  T& AddRightElement(int elementWidth, T& v, int stackPrio)  { return AddElement<T, RIGHT_OF_GRAPH>(elementWidth, v, stackPrio); }
		template<class T>  T& AddTopElement(int elementWidth, T& v, int stackPrio)    { return AddElement<T, TOP_OF_GRAPH>(elementWidth, v, stackPrio); }
		template<class T>  T& AddBottomElement(int elementWidth, T& v, int stackPrio) { return AddElement<T, BOTTOM_OF_GRAPH>(elementWidth, v, stackPrio); }
		template<class T>  T& AddFloatElement(int elementWidth, T& v, int stackPrio)   { return AddElement<T, FLOAT_OVER_GRAPH>(elementWidth, v, stackPrio); }

		template<class T, int POS_OF_GRAPH>
		T& CreateElement(int elementWidth, int stackPrio) {
			T* e = new T();
			e->SetElementWidth(elementWidth);
			e->_parent = this;
			_createdElements << e; // to manage object destruction
			AddElement<T, POS_OF_GRAPH>(*e, stackPrio);
			return *e;
		}

		template<class T>
		T& CreateElement(ElementPosition pos, int elementWidth, int stackPrio) {
			T* e = new T();
			e->SetElementWidth(elementWidth);
			e->_parent = this;
			_createdElements << e; // to manage object destruction
			AddElement<T>(pos, *e, stackPrio);
			return *e;
		}

		template<class T, int POS_OF_GRAPH, class P1>
		T& CreateElement1(int elementWidth, int stackPrio, P1& par1 ) {
			T* e = new T(par1);
			e->SetElementWidth(elementWidth);
			e->_parent = this;
			_createdElements << e; // to manage object destruction
			AddElement<T, POS_OF_GRAPH>(*e, stackPrio);
			return *e;
		}

		template<class T, int POS_OF_GRAPH, class P1, class P2>
		T& CreateElement2(int elementWidth, int stackPrio, P1& par1, P2& par2 ) {
			T* e = new T(par1,par2);
			e->SetElementWidth(elementWidth);
			e->_parent = this;
			_createdElements << e; // to manage object destruction
			AddElement<T, POS_OF_GRAPH>(*e, stackPrio);
			return *e;
		}

		void AddBlanklArea(ElementPosition pos, int width, int stackPrio) {
			CreateElement<typename TYPES::TypeBlankElement>( pos, width, stackPrio );
		}
		

		// Refresh called from child
		virtual void RefreshFromChild( RefreshStrategy strategy ) {
			Refresh();
		};

		virtual void Refresh() {};


		Image GetImage( Size size, Color backGndColor = Upp::White(), const int scale = 1 ) {
//			RLOGBLOCK_STR( debugTrace, "CRTP_EmptyGraphDraw::GetImage(" << this << ")   [ FastPaint , PlotImgEmpty ] => [ " << _doFastPaint << " , " << _PlotDrawImage.IsEmpty() << " ]");
			RectScreen screenRectSvg = _ctrlRect;
			Image plotDrawImageSvg = _PlotDrawImage;
			Image ctrlBackgroundImageSvg = _CtrlBackgroundImage;
			setScreenSize( size, scale );
			ImageBuffer ib(size);
			Upp::Fill( ib.Begin(),backGndColor, ib.GetLength() );
			BufferPainter bp(ib, MD_ANTIALIASED); 
			ClearPlotDrawImg();
			Paint(bp, scale);
			ClearPlotDrawImg();
			setScreenSize( screenRectSvg );
			_PlotDrawImage = plotDrawImageSvg;
			_CtrlBackgroundImage = ctrlBackgroundImageSvg;
			return ib;
		}

		Image GetImage(Size size, const int scale = 1 ) {
			return GetImage(size, White(), scale );
		}

		inline Image GetImage(const int scale=1) {
			return GetImage( _ctrlRect.Size()*scale, scale );
		}

		inline Image GetImage(Color backGndColor, const int scale=1) {
			return GetImage( _ctrlRect.Size()*scale, backGndColor, scale );
		}



		#define addToFullPointsList_withLine(testFct, pointList, xx, yy , xConverter, yConverter, nbVisiblePoints, prevPoint, prevPointIsAdded, isSeriesFilled, rect) {\
			PointGraph currPoint(xx, yy);\
			if (isSeriesFilled && xConverter.IsInGraphVisibleRange(xx) )\
			{\
				if (!prevPointIsAdded) { pointList.AddPick(PointScreen(xConverter.toScreen( prevPoint.x ), yConverter.toScreen( prevPoint.y ))); }\
				pointList.AddPick(PointScreen(xConverter.toScreen( xx ), yConverter.toScreen( yy )));\
				prevPointIsAdded=true;\
			}\
			else {\
				if ( testFct(prevPoint, currPoint, rect) )\
				{\
					++nbVisiblePoints;\
					if (!prevPointIsAdded) { pointList.AddPick(PointScreen(xConverter.toScreen( prevPoint.x ), yConverter.toScreen( prevPoint.y ))); }\
					pointList.AddPick(PointScreen(xConverter.toScreen( xx ), yConverter.toScreen( yy )));\
					prevPointIsAdded=true;\
				} else { \
					prevPointIsAdded = false;\
				}\
				prevPoint = currPoint;\
			}\
		}

		template<class T>
		void Paint(T& dw, int scale)
		{
//			RLOGBLOCK_STR( debugTrace, "CRTP_EmptyGraphDraw::Paint(" << this << ")   [ FastPaint , PlotImgEmpty ] => [ " << _doFastPaint << " , " << _PlotDrawImage.IsEmpty() << " ] ===========================");
			_paintTiming.beginTiming();
			_paintBackGndTiming.beginTiming();

			if ( _CtrlBackgroundImage.IsEmpty() )
			{
				_initBackGndPaintTiming.beginTiming();
				RGBA bckgColor;   bckgColor.r = 0; bckgColor.g = 0; bckgColor.b = 0; bckgColor.a = 0;
				ImageBuffer ib(_ctrlRect.Size());
				Upp::Fill( ib.Begin(), bckgColor, ib.GetLength() );
				BufferPainter bp(ib, _drawMode);
				_initBackGndPaintTiming.endTiming();
				// ------------
				// paint background
				// ------------
				_paintBackGndTiming_chPaint.beginTiming();
				if ( !styleGD->ctrlBckgndStyle.IsNull() ) ChPaint(bp, _ctrlRect, styleGD->ctrlBckgndStyle );
				if ( !styleGD->plotBckgndStyle.IsNull())  ChPaint(bp, _plotRect, styleGD->plotBckgndStyle );
				_paintBackGndTiming_chPaint.endTiming();
				_paintBackGndTiming_copyImage.beginTiming();
				_CtrlBackgroundImage = ib;
				_paintBackGndTiming_copyImage.endTiming();
			}
//			else
//			{
//				_initBackGndPaintTiming.reset();
//				_paintBackGndTiming_chPaint.reset();
//				_paintBackGndTiming_copyImage.reset();
//			}
			_paintBackGndTiming_paintImage.beginTiming();
			dw.DrawImage(0, 0, _CtrlBackgroundImage );
			_paintBackGndTiming_paintImage.endTiming();
			
			_paintBackGndTiming.endTiming();

			// --------------------------------------
			// BEGIN paint in PLOT AREA
			// --------------------------------------
			dw.Clipoff(_plotRect.left, _plotRect.top, _plotRect.GetWidth(), _plotRect.GetHeight());

			for (int j = 0; j < _drawElements.GetCount(); j++) {
				if (!_drawElements[j]->IsHidden()) {
					_drawElements[j]->PrePaint(scale);
				}
			}


			// --------------
			// GRAPH ELEMENTS on PLOT area --UNDER DATA-- ( X/Y Grid, or anything else )
			// --------------
			for (int j = 0; j < _drawElements.GetCount(); j++) {
				if ( (!_drawElements[j]->IsHidden()) && _drawElements[j]->IsFloat() ) _drawElements[j]->PaintOnPlot_underData(dw, _plotRect.GetWidth(), scale);
			}
			
			for (int j = 0; j < _drawElements.GetCount(); j++) {
				if (!_drawElements[j]->IsHidden()) {
					if      ( _drawElements[j]->IsVertical() )   _drawElements[j]->PaintOnPlot_underData(dw, _plotRect.GetWidth(), scale);
					else if ( _drawElements[j]->IsHorizontal() ) _drawElements[j]->PaintOnPlot_underData(dw, _plotRect.GetHeight(), scale);
				}
			}
			
			// ----------------
			// paint PLOT DATA
			// ----------------
			_paintPlotDataGlobalTiming.beginTiming();
			
			if ( ( _plotRect.GetHeight() > 0 ) && ( _plotRect.GetWidth() > 0 ) ) {
				if (_doFastPaint)
				{
					RGBA bckgColor;   bckgColor.r = 0; bckgColor.g = 0; bckgColor.b = 0; bckgColor.a = 0;
					ImageBuffer ib(_plotRect.Size());
					Upp::Fill( ib.Begin(), bckgColor, ib.GetLength() );
					BufferPainter bp(ib, _drawMode);
					_B::PaintAllGraphSeries(bp, _doFastPaint, scale);

					dw.DrawImage(0, 0, ib);
					ClearPlotDrawImg();
				}
				else
				{
					if ( _B::IsModifyGraphSeries() ) {
						ClearPlotDrawImg();
					}
					if ( _PlotDrawImage.IsEmpty() )
					{
						RGBA bckgColor;   bckgColor.r = 0; bckgColor.g = 0; bckgColor.b = 0; bckgColor.a = 0;
						ImageBuffer ib(_plotRect.Size());
						Upp::Fill( ib.Begin(), bckgColor, ib.GetLength() );
						BufferPainter bp(ib, _drawMode);
						_B::PaintAllGraphSeries(bp, _doFastPaint, scale);
						_PlotDrawImage = ib;
						_B::ClearModifyGraphSeries();
					}
					dw.DrawImage(0, 0, _PlotDrawImage);
				}
			}
			_paintPlotDataGlobalTiming.endTiming();
			
			// ------------------
			// paint SELECT DATA
			// ------------------
			if ( ( _plotRect.GetHeight() > 0 ) && ( _plotRect.GetWidth() > 0 ) ) {
				RGBA bckgColor;   bckgColor.r = 0; bckgColor.g = 0; bckgColor.b = 0; bckgColor.a = 0;
				ImageBuffer ib(_plotRect.Size());
				Upp::Fill( ib.Begin(), bckgColor, ib.GetLength() );
				BufferPainter bp(ib, _drawMode);
				
				_B::PaintAllSelectedGraphSeries(bp, _doFastPaint, scale);
				_PlotSelectImage = ib;
				dw.DrawImage(0, 0, _PlotSelectImage);
			}
			
			// --------------
			// GRAPH ELEMENTS on PLOT area --OVER DATA-- ( X/Y Grid, or anything else )
			// --------------
			for (int j = 0; j < _drawElements.GetCount(); j++) {
				if ( (!_drawElements[j]->IsHidden()) && _drawElements[j]->IsFloat() ) _drawElements[j]->PaintOnPlot_overData(dw, _plotRect.GetWidth(), scale);
			}
			
			for (int j = 0; j < _drawElements.GetCount(); j++) {
				if (!_drawElements[j]->IsHidden()) {
					if      ( _drawElements[j]->IsVertical() )   _drawElements[j]->PaintOnPlot_overData(dw, _plotRect.GetWidth(), scale);
					else if ( _drawElements[j]->IsHorizontal() ) _drawElements[j]->PaintOnPlot_overData(dw, _plotRect.GetHeight(), scale);
				}
			}
			
			// --------------------------------------
			// Paint SELECT Rect
			// --------------------------------------
			if ( !_selectRect.IsEmpty() && !styleGD->rectSelectStyle.IsNull()) {
				ChPaint(dw, _selectRect, styleGD->rectSelectStyle);
			}
			// --------------------------------------
			// END of paint in PLOT AREA
			// --------------------------------------
			dw.End();

			// --------------
			// GRAPH ELEMENTS ( painted in they're own area : the ones around the PLOT area )
			// --------------
			
			for (int j = 0; j < _drawElements.GetCount(); j++)
			{
				if ( (!_drawElements[j]->IsHidden()) && (!_drawElements[j]->IsFloat()) ) {
					dw.Offset(_drawElements[j]->GetFrame().TopLeft());
					_drawElements[j]->PaintElement(dw, scale);
					dw.End();
				}
			}
			// --------------
			// GRAPH ELEMENTS on ALL GRAPH area == FLOATING ELEMENTS  ( legend, or anything else )
			// --------------
			for (int j = 0; j < _drawElements.GetCount(); j++)
			{
				if ( (!_drawElements[j]->IsHidden()) && (_drawElements[j]->IsFloat()) ) {
					dw.Clipoff( _drawElements[j]->GetFloatFrame(scale) );
					_drawElements[j]->PaintFloatElement(dw, scale);
					dw.End();
				}
			}
			_paintTiming.endTiming();
			
			//PrintTimingStats(false);
		}
	};
};

template <class T>
class BlurringDecorator : public T {
	
	private:
	bool doBlur;

	void blurImage(Image& m) {
		m = Sharpen(m, -200);
		m = Sharpen(m, -200);
		m = Sharpen(m, -200);
		m = Sharpen(m, -200);
		m = Sharpen(m, -200);
		m = Sharpen(m, -200);
	}


	public:
	
	BlurringDecorator() : doBlur(true) {}
	virtual ~BlurringDecorator() {}
	void setBlur(bool blur = true)  { doBlur = blur; }
	
	virtual void Paint(Draw& w) {
		if (doBlur) {
			ImagePainter dw(T::GetSize(), MODE_NOAA);
			T::Paint(dw);
			Image im = dw;
			blurImage(im);
			w.DrawImage(0, 0, im);
		}
		else {
			T::Paint(w);
		}
	}
};


#endif
