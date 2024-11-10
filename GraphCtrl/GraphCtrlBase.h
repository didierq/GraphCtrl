#ifndef _GraphCtrl_GraphCtrlBase_h_
#define _GraphCtrl_GraphCtrlBase_h_



struct GraphCtrl_Constants {
	static float ZOOM_STEP_FACTOR;
};

struct GraphCtrl_Keys {
	// ------ KEYBOARD ACTIONS ------
	static dword K_KBD_UNDO;
	static dword K_KBD_REDO;
	static dword K_KBD_SELECT_CLEAR;
	static dword K_KBD_SELECT_ALL;
	static dword K_KBD_LEFT_SCROLL;
	static dword K_KBD_RIGHT_SCROLL;
	static dword K_KBD_UP_SCROLL;
	static dword K_KBD_DOWN_SCROLL;

	//  ------ MOUSE ACTIONS (+ CTRL/SHIFT/ALT )  ------
	// In PLOT AREA  &  GraphElement AREA
	static dword K_SCROLL;
	static dword K_PLOT_ZOOM;

	// In PLOT AREA
	
	static dword K_PLOT_MEASURE_TOOL;
	static dword K_PLOT_POINT_SELECT_REPLACE;
	static dword K_PLOT_POINT_SELECT_APPEND;
	
	static dword K_PLOT_AREA_SELECT_REPLACE_INCLUDED;
	static dword K_PLOT_AREA_SELECT_APPEND_INCLUDED;
	static dword K_PLOT_AREA_SELECT_REPLACE_INTERSECT;
	static dword K_PLOT_AREA_SELECT_APPEND_INTERSECT;

	// In GraphElement AREA
	static dword K_GE_AXIS_SELECT;
	static dword K_GE_AXIS_ZOOM;
	static dword K_GE_AXIS_SCROLL;

	static dword K_GE_FLOAT_RESIZE;
	static dword K_GE_FLOAT_MOVE;
	
	static void Reset();
};

// int event, Point p, int zdelta, dword keyflags
#define TEST_GC_KEYS( keyflags, MASKS)  ( ((keyflags) & ~((dword)(K_MOUSEMIDDLE|K_MOUSELEFT|K_MOUSERIGHT)) ) == (MASKS) )
#define TEST_GC_EVENT_KEYS( keyflags, MOUSE_SIDE, MOUSE_ACTION)  ( ((keyflags) & ~((dword)(K_MOUSEMIDDLE|K_MOUSELEFT|K_MOUSERIGHT)) ) == (MASKS) )


// inline bool TEST_GC_KEYS( dword keyflags, dword MASKS)  { return ( ((keyflags) & ~((dword)(K_MOUSEMIDDLE|K_MOUSELEFT|K_MOUSERIGHT)) ) == (MASKS) ); }
// inline bool TEST_GC_EVENT_KEYS( int event, int evtMask, dword keyflags, dword keyMask)  { return ( ((keyflags) & ~((dword)(K_MOUSEMIDDLE|K_MOUSELEFT|K_MOUSERIGHT)) ) == (keyMask) ); }

#define TEST_GC_MOUSEnKEYS( keyflags, MASKS)  ( keyflags == (MASKS) )





// ============================================================================================
//                        LOOP DELEGATION CLASS
// ============================================================================================

class GraphCtrlLooper : public LocalLoop {
	private:
	Image cursorImg;
	virtual void  LeftUp(PointScreen, dword)          { EndLoop(); }
	virtual void  RightUp(PointScreen, dword)         { EndLoop(); }
	virtual void  MouseMove(PointScreen p, dword f)   { WhenMouseMove(p, f); };
	virtual Image CursorImage(PointScreen p, dword keyflags) {
		if (cursorImg.IsNullInstance()) cursorImg = GetMaster().CursorImage(p,keyflags);
		return cursorImg;
	}
	
	virtual void  Paint(Draw& w) {
		GetMaster().Paint(w);
	}
	
	public:
	void SetCursorImg(Image img) { cursorImg = img; }
	GraphCtrlLooper(Ctrl& master) {
		SetMaster(master);
	}

	GraphCtrlLooper(Ctrl& master, Image img) {
		cursorImg = img;
		SetMaster(master);
	}
	
	GraphDraw_ns::MouseLocalLoopCB WhenMouseMove;
};




void SaveImageToFile(String fileName, const Image& img);

// ============================
//    GraphCtrl_Base   CLASS
// ============================
typedef GraphDraw_ns::GraphElement* (GraphDraw_ns::GraphElement::*mouseCallBack)(PointScreen,dword);

class CH_GraphCtrl_Base {
	public:
		struct StyleGC : ChStyle<StyleGC> {
			struct {
				Value    tabBody;
				struct {
					Value    style;
					int      height;
				} separator;
				int      LargeSepDist;
				int      SmallSepDist;
			} propDlg;
			struct {
				Color lineColor;
				int   lineWidth;
				Color textColor;
				Value textBackGnd;
				// GraphCtrlImg::MEASURE_BACKGND(
			} measureTool;
		};
	
		static const StyleGC& StyleGCDefault();
		
		CH_GraphCtrl_Base() {
			styleGC = &StyleGCDefault();
		}
	
	protected:
	const StyleGC *styleGC;

};

template<class TYPES, class DERIVED, class GRAPHDRAW_BASE_CLASS >
class GraphCtrl_Base :  public GRAPHDRAW_BASE_CLASS, public Ctrl, public CH_GraphCtrl_Base
{
	public:
	typedef GraphCtrl_Base<TYPES, DERIVED, GRAPHDRAW_BASE_CLASS> CLASSNAME;

	private:
	typedef GRAPHDRAW_BASE_CLASS _B;

	Image CaptureMouseMove_cursorImage;
	PointScreen prevMousePoint;
	PointScreen selectOriginPoint, selectEndPoint;
	int copyRatio;
	int autoWaitCursor_paint;
	int autoWaitCursor_saveClipBoard;
	int autoWaitCursor_saveToFile;
	bool useLocalSelectLoop;
	bool keepAspectRatio; // X & Y ration is kept constant
	bool isXZoomAllowed;
	bool isYZoomAllowed;
	bool isXScrollAllowed;
	bool isYScrollAllowed;
	bool isZoomFromAxisAllowed;
	bool isScrollFromAxisAllowed;
	bool isZoomFromGraphAllowed;
	bool isZoomFromGraphCenteredOnMouse;
	bool isScrollFromGraphAllowed;
	bool isMeasureAllowed;
	bool drawFocus;
	

	Callback1<Bar&> WhenBar;
	
	GraphDraw_ns::GraphElement* currElement;
	
	public:

	GraphCtrl_Base()
	: copyRatio(3)
	, autoWaitCursor_paint(0)
	, autoWaitCursor_saveClipBoard(0)
	, autoWaitCursor_saveToFile(0)
	, useLocalSelectLoop(true)
	, keepAspectRatio(false)
	, isXZoomAllowed(true)
	, isYZoomAllowed(true)
	, isXScrollAllowed(true)
	, isYScrollAllowed(true)
	, isZoomFromAxisAllowed(true)
	, isScrollFromAxisAllowed(true)
	, isZoomFromGraphAllowed(true)
	, isZoomFromGraphCenteredOnMouse(true)
	, isScrollFromGraphAllowed(true)
	, isMeasureAllowed(true)
	, drawFocus(false)
	, WhenBar( THISBACK(ContextMenu) )
	, currElement(0)
	{
		SetModify();
		_B::setScreenSize( GetSize() );
	}
	
	virtual ~GraphCtrl_Base() {}
	
	private:
	GraphCtrl_Base(const GraphCtrl_Base& p)
	: _B(p)
	, copyRatio(p.copyRatio)
	, autoWaitCursor_paint(0)
	, autoWaitCursor_saveClipBoard(0)
	, autoWaitCursor_saveToFile(0)
	, useLocalSelectLoop(true)
	, keepAspectRatio(false)
	, isXZoomAllowed(true)
	, isYZoomAllowed(true)
	, isXScrollAllowed(true)
	, isYScrollAllowed(true)
	, isZoomFromAxisAllowed(true)
	, isScrollFromAxisAllowed(true)
	, isZoomFromGraphAllowed(true)
	, isZoomFromGraphCenteredOnMouse(true)
	, isScrollFromGraphAllowed(true)
	, isMeasureAllowed(true)
	, drawFocus(false)
	, WhenBar( THISBACK(ContextMenu) )
	, currElement(0)
	{
		SetModify();
		_B::setScreenSize( GetSize() );
	}

	public:
	virtual Value GetParentCtrl() {
		return RawToValue(static_cast<Ctrl*>(this));
	}


	virtual void SetStyleGC(const StyleGC& s) {
		styleGC = &s;
		_B::ClearPlotDrawImg();
		_B::ClearCtrlBackGndImg();
	}

	virtual void SetStyleGD(const typename _B::StyleGD& s) {
		_B::SetStyleGD(s);
		if ( s.ctrlBckgndStyle.IsNull()) {
			Transparent();
		}
		else if (s.ctrlBckgndStyle.template Is<Image>() ) {
			const Image& img = s.ctrlBckgndStyle.template To<Image>();
			if ( img.GetKind() == IMAGE_ALPHA) Transparent();
			else NoTransparent();
		}
		else
			NoTransparent();

	}

	virtual void SetGDModify() { SetModify(); }
	
	virtual void Refresh() {
		_B::updateSizes();
		Ctrl::Refresh();
	};


	protected:
	void LayoutRefresh() {
		_B::_doFastPaint = false;
		Ctrl::Refresh();
	}
	
	void ScheduleFullRefresh() {
		enum { 
			TIMEID_LAYOUT_REFRESH = Ctrl::TIMEID_COUNT,
		    TIMEID_COUNT
		};
		SetTimeCallback(300, THISBACK(LayoutRefresh), TIMEID_LAYOUT_REFRESH );
	}
	
	public:
	virtual void Layout() {
		_B::_doFastPaint = true;
		SetModify();
		ScheduleFullRefresh();
	}

	DERIVED& UseLocalSelectLoop(bool p = true) {
		useLocalSelectLoop = p;
		return *static_cast<DERIVED*>(this);
	}


	DERIVED& DrawFocus(bool p = true) {
		drawFocus = p ;
		return *static_cast<DERIVED*>(this);
	}

	virtual void DrawFocus(Draw& w) {
		Upp::DrawFocus(w, RectScreen(GetSize()).Deflated(5));
	}

	private:
	void UpdateScrollZoomAuthorisations() {
		for (CoordinateConverter* xcc : _B::_xConverters) {
			xcc->AllowZoom(isXZoomAllowed);
			xcc->AllowScroll(isXScrollAllowed);
			xcc->AllowAxisZoom(isZoomFromAxisAllowed );
			xcc->AllowAxisScroll(isScrollFromAxisAllowed );
		}

		for (CoordinateConverter* ycc : _B::_yConverters) {
			ycc->AllowZoom(isYZoomAllowed );
			ycc->AllowScroll(isYScrollAllowed );
			ycc->AllowAxisZoom(isZoomFromAxisAllowed );
			ycc->AllowAxisScroll(isScrollFromAxisAllowed );
		}
	}
	public:
	
	
	DERIVED& SetZoomOnCursor(bool p = true) {
		isZoomFromGraphCenteredOnMouse= p;
		return *static_cast<DERIVED*>(this);
	}

	DERIVED& DisableGraphZoom(bool p = false) {
		isZoomFromGraphAllowed= !p;
		return *static_cast<DERIVED*>(this);
	}

	DERIVED& DisableGraphScroll(bool p = false) {
		isScrollFromGraphAllowed= !p;
		return *static_cast<DERIVED*>(this);
	}


	DERIVED& SetZoomProportional(bool p = true) {
		keepAspectRatio = p;
		UpdateScrollZoomAuthorisations();
		return *static_cast<DERIVED*>(this);
	}

	DERIVED& DisableAxisZoom(bool p = false) {
		isZoomFromAxisAllowed= !p;
		UpdateScrollZoomAuthorisations();
		return *static_cast<DERIVED*>(this);
	}

	DERIVED& DisableXZoom(bool p = false) {
		isXZoomAllowed = !p;
		UpdateScrollZoomAuthorisations();
		return *static_cast<DERIVED*>(this);
	}

	DERIVED& DisableYZoom(bool p = false) {
		isYZoomAllowed = !p;
		UpdateScrollZoomAuthorisations();
		return *static_cast<DERIVED*>(this);
	}

	DERIVED& DisableAxisScroll(bool p = false) {
		isScrollFromAxisAllowed = !p;
		UpdateScrollZoomAuthorisations();
		return *static_cast<DERIVED*>(this);
	}

	DERIVED& DisableXScroll(bool p = false) {
		isXScrollAllowed = !p;
		UpdateScrollZoomAuthorisations();
		return *static_cast<DERIVED*>(this);
	}

	DERIVED& DisableYScroll(bool p = false) {
		isYScrollAllowed = !p;
		UpdateScrollZoomAuthorisations();
		return *static_cast<DERIVED*>(this);
	}
	
	DERIVED& DisableMeasure(bool p = false) {
		isMeasureAllowed = !p;
		return *static_cast<DERIVED*>(this);
	}


	inline bool IsKeepAspectRatio()              { return  (keepAspectRatio        &&  isXZoomAllowed && isYZoomAllowed); }
	inline bool IsZoomFromGraphEnabled()         { return (isZoomFromGraphAllowed && (isXZoomAllowed || isYZoomAllowed)); }
	inline bool IsZoomFromGraphCenteredOnMouse() { return isZoomFromGraphCenteredOnMouse; }
	inline bool IsScrollFromGraphEnabled()       { return (isScrollFromGraphAllowed && (isXScrollAllowed || isYScrollAllowed)); }
	inline bool IsMeasureAllowed()               { return isMeasureAllowed; }


	virtual void AddXConverter(GraphDraw_ns::CoordinateConverter* conv) {
		_B::AddXConverter(conv);
		conv->AllowScroll(isXScrollAllowed);
		conv->AllowZoom(isXZoomAllowed);
	}

	virtual void AddYConverter(GraphDraw_ns::CoordinateConverter* conv) {
		_B::AddYConverter(conv);
		conv->AllowScroll(isYScrollAllowed);
		conv->AllowZoom(isYZoomAllowed);
	}

	// Refresh called from child
	virtual void RefreshFromChild( GraphDraw_ns::RefreshStrategy strategy ) {
//		RLOGBLOCK_STR( _B::debugTrace, "GraphCtrl_Base::RefreshFromChild(" << this << ")");
		if      (strategy == GraphDraw_ns::REFRESH_DEFAULT) _B::updateSizes();
		else if (strategy == GraphDraw_ns::REFRESH_FAST)    _B::_doFastPaint = true;
		else if (strategy == GraphDraw_ns::REFRESH_FULL)    _B::ClearPlotDrawImg();
		// else   REFRESH_KEEP_DATA
		SetModify();
		Refresh();
	};

	void Paint2(Draw& w) {
//		RLOGBLOCK_STR( _B::debugTrace, "GraphCtrl_Base::Paint2(" << this << ")");
		_B::setScreenSize( GetSize() );
		_B::Paint(w, 1);
	}

	virtual void Paint(Draw& w) {
//		RLOGBLOCK_STR( _B::debugTrace, "GraphCtrl_Base::Paint(" << this << ")   [ FastPaint , PlotImgEmpty ] => [ " << _B::_doFastPaint << " , " << _B::_PlotDrawImage.IsEmpty() << " ]");
		if ( _B::_doFastPaint == false ) {
			if (_B::_PlotDrawImage.IsEmpty()) {
				AutoWaitCursor waitcursor(autoWaitCursor_paint);
				Paint2(w);
			}
			else {
				Paint2(w);
			}
			ClearModify();
		}
		else {
			Paint2(w);
			SetModify();
		}
		if( drawFocus && HasFocus() ) DrawFocus(w);
	}

	int GetCopyRatio() { return copyRatio; }
	
	DERIVED& SetCopyRatio(int ratio) {
		copyRatio = ratio;
		return *static_cast<DERIVED*>(this);
	}


	void SaveToClipboard()
	{
			AutoWaitCursor waitcursor(autoWaitCursor_saveClipBoard);
			Image img = _B::GetImage(copyRatio);
			WriteClipboardImage(img);
	}

	void SaveToFile(String fileName)
	{
		GuiLock __;

		if (IsNull(fileName)) {
			FileSel fs;

			fs.Type("PNG file", "*.png");
			fs.Type("JPEG file", "*.jpg");
			fs.Type("TIFF file", "*.tif");
		    if(!fs.ExecuteSaveAs(t_("Saving plot to PNG, JPEG or TIFF file"))) {
		        Exclamation(t_("Plot has not been saved"));
		        return;
		    }
	        fileName = fs;
		}
		AutoWaitCursor waitcursor(autoWaitCursor_saveToFile);
		SaveImageToFile(fileName, _B::GetImage(copyRatio));
	}
	
	
	void ShowAllSeries(bool show=true) {
		if (show==false) _B::WhenPreSelectAction();
		_B::ShowAll(show);
		if (show==false) _B::WhenPostSelectAction();
		_B::ClearPlotDrawImg();
		SetModify();
		Refresh();
	}

	void HideNonSelectedSeries(bool invertSelection=false) {
		_B::WhenPreSelectAction();
		_B::HideNonSelected(invertSelection);
		_B::WhenPostSelectAction();
		_B::ClearPlotDrawImg();
		SetModify();
		Refresh();
	}

	void ExecuteWithUndo(Callback cb) {
		if ( cb ) {
			UndoStackData undo;
			undo.undoAction << _B::MakeRestoreGraphSizeCB();
			cb();
			undo.redoAction << _B::MakeRestoreGraphSizeCB();
			_B::AddUndoAction(undo);
			_B::UpdateAllLinks();
		}
	}

	void UndoWithLinks() { _B::Undo(); _B::ForceUpdateAllLinks(); }
	void RedoWithLinks() { _B::Redo(); _B::ForceUpdateAllLinks(); }



	protected:

	template <class ELEMENT, class ESTYLE>
	void AddGEPropertiesTab(GEPropertiesDlgInterface::VList& elemPropDlgList, TabCtrl& tabs, const String title
	                      , ELEMENT& e1, ESTYLE& st1)
	{
		if ( ! ( _B::IsDisabledGE(e1) ) ) {
			PropertiesTabBase* dlg = new PropertiesTabBase();
			dlg->SizePos();
			int yOffset = 0;
			dlg->AddSubCElement(styleGC->propDlg.SmallSepDist, yOffset, e1);
			dlg->AddSubElement (styleGC->propDlg.SmallSepDist, yOffset, e1, st1);

			if ( dlg->GetCountSubElement() > 0 ) {
				elemPropDlgList.Add(dlg);
				tabs.Add( *dlg, title );
			}
			else {
				delete dlg;
			}
		}
	}

	template <class ELEMENT1, class ESTYLE1, class ELEMENT2, class ESTYLE2>
	void AddGEPropertiesTab(GEPropertiesDlgInterface::VList& elemPropDlgList, TabCtrl& tabs, const String title
	                      , ELEMENT1& e1, ESTYLE1& st1
	                      , ELEMENT2& e2, ESTYLE2& st2)
	{
		if ( ! ( _B::IsDisabledGE(e1) && _B::IsDisabledGE(e2)) ) {
			PropertiesTabBase* dlg = new PropertiesTabBase();
			dlg->SizePos();
			int yOffset = 0;
			int sepDist   = styleGC->propDlg.SmallSepDist; // first separation distance is small
			int sepHeight = 0; //No separator for first GE
			if (!_B::IsDisabledGE(e1)) {
				dlg->AddSubCElement(sepDist                      , yOffset, e1, sepHeight);
				dlg->AddSubElement (styleGC->propDlg.SmallSepDist, yOffset, e1, st1);
				sepDist = styleGC->propDlg.LargeSepDist;
				sepHeight = styleGC->propDlg.separator.height;
			}
			if (!_B::IsDisabledGE(e2)) {
				dlg->AddSubCElement(sepDist                      , yOffset, e2, sepHeight);
				dlg->AddSubElement (styleGC->propDlg.SmallSepDist, yOffset, e2, st2);
				sepDist = styleGC->propDlg.LargeSepDist;
				sepHeight = styleGC->propDlg.separator.height;
			}

			if ( dlg->GetCountSubElement() > 0 ) {
				elemPropDlgList.Add(dlg);
				tabs.Add( *dlg, title );
			}
			else {
				delete dlg;
			}
		}
	}

	template <class ELEMENT1, class ESTYLE1, class ELEMENT2, class ESTYLE2, class ELEMENT3, class ESTYLE3>
	void AddGEPropertiesTab(GEPropertiesDlgInterface::VList& elemPropDlgList, TabCtrl& tabs, const String title
	                      , ELEMENT1& e1, ESTYLE1& st1
	                      , ELEMENT2& e2, ESTYLE2& st2
	                      , ELEMENT3& e3, ESTYLE3& st3)
	{
		if ( ! ( _B::IsDisabledGE(e1) && _B::IsDisabledGE(e2) && _B::IsDisabledGE(e3) ) ) {
			PropertiesTabBase* dlg = new PropertiesTabBase();
			dlg->SizePos();
			int yOffset = 0;
			int sepDist   = styleGC->propDlg.SmallSepDist; // first separation distance is small
			int sepHeight = 0; //No separator for first GE
			if (!_B::IsDisabledGE(e1)) {
				dlg->AddSubCElement(sepDist                  , yOffset, e1, sepHeight);
				dlg->AddSubElement (styleGC->propDlg.SmallSepDist, yOffset, e1, st1);
				sepDist = styleGC->propDlg.LargeSepDist;
				sepHeight = styleGC->propDlg.separator.height;
			}
			if (!_B::IsDisabledGE(e2)) {
				dlg->AddSubCElement(sepDist                  , yOffset, e2, sepHeight);
				dlg->AddSubElement (styleGC->propDlg.SmallSepDist, yOffset, e2, st2);
				sepDist = styleGC->propDlg.LargeSepDist;
				sepHeight = styleGC->propDlg.separator.height;
			}
			if (!_B::IsDisabledGE(e3)) {
				dlg->AddSubCElement(sepDist                  , yOffset, e3, sepHeight);
				dlg->AddSubElement (styleGC->propDlg.SmallSepDist, yOffset, e3, st3);
				sepDist = styleGC->propDlg.LargeSepDist;
			}

			if ( dlg->GetCountSubElement() > 0 ) {
				elemPropDlgList.Add(dlg);
				tabs.Add( *dlg, title );
			}
			else {
				delete dlg;
			}
		}
	}

	template <class ELEMENT1, class ESTYLE1, class ELEMENT2, class ESTYLE2, class ELEMENT3, class ESTYLE3, class ELEMENT4, class ESTYLE4>
	void AddGEPropertiesTab(GEPropertiesDlgInterface::VList& elemPropDlgList, TabCtrl& tabs, const String title
	                      , ELEMENT1& e1, ESTYLE1& st1
	                      , ELEMENT2& e2, ESTYLE2& st2
	                      , ELEMENT3& e3, ESTYLE3& st3
	                      , ELEMENT4& e4, ESTYLE4& st4)
	{
		if ( ! ( _B::IsDisabledGE(e1) && _B::IsDisabledGE(e2) && _B::IsDisabledGE(e3) && _B::IsDisabledGE(e4) ) ) {
			PropertiesTabBase* dlg = new PropertiesTabBase();
			dlg->SizePos();
			int yOffset = 0;
			int sepDist   = styleGC->propDlg.SmallSepDist; // first separation distance is small
			int sepHeight = 0; //No separator for first GE
			if (!_B::IsDisabledGE(e1)) {
				dlg->AddSubCElement(sepDist                  , yOffset, e1, sepHeight);
				dlg->AddSubElement (styleGC->propDlg.SmallSepDist, yOffset, e1, st1);
				sepDist = styleGC->propDlg.LargeSepDist;
				sepHeight = styleGC->propDlg.separator.height;
			}
			if (!_B::IsDisabledGE(e2)) {
				dlg->AddSubCElement(sepDist                  , yOffset, e2, sepHeight);
				dlg->AddSubElement (styleGC->propDlg.SmallSepDist, yOffset, e2, st2);
				sepDist = styleGC->propDlg.LargeSepDist;
				sepHeight = styleGC->propDlg.separator.height;
			}
			if (!_B::IsDisabledGE(e3)) {
				dlg->AddSubCElement(sepDist                  , yOffset, e3, sepHeight);
				dlg->AddSubElement (styleGC->propDlg.SmallSepDist, yOffset, e3, st3);
				sepDist = styleGC->propDlg.LargeSepDist;
				sepHeight = styleGC->propDlg.separator.height;
			}
			if (!_B::IsDisabledGE(e4)) {
				dlg->AddSubCElement(sepDist                  , yOffset, e4, sepHeight);
				dlg->AddSubElement (styleGC->propDlg.SmallSepDist, yOffset, e4, st4);
				sepDist = styleGC->propDlg.LargeSepDist;
			}

			if ( dlg->GetCountSubElement() > 0 ) {
				elemPropDlgList.Add(dlg);
				tabs.Add( *dlg, title );
			}
			else {
				delete dlg;
			}
		}
	}

	public:

	virtual void OpenGraphPropertiesDlg()
	{
		DERIVED& der = *static_cast<DERIVED*>(this);
		
		typename DERIVED::Style styl = der.GetStyle(); // make a local copy of current GraphCtrl style
		hash_t hash1 = memhash(&styl, sizeof(styl) );
		GEPropertiesDlgInterface::VList elemPropDlgList;
		WithGraphPropertiesLayout<TopWindow> dlg;
		CtrlLayoutOKCancel(dlg, t_("Properties") );
		dlg.Sizeable();
		
		TabCtrl::Style tabStyle = TabCtrl::StyleDefault();
		tabStyle.body = styl.gcStyle.propDlg.tabBody;
		if ( tabStyle.body.Is<Image>()) {
			const Image& img = tabStyle.body.To<Image>();
			if (img.GetKind() == IMAGE_ALPHA) dlg.tabs.Transparent();
		}
		dlg.tabs.SetStyle(tabStyle);
		
		GSeriesCtrlDlg gseriesDlg( _B::GetGSeries(), styl.gdStyle );
		gseriesDlg.SizePos();
		if (_B::GetGSeries().GetCount()>0) {
			dlg.tabs.Add(gseriesDlg, t_("Series"));
		}

		// Add TABs  for ALL GraphElements
		der.AddAllPropertiesTabs(elemPropDlgList, dlg.tabs, styl);

		if( dlg.Execute() == IDOK) {
			gseriesDlg.Retrieve();
			for( GEPropertiesDlgInterface* epi : elemPropDlgList) {
				epi->Retrieve();
			}
			hash_t hash2 = memhash( &styl, sizeof(styl) );
			
			bool needRefresh = false;
			if ( gseriesDlg.IsModified() ) // GraphSeries Style has been modified
			{
				needRefresh = true;
			}
			RDUMP(needRefresh);

			if (hash1 != hash2 ) // GraphElement Style has been modified
			{
				_B::template GetLocalChStyle<typename DERIVED::Style>() = styl;
				needRefresh = true;
			}
			
			if (needRefresh == true) RefreshFromChild( GraphDraw_ns::REFRESH_FULL );
		}
		else {
			gseriesDlg.RevertChanges();
		}

		for( GEPropertiesDlgInterface* epi : elemPropDlgList) {
			delete(epi);
		}
	}
	

	void ScrollXOnKey(double scrollFactor) {
		_B::ScrollX( (TypeScreenCoord)(scrollFactor * abs( _B::GetXCoordConverter(0).getScreenRange())), true);
	}
	
	void ScrollYOnKey(double scrollFactor) {
		_B::ScrollY( (TypeScreenCoord)(scrollFactor * abs(_B::GetYCoordConverter(0).getScreenRange())), true);
	}
	
	virtual void ZoomX(TypeScreenCoord left, TypeScreenCoord right)
	{
		if ( IsKeepAspectRatio() ) {
			double zoom = -((right-left)-_B::_plotRect.GetWidth())/(double)_B::_plotRect.GetWidth();
			TypeScreenCoord yDelta = TypeScreenCoord((_B::_plotRect.GetHeight() * zoom + .5)/2.0);
			RectScreen r( left,
			              yDelta,
			              right,
			              _B::_plotRect.GetHeight() -yDelta );
			_B::ZoomOnRect(r);
		}
		else {
			_B::ZoomX(left, right);
		}
	}

	virtual void ZoomY(TypeScreenCoord top, TypeScreenCoord bottom)
	{
		if ( IsKeepAspectRatio() ) {
			double zoom = -((bottom-top)-_B::_plotRect.GetHeight())/(double)_B::_plotRect.GetHeight();
			TypeScreenCoord xDelta = TypeScreenCoord((_B::_plotRect.GetWidth()  * zoom + .5)/2.0);
			RectScreen r( xDelta,
			              top,
			              _B::_plotRect.GetWidth() - xDelta,
			              bottom );
			_B::ZoomOnRect(r);
		}
		else {
			_B::ZoomY(top, bottom);
		}
	}


	void ContextMenu(Bar& bar)
	{
		bar.Add( t_("Copy to clipboard"), GraphCtrlImg::COPY(), THISBACK2(PostCallback, THISBACK(SaveToClipboard), 0)).Key(K_CTRL_C);
		bar.Add( t_("Save to file"), GraphCtrlImg::SAVE(), THISBACK1(SaveToFile, Null));

		bar.Separator();

		bar.Add( _B::_undoManager.CanUndo(), t_("Undo"), THISBACK(UndoWithLinks)).Key(GraphCtrl_Keys::K_KBD_UNDO);
		bar.Add( _B::_undoManager.CanRedo(), t_("Redo"), THISBACK(RedoWithLinks)).Key(GraphCtrl_Keys::K_KBD_REDO);

		bar.Separator();

		bar.Add( IsScrollFromGraphEnabled() && IsZoomFromGraphEnabled(), t_("Fit To Data"),         THISBACK1(ExecuteWithUndo, THISBACK1(_B::FitToData, GraphDraw_ns::ALL_SERIES)));
		bar.Add( IsScrollFromGraphEnabled() && IsZoomFromGraphEnabled(), t_("Fit To Visible Data"), THISBACK1(ExecuteWithUndo, THISBACK1(_B::FitToData, GraphDraw_ns::VISIBLE_SERIES_ONLY)));

		bar.Separator();
		
		bar.Add( isScrollFromGraphAllowed && isXScrollAllowed, t_("Scroll left"), THISBACK1(ExecuteWithUndo, THISBACK1( ScrollXOnKey,  .1) )).Key(GraphCtrl_Keys::K_KBD_LEFT_SCROLL);
		bar.Add( isScrollFromGraphAllowed && isXScrollAllowed, t_("Scroll right"),THISBACK1(ExecuteWithUndo, THISBACK1( ScrollXOnKey, -.1) )).Key(GraphCtrl_Keys::K_KBD_RIGHT_SCROLL);
		bar.Add( isScrollFromGraphAllowed && isYScrollAllowed, t_("Scroll up"),   THISBACK1(ExecuteWithUndo, THISBACK1( ScrollYOnKey,  .1) )).Key(GraphCtrl_Keys::K_KBD_UP_SCROLL);
		bar.Add( isScrollFromGraphAllowed && isYScrollAllowed, t_("Scroll down"), THISBACK1(ExecuteWithUndo, THISBACK1( ScrollYOnKey, -.1) )).Key(GraphCtrl_Keys::K_KBD_DOWN_SCROLL);
		bar.Separator();
		
		bar.Add( t_("Properties"), THISBACK(OpenGraphPropertiesDlg) );

		bar.Separator();
		
		bar.Add( t_("Show ALL"), THISBACK1(ShowAllSeries, true) );
		bar.Add( t_("Hide ALL"), THISBACK1(ShowAllSeries, false) );
		bar.Add( t_("Show only Selected series"), THISBACK1(HideNonSelectedSeries, false) );
		bar.Add( t_("Hide all Selected series"),  THISBACK1(HideNonSelectedSeries, true) );
	}

	virtual void DoLocalLoop(GraphDraw_ns::MouseLocalLoopCB CB, Image cursorOverrideImg = Null)
	{
		GraphCtrlLooper looper(*this, cursorOverrideImg);
		looper.WhenMouseMove << CB;
		looper.Run();
	}

	// GraphSerie  management
	template<class RESULT, class CBCK>
	bool ProcessMouseCB_GraphSerie(PointScreen p, dword keyflags, CBCK cbck, RESULT& output ,RESULT defaultRes = 0)
	{
		unsigned int index;
		p -= _B::_plotRect.TopLeft();
		for (GraphSerieDecorator& gsd : _B::graphSeriesProxyList) {
			if (gsd.IsCtrlable() && gsd.Contains(p, index) ) {
				if ((gsd.*cbck)(index, p, keyflags, output)) return true;
			}
		}
		return false;
	}


	template<class CBCK>
	bool ProcessMouseCB_GraphSerie(PointScreen p, dword keyflags, CBCK cbck)
	{
		unsigned int index;
		p -= _B::_plotRect.TopLeft();
		for (GraphSerieDecorator& gsd : _B::graphSeriesProxyList) {
			if (gsd.IsCtrlable() && gsd.Contains(p, index) ) {
				if ( (gsd.*cbck)(index, p, keyflags) ) return true;
			}
		}
		return false;
	}

	// GraphElements  management
	template<class RESULT, class CBCK>
	bool ProcessMouseCB_Elmt(PointScreen p, dword keyflags, CBCK cbck, RESULT& output ,RESULT defaultRes = 0) // TODO  prendre en compte 'defaultRes' ou le supprimer !
	{
		// process GraphElements in inverse order of their drawing
		// Process FLOAT GraphElements first
		for (int j = _B::_drawElements.GetCount()-1; j >= 0 ; --j)
		{
			if ( !_B::_drawElements[j]->IsHidden() ) {
				if ( _B::_drawElements[j]->IsFloat() ) {
					if (_B::_drawElements[j]->Contains(p)) {
						output = ((_B::_drawElements[j]->*cbck)(p, keyflags));
						return true;
					}
				}
			}
		}

		// Process NON FLOAT GraphElements after
		for (int j = _B::_drawElements.GetCount()-1; j >= 0 ; --j)
		{
			if ( !_B::_drawElements[j]->IsHidden() ) {
				if ( !_B::_drawElements[j]->IsFloat() ) {
					if (_B::_drawElements[j]->Contains(p)) {
						output = ((_B::_drawElements[j]->*cbck)(p, keyflags));
						return true;
					}
				}
			}
		}
		return false; 
	}

	
	template<class CBCK>
	bool ProcessMouseCB_Elmt(PointScreen p, dword keyflags, CBCK cbck)
	{
		// process GraphElements in inverse order of their drawing
		// Process FLOAT GraphElements first
		for (int j = _B::_drawElements.GetCount()-1; j >= 0 ; --j)
		{
			if ( !_B::_drawElements[j]->IsHidden() ) {
				if ( _B::_drawElements[j]->IsFloat() ) {
					if (_B::_drawElements[j]->Contains(p)) {
						((_B::_drawElements[j]->*cbck)(p, keyflags));
						return true;
					}
				}
			}
		}
		// Process NON FLOAT GraphElements after
		for (int j = _B::_drawElements.GetCount()-1; j >= 0 ; --j)
		{
			if ( !_B::_drawElements[j]->IsHidden() ) {
				if ( !_B::_drawElements[j]->IsFloat() ) {
					if (_B::_drawElements[j]->Contains(p)) {
						((_B::_drawElements[j]->*cbck)(p, keyflags));
						return true;
					}
				}
			}
		}
		return false;
	}

	void GotFocus() {
		Refresh();
	}
	
	void LostFocus() {
		Refresh();
	}
	
	private:
	void DoMouseSelectZoom(PointScreen p) {
		if (!IsZoomFromGraphEnabled()) return;
		UndoStackData undo;
		undo.undoAction << _B::MakeRestoreGraphSizeCB(); // PREV size before  ZOOM or SCROLL
		if (useLocalSelectLoop) {
			selectEndPoint = selectOriginPoint = p - _B::_plotRect.TopLeft();
			DoLocalLoop( THISBACK(LoopedPlotZoomSelectCB) );
			_B::ZoomOnRect( _B::_selectRect );
			_B::_selectRect.Clear();
		}
		else {
			// use RectTraker instead of LocalSelectLoop (but select box Styling is not used)
			RectTracker tracker(*this);
			RectScreen selectedZoomArea = tracker.Track( RectfC(p.x,p.y,0,0), ALIGN_NULL, ALIGN_NULL) - _B::_plotRect.TopLeft();
			if ( !selectedZoomArea.IsEmpty() ) {
				_B::ZoomOnRect( selectedZoomArea );
				Refresh();
			}
		}
		if ( p != GetMouseViewPos() ) {
			_B::UpdateAllLinks();
			undo.redoAction << _B::MakeRestoreGraphSizeCB(); // NEW size after  ZOOM
			_B::AddUndoAction(undo);
		}
	}

	void DoMouseMeasure(PointScreen p) {
		if (!isMeasureAllowed) return;
		selectEndPoint = selectOriginPoint = p - _B::_plotRect.TopLeft();
		_B::_isMeasureToolAcive = true;
		DoLocalLoop( THISBACK(LoopedPlotMeasureCB), GraphCtrlImg::MEASURE_TOOL() );
		_B::_isMeasureToolAcive = false;
	}

	void DoMouseSelectData(PointScreen p, bool intersect, bool append) {
//		UndoStackData undo;
//		undo.undoAction << _B::MakeRestoreGraphSizeCB(); // PREV size before  ZOOM or SCROLL
		_B::WhenPreSelectAction();
		if (useLocalSelectLoop) {
			selectEndPoint = selectOriginPoint = p - _B::_plotRect.TopLeft();
			DoLocalLoop( THISBACK(LoopedPlotSelectCB) );
			_B::SelectData( _B::_selectRect, intersect, append );
			_B::_selectRect.Clear();
		}
		else {
			RectTracker tracker(*this);
			RectScreen selectArea = tracker.Track( RectfC(p.x,p.y,0,0), ALIGN_NULL, ALIGN_NULL) - _B::_plotRect.TopLeft();
			if ( !selectArea.IsEmpty() ) {
				_B::SelectData( selectArea, intersect, append );
				Refresh();
			}
		}
		_B::WhenPostSelectAction();
//		if ( p != GetMouseViewPos() ) {
//			_B::UpdateAllLinks();
//			undo.redoAction << _B::MakeRestoreGraphSizeCB(); // NEW size after  ZOOM
//			_B::AddUndoAction(undo);
//		}
	}

	void DoMouseScroll(PointScreen p) {
		if (!IsScrollFromGraphEnabled()) return;
		UndoStackData undo;
		undo.undoAction << _B::MakeRestoreGraphSizeCB(); // PREV size before  ZOOM or SCROLL
		DoLocalLoop( THISBACK(LoopedPlotScrollCB) );
		if ( p != GetMouseViewPos() ) {
			_B::UpdateAllLinks();
			undo.redoAction << _B::MakeRestoreGraphSizeCB(); // NEW size after  MOVE
			_B::AddUndoAction(undo);
		}
	}
	
	public:
	#define ProcessMouseEventCommonSeriesCode(MOUSE_EVT) \
		if ( ProcessMouseCB_Elmt(p, keyflags, &GraphDraw_ns::GraphElement::MOUSE_EVT) )          return;\
		if ( ProcessMouseCB_GraphSerie(p, keyflags, &GraphDraw_ns::GraphSerieDecorator::MOUSE_EVT) ) return;
	
	
	// =====================
	//   -- LEFT -- MOUSE BUTTON
	// =====================
	virtual Image MouseEvent(int event, Point p, int zdelta, dword keyflags) {
		
//		prevMousePoint = p;
//		ProcessMouseEventCommonSeriesCode(LeftDrag);
//		if ( _B::_plotRect.Contains(p) ) {
//			if (      TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_ZOOM) )                            DoMouseSelectZoom(p);
//			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_SCROLL ) )                              DoMouseScroll(p);
//			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_MEASURE_TOOL ) )                   DoMouseMeasure(p);
//			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_REPLACE_INCLUDED ) )   DoMouseSelectData(p, false, false);
//			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_APPEND_INCLUDED ) )    DoMouseSelectData(p, false, true);
//			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_REPLACE_INTERSECT ) )  DoMouseSelectData(p, true,  false);
//			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_APPEND_INTERSECT ) )   DoMouseSelectData(p, true,  true);
//		}

//		LLOG("MouseEvent " << UPP::Name(this) << " " << FormatIntHex(event));
//		switch(event) {
//			case MOUSEENTER:
//				MouseEnter(p, keyflags);
//				break;
//			case MOUSEMOVE:
//				MouseMove(p, keyflags);
//				break;
//			case LEFTDOWN:
//				LeftDown(p, keyflags);
//				break;
//			case LEFTDOUBLE:
//				LeftDouble(p, keyflags);
//				break;
//			case LEFTDRAG:
//				LeftDrag(p, keyflags);
//				break;
//			case LEFTHOLD:
//				LeftHold(p, keyflags);
//				break;
//			case LEFTTRIPLE:
//				LeftTriple(p, keyflags);
//				break;
//			case LEFTREPEAT:
//				LeftRepeat(p, keyflags);
//				break;
//			case LEFTUP:
//				LeftUp(p, keyflags);
//				break;
//			case RIGHTDRAG:
//				RightDrag(p, keyflags);
//				break;
//			case RIGHTHOLD:
//				RightHold(p, keyflags);
//				break;
//			case RIGHTTRIPLE:
//				RightTriple(p, keyflags);
//				break;
//			case RIGHTDOWN:
//				RightDown(p, keyflags);
//				break;
//			case RIGHTDOUBLE:
//				RightDouble(p, keyflags);
//				break;
//			case RIGHTREPEAT:
//				RightRepeat(p, keyflags);
//				break;
//			case RIGHTUP:
//				RightUp(p, keyflags);
//				break;
//			case MIDDLEDRAG:
//				MiddleDrag(p, keyflags);
//				break;
//			case MIDDLEHOLD:
//				MiddleHold(p, keyflags);
//				break;
//			case MIDDLETRIPLE:
//				MiddleTriple(p, keyflags);
//				break;
//			case MIDDLEDOWN:
//				MiddleDown(p, keyflags);
//				break;
//			case MIDDLEDOUBLE:
//				MiddleDouble(p, keyflags);
//				break;
//			case MIDDLEREPEAT:
//				MiddleRepeat(p, keyflags);
//				break;
//			case MIDDLEUP:
//				MiddleUp(p, keyflags);
//				break;
//			case MOUSELEAVE:
//				MouseLeave();
//				break;
//			case MOUSEWHEEL:
//				MouseWheel(p, zdelta, keyflags);
//				break;
//			case MOUSEHWHEEL:
//				HorzMouseWheel(p, zdelta, keyflags);
//				break;
//			case CURSORIMAGE:
//				return CursorImage(p, keyflags);
//		}


		return Ctrl::MouseEvent(event, p, zdelta, keyflags);
	}



	virtual void LeftDown(PointScreen p, dword keyflags) {
		if(IsWantFocus() && !HasFocus() ) SetFocus();
		ProcessMouseEventCommonSeriesCode(LeftDown);
	}
	virtual void LeftUp     (PointScreen p, dword keyflags) {
		ProcessMouseEventCommonSeriesCode(LeftUp);
		if (  TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_POINT_SELECT_REPLACE)
		   || TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_POINT_SELECT_APPEND) ) {
			_B::WhenPreSelectAction();
			_B::SelectOneData(p-_B::_plotRect.TopLeft(), TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_POINT_SELECT_APPEND) );
			_B::WhenPostSelectAction();
		}
		Refresh();
	}
	virtual void LeftDouble (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(LeftDouble); }
	virtual void LeftTriple (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(LeftTriple); }
	virtual void LeftRepeat (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(LeftRepeat); }
	virtual void LeftHold   (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(LeftHold  ); }
	virtual void LeftDrag   (PointScreen p, dword keyflags) {
		prevMousePoint = p;
		ProcessMouseEventCommonSeriesCode(LeftDrag);
		if ( _B::_plotRect.Contains(p) ) {
			if (      TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_ZOOM) )                            DoMouseSelectZoom(p);
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_SCROLL ) )                              DoMouseScroll(p);
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_MEASURE_TOOL ) )                   DoMouseMeasure(p);
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_REPLACE_INCLUDED ) )   DoMouseSelectData(p, false, false);
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_APPEND_INCLUDED ) )    DoMouseSelectData(p, false, true);
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_REPLACE_INTERSECT ) )  DoMouseSelectData(p, true,  false);
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_APPEND_INTERSECT ) )   DoMouseSelectData(p, true,  true);
		}
	}


	// =====================
	//   -- RIGHT -- MOUSE BUTTON
	// =====================
	virtual void RightDown(PointScreen p, dword keyflags) {
		if( IsWantFocus() && !HasFocus() ) SetFocus();
		ProcessMouseEventCommonSeriesCode(RightDown);
		if ( _B::_plotRect.Contains(p) ) {
			MenuBar::Execute(WhenBar);
			return;
		}
	}
	virtual void RightUp     (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(RightUp    ); }
	virtual void RightDouble (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(RightDouble); }
	virtual void RightTriple (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(RightTriple); }
	virtual void RightRepeat (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(RightRepeat); }
	virtual void RightDrag   (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(RightDrag  ); }
	virtual void RightHold   (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(RightHold  ); }

	// =====================
	//   -- MIDDLE -- MOUSE BUTTON
	// =====================
	virtual void MiddleDown(PointScreen p, dword keyflags) {
		if( IsWantFocus() && !HasFocus() ) SetFocus();
		ProcessMouseEventCommonSeriesCode(MiddleDown);
		if ( _B::_plotRect.Contains(p) ) {
			// do PLOT  CENTER  at point
			return;
		}
	}
	virtual void MiddleUp     (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(MiddleUp    ); }
	virtual void MiddleDouble (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(MiddleDouble); }
	virtual void MiddleTriple (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(MiddleTriple); }
	virtual void MiddleRepeat (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(MiddleRepeat); }
	virtual void MiddleDrag   (PointScreen p, dword keyflags) { 
		ProcessMouseEventCommonSeriesCode(MiddleDrag  );
		if ( _B::_plotRect.Contains(p) ) {
			//if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_MEASURE_TOOL ) )
				DoMouseMeasure(p);
		}
	}
	virtual void MiddleHold   (PointScreen p, dword keyflags) { ProcessMouseEventCommonSeriesCode(MiddleHold  ); }

	private:
	void LoopedPlotScrollCB(PointScreen p, dword keyflags) {
		_B::_doFastPaint = true;
		if (p != prevMousePoint) {
			if ( !isXScrollAllowed ) p.x = prevMousePoint.x;
			if ( !isYScrollAllowed ) p.y = prevMousePoint.y;
			_B::Scroll(p.x-prevMousePoint.x, p.y-prevMousePoint.y);
			SetModify();
		}
		prevMousePoint = p;
		Refresh();
	}
	
	void LoopedPlotSelectCB(PointScreen p, dword keyflags) {
		selectEndPoint = p - _B::_plotRect.TopLeft();
		if (p != prevMousePoint) {
			_B::_selectRect.left   = Upp::min(selectEndPoint.x, selectOriginPoint.x);
			_B::_selectRect.right  = Upp::max(selectEndPoint.x, selectOriginPoint.x);
			_B::_selectRect.top    = Upp::min(selectEndPoint.y, selectOriginPoint.y);
			_B::_selectRect.bottom = Upp::max(selectEndPoint.y, selectOriginPoint.y);
		}
		Refresh();
	}

	void LoopedPlotMeasureCB(PointScreen p, dword keyflags) {
		selectEndPoint = p - _B::_plotRect.TopLeft();
		Refresh();
	}


	void PaintText(Draw& dw, PointScreen pt, String text, const Color color, const Font scaledFont, int scale) {
		if (!text.IsEmpty()) {
			Size sz = GraphDraw_ns::GetSmartTextSize(text, scaledFont, scale);
			GraphDraw_ns::DrawSmartText(dw, pt.x, pt.y, sz.cx, text, scaledFont, color, scale);
		}

	}

	enum MeasureTextPlacement{
		MEASURE_TEXT_RIGHT,
		MEASURE_TEXT_LEFT,
		MEASURE_TEXT_TOP,
		MEASURE_TEXT_BOTTOM
	};

	void PaintMeasureText(Draw& dw, const MeasureTextPlacement pos, const String& text, const PointScreen pt, const Color txtColor, const Font scaledFont, const Value& txtBackgnd, int scale) {
		if (!text.IsEmpty()) {
			Size sz = GraphDraw_ns::GetSmartTextSize(text, scaledFont, scale);
			Rect textRect(sz);
			if (pos==MEASURE_TEXT_RIGHT) { // draw on the right of Point
				if (!txtBackgnd.IsNull()) {
					textRect.Offset(pt.x+4, pt.y-(sz.cy/2));
					textRect.Inflate(3, 0);
					ChPaint(dw, textRect, txtBackgnd);
				}
				GraphDraw_ns::DrawSmartText(dw, pt.x+4, pt.y-(sz.cy/2), sz.cx, text, scaledFont, txtColor, scale);
			}
			else if (pos==MEASURE_TEXT_BOTTOM) { // draw under point
				if (!txtBackgnd.IsNull()) {
					textRect.Offset(pt.x-(sz.cx/2), pt.y);
					textRect.Inflate(3, 0);
					ChPaint(dw, textRect, txtBackgnd);
				}
				GraphDraw_ns::DrawSmartText(dw, pt.x-(sz.cx/2), pt.y, sz.cx, text, scaledFont, txtColor, scale);
			}
			else if (pos==MEASURE_TEXT_TOP) { // draw over point
				if (!txtBackgnd.IsNull()) {
					textRect.Offset(pt.x-(sz.cx/2), pt.y-sz.cy);
					textRect.Inflate(3, 0);
					ChPaint(dw, textRect, txtBackgnd);
				}
				GraphDraw_ns::DrawSmartText(dw, pt.x-(sz.cx/2), pt.y-sz.cy, sz.cx, text, scaledFont, txtColor, scale);
			}
		}
	}

	virtual void PaintMeasureTool(Draw& dw) {
		RectScreen rect(selectOriginPoint, selectEndPoint);
		rect.Normalize();
		Color lineColor = styleGC->measureTool.lineColor;
		int   lineWidth = styleGC->measureTool.lineWidth;

		String xDelta, yDelta;
		for (int c=0; c<_B::_xConverters.GetCount(); ++c) {
			if (c>0) xDelta << "\n";
			xDelta << "X"<< c+1 << ": " << _B::_xConverters[c]->Format( abs(_B::_xConverters[c]->toGraph(rect.right) - _B::_xConverters[c]->toGraph(rect.left) ) );
		}
		for (int c=0; c<_B::_yConverters.GetCount(); ++c) {
			if (c>0) yDelta << "\n";
			yDelta << "Y"<< c+1 << ": " << _B::_yConverters[c]->Format( abs(_B::_yConverters[c]->toGraph(rect.bottom) - _B::_yConverters[c]->toGraph(rect.top) ) );
		}
		
		if ( selectOriginPoint.y <= selectEndPoint.y ) {
			if ( selectOriginPoint.x <= selectEndPoint.x ) { // -45° (bottom right) |_
				dw.DrawLine(rect.BottomLeft(), selectEndPoint   , lineWidth, lineColor);
				dw.DrawLine(selectOriginPoint, rect.BottomLeft(), lineWidth, lineColor);
				PaintMeasureText(dw, MEASURE_TEXT_BOTTOM, xDelta, rect.BottomCenter(), styleGC->measureTool.textColor, StdFont(), styleGC->measureTool.textBackGnd, 1);
			}
			else {  // -135° (bottom left)  |-
				dw.DrawLine(selectEndPoint, rect.TopLeft()    , lineWidth, lineColor);
				dw.DrawLine(rect.TopLeft(), selectOriginPoint , lineWidth, lineColor);
				PaintMeasureText(dw, MEASURE_TEXT_TOP, xDelta, rect.TopCenter(), styleGC->measureTool.textColor, StdFont(), styleGC->measureTool.textBackGnd, 1);
			}
		}
		else { // 45° (top right) |-
			if ( selectOriginPoint.x <= selectEndPoint.x ) {
				dw.DrawLine(selectOriginPoint, rect.TopLeft(), lineWidth, lineColor);
				dw.DrawLine(rect.TopLeft(), selectEndPoint   , lineWidth, lineColor);
				PaintMeasureText(dw, MEASURE_TEXT_TOP, xDelta, rect.TopCenter(), styleGC->measureTool.textColor, StdFont(), styleGC->measureTool.textBackGnd, 1);
			}
			else { // 135° (top left) |_
				dw.DrawLine(selectEndPoint, rect.BottomLeft()    , lineWidth, lineColor);
				dw.DrawLine(rect.BottomLeft(), selectOriginPoint , lineWidth, lineColor);
				PaintMeasureText(dw, MEASURE_TEXT_BOTTOM, xDelta, rect.BottomCenter(), styleGC->measureTool.textColor, StdFont(), styleGC->measureTool.textBackGnd, 1);
			}
		}
		PaintMeasureText(dw, MEASURE_TEXT_RIGHT, yDelta, rect.CenterLeft(), styleGC->measureTool.textColor, StdFont(), styleGC->measureTool.textBackGnd, 1);
	}

	void LoopedPlotZoomSelectCB(PointScreen p, dword keyflags) { // TODO_ZOOM
		selectEndPoint = p - _B::_plotRect.TopLeft();
		if ( IsKeepAspectRatio() ) {
			float yFactor = (float)_B::_plotRect.GetHeight() / _B::_plotRect.GetWidth();
			TypeScreenCoord d = Upp::max(Upp::abs(selectEndPoint.x - selectOriginPoint.x), (TypeScreenCoord) (Upp::abs(selectEndPoint.y - selectOriginPoint.y)/yFactor) );
			if ( selectEndPoint.x > selectOriginPoint.x ) selectEndPoint.x = selectOriginPoint.x + d;
			else                                          selectEndPoint.x = selectOriginPoint.x - d;

			if ( selectEndPoint.y > selectOriginPoint.y ) selectEndPoint.y = selectOriginPoint.y + d*yFactor;
			else                                          selectEndPoint.y = selectOriginPoint.y - d*yFactor;
		}
		
		if (p != prevMousePoint) {
			_B::_selectRect.left   = Upp::min(selectEndPoint.x, selectOriginPoint.x);
			_B::_selectRect.right  = Upp::max(selectEndPoint.x, selectOriginPoint.x);
			_B::_selectRect.top    = Upp::min(selectEndPoint.y, selectOriginPoint.y);
			_B::_selectRect.bottom = Upp::max(selectEndPoint.y, selectOriginPoint.y);
		}

		if ( !isXZoomAllowed ) {
			_B::_selectRect.left = 0;
			_B::_selectRect.right = _B::_plotRect.GetWidth();
		}
		
		if ( !isYZoomAllowed ) {
			_B::_selectRect.top = 0;
			_B::_selectRect.bottom = _B::_plotRect.GetHeight();
		}

		Refresh();
	}


	public:
	virtual void MouseMove(PointScreen p, dword keyflags) {
//		RLOGBLOCK_STR( _B::debugTrace, "GraphCtrl_Base::MouseMove(" << this << ")");
		
		GraphDraw_ns::GraphElement* tmpElment = 0;
		for (GraphElement* ge : _B::_drawElements) {
			if ( !ge->IsHidden() && ge->Contains(p) ) {
					tmpElment = ge;
					break;
			}
		}
	
		if (tmpElment != currElement)
		{
			if (tmpElment) tmpElment->MouseEnter(p, keyflags);
			if (currElement) currElement->MouseLeave();
			currElement = tmpElment;
		}
		
		if ( ProcessMouseCB_Elmt(p, keyflags, &GraphDraw_ns::GraphElement::MouseMove)) {}

		if (_B::_doFastPaint) {
			// Do complete drawing when nothing special to be done ( only if needed )
			_B::_doFastPaint = false;
			Refresh();
		}
	}

	virtual void MouseLeave() {
		ScheduleFullRefresh();
	}
	
	virtual void MouseEnter(PointScreen, dword)
	{
	}

	virtual Image  CursorImage(PointScreen p, dword keyflags)
	{
		Image output;
		if ( ProcessMouseCB_Elmt<Image>(p, keyflags, &GraphDraw_ns::GraphElement::CursorImage, output, GraphDrawImg::CROSS())) {
			return output;
		}

		if ( ProcessMouseCB_GraphSerie<Image>(p, keyflags, &GraphDraw_ns::GraphSerieDecorator::CursorImage, output, GraphDrawImg::CROSS())) {
			return output;
		}
		
		if ( _B::_plotRect.Contains(p) ) {
			if      ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_ZOOM)   && IsZoomFromGraphEnabled() )  return GraphCtrlImg::ZOOM();
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_SCROLL) && IsScrollFromGraphEnabled() )     return GraphCtrlImg::SCROLL();
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_MEASURE_TOOL) && IsMeasureAllowed())   return GraphCtrlImg::MEASURE_TOOL();
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_REPLACE_INCLUDED ) )       return GraphCtrlImg::AREA_SELECT();
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_APPEND_INCLUDED ) )        return GraphCtrlImg::AREA_SELECT_APPEND();
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_REPLACE_INTERSECT ) )      return GraphCtrlImg::AREA_SELECT_INTERSECT();
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_AREA_SELECT_APPEND_INTERSECT ) )       return GraphCtrlImg::AREA_SELECT_APPEND_INTERSECT();
		}
		return GraphDrawImg::CROSS();
	}

	virtual bool Key(dword key, int repcnt) {
		if      (key == GraphCtrl_Keys::K_KBD_UNDO) { UndoWithLinks(); return true; }
		else if (key == GraphCtrl_Keys::K_KBD_REDO) { RedoWithLinks(); return true; }
		else if (key == GraphCtrl_Keys::K_KBD_SELECT_CLEAR) {
			_B::WhenPreSelectAction();
			_B::ClearSelection();
			_B::WhenPostSelectAction();
			Refresh();
			return true;
		}
		else if (key == GraphCtrl_Keys::K_KBD_SELECT_ALL) {
			_B::WhenPreSelectAction();
			_B::SelectAllData();
			_B::WhenPostSelectAction();
			Refresh();
			return true;
		}
		return MenuBar::Scan( WhenBar, key);
	}
	
	virtual bool HotKey(dword key) {
		if      (key == GraphCtrl_Keys::K_KBD_UNDO) { UndoWithLinks(); return true; }
		else if (key == GraphCtrl_Keys::K_KBD_REDO) { RedoWithLinks(); return true; }
		return Ctrl::HotKey(key);
	}
	
	virtual void MouseWheel(PointScreen p, int zdelta, dword keyflags) { // TODO_ZOOM
		// Process FLOAT elements FIRST
		for (GraphElement* ge : _B::_drawElements) {
			if ( ge->IsFloat() && ge->Contains(p) ) {
				(ge->MouseWheel)(p, zdelta, keyflags);
				return;
			}
		}
		
		// Process NON FLOAT elements
		for (GraphElement* ge : _B::_drawElements) {
			if ( !ge->IsFloat() && ge->Contains(p) ) {
				(ge->MouseWheel)(p, zdelta, keyflags);
				return;
			}
		}
		
		//Process Graph
		if ( _B::_plotRect.Contains(p) ) {
			if (  TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_PLOT_ZOOM) ) // => WHEEL ZOOM
			{
				if ( !IsZoomFromGraphEnabled() ) return;
				UndoStackData undo;
				undo.undoAction << _B::MakeRestoreGraphSizeCB(); // PREV size before  ZOOM
					p -= _B::_plotRect.TopLeft();
					if ( !isZoomFromGraphCenteredOnMouse ) p = Null;
					if (zdelta < 0) _B::ApplyInvZoomFactor(GraphCtrl_Constants::ZOOM_STEP_FACTOR, p);
					else            _B::ApplyZoomFactor(GraphCtrl_Constants::ZOOM_STEP_FACTOR, p);
					_B::_doFastPaint = true;
				undo.redoAction << _B::MakeRestoreGraphSizeCB(); // NEW size after  ZOOM
				_B::AddUndoAction(undo);
				_B::UpdateAllLinks();
			}
			return;
		}
	}
};

#endif
