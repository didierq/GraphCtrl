#ifndef _GraphCtrl_CoordinateConverter_h_
#define _GraphCtrl_CoordinateConverter_h_



namespace GraphDraw_ns
{

	class CoordinateConverterOwner {
		public:
		virtual void RefreshWhenLinkUpdate() = 0;
		
	};


	class ChangeStatus {
		private:
			unsigned int status;
			ChangeStatus(const ChangeStatus& p) : status(0) {}

		public:
			ChangeStatus() : status(0) {}
			
			ChangeStatus& incChangeStatus() {
				++status;
				return *this;
			}
			
			inline bool hasChangedUpdate(const ChangeStatus& p) {
				if ( status == 0 || status != p.status )  {
					status = p.status;
					return true;
				}
				return false;
			}

			inline bool hasChanged(const ChangeStatus& p) {
				if ( status != p.status )  return true;
				return false;
			}
	};


	
	typedef enum {
		LINK_UPDATE_RANGE  = 0x01,
		LINK_UPDATE_LIMITS = 0x02,
		LINK_UPDATE_RANGE_LIMITS = LINK_UPDATE_RANGE + LINK_UPDATE_LIMITS,
	} LinkUpdateStrategy;
	

	class  LinearConverter {
		private:
			TypeGraphCoord gcLeft;
			TypeGraphCoord gcRight;
			TypeScreenCoord scMin;
			TypeScreenCoord scMax;
			
			TypeGraphCoord toGraphScale;
			TypeGraphCoord toScreenScale;
			TypeGraphCoord toGraphOffset;
			TypeGraphCoord toScreenOffset;
			bool isInverted;

		public:
			LinearConverter() : toGraphScale(1), toScreenScale(1), toGraphOffset(0), toScreenOffset(0), isInverted(false) {}
			LinearConverter(const LinearConverter& p) : toGraphScale(p.toGraphScale), toScreenScale(p.toScreenScale), toGraphOffset(p.toGraphOffset), toScreenOffset(p.toScreenOffset), isInverted(p.isInverted) {}
			
			bool IsInverted() const { return isInverted; }
			void SetInverted(bool v=true) {
				isInverted = v;
				Update();
			}

			void Update(TypeGraphCoord gLeft, TypeGraphCoord gRight, const TypeScreenCoord sMin, const TypeScreenCoord sMax) {
				gcLeft = gLeft;
				gcRight = gRight;
				scMin = sMin;
				scMax = sMax;
				Update();
			}
			
			void Update() {
				TypeGraphCoord gLeft = gcLeft;
				TypeGraphCoord gRight = gcRight;
				if (isInverted) Swap(gLeft, gRight);
				toScreenScale = (TypeGraphCoord)( (scMax - scMin) / (gRight - gLeft));
				toGraphScale = (TypeGraphCoord)( (gRight - gLeft) / (scMax - scMin));
				
				toScreenOffset = scMin - toScreenScale*gLeft;
				toGraphOffset  = gLeft - toGraphScale*scMin;
			}

			inline TypeScreenCoord toScreen(const TypeGraphCoord v) const { return (TypeScreenCoord)(v*toScreenScale + toScreenOffset); }
			inline TypeGraphCoord  toGraph(const TypeScreenCoord v) const { return (TypeGraphCoord)(v*toGraphScale  + toGraphOffset); }
			inline void toGraph(const TypeScreenCoord* v, TypeGraphCoord* out, const int n) const {
				const TypeScreenCoord* const iterEnd = --v+n;
				--out;
				while (v<iterEnd) {
					*(++out) = toGraph(*(++v));
				}
			}
	};

	// ============================
	//    CoordinateConverter   CLASS
	// ============================
	typedef enum {
		UPDATE_AUTO =   0,
		UPDATE_FORCED = 1	
	} ForceUpdate;
	
	class CoordinateConverter : public ChangeStatus
	{
		public:
			typedef enum {
				AXIS_SCALE_STD = 0,
				AXIS_SCALE_LOG,
				AXIS_SCALE_POW10,
			} AxisScaleType;

		private:
			// copy constructor forbidden
			CoordinateConverter& operator=(const CoordinateConverter& c) {	return *this;}
			CoordinateConverter(const CoordinateConverter& p) : _owner(p._owner), _linConv(p._linConv) {}

		protected:
			
			CoordinateConverterOwner& _owner;
			bool _isZoomAllowed;
			bool _isScrollAllowed;
			bool _isAxisZoomAllowed;
			bool _isAxisScrollAllowed;
			TypeScreenCoord _screenMin;
			TypeScreenCoord _screenMax;
			TypeScreenCoord _screenRange;
			TypeGraphCoord _graphToScreenScale;
			TypeGraphCoord _graphMin;
			TypeGraphCoord _graphMax;
			TypeGraphCoord _graphRange;
			TypeGraphCoord _screenToGraphScale;
			TypeGraphCoord _graphMaxLimit;
			TypeGraphCoord _graphMinLimit;
			LinearConverter _linConv;
			
			TypeGraphCoord _fctGraphMin;
			TypeGraphCoord _fctGraphMax;
			typedef TypeGraphCoord (*TypeConvertFct) (TypeGraphCoord);
			TypeConvertFct _convertFct;
			TypeConvertFct _unConvertFct;
			const char* _convFctName;
			int _scaleType;

			static TypeGraphCoord _defautFct(TypeGraphCoord v) { return v; }
			static TypeGraphCoord _logFct(TypeGraphCoord v)    { if (v<=0) v=0.00001; return log10(v); }
			static TypeGraphCoord _pow10Fct(TypeGraphCoord v)  { return pow(10.0,v); }

		public:
			typedef CoordinateConverter CLASSNAME;
			CoordinateConverter(CoordinateConverterOwner& owner);
			CoordinateConverter(CoordinateConverterOwner& owner, TypeGraphCoord graphMin, TypeGraphCoord graphMax, TypeScreenCoord screenMin, TypeScreenCoord screenMax);
			virtual ~CoordinateConverter();

			Index<CoordinateConverter*> links;
			UpdateCounter<CoordinateConverter> linkStatusCounter;
			
			void UpdateLinks(LinkUpdateStrategy strategy);

			static void Link(CoordinateConverter& local, CoordinateConverter& other) {
				if (local.Link(other) ) {
					other.Link(local);
				}
			}
			
			static void Unlink(CoordinateConverter& local, CoordinateConverter& other) {
				local.Unlink(other);
			}
			
			bool Link(CoordinateConverter& conv);
			void Unlink(CoordinateConverter& conv);
			void UnlinkAll();
			
			inline TypeScreenCoord getScreenMin()               const { return _screenMin; }
			inline TypeScreenCoord getScreenMax()               const { return _screenMax; }
			inline TypeScreenCoord getScreenRange()             const { return _screenRange; }
			inline TypeGraphCoord  getGraphMin()                const { return _graphMin; }
			inline TypeGraphCoord  getGraphMax()                const { return _graphMax; }
			inline TypeGraphCoord  getGraphMinRangeLimit()      const { return _graphMinLimit; }
			inline TypeGraphCoord  getGraphMaxRangeLimit()      const { return _graphMaxLimit; }
			inline TypeGraphCoord  getGraphRange()              const { return _graphRange; }
			inline TypeGraphCoord  getSignedGraphRange()        const { return (_graphMax-_graphMin); }
			inline bool IsInGraphVisibleRange(TypeGraphCoord p) const { return ((_graphMin <= p) && (p <= _graphMax)); }

			inline void AllowZoom(bool p = true)               { _isZoomAllowed = p; }
			inline void AllowScroll(bool p = true)             { _isScrollAllowed = p; }
			inline void AllowAxisZoom(bool p = true)           { _isAxisZoomAllowed = p; }
			inline void AllowAxisScroll(bool p = true)         { _isAxisScrollAllowed = p; }
			inline bool IsZoomAllowed()                  const { return _isZoomAllowed; }
			inline bool IsScrollAllowed()                const { return _isScrollAllowed; }
			inline bool IsAxisZoomAllowed()              const { return _isAxisZoomAllowed; }
			inline bool IsAxisScrollAllowed()            const { return _isAxisScrollAllowed; }


			Callback MakeRestoreAxisMinMaxCB() {
				return THISBACK2(UpdateGraphSize, _graphMin, _graphMax);
			}
			inline void setGraphMaxRangeLimit(TypeGraphCoord v) { _graphMaxLimit = v; }
			inline void setGraphMinRangeLimit(TypeGraphCoord v) { _graphMinLimit = v; }
			inline void ClearGraphRangeLimits() { _graphMaxLimit = Null; _graphMinLimit = Null; }

			virtual TypeGraphCoord applyRangeLimits(TypeGraphCoord v);
			virtual bool isInRangeLimits(TypeGraphCoord v);

			inline void SetGraphMin(TypeGraphCoord v) { Update( v, _graphMax, _screenMin, _screenMax, false ); }
			inline void SetGraphMax(TypeGraphCoord v) { Update( _graphMin, v, _screenMin, _screenMax, false ); }

			virtual void Update(TypeGraphCoord graphMin, TypeGraphCoord graphMax, TypeScreenCoord screenMin, TypeScreenCoord screenMax, bool doSwap=true, ForceUpdate forceUpdate=UPDATE_AUTO);
			inline void Update(TypeGraphCoord graphMin, TypeGraphCoord graphMax, TypeScreenCoord screenMin, TypeScreenCoord screenMax, ForceUpdate forceUpdate) {
				Update( graphMin, graphMax, screenMin, screenMax, true, forceUpdate);
			}
			inline void Update(ForceUpdate forceUpdate=UPDATE_AUTO) { Update( getGraphMin(), getGraphMax(), getScreenMin(), getScreenMax(), true, forceUpdate); }

			inline void UpdateScreenSize(TypeScreenCoord screenMin, TypeScreenCoord screenMax) { Update( _graphMin, _graphMax, screenMin, screenMax ); }
			inline void UpdateGraphSize(TypeGraphCoord graphMin, TypeGraphCoord graphMax)      { Update( graphMin, graphMax, _screenMin, _screenMax ); }
			virtual void Scroll( TypeScreenCoord offset );
			virtual void Zoom( double factor );

			void SetInverted(bool v=true) { _linConv.SetInverted(v);  incChangeStatus(); Update(); }
			bool IsInverted() const { return _linConv.IsInverted(); }
			virtual void SetScaleType(int t);
			inline int GetScaleType() const { return _scaleType; }
			String GetConversionType() const { return _convFctName; }

			void SetConvFct(TypeConvertFct convertFct, TypeConvertFct unConvertFct, const char* convTypeName);
			void SetConvStd();
			void SetConvLog();
			void SetConvPow10();

			inline TypeScreenCoord toScreen(const TypeGraphCoord v) const { return _linConv.toScreen( _convertFct(v) ); }
			inline TypeGraphCoord  toGraph(const TypeScreenCoord v) const { return _unConvertFct( _linConv.toGraph(v) ); }
	};



	class MCoordinateConverter {
		private:
			const CoordinateConverter* xcc;
			const CoordinateConverter* ycc;

		public:
			inline void SetXCoordConverter( CoordinateConverter* cc ) { xcc = cc; }
			inline void SetYCoordConverter( CoordinateConverter* cc ) { ycc = cc; }

			inline const CoordinateConverter* GetXCoordConverter() const { return xcc; }
			inline const CoordinateConverter* GetYCoordConverter() const { return ycc; }
			
			inline RectGraph GetGraphMinMax() const { return RectGraph( xcc->getGraphMin(), ycc->getGraphMin(), xcc->getGraphMax(), ycc->getGraphMax() ); }
			
			MCoordinateConverter(const MCoordinateConverter& mcc)
			: xcc(mcc.xcc)
			, ycc(mcc.ycc)
			{}

			MCoordinateConverter(CoordinateConverter& xCoordConv, CoordinateConverter& yCoordConv)
			: xcc(&xCoordConv)
			, ycc(&yCoordConv)
			{}

			MCoordinateConverter(CoordinateConverter* xCoordConv, CoordinateConverter* yCoordConv)
			: xcc(xCoordConv)
			, ycc(yCoordConv)
			{}
			
			inline TypeGraphCoord ToGraphX(const TypeScreenCoord p) const { return  xcc->toGraph(p); }
			inline TypeGraphCoord ToGraphY(const TypeScreenCoord p) const { return  ycc->toGraph(p); }
			inline PointGraph     ToGraph( const PointScreen& p)     const { return  PointGraph(ToGraphX(p.x), ToGraphY(p.y)); }
			inline RectGraph ToGraph(const RectScreen& p) const {
				RectGraph r(ToGraphX(p.left), ToGraphY(p.top), ToGraphX(p.right), ToGraphY(p.bottom));
				r.Normalize();
				return r;
			}

			inline TypeScreenCoord ToScreenX(const TypeGraphCoord p) const { return xcc->toScreen(p); }
			inline TypeScreenCoord ToScreenY(const TypeGraphCoord p) const { return ycc->toScreen(p); }
			inline PointScreen     ToScreen( const PointGraph& p)    const { return PointScreen(ToScreenX(p.x), ToScreenY(p.y)); }
			inline RectScreen ToScreen(const RectGraph& p) const {
				RectGraph r(ToScreenX(p.left), ToScreenY(p.top), ToScreenX(p.right), ToScreenY(p.bottom));
				r.Normalize();
				return r;
			}
	};


	template<class STREAM>
	STREAM& operator<<(STREAM& str, CoordinateConverter v)
	{
		str << "\n CoordinateConverter :   " << v.GetConversionType();
		str << "\n     - G[" << v.getGraphMin() << ", " << v.getGraphMax() << "] ==> range = " << v.getGraphRange();
		str << "\n     - S[" << v.getScreenMin() << ", " << v.getScreenMax()<< "]  ==> range = " << v.getScreenRange();

		str << "\n     - TEST :  G["<< v.getGraphMin() <<                          "] => S " << v.toScreen(v.getGraphMin());
		str << "\n               G["<< (v.getGraphMin()+v.getGraphMax())/2.0 <<    "] => S " << v.toScreen((v.getGraphMin()+v.getGraphMax())/2.0);
		str << "\n               G["<< v.getGraphMax() <<                          "] => S " << v.toScreen(v.getGraphMax());
		str << "\n               S["<< v.getScreenMin() <<                         "] => G " << v.toGraph(v.getScreenMin());
		str << "\n               S["<< (v.getScreenMin()+v.getScreenMax())/2.0 <<  "] => G " << v.toGraph((v.getScreenMin()+v.getScreenMax())/2.0);
		str << "\n               S["<< v.getScreenMax() <<                         "] => G " << v.toGraph(v.getScreenMax());

		return str;
	}

} // namespace GraphDraw_ns

typedef GraphDraw_ns::CoordinateConverter GraphGConv; // Needed by '.USC' file

#endif
