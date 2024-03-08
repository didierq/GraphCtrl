
class Ctrl;


namespace GraphDraw_ns
{
	// Style GraphSerie base
	struct StyleGS_base {
		Color highlightColor;

		virtual hash_t GetHashValue() const = 0;

		hash_t GetHashValue_base() const {
			CombineHash hash;
			hash << highlightColor;
			return hash;
		}
		
		StyleGS_base() {}
		virtual ~StyleGS_base() {}
	};
	
	// GraphSerie editor dialog interface object
	class GraphSerieEditorInterface {
		private:
			Ctrl* dlg;
			Function<void()> DeleteTmpStyle;
			Function<void()> _RevertChanges;

		public:
			Function<void()> DeleteDlg;
			Function<void()> RetrieveFromDlg;
			Function<void()> WhenDlgAction;

			
			template <class CTRL, class STYL>
			static GraphSerieEditorInterface* Create(CTRL* dlg, STYL& styl) {
				GraphSerieEditorInterface* gei = new GraphSerieEditorInterface(dlg);
				STYL* sav = new STYL;
				*sav = styl;
				gei->RetrieveFromDlg = [=] () { dlg->Retrieve(); };
				gei->DeleteDlg = [=] ()   { delete dlg; };
				dlg->WhenAction = [=] ()  { gei->WhenDlgAction(); };
				gei->DeleteTmpStyle = [=] { if (sav) { delete sav; } };
				gei->_RevertChanges = [=, &styl] { styl = *sav; };
				return gei;
			}
			
			void RevertChanges() { _RevertChanges(); }
			~GraphSerieEditorInterface();
			Ctrl* const GetCtrl() const { return dlg; }

		private:
			GraphSerieEditorInterface()  = delete;
			GraphSerieEditorInterface(Ctrl* p) : dlg(p) {}
			GraphSerieEditorInterface(const GraphSerieEditorInterface& p) = delete;
			GraphSerieEditorInterface(      GraphSerieEditorInterface& p) = delete;
			GraphSerieEditorInterface(GraphSerieEditorInterface&& p)            = delete;
			GraphSerieEditorInterface& operator= (const GraphSerieEditorInterface& p) = delete;
			GraphSerieEditorInterface& operator= (      GraphSerieEditorInterface& p) = delete;
			GraphSerieEditorInterface& operator=(GraphSerieEditorInterface&& p) = delete;
	};
	
	
	// ============================
	// GraphSerie   CLASS
	// ============================
	class GraphSerie
	{
		private:
			bool isCtrlable;
			bool isSelectable;
			bool isDataSelectable;

		protected:
			bool show;
			bool showLegend; // TODO : must this be in this class ==> maybe in GraphSerieDecorator ?
			String legend;
			bool isSerieSelected;

		public:
			Event<> RefreshOwnerGraph;
			
			Event<> WhenPreSelectAction;
			Event<> WhenPostSelectAction;

			GraphSerie()
			: isCtrlable(false)
			, isSelectable(false)
			, isDataSelectable(false)
			, show(true)
			, showLegend(true)
			, legend(t_("Legend Not Set"))
			, isSerieSelected(false)
			{}

			virtual ~GraphSerie() {}

			inline bool IsShow()           const { return show; }
			inline bool IsCtrlable()       const { return isCtrlable && show; }
			inline bool IsSelectable()     const { return isSelectable; }
			inline bool IsDataSelectable() const { return isDataSelectable && IsSelectable(); }
			inline bool IsShowLegend()     const { return showLegend && show; }

			void Show(bool v=true) { show = v; }
			void Hide(bool v=true) { show = !v; }
			void SetCtrlable(bool v=true) { isCtrlable = v; }
			void SetSelectable(bool v=true) { isSelectable = v; }
			void SetDataSelectable(bool v=true) { isDataSelectable = v; }
			void ShowLegend(bool v=true) { showLegend = v; }


			virtual StyleGS_base& GetStyleGDS() = 0;
			virtual GraphSerieEditorInterface* MakeGraphSerieEditorInfo() { return nullptr; }
			virtual hash_t GetHashValue_base() const
			{
				CombineHash hash;
				hash << show;
				if (show && showLegend) hash << legend << showLegend;
				return hash;
			}
			virtual hash_t GetHashValue() const = 0;
			virtual hash_t GetSelectHashValue() const { return 0; }
			
			virtual unsigned int GetCount() const = 0;
			virtual bool Contains(const PointGraph p, unsigned int& pIndexOut) const = 0;
			virtual bool Intersects(const RectGraph rect, unsigned int& pIndexOut) const = 0;
			
			virtual void PaintSerie(BufferPainter& dw, const bool doFastPaint, int scale, const MCoordinateConverter& coordConv ) = 0;
			virtual void PaintSelected(BufferPainter& dw, const bool doFastPaint, int scale, const MCoordinateConverter& coordConv ) {}
			virtual void PaintOne(unsigned int index, int style, BufferPainter& dw, int scale, const MCoordinateConverter& coordConv ) const = 0;

			// Serie selection capacity management
			
			// Serie selection
			inline bool IsSerieSelected() const { return (isSerieSelected); }
			virtual void SelectSerie(bool v = true) { isSerieSelected = v && IsSelectable(); }
			
			// Serie Data selection
			virtual bool HasDataSelected() const { return false; }
			virtual unsigned int GetSelectDataCount() const { return 0; }
			virtual bool IsDataSelected(unsigned int dataIndex) const { return false; }
			virtual void SelectAllData() {}
			virtual void SelectData(const Vector<unsigned int>& dataIndexList, bool append=false) {}
			virtual unsigned int SelectData(RectGraph rect, bool instersect = false, bool append=false) { return 0; }
			virtual Vector<unsigned int> SelectOneData(RectGraph rect, bool append=false) { return Vector<unsigned int>(); }
			virtual void InvertDataSelection() {}
			virtual void UnselectData(const Vector<unsigned int>& dataIndexList) {}
			virtual void ClearDataSelection() {}
			virtual Vector<unsigned int> GetDataSelection() const { return Vector<unsigned int>(); }
			virtual Vector<unsigned int> GetInvertedDataSelection() const { return Vector<unsigned int>(); }
			
			// Selection painting
			
			// Autocolor management
			virtual void SetAutoColor(int id, Color colorHint) = 0;
			virtual Color GetAutoColor() const { return SBlack(); }

			virtual bool HasMinMax() const = 0;
			virtual TypeGraphCoord MinX() const = 0;
			virtual TypeGraphCoord MinY() const = 0;
			virtual TypeGraphCoord MaxX() const = 0;
			virtual TypeGraphCoord MaxY() const = 0;


			// Legend management
			const String& GetLegend() const { return legend; }
			void SetLegend(String v)        { legend = v; }
			
			// Serie icon management
			virtual Image MakeSerieIcon( Size sz, const int scale ) const { return Null; } // No Serie Icon by default
			Image MakeSerieIcon( int width=16, const int scale=1 ) const {
				return MakeSerieIcon(Size(width, width), scale);
			}

			// ===========================
			// stubs for Ctrl enabling
			// ===========================
			
			virtual bool LeftDown    (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool LeftUp      (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool LeftDouble  (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool LeftTriple  (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool LeftRepeat  (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool LeftDrag    (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool LeftHold    (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }

			virtual bool RightDown   (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool RightUp     (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool RightDouble (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool RightTriple (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool RightRepeat (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool RightDrag   (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool RightHold   (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }

			virtual bool MiddleDown  (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool MiddleUp    (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool MiddleDouble(unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool MiddleTriple(unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool MiddleRepeat(unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool MiddleDrag  (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool MiddleHold  (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }

			virtual bool MouseMove  (unsigned int pIndex, PointGraph p, dword keyflags) { return false; }
			virtual bool MouseWheel (unsigned int pIndex, PointGraph p, int zdelta, dword keyflags) { return false; }
			
			virtual bool CursorImage(unsigned int pIndex, PointGraph p, dword keyflags, Image& outImg ) const { return false; }
		
			virtual bool ContextMenu(unsigned int pIndex, Bar& bar) { return false; }
	};


	// ============================
	// CustomData   CLASS
	// ============================
	class CustomData
	{
		public:
			enum DataPaintingStyle {
				DEFAULT_STYLE=0,
				HIGHLIGHT_STYLE=-1
			};
				
			
		protected:
			bool isSelected;

		public:
			CustomData() : isSelected(false) {}
			virtual ~CustomData() {}
			
			virtual bool Contains(const PointGraph& pt) const = 0;
			virtual bool Intersects(const RectGraph& rect) const = 0;
			virtual bool Contained(const RectGraph& rect) const = 0;
			virtual void PaintDataPoint(BufferPainter& dw, int scale, int style, const MCoordinateConverter& coordConv ) const = 0;
			
			inline void Select(bool v = true) { isSelected = v; }
			inline void SelectFlip() { isSelected = !isSelected; }
			inline bool IsSelected() const { return isSelected; }
	};



	class SimpleGraphSerie : public GraphSerie
	{
		public:
			SimpleGraphSerie() {}
			
			virtual ~SimpleGraphSerie() {}
			
			virtual const CustomData& Get(unsigned int dataIndex) const = 0;
			virtual       CustomData& Get(unsigned int dataIndex) = 0;
			virtual void PaintSerie(BufferPainter& dw, const bool doFastPaint, int scale, const MCoordinateConverter& coordConv ) override;
			virtual void PaintSelected(BufferPainter& dw, const bool doFastPaint, int scale, const MCoordinateConverter& coordConv ) override;
			virtual void PaintOne(unsigned int index, int style, BufferPainter& dw, int scale, const MCoordinateConverter& coordConv ) const override;
			virtual bool Contains(const PointGraph p, unsigned int& pIndexOut) const override;
			virtual bool Intersects(const RectGraph rect, unsigned int& pIndexOut) const override;

			// Serie Data selection
			virtual bool HasDataSelected() const override;
			virtual unsigned int GetSelectDataCount() const override;
			virtual bool IsDataSelected(unsigned int dataIndex) const override;
			virtual void SelectAllData() override;
			virtual void SelectData(const Vector<unsigned int>& dataIndexList, bool append=false) override;
			virtual unsigned int SelectData(RectGraph rect, bool instersect = false, bool append=false) override;
			virtual Vector<unsigned int> SelectOneData(RectGraph rect, bool append=false) override;
			virtual void InvertDataSelection() override;
			virtual void UnselectData(const Vector<unsigned int>& dataIndexList) override;
			virtual void ClearDataSelection() override;
			virtual Vector<unsigned int> GetDataSelection() const override;
			virtual Vector<unsigned int> GetInvertedDataSelection() const override;
			
			// Selection painting
			virtual hash_t GetSelectHashValue() const override;
	};



	template <class CUSTOM_DATA_TYPE>
	class SimpleArrayGraphSerie : public SimpleGraphSerie {
		protected:
			Array<CUSTOM_DATA_TYPE> dataArray;
			
		public:
			SimpleArrayGraphSerie() {}
			virtual ~SimpleArrayGraphSerie() {}
			
			virtual unsigned int GetCount() const  override { return dataArray.GetCount(); }
			virtual const CustomData& Get(unsigned int dataIndex) const override { return dataArray[dataIndex]; }
			virtual       CustomData& Get(unsigned int dataIndex) override { return dataArray[dataIndex]; }
			CUSTOM_DATA_TYPE& operator[](int dataIndex) { return dataArray[dataIndex]; }
	};


};

