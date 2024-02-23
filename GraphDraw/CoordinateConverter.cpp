#include "GraphDraw.h"



namespace Upp {
namespace GraphDraw_ns {

	CoordinateConverter::CoordinateConverter(CoordinateConverterOwner& owner)
	: _owner(owner)
	, _isZoomAllowed(true)
	, _isScrollAllowed(true)
	, _isAxisZoomAllowed(true)
	, _isAxisScrollAllowed(true)
	, _screenMin(0)
	, _screenMax(10)
	, _screenRange(_screenMax-_screenMin)
	, _graphMin(0)
	, _graphMax(10)
	, _graphRange(_graphMax - _graphMin)
	{
		SetConvStd();
		Update( 0, 100, 0, 100);
	}
	
	CoordinateConverter::CoordinateConverter(CoordinateConverterOwner& owner, TypeGraphCoord graphMin, TypeGraphCoord graphMax, TypeScreenCoord screenMin, TypeScreenCoord screenMax)
	: _owner(owner)
	, _isZoomAllowed(true)
	, _isScrollAllowed(true)
	, _isAxisZoomAllowed(true)
	, _isAxisScrollAllowed(true)
	, _screenMin(0)
	, _screenMax(10)
	, _screenRange(_screenMax-_screenMin)
	, _graphMin(0)
	, _graphMax(100)
	, _graphRange(_graphMax - _graphMin)
	{
		SetConvStd();
		Update( graphMin, graphMax, screenMin, screenMax);
	}
	
	CoordinateConverter::~CoordinateConverter() {
		UnlinkAll();
	}
	
	void CoordinateConverter::UpdateLinks(LinkUpdateStrategy strategy) {
		for (int l=(links.GetCount()-1); l>=0; --l) {
			if (links[l]->linkStatusCounter != linkStatusCounter) {
				links[l]->linkStatusCounter = linkStatusCounter;
				if (strategy & LINK_UPDATE_LIMITS) {
					links[l]->_graphMinLimit = _graphMinLimit;
					links[l]->_graphMaxLimit = _graphMaxLimit;
					links[l]->Update();
				}
				if (strategy & LINK_UPDATE_RANGE) {
					links[l]->UpdateGraphSize(_graphMin, _graphMax);
				}
				links[l]->_owner.RefreshWhenLinkUpdate();
				links[l]->UpdateLinks(strategy); // update indirect links
			}
		}
	}
	/*
	void CoordinateConverter::Link(CoordinateConverter& local, CoordinateConverter& other) {
		if (local.Link(other) ) {
			other.Link(local);
		}
	}
	
	void CoordinateConverter::Unlink(CoordinateConverter& local, CoordinateConverter& other) {
		local.Unlink(other);
	}
	*/
	bool CoordinateConverter::Link(CoordinateConverter& conv) {
		if (links.Find(&conv) >= 0) return false;
		links.Add(&conv);
		return true;
	}
	
	void CoordinateConverter::Unlink(CoordinateConverter& conv) {
		if (links.Find(&conv) < 0) return;
		links.RemoveKey(&conv);
		conv.Unlink(*this);
	}
	
	void CoordinateConverter::UnlinkAll() {
		while (links.GetCount()>0) {
			Unlink(*(links[0]));
		}
	}
	
	TypeGraphCoord CoordinateConverter::applyRangeLimits(TypeGraphCoord v) {
		if ( (!IsNull(_graphMaxLimit)) && (v > _graphMaxLimit) ) { v = _graphMaxLimit; }
		if ( (!IsNull(_graphMinLimit)) && (v < _graphMinLimit) ) { v = _graphMinLimit; }
		return v;
	}
	
	bool CoordinateConverter::isInRangeLimits(TypeGraphCoord v) {
		if ( (!IsNull(_graphMaxLimit)) && (v > _graphMaxLimit) ) { return false; }
		if ( (!IsNull(_graphMinLimit)) && (v < _graphMinLimit) ) { return false; }
		return true;
	}
	
	void CoordinateConverter::Update(TypeGraphCoord graphMin, TypeGraphCoord graphMax, TypeScreenCoord screenMin, TypeScreenCoord screenMax, bool doSwap, ForceUpdate forceUpdate)
	{
		if (doSwap && (graphMin>graphMax)) Swap(graphMin, graphMax);

		if ( screenMin!=_screenMin  || screenMax!=_screenMax || _graphMin!=graphMin || _graphMax!=graphMax || forceUpdate==UPDATE_FORCED) {
			//LOG("CoordinateConverter.update(" << graphMin << ", " << graphMax  << ", " << screenMin<< ", " << screenMax << " )" );
			_graphMin = applyRangeLimits(graphMin);
			_graphMax = applyRangeLimits(graphMax);
			_screenMin = screenMin;
			_screenMax = screenMax;
			_graphRange =  tabs(_graphMax - _graphMin);
			_screenRange = tabs(_screenMax - _screenMin);
	
			_fctGraphMin = _convertFct(_graphMin);
			_fctGraphMax = _convertFct(_graphMax);
			_graphToScreenScale = (decltype(_graphToScreenScale))( (_screenMax - _screenMin) / (_fctGraphMax - _fctGraphMin));
			_screenToGraphScale = (decltype(_screenToGraphScale))( (_fctGraphMax - _fctGraphMin) / (_screenMax - _screenMin));
			_linConv.Update(_fctGraphMin, _fctGraphMax, _screenMin, _screenMax);
			incChangeStatus();
		}
	}

	void CoordinateConverter::Scroll( TypeScreenCoord offset ) {
		TypeGraphCoord graphMin = toGraph( _screenMin - offset );
		TypeGraphCoord graphMax = toGraph( _screenMax - offset );
		if ( isInRangeLimits(graphMin) && isInRangeLimits(graphMax)) {
			UpdateGraphSize( graphMin, graphMax );
		}
	}
	
	void CoordinateConverter::Zoom( double factor ) {
		TypeScreenCoord addRange=(TypeScreenCoord)((_screenRange*(factor-1.0))/2.0);
		UpdateGraphSize( toGraph( _screenMin - addRange ),
						 toGraph( _screenMax + addRange )
						);
	}
	
	void CoordinateConverter::SetScaleType(int t) {
		switch(t) {
			case AXIS_SCALE_STD:
				SetConvStd();
				break;
			case AXIS_SCALE_LOG:
				SetConvLog();
				break;
			case AXIS_SCALE_POW10:
				SetConvPow10();
				break;
			default:
				SetConvStd();
				RLOG("## ERROR ## : CoordinateConverter::SetScaleType( " << t << " ) : UNKNOWN SCALE TYPE");
//				ASSERT_(false, MISSING_OR_WRONG_SCALE_TYPE);
				break;
		}
	}
	
	void CoordinateConverter::SetConvFct(TypeConvertFct convertFct, TypeConvertFct unConvertFct, const char* convTypeName) {
		_convFctName = convTypeName;
		_convertFct = convertFct;
		_unConvertFct = unConvertFct;
		ClearGraphRangeLimits(); // TODO  must be removed
		Update(UPDATE_FORCED);
	}
	
	void CoordinateConverter::SetConvStd() {
		SetConvFct(_defautFct, _defautFct, "STD");
		_scaleType = AXIS_SCALE_STD;
		Update(UPDATE_FORCED);
	}
	
	void CoordinateConverter::SetConvLog() {
		setGraphMinRangeLimit(0.00000000000001);  // TODO  must managed differently
		Update(UPDATE_FORCED);
		SetConvFct(_logFct,    _pow10Fct,  "LOG");
		_scaleType = AXIS_SCALE_LOG;
		Update(UPDATE_FORCED);
	}
	
	void CoordinateConverter::SetConvPow10() {
		SetConvFct(_pow10Fct,  _logFct,    "10^x");
		_scaleType = AXIS_SCALE_POW10;
		Update(UPDATE_FORCED);
	}

}
}

