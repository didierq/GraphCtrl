#ifndef _GraphCtrl_GridStepManager_h_
#define _GraphCtrl_GridStepManager_h_

#include <limits>

namespace GraphDraw_ns
{

	// ============================
	//    GridStepManager   CLASS
	// ============================
	class  GridStepData {
		public:
			int                 tickLevel;    // 0:Major tick    1:secondary tick    2: ....
			bool                drawTickText;
			Size_<Upp::uint16>  textSize;
			TypeGraphCoord      stepGraphValue;
			String              text;
			Value               customParams; // general purpose step parameter holder : filled when calculating the steps
			
			GridStepData()
			: tickLevel(0)
			, drawTickText(true)
			{
			}
			
			String ToString() const {
				String str;
				str << "LVL:" << tickLevel << "   drawText="<<drawTickText<< "    value="<< stepGraphValue<<"      text="<< text;
				return str;
			}
	};
	
	class const_GridStepIterator {
		protected:
			unsigned int _nbSteps;     // current step range (according to grid step)
			unsigned int _currentStep; // current step number
			CoordinateConverter& _coordConverter;
			GridStepData* const  _stepData; // points to steps parameters array (pre-calculated by GridStepManager)

		public:
			typedef const_GridStepIterator CLASSNAME;

			const_GridStepIterator( CoordinateConverter& conv, unsigned int nbSteps, GridStepData* stepData, unsigned int currentStep)
			: _nbSteps(nbSteps)
			, _currentStep(currentStep)
			, _coordConverter(conv)
			, _stepData(stepData)
			{}
		
			const_GridStepIterator(const CLASSNAME& p)
			: _nbSteps(p._nbSteps)
			, _currentStep(p._currentStep)
			, _coordConverter(p._coordConverter)
			, _stepData(p._stepData)
			{}
		
		public:
			inline const GridStepData* operator->()     const { return _stepData + _currentStep; }

			inline bool operator==( const CLASSNAME& v) const { return( _currentStep==v._currentStep ); }
			inline bool operator!=( const CLASSNAME& v) const { return( _currentStep!=v._currentStep ); }
			inline TypeScreenCoord toScreen()           const { return _coordConverter.toScreen( _stepData[_currentStep].stepGraphValue ); }
			inline operator TypeScreenCoord()           const { return _coordConverter.toScreen( _stepData[_currentStep].stepGraphValue ); }
			inline operator String()                    const { return _stepData[_currentStep].text; }
			inline TypeGraphCoord getGraphRange()       const { return _coordConverter.getSignedGraphRange(); }
			inline unsigned int getStepNum()                     const { return _currentStep; }
			inline unsigned int getNbSteps()                     const { return _nbSteps; }
			inline bool isFirst()                       const { return (_currentStep==0); }
			inline bool isLast()                        const { return (_currentStep==(_nbSteps-1)); }

			inline const_GridStepIterator& toEnd()            { _currentStep = _nbSteps; return *this; }
			inline const_GridStepIterator& toBegin()          { _currentStep = 0; return *this; }

			// ++X
			inline const_GridStepIterator&  operator++()	  { ++_currentStep; return *this; }

			// X++
			const_GridStepIterator  operator++(int)           { const_GridStepIterator tmp(*this); ++_currentStep; return tmp; }
	};

	class GridStepIterator  : public const_GridStepIterator {
		public:
			typedef GridStepIterator CLASSNAME;

			GridStepIterator( CoordinateConverter& conv, unsigned int nbSteps, GridStepData* stepData, unsigned int currentStep) : const_GridStepIterator(conv, nbSteps, stepData, currentStep) {}
			GridStepIterator(const GridStepIterator& p) : const_GridStepIterator(p) {}
		private:
			GridStepIterator(const const_GridStepIterator& p) : const_GridStepIterator(p) {}
			
		public:

			inline const GridStepData*    operator->()  const { return _stepData + _currentStep; }
			inline GridStepData*          operator->()        { return _stepData + _currentStep; }
			inline operator TypeScreenCoord()           const { return _coordConverter.toScreen( _stepData[_currentStep].stepGraphValue ); }
			inline operator String()                    const { return _stepData[_currentStep].text; }
	};



	typedef Function< void(const const_GridStepIterator&, String&) > TypeFormatTextCbk; // IN: valueIterator,  OUT: formated value

	class GridStepManager
	{
		public:
			enum { NB_MAX_STEPS = 100 };
			typedef GridStepManager  CLASSNAME;
			typedef GridStepIterator Iterator;
			typedef const_GridStepIterator const_Iterator;
			typedef Function< void(GridStepManager&, CoordinateConverter&, const int /*scale*/) > TypeGridStepCalcCallBack;

		protected:
			double       _textSize;    // tick Text MAX Size  ( can be height or width )
			unsigned int _nbMaxSteps;  // steps range is : [0, _nbMaxSteps]
			unsigned int _nbSteps;     // current step range (according to grid step)
			unsigned int _currentStep; // current step number
			CoordinateConverter& _coordConverter;
			bool updateNeeded;
			
			GridStepData   _stepDrawingParams[NB_MAX_STEPS+1]; // general purpose step parameter holder : filled when calculating the steps
			TypeGridStepCalcCallBack _updateCbk;
			ChangeStatus  coordConvLastStatus;


		public:
			GridStepManager(CoordinateConverter& coordConv);
			GridStepManager(unsigned int nbSteps, unsigned int currStep, CoordinateConverter& coordConv);
			virtual ~GridStepManager() {}
			
		private:
			// explicitly forbidden to use
			CLASSNAME& operator=( const CLASSNAME& v) { return *this; }

		public:
			static inline TypeGraphCoord  GetGridStartValue(int64           pstepValue, TypeGraphCoord pgraphMin) { return GetGridStartValue((TypeGraphCoord)pstepValue, pgraphMin); }
			static inline TypeGraphCoord  GetGridStartValue(int             pstepValue, TypeGraphCoord pgraphMin) { return GetGridStartValue((TypeGraphCoord)pstepValue, pgraphMin); }
			static        TypeGraphCoord  GetGridStartValue(TypeGraphCoord  pstepValue, TypeGraphCoord pgraphMin);
			static TypeGraphCoord  GetNormalizedStep(TypeGraphCoord range, unsigned int nbMaxSteps);
			template <class T>
			static T  GetNormalizedStep(TypeGraphCoord  range, const Vector<T>& stepValues, unsigned int nbMaxSteps)
			{
				double s = range/(nbMaxSteps+1);
				T sign = 1;
				if (s<0) sign = -1;

				s = sign*s;
				int c=0;
				while (c < stepValues.GetCount()-2) {
					if ( (s>stepValues[c]) && (s<=stepValues[c+1])  ) {
						s = stepValues[c+1];
						return sign*s;
					}
					++c;
				}
				if (c==stepValues.GetCount()-1) s = stepValues[0];
				return sign*s;
			}
			
			template <class T> static inline T GetNormalizedStep(int64 range, const Vector<T>& stepValues, unsigned int nbMaxSteps) { return GetNormalizedStep((TypeGraphCoord)range, stepValues, nbMaxSteps); }
			template <class T> static inline T GetNormalizedStep(int   range, const Vector<T>& stepValues, unsigned int nbMaxSteps) { return GetNormalizedStep((TypeGraphCoord)range, stepValues, nbMaxSteps); }

			static void stdGridStepCalcCbk(CLASSNAME& gridStepManager, CoordinateConverter& coordConv, const int scale );
			static void log10GridStepCalcCbk(CLASSNAME& gridStepManager, CoordinateConverter& coordConv, const int scale );
			static void dateGridStepCalcCbk(CLASSNAME& gridStepManager, CoordinateConverter& coordConv, const int scale );
			static void timeGridStepCalcCbk(CLASSNAME& gridStepManager, CoordinateConverter& coordConv, const int scale );

			void setCustomGridSteps(TypeGridStepCalcCallBack cbk)  { _updateCbk = cbk; updateNeeded = true; }
			
			void setStdGridSteps()                                 { _updateCbk = stdGridStepCalcCbk;   updateNeeded = true; }
			void setLogGridSteps()                                 { _updateCbk = log10GridStepCalcCbk; updateNeeded = true; }
			void setTimeGridSteps()                                { _updateCbk = timeGridStepCalcCbk;  updateNeeded = true; }
			void setDateGridSteps()                                { _updateCbk = dateGridStepCalcCbk;  updateNeeded = true; }

			virtual void UpdateGridSteps(const int scale = 1)
			{
				//RLOGBLOCK("UpdateGridSteps()");
				if ( updateNeeded || coordConvLastStatus.hasChangedUpdate(_coordConverter) ) {
					if (_textSize > 1.0) _nbMaxSteps = (unsigned int)((double)(_coordConverter.getScreenRange())/_textSize);
					_updateCbk(*this, _coordConverter, scale);
					updateNeeded = false;
				}
			}

			void SetNbSteps(unsigned int nbSteps) { _nbSteps = nbSteps; }

			unsigned int GetNbSteps() const { return _nbSteps; }
			unsigned int GetNbMaxSteps() const { return _nbMaxSteps; }
			GridStepData* GetGridStepData() { return  _stepDrawingParams; }
			const GridStepData* GetGridStepData() const { return  _stepDrawingParams; }

			bool SetTextMaxSize(double textSize);

			Iterator End() { return GridStepIterator( _coordConverter, _nbSteps+1, _stepDrawingParams, _nbSteps+1); }
			Iterator Begin() { return GridStepIterator( _coordConverter, _nbSteps+1, _stepDrawingParams, 0); }
	};



};
#endif
