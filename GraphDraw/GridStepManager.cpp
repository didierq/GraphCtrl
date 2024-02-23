#include "GraphDraw.h"

#define GRIDLOG(a) //RLOG(a)

namespace Upp {
namespace GraphDraw_ns
{

	GridStepManager::GridStepManager(CoordinateConverter& coordConv)
	: _textSize(30)
	, _nbMaxSteps(  Upp::min((unsigned int)15, (unsigned int)NB_MAX_STEPS) )
	, _currentStep( 0 )
	, _coordConverter( coordConv )
	{
		setStdGridSteps();
		UpdateGridSteps();
	}
	GridStepManager::GridStepManager(unsigned int nbSteps, unsigned int currStep, CoordinateConverter& coordConv)
	: _textSize(30)
	, _nbMaxSteps( Upp::max((unsigned int)5, Upp::min(nbSteps, (unsigned int)NB_MAX_STEPS) ) )
	, _currentStep( currStep )
	, _coordConverter( coordConv )
	{
		setStdGridSteps();
		UpdateGridSteps();
	}
	
	TypeGraphCoord  GridStepManager::GetNormalizedStep(TypeGraphCoord  range, unsigned int nbMaxSteps)
	{
		int e = 0;
		double s = Upp::normalize(range/(nbMaxSteps+1), e);
		double sign = 1;
		if (s<0) sign = -1;
	
		s = sign*s;
		if     ( (s>2) && (s<=5)  ) { s = 5; }
		else if( (s>1) && (s<=2)  ) { s = 2; }
		else if( (s>5) && (s<=10) ) { s = 1; e++; }
		else   { s = 1; }
		return sign * s * Upp::ipow10(e);
	}


	TypeGraphCoord  GridStepManager::GetGridStartValue(TypeGraphCoord  pstepValue, TypeGraphCoord pgraphMin)
	{
		TypeGraphCoord res;
		TypeGraphCoord stepValue = pstepValue;
		TypeGraphCoord graphMin = pgraphMin;
		res = (((Upp::int64)(graphMin/stepValue) ) * stepValue);
		if (res < pgraphMin)// res = pgraphMin;
		{
			res = ((Upp::int64)(graphMin/stepValue + 1.0 - std::numeric_limits<TypeGraphCoord>::epsilon()) ) * stepValue;
		}
		return res;
	}

	bool GridStepManager::SetTextMaxSize(double textSize)
	{
		textSize *= 2;
		if ( _textSize < textSize) {
			if ( textSize/_textSize > 1.2) {
				//RLOG("> SetTextMaxSize(>1.2)(" << textSize << ")  old  _textSize=" << _textSize  <<  "  ---UPDATED---");
				_textSize = textSize;
				updateNeeded = true;
				return true;
			}
		} else {
			if (textSize/_textSize < 0.5) {
				//RLOG("> SetTextMaxSize(<0.5)(" << textSize << ")  old  _textSize=" << _textSize  <<  "  ---UPDATED---");
				_textSize = textSize;
				updateNeeded = true;
				return true;
			}
		}
		return false;
	}

	
	void GridStepManager::stdGridStepCalcCbk(GridStepManager& gridStepManager, CoordinateConverter& coordConv, const int scale )
	{
		const unsigned int nbMaxSteps = gridStepManager.GetNbMaxSteps();
		GridStepData* gridStepData = gridStepManager.GetGridStepData();
		TypeGraphCoord gridStepValue = GetNormalizedStep( (float)coordConv.getSignedGraphRange(), nbMaxSteps ); // DO NOT REMOVE (float) ==> prevents artifacts du to range precision errors when scrolling  (ex: range changes from 14.000000000000052 to 13.99999999999997)
		TypeGraphCoord gridStartValue = GetGridStartValue( gridStepValue, coordConv.getGraphMin() );

		unsigned int nbSteps = (unsigned int)tabs((coordConv.getGraphMax() - gridStartValue) / gridStepValue);
		
		if (nbSteps > nbMaxSteps) {
			nbSteps = nbMaxSteps;
		}
		gridStepManager.SetNbSteps(nbSteps);
	
		GRIDLOG("stdGrid [" << (long) &gridStepManager << "] ==============");
		// fill step values ==> used by gridStepIterator
		for (unsigned int c=0; c<nbSteps+1; ++c) {
			gridStepData[c].stepGraphValue = gridStartValue + gridStepValue*c;
			gridStepData[c].drawTickText = 1;// ==> draw tick text
			GRIDLOG("stdGrid [" << (long) &gridStepManager << "]    - step["<< c <<"] = " << gridStepData[c].stepGraphValue );
		}
		GRIDLOG("stdGrid [" << (long) &gridStepManager << "]  SignedRange   =" << coordConv.getSignedGraphRange() );
		GRIDLOG("stdGrid [" << (long) &gridStepManager << "]  getGraphMin   =" << coordConv.getGraphMin() );
		GRIDLOG("stdGrid [" << (long) &gridStepManager << "]  getGraphMax   =" << coordConv.getGraphMax() );
		GRIDLOG("stdGrid [" << (long) &gridStepManager << "]  gridStartValue=" << gridStartValue );
		GRIDLOG("stdGrid [" << (long) &gridStepManager << "]  gridStepValue =" << gridStepValue );
		GRIDLOG("stdGrid [" << (long) &gridStepManager << "]    screenRange =" << coordConv.getScreenRange() );
		GRIDLOG("stdGrid [" << (long) &gridStepManager << "]    screenMin   =" << coordConv.getScreenMin() );
		GRIDLOG("stdGrid [" << (long) &gridStepManager << "]    screenMax   =" << coordConv.getScreenMax() );
		GRIDLOG("stdGrid [" << (long) &gridStepManager << "]  nbSteps       =" << nbSteps );
		GRIDLOG("stdGrid [" << (long) &gridStepManager << "]  nbMaxSteps    =" << nbMaxSteps );
		//GRIDLOG("stdGrid [" << (long) this << "]  _textSize     =" << _textSize );
	}

	
	void GridStepManager::log10GridStepCalcCbk(GridStepManager& gridStepManager, CoordinateConverter& coordConv, const int scale )
	{
		const unsigned int nbMaxSteps = gridStepManager.GetNbMaxSteps();
		GridStepData* gridStepData = gridStepManager.GetGridStepData();
		const double rangeFactor = coordConv.getGraphMax()/coordConv.getGraphMin();
		if ( rangeFactor < 10 ) {
			// if less than 1 to 10 ==> fallback to standard steps (no LOG)
			stdGridStepCalcCbk(gridStepManager, coordConv, scale);
		}
		else
		{
			const TypeGraphCoord logRangeFactor = floor(log10(rangeFactor));
			TypeGraphCoord logStepValue = (int) GetNormalizedStep( logRangeFactor, nbMaxSteps );
			if ((int)logStepValue == 0) logStepValue = 1;
			
			TypeGraphCoord gridStartValue =  GetGridStartValue(logStepValue, log10(coordConv.getGraphMin()));
			--gridStartValue;
			unsigned int nbLogSteps = (unsigned int) ( (log10(coordConv.getGraphMax())-gridStartValue) / logStepValue);
			if (nbLogSteps > nbMaxSteps) {
				nbLogSteps = nbMaxSteps;
			}
			
			TypeGraphCoord logStepDensity = 2;
			if ( nbLogSteps > 0 ) logStepDensity = (nbMaxSteps*logStepValue)/logRangeFactor;
	
			GRIDLOG("============================");
			GRIDLOG("log10  getGraphMin   =" << coordConv.getGraphMin() );
			GRIDLOG("log10  getGraphMax   =" << coordConv.getGraphMax() );
			GRIDLOG("log10  rangeFactor   =" << rangeFactor );
			GRIDLOG("log10  logRangeFactor=" << logRangeFactor );
			GRIDLOG("log10  logStepValue  =" << logStepValue );
			GRIDLOG("log10  gridStartValue=" << gridStartValue );
			GRIDLOG("log10  nbMaxSteps    =" << nbMaxSteps );
			GRIDLOG("log10  nbLogSteps    =" << nbLogSteps );
			GRIDLOG("log10  logStepDensity=" << logStepDensity );
			//GRIDLOG("log10  _textSize     =" << _textSize );
	
			// fill step values ==> used by gridStepIterator
			unsigned int nbSteps = 0;
			for (unsigned int c=0; c<(nbLogSteps+1); ++c)
			{
				double stepValue = pow( 10, gridStartValue + logStepValue*c );
				double currVal = stepValue;
	
				if ( (currVal > coordConv.getGraphMin()) && (currVal < coordConv.getGraphMax())) {
					gridStepData[nbSteps].drawTickText = 1; // ==> draw tick text
					gridStepData[nbSteps].tickLevel = 0;
					gridStepData[nbSteps].stepGraphValue = currVal;
					++nbSteps;
				}
				currVal += stepValue;
	
				typedef struct {
					bool isStep[9];
					bool displayText[9];
				} Log10Steps;
				
				const Log10Steps* logSteps = 0;
				if (logStepDensity < 2. || logStepValue>1)
				{}
				else if (logStepDensity < 3.) {
					static const Log10Steps tmpLogSteps = {
						//1 2 3 4 5 6 7 8 9
						{ 1,0,1,0,1,0,1,0,1},
						{ 1,0,0,0,1,0,0,0,0}
					};
					logSteps = &tmpLogSteps;
				} else if (logStepDensity < 5.) {
					static const Log10Steps tmpLogSteps = {
						//1 2 3 4 5 6 7 8 9
						{ 1,1,1,1,1,1,1,1,1},
						{ 1,1,0,0,1,0,0,0,0}
					};
					logSteps = &tmpLogSteps;
				} else if (logStepDensity < 7.) {
					static const Log10Steps tmpLogSteps = {
						//1 2 3 4 5 6 7 8 9
						{ 1,1,1,1,1,1,1,1,1},
						{ 1,1,1,0,1,0,0,0,0}
					};
					logSteps = &tmpLogSteps;
				} else if (logStepDensity < 11.) {
					static const Log10Steps tmpLogSteps = {
						//1 2 3 4 5 6 7 8 9
						{ 1,1,1,1,1,1,1,1,1},
						{ 1,1,1,1,1,0,1,0,0}
					};
					logSteps = &tmpLogSteps;
				}
				else
				{
					static const Log10Steps tmpLogSteps = {
						//1 2 3 4 5 6 7 8 9
						{ 1,1,1,1,1,1,1,1,1},
						{ 1,1,1,1,1,1,1,1,1}
					};
					logSteps = &tmpLogSteps;
				}
				// fill log steps according to desired pattern configured above
				if (logSteps) {
					for (unsigned int l=1; l < 9; ++l)
					{
						if (logSteps->isStep[l]) {
							if ( (currVal > coordConv.getGraphMin()) && (currVal < coordConv.getGraphMax())) {
								gridStepData[nbSteps].drawTickText = logSteps->displayText[l];
								gridStepData[nbSteps].stepGraphValue = currVal;
								gridStepData[nbSteps].tickLevel = 1-logSteps->displayText[l];
								++nbSteps;
							}
						}
						currVal += stepValue;
					}
				}
				gridStepManager.SetNbSteps(nbSteps-1);
				GRIDLOG("log10  step[" << c << "] = " << gridStepData[c].stepGraphValue << "     nbLogSteps="<<nbLogSteps);
			}
		}
	}
	
	void GridStepManager::dateGridStepCalcCbk(GridStepManager& gridStepManager, CoordinateConverter& coordConv, const int scale)
	{
		const unsigned int nbMaxSteps = gridStepManager.GetNbMaxSteps();
		GridStepData* gridStepData = gridStepManager.GetGridStepData();
		Date dateRange;      dateRange.Set((int)(coordConv.getSignedGraphRange()));
		Date graphStartDate; graphStartDate.Set((int)(coordConv.getGraphMin()));
		unsigned int nbSteps = gridStepManager.GetNbSteps();
		Date graphEndDate;   graphEndDate.Set((int)(coordConv.getGraphMax()));
		// ===================
		//        YEARS
		// ===================
		if (dateRange.year >= 7) {
			int yearRange = dateRange.year;
			int normalizedYearStep = (int) GetNormalizedStep( yearRange, nbMaxSteps );
			if (normalizedYearStep==0) normalizedYearStep = 1;
	
			Date dateIter(0,1,1);
			dateIter.year = (decltype(dateIter.year)) GetGridStartValue( normalizedYearStep, graphStartDate.year+1 );
			if ( dateIter < graphStartDate ) {
				GRIDLOG("     #### YEAR  STEP_2 :    dateIter="<< dateIter << "      graphStartDate="<< graphStartDate);
				dateIter.year += normalizedYearStep;
			}
	
			nbSteps = (unsigned int)tabs((graphEndDate.year - dateIter.year) / normalizedYearStep);
			if (nbSteps > nbMaxSteps) {
				nbSteps = nbMaxSteps;
			}
			else if (nbSteps==0) nbSteps = 1;

	
			GRIDLOG("YEAR  range=" << yearRange << "years    normalizedStep = "<< normalizedYearStep << " years     nbSteps=" << nbSteps<< "       graphStartDate = "<< dateIter);
			for (unsigned int c=0; c<= nbSteps; ++c) {
				Time tmp = ToTime(dateIter);
				gridStepData[c].stepGraphValue = (TypeGraphCoord)(tmp.Get());
				GRIDLOG("     YEAR  STEP :    dateIter="<< dateIter);
				dateIter = AddYears(dateIter, normalizedYearStep);
			}
		}
		// ===================
		//        MONTHS
		// ===================
		else if ((dateRange.month >= 7) || (dateRange.year > 0 )) {
			int monthRange = dateRange.year*12 + dateRange.month;
			Vector<double> monthSteps;
			monthSteps << 1 << 2 << 3 << 4 << 6 << 12 << 24 << 48;
			int normalizedMonthStep = (int)GetNormalizedStep( monthRange, monthSteps, nbMaxSteps );
			if (normalizedMonthStep==0) normalizedMonthStep = 1;
	
			Date dateIter(0,1,1);
	
			int nbMonths = (int) GetGridStartValue( normalizedMonthStep, graphStartDate.year*12+graphStartDate.month-1 );
			dateIter.year = (decltype(dateIter.year))(nbMonths/12);
			dateIter.month= (decltype(dateIter.month))(nbMonths - dateIter.year*12 + 1);
			dateIter.day = 1;
			GRIDLOG("     MONTH  STEP_1 : "<< dateIter << "       nbMonths=" << nbMonths << "     graphStartDate=" << graphStartDate);
			if ( dateIter < graphStartDate ) {
				GRIDLOG("     #### MONTH  STEP_2 :    dateIter="<< dateIter << "      graphStartDate="<< graphStartDate);
				dateIter = AddMonths(dateIter, normalizedMonthStep);
			}
	
			nbSteps = (unsigned int)tabs(((graphEndDate.year-dateIter.year)*12 + (graphEndDate.month-dateIter.month)) / normalizedMonthStep);
			if (nbSteps > nbMaxSteps) {
				nbSteps = nbMaxSteps;
			}
			else if (nbSteps==0) nbSteps = 1;

			GRIDLOG("MONTH  range=" << monthRange << " months    normalizedMonthStep = "<< normalizedMonthStep << " months     nbSteps=" << nbSteps<< "       graphStartDate = "<< graphStartDate);
			for (unsigned int c=0; c<= nbSteps; ++c) {
				Time tmp = ToTime(dateIter);
				gridStepData[c].stepGraphValue = (TypeGraphCoord)(tmp.Get());
				GRIDLOG("     MONTH  STEP : "<< dateIter);
				dateIter = AddMonths(dateIter, normalizedMonthStep);
			}
		}
		// ======
		//  DAYS
		// ======
		else {
			TypeGraphCoord gridStartValue;
			Upp::int64 normalizedStep;
			Vector<double> daySteps;
			daySteps << 1 << 2  << 3 << 4 << 5 << 7 << 14 << 28 << 56;
			normalizedStep = (Upp::int64)(GetNormalizedStep( dateRange.Get(), daySteps, nbMaxSteps ));
			if (normalizedStep == 0) normalizedStep = 1;
			gridStartValue = GetGridStartValue( normalizedStep, coordConv.getGraphMin() );
			nbSteps = (unsigned int)tabs((graphEndDate.Get() - gridStartValue) / normalizedStep);
	
			if (nbSteps > nbMaxSteps) {
				nbSteps = nbMaxSteps;
			}
			else if (nbSteps==0) nbSteps = 1;
	
			GRIDLOG("D/H/M/S  ==>  nbSteps=" << nbSteps << "      gridStepValue=" << normalizedStep);
			for (unsigned int c=0; c<nbSteps+1; ++c)
			{
				gridStepData[c].stepGraphValue = gridStartValue + normalizedStep * c;
			}
		}
		gridStepManager.SetNbSteps(nbSteps);
	}
	
	void GridStepManager::timeGridStepCalcCbk(GridStepManager& gridStepManager, CoordinateConverter& coordConv, const int scale )
	{
		enum {
			DAY_sec     = 24*60*60,
			HOUR_sec    = 60*60,
			MINUTES_sec = 60,
		};
		const unsigned int nbMaxSteps = gridStepManager.GetNbMaxSteps();
		unsigned int nbSteps = gridStepManager.GetNbSteps();
		GridStepData* gridStepData = gridStepManager.GetGridStepData();
		Time timeOrigin;     timeOrigin.Set(0);
		Time graphStartTime; graphStartTime.Set((int64)(coordConv.getGraphMin()));
		Time graphEndTime;   graphEndTime.Set((int64)(coordConv.getGraphMax()));
		Time timeRange;      timeRange.Set((int64)(coordConv.getSignedGraphRange()));
	
		GRIDLOG("\n--timeGridStepCalcCbk--   range=" << timeRange << "       GraphMin = "<< graphStartTime << "     GraphMax = " << graphEndTime);
	
		// ===================
		//        YEARS
		// ===================
		if (timeRange.year >= 7) {
			Date graphStartDate( graphStartTime.year, graphStartTime.month, graphStartTime.day);
			Date graphEndDate( graphEndTime.year, graphEndTime.month, graphEndTime.day);
			int yearRange = timeRange.year;
			int normalizedYearStep = (int)GetNormalizedStep( yearRange, nbMaxSteps );
			if (normalizedYearStep==0) normalizedYearStep = 1;
	
			Date dateIter(0,1,1);
			dateIter.year = (decltype(dateIter.year)) GetGridStartValue( normalizedYearStep, graphStartDate.year+1 );
			if ( dateIter < graphStartDate ) {
				GRIDLOG("     #### YEAR  STEP_2 :    dateIter="<< dateIter << "      graphStartDate="<< graphStartDate);
				dateIter.year += normalizedYearStep;
			}
	
			nbSteps = (unsigned int)tabs((graphEndDate.year - dateIter.year) / normalizedYearStep);
			if (nbSteps > nbMaxSteps) {
				nbSteps = nbMaxSteps;
			}
			else if (nbSteps==0) nbSteps = 1;
	
			GRIDLOG("YEAR  range=" << yearRange << "years    normalizedStep = "<< normalizedYearStep << " years     nbSteps=" << nbSteps<< "       graphStartDate = "<< dateIter);
			for (unsigned int c=0; c<= nbSteps; ++c) {
				Time tmp = ToTime(dateIter);
				gridStepData[c].stepGraphValue = (TypeGraphCoord) (tmp.Get());
				GRIDLOG("     YEAR  STEP :    dateIter="<< dateIter);
				dateIter = ToTime(AddYears(dateIter, normalizedYearStep));
			}
		}
		// ===================
		//        MONTHS
		// ===================
		else if ((timeRange.month >= 7) || (timeRange.year > 0 )) {
			Date graphStartDate( graphStartTime.year, graphStartTime.month, graphStartTime.day);
			Date graphEndDate( graphEndTime.year, graphEndTime.month, graphEndTime.day);
			int monthRange = timeRange.year*12+timeRange.month-1 ;
			Vector<double> monthStep;
			monthStep << 1 << 2 << 3 << 4 << 6 << 12 << 24 << 48;
			int normalizedMonthStep = (int) GetNormalizedStep( monthRange, monthStep, nbMaxSteps );
			if (normalizedMonthStep==0) normalizedMonthStep = 1;
	
			Date dateIter(0,1,1);
	
			int nbMonths = (int) GetGridStartValue( normalizedMonthStep, graphStartDate.year*12+graphStartDate.month-1 );
			dateIter.year = (decltype(dateIter.year))(nbMonths/12);
			dateIter.month= (decltype(dateIter.month))(nbMonths - dateIter.year*12 + 1);
			dateIter.day = 1;
			GRIDLOG("     MONTH  STEP_1 : "<< dateIter << "       nbMonths=" << nbMonths << "     graphStartDate=" << graphStartDate);
			if ( dateIter < graphStartDate ) {
				GRIDLOG("     #### MONTH  STEP_2 :    dateIter="<< dateIter << "      graphStartDate="<< graphStartDate);
				dateIter = AddMonths(dateIter, normalizedMonthStep);
			}
	
			nbSteps = (unsigned int)tabs(((graphEndDate.year-dateIter.year)*12 + (graphEndDate.month-dateIter.month)) / normalizedMonthStep);
			if (nbSteps > nbMaxSteps) {
				nbSteps = nbMaxSteps;
			}
			else if (nbSteps==0) nbSteps = 1;
	
			GRIDLOG("MONTH  range=" << monthRange << " months    normalizedMonthStep = "<< normalizedMonthStep << " months     nbSteps=" << nbSteps<< "       graphStartDate = "<< graphStartDate);
			for (unsigned int c=0; c<= nbSteps; ++c) {
				Time tmp = ToTime(dateIter);
				gridStepData[c].stepGraphValue = (TypeGraphCoord) (tmp.Get());
				GRIDLOG("     MONTH  STEP : "<< dateIter);
				dateIter = AddMonths(dateIter, normalizedMonthStep);
			}
		}
		// ================================
		//  DAY / HOUR / MINUTES / SECONDS
		// ================================
		else {
			TypeGraphCoord gridStartValue;
			Upp::int64 normalizedStep;
			Vector<double> secondsSteps;
			secondsSteps << 1 << 2 << 5 << 10 << 15 << 20 << 30;
			secondsSteps << MINUTES_sec << MINUTES_sec*2 << MINUTES_sec*3 << MINUTES_sec*5 << MINUTES_sec*10 << MINUTES_sec*15 << MINUTES_sec*20 << MINUTES_sec*30;
			secondsSteps << HOUR_sec << HOUR_sec*2 << HOUR_sec*3 << HOUR_sec*4 << HOUR_sec*6 << HOUR_sec*8 << HOUR_sec*12;
			secondsSteps << DAY_sec << DAY_sec*2  << DAY_sec*3 << DAY_sec*4 << DAY_sec*5 << DAY_sec*7 << DAY_sec*14 << DAY_sec*28 << DAY_sec*56;
			normalizedStep = (Upp::int64) GetNormalizedStep( (timeRange - timeOrigin), secondsSteps, nbMaxSteps );
			if (normalizedStep == 0) normalizedStep = 1;
			gridStartValue = GetGridStartValue( normalizedStep, coordConv.getGraphMin() );
			nbSteps = (unsigned int)tabs((graphEndTime.Get() - gridStartValue) / normalizedStep);
	
			if (nbSteps > nbMaxSteps) {
				nbSteps = nbMaxSteps;
			}
			else if (nbSteps==0) nbSteps = 1;
	
			GRIDLOG("D/H/M/S  ==>  nbSteps=" << nbSteps << "      gridStepValue=" << normalizedStep);
			gridStepData[0].stepGraphValue = gridStartValue;
			for (unsigned int c=1; c<nbSteps+1; ++c)
			{
				gridStepData[c].stepGraphValue = gridStartValue + normalizedStep * c;
				Time time, time2;
				time.Set( (int64) (gridStepData[c].stepGraphValue) );
				time2.Set( (int64) (gridStepData[c-1].stepGraphValue) );
				if ((time.month - time2.month) == 1  ||  (time.month - time2.month)==-11) {
					Time addTime = time;
					addTime.day = 1;
					addTime.minute = 0;
					addTime.second = 0;
					TypeGraphCoord t = (TypeGraphCoord)(addTime.Get());
					if (( t - gridStepData[c-1].stepGraphValue ) < (normalizedStep/2) ) gridStepData[c-1].stepGraphValue = t;
					else                                                                    gridStepData[c].stepGraphValue = t;
					GRIDLOG("D/H/M/S  ==>  Modified step at: " << addTime);
				}
			}
		}
		gridStepManager.SetNbSteps(nbSteps);
	}
}

END_UPP_NAMESPACE
