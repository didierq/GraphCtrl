#include "GraphDraw.h"

/*
 * GridAxisDraw.h
 *
 *  Created on: 6 avr. 2012
 *      Author: didier
 */

namespace Upp {
namespace GraphDraw_ns
{

	void GridAxisDraw::PrePaint( int scale ) {
		//RLOGBLOCK( "GridAxisDraw::PrePaint()" );
		UpdateTickTextData(scale);
		if ( _B::IsHorizontal() ) { _gridStepManager.SetTextMaxSize( _meanTickTextsz.cx ); }
		else                      { _gridStepManager.SetTextMaxSize( _meanTickTextsz.cy ); }
		_gridStepManager.UpdateGridSteps(scale);
	}
	

	void  GridAxisDraw::SetElementPos(ElementPosition v) {
		if (v==LEFT_OF_GRAPH || v==RIGHT_OF_GRAPH) {
			_B::DisablePos(BOTTOM_OF_GRAPH);
			_B::DisablePos(TOP_OF_GRAPH);
		} else {
			_B::DisablePos(LEFT_OF_GRAPH);
			_B::DisablePos(RIGHT_OF_GRAPH);
		}
		_B::SetElementPos(v);
	}

	
	void GridAxisDraw::FitToData(FitToDataStrategy fitStrategy) {
		GraphSeriesDecoratorVector& g_series = _B::_parent->GetGSeries();
		
		double lmin = -DOUBLE_NULL;
		double lmax =  DOUBLE_NULL;
		bool doFitToData = false;
		switch(_B::GetElementPos()) {
			case LEFT_OF_GRAPH:
			case RIGHT_OF_GRAPH:
				for (int c=0; c<g_series.GetCount(); ++c) {
					if ( (fitStrategy==ALL_SERIES)  || g_series[c].IsShow() ) {
						doFitToData |= g_series[c].FitToYData(_coordConverter, lmin, lmax);
					}
				}
				break;
			case BOTTOM_OF_GRAPH:
			case TOP_OF_GRAPH:
				for (int c=0; c<g_series.GetCount(); ++c) {
					if ( (fitStrategy==ALL_SERIES)  || g_series[c].IsShow() ) {
						doFitToData |= g_series[c].FitToXData(_coordConverter, lmin, lmax);
					}
				}
				break;
			case FLOAT_OVER_GRAPH:
				break;
		}
		if (doFitToData) {
			double d = (lmax-lmin)/100.0;
			_coordConverter.UpdateGraphSize( lmin-d, lmax+d );
		}
	}
	
	GridAxisDraw& GridAxisDraw::resetAxisTextFormat() {
		_formatTextCbk = THISBACK(FormatAsDouble);
		GetCoordConverter().SetFormatCbk( [] (TypeGraphCoord v) { return FormatDouble(v,5); } );
		_gridStepManager.setStdGridSteps();
		return *this;
	}
	
	GridAxisDraw& GridAxisDraw::setAxisLogFormat(TypeFormatTextCbk cbk ) {
		if ( cbk ) _formatTextCbk = cbk;
		else       _formatTextCbk = THISBACK(FormatAsLog10);
		
		GetCoordConverter().SetFormatCbk( [] (TypeGraphCoord v) { if (v < 0.001 || v > 9999) return FormatDoubleExp(v, 3);
		                                                          else                       return FormatDouble(v,3) ;
		                                                         } );

		_gridStepManager.setLogGridSteps();
		return *this;
	}

	GridAxisDraw& GridAxisDraw::setAxisDateFormat( TypeFormatTextCbk cbk ) {
		if ( cbk ) _formatTextCbk = cbk;
		else       _formatTextCbk = THISBACK(FormatAsDate);
		GetCoordConverter().SetFormatCbk( [] (TypeGraphCoord v) {Date dat; dat.Set((int)v); return Upp::Format("%d/%d/%d",dat.day, dat.month, dat.year); } );
		_gridStepManager.setDateGridSteps();
		return *this;
	}
	
	GridAxisDraw& GridAxisDraw::setAxisTimeFormat( TypeFormatTextCbk cbk ) {
		if ( cbk ) _formatTextCbk = cbk;
		else       _formatTextCbk = THISBACK(FormatAsTime);
		//"\1[1 " << FormatTime( time, "h`hmm:ss" ) << "]"
		GetCoordConverter().SetFormatCbk( [] (TypeGraphCoord v) {Time time; time.Set((Upp::int64)v); return Upp::FormatTime( time, "h`hmm:ss" ); } );
		_gridStepManager.setTimeGridSteps();
		return *this;
	}


	void GridAxisDraw::FormatAsDouble( const const_GridStepIterator& iter, String& output ) {
		if (iter->drawTickText) {
			output = FormatDouble( iter->stepGraphValue );
		}
	}

	void GridAxisDraw::FormatAsLog10( const const_GridStepIterator& iter, String& output ) {
		if (iter->drawTickText) {
			const double d = iter->stepGraphValue;
			if (d < 0.001 || d > 9999) output << FormatDoubleExp(d, 3);//, FD_SIGN_EXP | FD_SIGN | FD_ZERO);
			else                       output << d ;
		}
	}

	void GridAxisDraw::FormatAsDate( const const_GridStepIterator& value, String& output ) {
		Date dat;
		dat.Set(int(value->stepGraphValue));
		output = Format("%d/%d/%d",dat.day, dat.month, dat.year);
	}

	void GridAxisDraw::FormatAsTime( const const_GridStepIterator& value, String& output ) {
		Time time;
		time.Set(Upp::int64( value->stepGraphValue ));
		
		TypeGraphCoord range = value.getGraphRange();
		Time timeStep;
		timeStep.Set( Upp::int64(range / value.getNbSteps()) );
		//LOG("TimeStep = " << timeStep);
		
		if (range > 7*365*24*60*60) { // 7 years
			output << "\1[1= " << time.year << "]";
		}
		else if (range > 182.5*24*60*60) { // 6 months
			if (((time.month == 1) && (time.day == 1) )
				|| value.isFirst() || value.isLast() )
			   {
				switch(_B::GetElementPos()){
					case LEFT_OF_GRAPH:
						output << "\1[1* " << time.year;
						output << " ][1 " << MonName(time.month-1) << "]";
						break;
					case RIGHT_OF_GRAPH:
						output << "\1[1 " << MonName(time.month-1) ;
						output << " ][1* " << time.year << "]";
						break;
					case BOTTOM_OF_GRAPH:
						output << "\1[1= " << MonName(time.month-1) ;
						output << "&][1*= " << time.year << "]";
						break;
					case FLOAT_OVER_GRAPH:
					case TOP_OF_GRAPH:
						output << "\1[1*= " << time.year;
						output << "&][1= " << MonName(time.month-1) << "]";
						break;
				}
			}
			else {
				output << "\1[1 " << MonName(time.month-1) << "]";
			}
		}
		else if (range > 7*24*60*60) { // 7 days
			if ( ((time.day == 1) && (time.hour==0))
					|| value.isFirst() || value.isLast() )
			{
				switch(_B::GetElementPos()){
					case LEFT_OF_GRAPH:
						output << "\1[1* " << time.year;
						output << " ][1 " << int(time.day) << " " << MonName(time.month-1) << "]";
						break;
					case RIGHT_OF_GRAPH:
						output << "\1[1 " << int(time.day) << " " << MonName(time.month-1) ;
						output << " ][1* " << time.year << "]";
						break;
					case BOTTOM_OF_GRAPH:
						// [ [= 25&][= [* Mar 2014]]]
						output << "\1[1= " << int(time.day) ;
						output << "&][1*= " << MonName(time.month-1) << " " << time.year << "]";
						break;
					case FLOAT_OVER_GRAPH:
					case TOP_OF_GRAPH:
						output << "\1[1*= " << time.year;
						output << "&][1= " << int(time.day) << " " << MonName(time.month-1) << "]";
						break;
				}
			}
			else {
				output << "\1[1 " << int(time.day) << "]";
			}
		}
		 else { // Range < 7 days
			if ( value.isFirst() || value.isLast() ) {
				switch(_B::GetElementPos()) {
					case LEFT_OF_GRAPH:
						output << "\1[1* " << time.year;
						output << " ][1 " << int(time.day) << " " << MonName(time.month-1) << "]";
						output << "[1 " << FormatTime( time, " h`hmm:ss" ) << "]";
						break;
					case RIGHT_OF_GRAPH:
						output << "\1[1 " << FormatTime( time, "h`hmm:ss " ) << "]";
						output << "[1 " << int(time.day) << " " << MonName(time.month-1) ;
						output << " ][1* " << time.year << "]";
						break;
					case BOTTOM_OF_GRAPH:
						output << "\1[1= " << FormatTime( time, "h`hmm:ss" ) << "&]";
						output << "[1= " << int(time.day) << " " << MonName(time.month-1) ;
						output << "&][1*= " << time.year << "]";
						break;
					case FLOAT_OVER_GRAPH:
					case TOP_OF_GRAPH:
						output << "\1[1*= " << time.year;
						output << "&][1= " << int(time.day) << " " << MonName(time.month-1) << "&]";
						output << "[1= " << FormatTime( time, "h`hmm:ss" ) << "]";
						break;
				}
			}
			else {
				if (range > 24*60*60) { // 24 hours
					switch(_B::GetElementPos()) {
							case LEFT_OF_GRAPH:
								output << "\1[1 " << int(time.day) << " " << MonName(time.month-1) << "]";
								if (time.hour != 0 || time.minute!=0 || time.second!=0) {
									output << "[1 " << FormatTime( time, " h`hmm:ss" ) << "]";
								}
								break;
							case RIGHT_OF_GRAPH:
								output << "\1";
								if (time.hour != 0 || time.minute!=0 || time.second!=0) {
									output <<"[1 " << FormatTime( time, "h`hmm:ss " ) << "]";
								}
								output << "[1 " << int(time.day) << " " << MonName(time.month-1) ;
								output << " ]";
								break;
							case BOTTOM_OF_GRAPH:
								output << "\1";
								if (time.hour != 0 || time.minute!=0 || time.second!=0) {
									output << "[1= " << FormatTime( time, "h`hmm:ss" ) << "&]";
								}
								output << "[1= " << int(time.day) << " " << MonName(time.month-1) ;
								output << "&]";
								break;
							case FLOAT_OVER_GRAPH:
							case TOP_OF_GRAPH:
								output << "\1[1= " << int(time.day) << " " << MonName(time.month-1) << "&]";
								if (time.hour != 0 || time.minute!=0 || time.second!=0) {
									output << "[1= " << FormatTime( time, "h`hmm:ss" ) << "]";
								}
								break;
					}
				}
				else {
					output << "\1[1 " << FormatTime( time, "h`hmm:ss" ) << "]";
				}
			}
		}
	}


	void GridAxisDraw::UpdateTickTextData( int scale ) {
		Sizef tmpSize(0,0);
		int nbSizeValues = 0;
		 _gridStepManager.UpdateGridSteps(scale);

		GridStepIterator iter = GridStepBegin();
		const_GridStepIterator endIter = GridStepEnd();

		Font scaledAxisTextFont( style->axisTextFont );
		if (scale>1) scaledAxisTextFont.Height(scale*scaledAxisTextFont.GetHeight());
		while ( iter != endIter )
		{
			iter->text.Clear();
			_formatTextCbk( iter, iter->text );
			
			if (!iter->text.IsEmpty()) {
				iter->textSize = GraphDraw_ns::GetSmartTextSize(iter->text , scaledAxisTextFont, scale);
				tmpSize.cx += iter->textSize.cx;
				tmpSize.cy += iter->textSize.cy;
				++nbSizeValues;
			}
			++iter;
		}
		tmpSize /= nbSizeValues;
		_meanTickTextsz = tmpSize;
	}

	void GridAxisDraw::PaintTickText(Draw& dw,  const ElementPosition ePos, const const_GridStepIterator& value, TypeScreenCoord x, TypeScreenCoord y, const Color color, const Font scaledFont, int scale) {
		Upp::String text;
		_formatTextCbk( value, text );
		if (!text.IsEmpty()) {
			Size sz = GraphDraw_ns::GetSmartTextSize(text, scaledFont, scale);
			_tmpTextSize += sz;
			++_nbMeanValues;

			if (ePos == LEFT_OF_GRAPH) {
				GraphDraw_ns::DrawSmartText(dw, x-sz.cx, y-(sz.cy/2), sz.cx, text, scaledFont, color, scale);
			}
			else if (ePos == BOTTOM_OF_GRAPH) {
				GraphDraw_ns::DrawSmartText(dw, x-(sz.cx/2), y, sz.cx, text, scaledFont, color, scale);
			}
			else if (ePos == RIGHT_OF_GRAPH) {
				GraphDraw_ns::DrawSmartText( dw, x, y-(sz.cy/2), sz.cx, text, scaledFont, color, scale);
			}
			else {
				GraphDraw_ns::DrawSmartText( dw,  x-(sz.cx/2), y-sz.cy , sz.cx, text, scaledFont, color, scale);
			}
		}
	}

	void GridAxisDraw::PaintAxisLeft(Draw& dw, const int scale, const_GridStepIterator iter, const_GridStepIterator endIter)
	{
		Font scaledAxisTextFont( style->axisTextFont );
		if (scale>1) scaledAxisTextFont.Height(scale*scaledAxisTextFont.GetHeight());
		dw.DrawLineOp(_B::GetElementWidth()*scale, _coordConverter.getScreenMin(), _B::GetElementWidth()*scale, _coordConverter.getScreenMax(), style->axisWidth*scale, style->axisColor );
		while ( iter != endIter)
		{
			if (_tickMarks[iter->tickLevel].IsEmpty()) {
				PaintTickText(dw, LEFT_OF_GRAPH, iter, (_B::GetElementWidth()-8)*scale, iter, style->axisTextColor, scaledAxisTextFont, scale);
			} else {
				_tickMarks[iter->tickLevel]->Paint(dw, LEFT_OF_GRAPH, scale, _B::GetElementWidth()*scale, iter, style->axisTickColor );
				PaintTickText(dw, LEFT_OF_GRAPH, iter, (_B::GetElementWidth()-_tickMarks[0]->GetTickLength()-2)*scale, iter, style->axisTextColor, scaledAxisTextFont, scale);
			}
			++iter;
		}
	}

	void GridAxisDraw::PaintAxisRight(Draw& dw, const int scale, const_GridStepIterator iter, const_GridStepIterator endIter)
	{
		Font scaledAxisTextFont( style->axisTextFont );
		if (scale>1) scaledAxisTextFont.Height(scale*scaledAxisTextFont.GetHeight());
		dw.DrawLineOp(0, _coordConverter.getScreenMin(), 0, _coordConverter.getScreenMax(), style->axisWidth*scale, style->axisColor);
		while ( iter != endIter)
		{
			if (_tickMarks[iter->tickLevel].IsEmpty())
			{
				PaintTickText(dw, RIGHT_OF_GRAPH, iter, 8, iter, style->axisTextColor, scaledAxisTextFont, scale);
			} else {
				_tickMarks[iter->tickLevel]->Paint(dw, RIGHT_OF_GRAPH, scale, 0, iter, style->axisTickColor );
				PaintTickText(dw, RIGHT_OF_GRAPH, iter, (_tickMarks[0]->GetTickLength()+2)*scale, iter, style->axisTextColor, scaledAxisTextFont, scale);
			}
			++iter;
		}
	}

	void GridAxisDraw::PaintAxisBottom(Draw& dw, const int scale, const_GridStepIterator iter, const_GridStepIterator endIter)
	{
		Font scaledAxisTextFont( style->axisTextFont );
		if (scale>1) scaledAxisTextFont.Height(scale*scaledAxisTextFont.GetHeight());
		dw.DrawLineOp(_coordConverter.getScreenMin(), 0, _coordConverter.getScreenMax(),0 , style->axisWidth*scale, style->axisColor );
		while ( iter != endIter )
		{
			if (_tickMarks[iter->tickLevel].IsEmpty()) {
				PaintTickText(dw, BOTTOM_OF_GRAPH, iter, iter, 4, style->axisTextColor, scaledAxisTextFont, scale);
			} else {
				_tickMarks[iter->tickLevel]->Paint(dw, BOTTOM_OF_GRAPH, scale, iter, 0, style->axisTickColor );
				PaintTickText(dw, BOTTOM_OF_GRAPH, iter, iter, (_tickMarks[0]->GetTickLength()+2)*scale, style->axisTextColor, scaledAxisTextFont, scale);
			}
			++iter;
		}
	}

	void GridAxisDraw::PaintAxisTop(Draw& dw, const int scale, const_GridStepIterator iter, const_GridStepIterator endIter)
	{
		Font scaledAxisTextFont( style->axisTextFont );
		if (scale>1) scaledAxisTextFont.Height(scale*scaledAxisTextFont.GetHeight());
		dw.DrawLineOp(_coordConverter.getScreenMin(), _B::GetElementWidth()*scale, _coordConverter.getScreenMax(), _B::GetElementWidth()*scale, style->axisWidth*scale, style->axisColor );
		while ( iter != endIter)
		{
			if (_tickMarks[iter->tickLevel].IsEmpty()) {
				PaintTickText(dw, TOP_OF_GRAPH, iter, iter, (_B::GetElementWidth()-4)*scale, style->axisTextColor, scaledAxisTextFont, scale);
			} else {
				_tickMarks[iter->tickLevel]->Paint(dw, TOP_OF_GRAPH, scale, iter, _B::GetElementWidth()*scale, style->axisTickColor );
				PaintTickText(dw, TOP_OF_GRAPH, iter, iter, (_B::GetElementWidth()-_tickMarks[0]->GetTickLength()-2)*scale, style->axisTextColor, scaledAxisTextFont, scale);
			}
			++iter;
		}
	}


	void GridAxisDraw::PaintVGrid(Draw& dw, const int scale, int xRange, const_GridStepIterator iter, const_GridStepIterator endIter)
	{
		if ( !style->gridColor.IsNullInstance() )
		{
			while( iter != endIter)
			{
				DrawLineOpa(dw, 0, iter, xRange, iter, 1.0, 1.0, style->gridThickness, style->gridColor, style->gridDash);
				++iter;
			}
		}
	}

	void GridAxisDraw::PaintHGrid(Draw& dw, const int scale, int yRange, const_GridStepIterator iter, const_GridStepIterator endIter)
	{
		if ( !style->gridColor.IsNullInstance())
		{
			const_GridStepIterator iter = GridStepBegin();
			const_GridStepIterator endIter = GridStepEnd();
			while( iter != endIter)
			{
				DrawLineOpa(dw, iter, 0, iter, yRange, 1.0, 1.0, style->gridThickness, style->gridColor, style->gridDash);
				++iter;
			}
		}
	}

	void GridAxisDraw::PaintOnPlot_underData(Draw& dw, int otherWidth, int scale)
	{
		const_GridStepIterator iter = GridStepBegin();
		const_GridStepIterator endIter = GridStepEnd();
		switch(_B::GetElementPos()){
			case LEFT_OF_GRAPH:
			case RIGHT_OF_GRAPH:
				PaintVGrid(dw, scale, otherWidth, iter, endIter);
				break;
			case BOTTOM_OF_GRAPH:
			case TOP_OF_GRAPH:
				PaintHGrid(dw, scale, otherWidth, iter, endIter);
				break;
			case FLOAT_OVER_GRAPH:
				break;
		}
	}

	void GridAxisDraw::PaintElement(Draw& dw, int scale)
	{
		_tmpTextSize.Clear();
		_nbMeanValues = 0;
		_B::PaintElementBckGround(dw, _B::GetFrame().GetSize(), style->geBase.lmntBackgnd);
		const_GridStepIterator iter = GridStepBegin();
		const_GridStepIterator endIter = GridStepEnd();

		if ( _B::GetStackingPriority() > 0) {
			switch(_B::GetElementPos()) {
				case LEFT_OF_GRAPH:
					PaintAxisLeft(dw, scale, iter, endIter);
					break;
				case BOTTOM_OF_GRAPH:
					PaintAxisBottom(dw, scale, iter, endIter);
					break;
				case TOP_OF_GRAPH:
					PaintAxisTop(dw, scale, iter, endIter);
					break;
				case RIGHT_OF_GRAPH:
					PaintAxisRight(dw, scale, iter, endIter);
					break;
				case FLOAT_OVER_GRAPH:
					break;
			}
		}
		else {
			switch(_B::GetElementPos()){
				case LEFT_OF_GRAPH:
					PaintAxisRight(dw, scale, iter, endIter);
					break;
				case BOTTOM_OF_GRAPH:
					PaintAxisTop(dw, scale, iter, endIter);
					break;
				case TOP_OF_GRAPH:
					PaintAxisBottom(dw, scale, iter, endIter);
					break;
				case RIGHT_OF_GRAPH:
					PaintAxisLeft(dw, scale, iter, endIter);
					break;
				case FLOAT_OVER_GRAPH:
					break;
			}
		}
		_meanTickTextsz = _tmpTextSize;
//			LOG("   SumTickTextsz=" << _meanTickTextsz << "   _nbMeanValues=" << _nbMeanValues << "    ==> mean=" << _meanTickTextsz/_nbMeanValues);
		if ( _nbMeanValues>0.9 ) { _meanTickTextsz /= _nbMeanValues; }
		else                     { _meanTickTextsz.cx = 10; _meanTickTextsz.cy=10; }
	}
}}


