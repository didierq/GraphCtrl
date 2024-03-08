#ifndef _GraphDraw_CustomSeriesGroup_h_
#define _GraphDraw_CustomSeriesGroup_h_


namespace GraphDraw_ns
{
	
	// ============================
	// GraphSeriesGroup<>   CLASS
	// ============================
	class GraphSerieDecorator : public Moveable<GraphSerieDecorator> {
		private:
			GraphSerie* gSerie;
			MCoordinateConverter mcc;
			

		public:
			GraphSerieDecorator() : gSerie(0), mcc(0,0) {}
			GraphSerieDecorator(const GraphSerieDecorator& ds) : gSerie(ds.gSerie), mcc(ds.mcc) {}
			~GraphSerieDecorator() {}
			
			
			virtual hash_t GetHashValue()            const { return gSerie->GetHashValue(); }

			void SetGraphSerie(GraphSerie* ds)             { gSerie = ds; }
			inline const GraphSerie& GetGraphSerie() const { return *gSerie; }
			inline       GraphSerie& GetGraphSerie()       { return *gSerie; }

			StyleGS_base& GetStyleGDS()                           { return gSerie->GetStyleGDS(); };
			GraphSerieEditorInterface* MakeGraphSerieEditorInfo() { return gSerie->MakeGraphSerieEditorInfo(); }

			inline void SetXCoordConverter(CoordinateConverter& c) { mcc.SetXCoordConverter(&c); }
			inline void SetXCoordConverter(CoordinateConverter* c) { mcc.SetXCoordConverter(c); }

			inline void SetYCoordConverter(CoordinateConverter& c) { mcc.SetYCoordConverter(&c); }
			inline void SetYCoordConverter(CoordinateConverter* c) { mcc.SetYCoordConverter(c); }

			inline TypeGraphCoord ToGraphX(const TypeScreenCoord p)  const { return  mcc.ToGraphX(p); }
			inline TypeGraphCoord ToGraphY(const TypeScreenCoord p)  const { return  mcc.ToGraphY(p); }
			inline PointGraph     ToGraph( const PointScreen& pt)    const { return  mcc.ToGraph(pt); }

			inline TypeScreenCoord ToScreenX(const TypeGraphCoord p) const { return mcc.ToScreenX(p); }
			inline TypeScreenCoord ToScreenY(const TypeGraphCoord p) const { return mcc.ToScreenY(p); }
			inline PointScreen     ToScreen( const PointGraph& pt)   const { return mcc.ToScreen(pt); }
			
			inline RectGraph ToGraph(const RectScreen& p) const {
				RectGraph r(ToGraphX(p.left), ToGraphY(p.top), ToGraphX(p.right), ToGraphY(p.bottom));
				r.Normalize();
				return r;
			}

			inline RectScreen ToScreen(const RectGraph& p) const {
				RectGraph r(ToScreenX(p.left), ToScreenY(p.top), ToScreenX(p.right), ToScreenY(p.bottom));
				r.Normalize();
				return r;
			}
			
			inline bool Contains(PointScreen pt, unsigned int& pIndexOut) const { return gSerie->Contains( mcc.ToGraph(pt), pIndexOut); } // return index of point which is at 'p' coord
			
			bool FitToXData(const CoordinateConverter& cc, TypeGraphCoord& v_min, TypeGraphCoord& v_max) {
				bool minMaxModified = false;
				if (gSerie->HasMinMax()) {
					if ( mcc.GetXCoordConverter() == &cc) {
						v_min = Upp::min(v_min, gSerie->MinX() );
						v_max = Upp::max(v_max, gSerie->MaxX() );
						minMaxModified = true;
					}
				}
				return minMaxModified;
			}

			bool FitToYData(const CoordinateConverter& cc, TypeGraphCoord& v_min, TypeGraphCoord& v_max) {
				bool minMaxModified = false;
				if (gSerie->HasMinMax()) {
					if ( mcc.GetYCoordConverter() == &cc) {
						v_min = Upp::min(v_min, gSerie->MinY() );
						v_max = Upp::max(v_max, gSerie->MaxY() );
						minMaxModified = true;
					}
				}
				return minMaxModified;
			}

			inline bool IsShow()          const { return gSerie->IsShow(); }
			inline void Show(bool v=true)       { gSerie->Show(v); if (v==false) gSerie->ClearDataSelection(); }  // TODO add WhenSelectAction() call
			inline void Hide(bool v=true)       { Show(!v); }

			inline void PaintSerie(BufferPainter& dw, const bool doFastPaint, int scale)    const { if ( IsShow() ) gSerie->PaintSerie(dw, doFastPaint, scale, mcc); }
			inline void PaintSelected(BufferPainter& dw, const bool doFastPaint, int scale) const { if ( IsShow() ) gSerie->PaintSelected(dw, doFastPaint, scale, mcc); }

			inline Image MakeSerieIcon( Size sz, const int scale )        const { return gSerie->MakeSerieIcon(sz, scale); } // No Serie Icon by default
			inline Image MakeSerieIcon( int width=16, const int scale=1 ) const {	return gSerie->MakeSerieIcon(width, scale); }

			inline const String& GetLegend()                  const { return gSerie->GetLegend(); }
			inline void SetLegend(const String& v)                  { gSerie->SetLegend(v); }
			inline bool IsShowLegend()                        const { return gSerie->IsShowLegend(); }




			// Serie selection capacity management
			inline bool IsSelectable()                         const { return gSerie->IsSelectable(); }
			inline bool IsDataSelectable()                     const { return gSerie->IsDataSelectable(); }
			inline bool IsSerieSelected()                      const { return gSerie->IsSerieSelected(); }
			inline bool HasDataSelected()                      const { return gSerie->HasDataSelected(); }
			inline unsigned int GetSelectDataCount()           const { return gSerie->GetSelectDataCount(); }
			inline bool IsDataSelected(unsigned int dataIndex) const { return gSerie->IsDataSelected(dataIndex); }

			void SelectSerie(bool v=true){ if (IsSelectable()) gSerie->SelectSerie(v); }
			void SelectAllData()         { if (IsDataSelectable()) gSerie->SelectAllData();      }
			void ClearDataSelection()    { if (IsDataSelectable()) gSerie->ClearDataSelection(); }
			void InvertDataSelection()   { if (IsDataSelectable()) gSerie->InvertDataSelection();}
			
			unsigned int SelectData(RectScreen rect, bool instersect = false, bool append=false) {
				if (IsDataSelectable()) {
					unsigned int r = gSerie->SelectData(ToGraph(rect), instersect, append);
					return r;
				}
				return 0;
			}
			
			Vector<unsigned int> SelectOneData(PointScreen pt, TypeScreenCoord r, bool append=false)	{
				if (IsDataSelectable()) {
					RectScreen rect(pt.x-r, pt.y-r, pt.x+r, pt.y+r);
					rect.Normalize();
					return Vector<unsigned int>( gSerie->SelectOneData( ToGraph(rect), append) );
				}
				return Vector<unsigned int>();
			}
			

			void WhenPreSelectAction()  { if (IsSelectable()) gSerie->WhenPreSelectAction();  }
			void WhenPostSelectAction() { if (IsSelectable()) gSerie->WhenPostSelectAction(); }


			inline bool IsCtrlable() const                                                 { return gSerie->IsCtrlable(); }
//			virtual void MouseEnter(int pIndex, PointScreen p, dword keyflags)  {}
//			virtual void MouseLeave()                                           {}
			inline bool LeftDown   (unsigned int pIndex, PointScreen p, dword keyflags)    { return gSerie->LeftDown    ( pIndex, ToGraph(p), keyflags); }
			inline bool LeftUp     (unsigned int pIndex, PointScreen p, dword keyflags)    { return gSerie->LeftUp      ( pIndex, ToGraph(p), keyflags); }
			inline bool LeftDouble (unsigned int pIndex, PointScreen p, dword keyflags)    { return gSerie->LeftDouble  ( pIndex, ToGraph(p), keyflags); }
			inline bool LeftTriple (unsigned int pIndex, PointScreen p, dword keyflags)    { return gSerie->LeftTriple  ( pIndex, ToGraph(p), keyflags); }
			inline bool LeftRepeat (unsigned int pIndex, PointScreen p, dword keyflags)    { return gSerie->LeftRepeat  ( pIndex, ToGraph(p), keyflags); }
			inline bool LeftDrag   (unsigned int pIndex, PointScreen p, dword keyflags)    { return gSerie->LeftDrag    ( pIndex, ToGraph(p), keyflags); }
			inline bool LeftHold   (unsigned int pIndex, PointScreen p, dword keyflags)    { return gSerie->LeftHold    ( pIndex, ToGraph(p), keyflags); }

			inline bool RightDown   (unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->RightDown    ( pIndex, ToGraph(p), keyflags); }
			inline bool RightUp     (unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->RightUp      ( pIndex, ToGraph(p), keyflags); }
			inline bool RightDouble (unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->RightDouble  ( pIndex, ToGraph(p), keyflags); }
			inline bool RightTriple (unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->RightTriple  ( pIndex, ToGraph(p), keyflags); }
			inline bool RightRepeat (unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->RightRepeat  ( pIndex, ToGraph(p), keyflags); }
			inline bool RightDrag   (unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->RightDrag    ( pIndex, ToGraph(p), keyflags); }
			inline bool RightHold   (unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->RightHold    ( pIndex, ToGraph(p), keyflags); }

			inline bool MiddleDown  (unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->MiddleDown  ( pIndex, ToGraph(p), keyflags); }
			inline bool MiddleUp    (unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->MiddleUp    ( pIndex, ToGraph(p), keyflags); }
			inline bool MiddleDouble(unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->MiddleDouble( pIndex, ToGraph(p), keyflags); }
			inline bool MiddleTriple(unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->MiddleTriple( pIndex, ToGraph(p), keyflags); }
			inline bool MiddleRepeat(unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->MiddleRepeat( pIndex, ToGraph(p), keyflags); }
			inline bool MiddleDrag  (unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->MiddleDrag  ( pIndex, ToGraph(p), keyflags); }
			inline bool MiddleHold  (unsigned int pIndex, PointScreen p, dword keyflags)   { return gSerie->MiddleHold  ( pIndex, ToGraph(p), keyflags); }

			inline bool MouseMove  (unsigned int pIndex, PointScreen p, dword keyflags)             { return gSerie->MouseMove(  pIndex, ToGraph(p), keyflags); }
			inline bool MouseWheel (unsigned int pIndex, PointScreen p, int zdelta, dword keyflags) { return gSerie->MouseWheel( pIndex, ToGraph(p), zdelta, keyflags); }

			inline bool CursorImage(unsigned int pIndex, PointScreen p, dword keyflags, Image& outImg ) const { return gSerie->CursorImage(pIndex, ToGraph(p), keyflags, outImg); }

			inline bool ContextMenu(unsigned int pIndex, Bar& bar) { return gSerie->ContextMenu(pIndex, bar); }
			

	};
	
	typedef Vector<GraphSerieDecorator> GraphSeriesDecoratorVector;
	

	template<class DERIVED>
	class GraphSeriesGroup
	{
		private:
			bool _isGraphSeriesModified;
			Vector<GraphSerie*> OwnedGraphSeries;
		
		protected:
			CoordinateConverter* _currentXConverter;
			CoordinateConverter* _currentYConverter;
			
		public:
			typedef GraphSeriesGroup CLASSNAME;
			GraphSeriesDecoratorVector graphSeriesProxyList;
			
			GraphSeriesGroup() : _isGraphSeriesModified(true) {}
			virtual ~GraphSeriesGroup() { ClearAllOwnedGraphSeries(); }


			inline void SetModifyGraphSeries()      { _isGraphSeriesModified = true;  }
			inline void ClearModifyGraphSeries()    { _isGraphSeriesModified = false; }
			inline bool IsModifyGraphSeries() const { return _isGraphSeriesModified;  }
			
			void ShowAll(bool v=true) {
				for (GraphSerieDecorator& gsd : graphSeriesProxyList) {
					gsd.Show(v);
				}
			}
			
			void HideAll() {
				for (GraphSerieDecorator& gsd : graphSeriesProxyList) {
					gsd.Hide();
				}
			}
			
			void ClearAllOwnedGraphSeries() {
				graphSeriesProxyList.Clear();
				for (int c=0; c<OwnedGraphSeries.GetCount(); ++c) {
					delete OwnedGraphSeries[c];
				}
				OwnedGraphSeries.Clear();
			}

			template <class GRAPH_SERIE, class ...Targs>
			GRAPH_SERIE& CreateGraphSerie(Targs&... p) {
				static_assert(std::is_base_of<GraphSerie, GRAPH_SERIE>::value, "'gds' should inherit from GraphSerie");
				GRAPH_SERIE* gds = new GRAPH_SERIE(p...);
				OwnedGraphSeries.Add(gds);
				AddGraphSerie(gds);
				return *gds;
			}

			template <class GRAPH_SERIE>
			void AddGraphSerie(GRAPH_SERIE& gds) {
				static_assert(std::is_base_of<GraphSerie, GRAPH_SERIE>::value, "'gds' should inherit from GraphSerie");
				AddGraphSerie(&gds);
			}
			

			template <class GRAPH_SERIE>
			void AddGraphSerie(GRAPH_SERIE* gds) {
				static_assert(std::is_base_of<GraphSerie, GRAPH_SERIE>::value, "'gds' should inherit from GraphSerie");
				GraphSerieDecorator& gdsd = graphSeriesProxyList.Add();
				gds->SetAutoColor(graphSeriesProxyList.GetCount(), Null);
				gds->RefreshOwnerGraph << [&]()->void { this->SetModifyGraphSeries(); static_cast<DERIVED*>(this)->Refresh(); }; // 
				gdsd.SetGraphSerie(gds);
				gdsd.SetXCoordConverter(*_currentXConverter); // TODO_currentXConverter changer gestion _currentXConverter  ==> refactorer SeriesGroup
				gdsd.SetYCoordConverter(*_currentYConverter);
				SetModifyGraphSeries();
			}

			void PaintAllGraphSeries(BufferPainter& dw, const bool doFastPaint, int scale) {
				for (GraphSerieDecorator& gsd : graphSeriesProxyList) {
					gsd.PaintSerie(dw, doFastPaint, scale);
				}
			}

			void WhenPreSelectAction() {
				for (GraphSerieDecorator& gsd : graphSeriesProxyList) {
					gsd.WhenPreSelectAction();
				}
			}

			void WhenPostSelectAction() {
				for (GraphSerieDecorator& gsd : graphSeriesProxyList) {
					gsd.WhenPostSelectAction();
				}
			}

			void ClearDataSelection() {
				for (GraphSerieDecorator& gsd : graphSeriesProxyList) {
					gsd.ClearDataSelection();
				}
			}

			void SelectAllData() {
				for (GraphSerieDecorator& gsd : graphSeriesProxyList) {
					gsd.SelectAllData();
				}
			}

			void SelectOneData(PointScreen pt, bool append=false)	{
				for (GraphSerieDecorator& gsd : graphSeriesProxyList) {
					const int selectRadius = 1; // TODO make  radius  configurable
					gsd.SelectOneData(pt, selectRadius, append);
				}
			}

			void SelectData(RectGraph rect, bool instersect = false, bool append=false) {
				for (GraphSerieDecorator& gsd : graphSeriesProxyList) {
					gsd.SelectData(rect, instersect, append);
				}
			}

			bool HasSelectedGraphSeries() {
				for (GraphSerieDecorator& gsd : graphSeriesProxyList) {
					if (gsd.IsSerieSelected() || gsd.HasDataSelected()) return true;
				}
				return false;
			}

			void PaintAllSelectedGraphSeries(BufferPainter& dw, const bool doFastPaint, int scale) {
				for (GraphSerieDecorator& gsd : graphSeriesProxyList) {
					if (gsd.IsSerieSelected() || gsd.HasDataSelected()) gsd.PaintSelected(dw, doFastPaint, scale);
				}
			}
	};
}
#endif
