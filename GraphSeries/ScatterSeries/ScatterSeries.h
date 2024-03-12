#ifndef _ScatterSeries_ScatterSeries_h
#define _ScatterSeries_ScatterSeries_h

#include <GraphDraw/GraphDraw.h>
#include <ScatterDraw/ScatterDraw.h>

namespace Upp {
namespace GraphDraw_ns {
	
	MarkPlot* GetNewMarkPlot(int id);
	SeriesPlot* GetNewPlotStyle(int id);
	Color GetNewColor(int id);
	String GetNewDash(int id);
	

	template <class T>
	int FindIndexX(DataSource* src, int idxMin, int idxMax, T xVal)
	{
		if(idxMin == idxMax)
			return idxMin;
		int64 min = 0;
		int64 max = idxMax - idxMin;
	
		while(min < max)
		{
			int64 mid = (max + min) >> 1;
			if( src->x(idxMin + mid) < xVal ) min = mid + 1;
			else                              max = mid;
		}
		return (int)(min+idxMin);
	}


	class FastMarkPlot : public MarkPlot {
	private:
		template <class T>
		void DoPaint(T& w, const double& scale, const GraphDraw_ns::PointScreen& cp, const double& size, const Color markColor) const
		{
			w.DrawLine(cp.x, cp.y, cp.x, cp.y+1, 1, markColor);
		}
	
	public:
		virtual ~FastMarkPlot() {}
	
		virtual void Paint(Draw &p
						, const double& scale
						, const GraphDraw_ns::PointScreen& cp
						, const double& size
						, const Color& markColor
						, const double& markBorderWidth
						, const Color& markBorderColor) const
		{
			DoPaint(p, scale, cp, size, markColor);
		}
		virtual void Paint(Painter &p
						, const double& scale
						, const GraphDraw_ns::PointScreen& cp
						, const double& size
						, const Color& markColor
						, const double& markBorderWidth
						, const Color& markBorderColor) const
		{
			DoPaint(p, scale, cp, size, markColor);
		}
	};



	class ScatterGraphSeries : public GraphSerie
	{
		public:
			struct StyleGS  : public StyleGS_base {
				// Line
				One<SeriesPlot> seriesPlot;
				double thickness;
				Color color;
				String dash;
	
				// Mark
				One<MarkPlot> markPlot;
				double markWidth;
				Color markColor;
				
				// Filling
				Color fillColor;
				double opacity;

				virtual hash_t GetHashValue() const  override{
					CombineHash hash;
					hash << GetHashValue_base();
					hash << color << thickness << opacity << dash;
					hash << markWidth << markColor << fillColor;
					return hash;
				}
				
				
				StyleGS()
				:  thickness(1)
				, color (Null)
				, markWidth(3)
				, markColor(color)
				, fillColor(color)
				, opacity(0.3)
				{}
				
				StyleGS& operator=(const StyleGS& s) {
					thickness  = s.thickness;
					color      = s.color;
					markWidth  = s.markWidth;
					markColor  = s.markColor;
					fillColor  = s.fillColor;
					opacity    = s.opacity;
					if (! s.seriesPlot.IsEmpty() ) seriesPlot = SeriesPlot::Create( s.seriesPlot.Get()->GetType() );
					if (! s.markPlot.IsEmpty() )   markPlot   = MarkPlot::Create( s.markPlot.Get()->GetType() );
					return *this;
				}
				
				
				virtual ~StyleGS() {}
			};

		public:
			typedef Function<GraphSerieEditorInterface*(StyleGS&)> MakeEditorFunction;
		
		private:
			static MakeEditorFunction& GetDefaultMakeEditorCB();
			MakeEditorFunction makeEditorFct;
		
		public:
			static void SetDefaultMakeScatterEditorFct(MakeEditorFunction f) { GetDefaultMakeEditorCB() = f; }
			void SetMakeScatterEditorFct(MakeEditorFunction f) { makeEditorFct = f; }


		private:
			DataSource* pD;
			bool owns;
			StyleGS style;
			
			bool sequential;
			unsigned int sequentialPointsRangeMin;
			unsigned int sequentialPointsRangeMax;

			unsigned int nbVisiblePoints;

			int autoColorId;
			CoordinateConverter* xConverter;
			CoordinateConverter* yConverter;

			Vector<Pointf> p1; // screen coordinates (float values for ScatterDraw)

		public:
			ScatterGraphSeries();
			virtual ~ScatterGraphSeries();

			virtual StyleGS_base& GetStyleGDS() override { return style; }
			virtual GraphSerieEditorInterface* MakeGraphSerieEditorInfo() override { return makeEditorFct(style); }
			
			virtual unsigned int GetCount() const override { if (pD) return (unsigned int)(pD->GetCount()); else return 0; }
			virtual bool Contains(PointGraph p, unsigned int& pIndexOut) const override;
			virtual bool Intersects(const RectGraph rect, unsigned int& pIndexOut) const override;

			virtual bool HasMinMax() const override { return (pD != 0 && (!pD->IsExplicit()) && (!pD->IsParam()) ); }
			virtual TypeGraphCoord MinX() const override { return pD->MinX(); }
			virtual TypeGraphCoord MinY() const override { return pD->MinY(); }
			virtual TypeGraphCoord MaxX() const override { return pD->MaxX(); }
			virtual TypeGraphCoord MaxY() const override { return pD->MaxY(); }
		private:
			void _PaintSerie(bool selected, BufferPainter& dw, const bool _doFastPaint, int scale, const MCoordinateConverter& coordConv );
		
		public:
			virtual void PaintSerie(BufferPainter& dw, const bool doFastPaint, int scale, const MCoordinateConverter& coordConv ) override { _PaintSerie(false, dw, doFastPaint, scale, coordConv); }
			virtual void PaintSelected(BufferPainter& dw, const bool doFastPaint, int scale, const MCoordinateConverter& coordConv ) override { _PaintSerie(true, dw, doFastPaint, scale, coordConv); }
			virtual void PaintOne(unsigned int index, int paintStyle, BufferPainter& dw, int scale, const MCoordinateConverter& coordConv ) const override	{}

			virtual void ClearSelection() override { SelectSerie(false); }
			
			virtual void SelectData(const MCoordinateConverter& coordConv, const Vector<unsigned int>& dataIndexList, bool append=false) override	{}
			virtual unsigned int SelectData(const MCoordinateConverter& coordConv, RectScreen rect, bool instersect = false, bool append=false) override { return 0; }
			virtual Vector<unsigned int> SelectOneData(const MCoordinateConverter& coordConv, RectScreen rects, bool append=false) override;

			ScatterGraphSeries& SetSerieDataSource(DataSource *pointsData, bool ownsData = true) {
				pD = pointsData;
				owns = ownsData;
				return *this;
			}

			inline const DataSource& GetDataSource() const	{ return *pD; }
			inline       DataSource& GetDataSource()        { return *pD; }

			virtual hash_t GetHashValue() const override {
				CombineHash hash;
				hash << GetHashValue_base();
				hash << style.GetHashValue() << pD;
				return hash;
			}
			
			virtual void SetAutoColor(int id, Color colorHint) override;
			virtual Color GetAutoColor() const override {
				if (!style.seriesPlot.IsEmpty() ) return style.color;
				if (!style.markPlot.IsEmpty() )   return style.markColor;
				return style.color;
			}
	
			virtual Image MakeSerieIcon( Size sz, const int scale ) const override;

			ScatterGraphSeries&  SetSequential(bool v=true) { sequential = v; return *this; }
			
//			bool IsVisible() { return style.show; }
	
			ScatterGraphSeries& SetSerieData(double *yData, int numData, double x0 = 0, double deltaX = 1)       { return SetSerieData<CArray>(yData, numData, x0, deltaX); }
			ScatterGraphSeries& SetSerieData(double *xData, double *yData, int numData)                          { return SetSerieData<CArray>(xData, yData, numData);}
			ScatterGraphSeries& SetSerieData(Vector<double> &xData, Vector<double> &yData)                       { return SetSerieData<VectorXY>(xData, yData);}
			ScatterGraphSeries& SetSerieData(Upp::Array<double> &xData, Upp::Array<double> &yData)               { return SetSerieData<ArrayXY>(xData, yData);}
			ScatterGraphSeries& SetSerieData(Vector<Pointf> &points)                                             { return SetSerieData<VectorPointf>(points);}
			ScatterGraphSeries& SetSerieData(Upp::Array<Pointf> &points)                                         { return SetSerieData<ArrayPointf>(points);}
			ScatterGraphSeries& SetSerieData(double (*function)(double))                                         { return SetSerieData<FuncSource>(function);}
			ScatterGraphSeries& SetSerieData(void (*function)(double&, double))                                  { return SetSerieData<FuncSourceV>(function);}
			ScatterGraphSeries& SetSerieData(Pointf (*function)(double), int np, double from = 0, double to = 1) { return SetSerieData<FuncSourcePara>(function, np, from, to);}
			ScatterGraphSeries& SetSerieData(PlotExplicFunc &function)                                           { return SetSerieData<PlotExplicFuncSource>(function);}
			ScatterGraphSeries& SetSerieData(PlotParamFunc function, int np, double from = 0, double to = 1)     { return SetSerieData<PlotParamFuncSource>(function, np, from, to);}
	
			ScatterGraphSeries& SetSerieData(DataSource &data) {
				SetSerieDataSource(&data, false);
				return *this;
			}
			
			ScatterGraphSeries& SetOwnSerieData(DataSource *data) {
				SetSerieDataSource(data, true);
				return *this;
			}
	
			template <class C, class ...Targs>  ScatterGraphSeries& SetSerieData( Targs&...       args)   { return SetOwnSerieData(new C(args...)); }
			template <class Y>                  ScatterGraphSeries& SetSerieData( Vector<Y>       &yData) { return SetOwnSerieData(new VectorY<Y>(yData));}
			template <class Y>                  ScatterGraphSeries& SetSerieData( Upp::Array<Y>   &yData) { return SetOwnSerieData(new ArrayY<Y>(yData));}
			template <class X, class Y>         ScatterGraphSeries& SetSerieData( VectorMap<X, Y> &data)  { return SetOwnSerieData(new VectorMapXY<X, Y>(data));}
			template <class X, class Y>         ScatterGraphSeries& SetSerieData( ArrayMap<X, Y>  &data)  { return SetOwnSerieData(new ArrayMapXY<X, Y>(data));}
	
			ScatterGraphSeries& NoPlot()	                 { style.seriesPlot = nullptr; return *this; }
			template <class C, class...Targs>
			ScatterGraphSeries& PlotStyle(Targs&...args)    { style.seriesPlot = new C(args...); return *this; }
	
	
			ScatterGraphSeries& NoMark()	               { style.markPlot = nullptr; return *this; }
			template <class C, class...Targs>
			ScatterGraphSeries& MarkStyle(Targs&...args)  { style.markPlot = new C(args...); return *this; }
		
			Color GetLineColor () const { return style.color; }
			ScatterGraphSeries& SetLineColor(const Color v)     { style.color = v; return *this; }
			inline ScatterGraphSeries& LineColor(const Color v) { return SetLineColor(v); }
	
	
			double GetLineThickness() const                { return style.thickness; }
			ScatterGraphSeries&  SetLineThickness(double v) { style.thickness = v; return *this; }
			inline ScatterGraphSeries&  LineThickness(double v) { return SetLineThickness(v); }
	
		
			ScatterGraphSeries& Stroke(double pthickness = 3, Color pcolor = Null);
			ScatterGraphSeries& SetDash(const char *dashDesc)     { style.dash = dashDesc; return *this; }
			inline ScatterGraphSeries& Dash(const char *dashDesc) { return SetDash(dashDesc); }
			inline ScatterGraphSeries& SetNoDash()                { return SetDash(LINE_SOLID); }
			inline ScatterGraphSeries& NoDash()                   { return SetDash(LINE_SOLID); }
	

			ScatterGraphSeries& SetFillColor(Color fcolor = Null);
			inline ScatterGraphSeries& Fill(Color fcolor = Null)  { return SetFillColor(fcolor); }
	
			ScatterGraphSeries& SetOpacity(double v = 1)     { style.opacity = v; return *this;	}
			inline ScatterGraphSeries& Opacity(double v = 1) { return SetOpacity(v);	}
			
//			ScatterGraphSeries& SetLegend(const String& v)     { style.legend = v; return *this;	}
			inline ScatterGraphSeries& Legend(const String& v) { SetLegend(v); return *this;	}

			ScatterGraphSeries& SetMarkColor(Color c = Null);
			inline ScatterGraphSeries& MarkColor(Color c = Null) {return SetMarkColor(c); }
			
			ScatterGraphSeries& SetMarkWidth(double v = 8)     { style.markWidth = v; return *this; }
			inline ScatterGraphSeries& MarkWidth(double v = 8) { return SetMarkWidth(v); }
	};
}
}

#endif
