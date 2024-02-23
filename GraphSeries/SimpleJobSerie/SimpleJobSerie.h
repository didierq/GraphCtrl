#ifndef _SimpleJobSerie_SimpleJobSerie_h
#define _SimpleJobSerie_SimpleJobSerie_h

#include <GraphCtrl/GraphCtrl.h>

namespace Upp {
namespace GraphDraw_ns {

	INITIALIZE(SimpleJobSerie);

	void InitGraphSerieSimpleJobSerie();

	// =========================================================
	//    TEST CLASSES
	// =========================================================
	class CustomData_Job : public CustomData {
		public:
			double dateDebut;
			double dateFin;
			double hauteur;
			int priorite;
			Value rectStyle;
			RectGraph rectGraphBound;
			
			CustomData_Job(double deb, double fin, int prio=0, double haut=10, Value style=Color(113, 255, 255) )
			{
				Init(deb, fin, prio, haut, style);
			}
			
			CustomData_Job()
			{
				Init(0, 1000);
				rectGraphBound.SetNull();
			}
			
			void Init(double deb, double fin, int prio=0, double haut=10, Value style=Color(113, 255, 255) )
			{
				dateDebut = deb;
				dateFin = fin;
				hauteur = haut;
				priorite = prio;
				rectStyle = style;

				double start = dateDebut;
				double end = dateFin;
				rectGraphBound.left = start/10;
				rectGraphBound.right = end/10;
				rectGraphBound.top = priorite/10;
				rectGraphBound.bottom = priorite/10 + hauteur;
			}
			
			virtual ~CustomData_Job() {}

			virtual bool Contains(const PointGraph& pt) const override;
			virtual bool Intersects(const RectGraph& graphView) const override;
			virtual bool Contained(const RectGraph& rect) const override;
			virtual void PaintDataPoint(BufferPainter& dw, int scale, int style, const MCoordinateConverter& coordConv ) const override;
	};
	
	class SimpleJobSerie : public SimpleGraphSerie
	{
		public:
			struct StyleGS  : public StyleGS_base {
				virtual hash_t GetHashValue() const override{
					CombineHash hash;
					hash << GetHashValue_base();
					return hash;
				}
			};

			typedef Function<GraphSerieEditorInterface*(StyleGS&)> MakeEditorFunction;

		private:
			enum {DATA_COUNT=6};
			CustomData_Job data[DATA_COUNT];
			StyleGS style;
			

			static MakeEditorFunction& GetDefaultMakeEditorCB();
			MakeEditorFunction makeEditorFct;
			

		public:
			static void SetDefaultMakeEditorFct(MakeEditorFunction f) { GetDefaultMakeEditorCB() = f; }
			void SetMakeEditorFct(MakeEditorFunction f) { makeEditorFct = f; }


			SimpleJobSerie();
			virtual ~SimpleJobSerie() {}

			virtual Image MakeSerieIcon( Size sz, const int scale ) const override;

			virtual void SetAutoColor(int id, Color colorHint) override {};
			
			virtual StyleGS_base& GetStyleGDS() override { return style; }
			virtual GraphSerieEditorInterface* MakeGraphSerieEditorInfo() override { return makeEditorFct(style); }
			virtual hash_t GetHashValue() const override {
				CombineHash hash;
				hash << GetHashValue_base();
				hash << style.GetHashValue();
				return hash;
			}

			virtual unsigned int GetCount() const override {return DATA_COUNT;};
			virtual const CustomData& Get(unsigned int dataIndex) const override { return data[dataIndex]; }
			virtual       CustomData& Get(unsigned int dataIndex)       override { return data[dataIndex]; }

			
			virtual bool HasMinMax() const override { return true; }
			RectGraph GetMinMaxGraphRect() const;
			
			virtual TypeGraphCoord MinX() const override { return GetMinMaxGraphRect().left; }
			virtual TypeGraphCoord MinY() const override { return GetMinMaxGraphRect().top; }
			virtual TypeGraphCoord MaxX() const override { return GetMinMaxGraphRect().right; }
			virtual TypeGraphCoord MaxY() const override { return GetMinMaxGraphRect().bottom; }

			CustomData_Job& operator[](int dataIndex) { return data[dataIndex]; }

			virtual bool LeftDouble (unsigned int pIndex, PointGraph p, dword keyflags) override;
			virtual bool CursorImage(unsigned int pIndex, PointGraph p, dword keyflags, Image& outImg ) const override;
	};
	
}
}


#endif
