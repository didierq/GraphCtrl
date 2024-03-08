#include "GraphDraw.h"


namespace Upp {
namespace GraphDraw_ns {
	
	
		// =============================================================
		//      LabelElement
		// =============================================================
		void LabelElement::PaintElement(Draw& dw, int scale)
		{
			_B::PaintElementBckGround(dw, _B::GetFrame().GetSize(), styleGE->geBase.lmntBackgnd );
			
			Font scaledFont( styleGE->labelFont );
			scaledFont.Height(scale*scaledFont.GetHeight());
			Size sz = GetTextSize(_label, scaledFont);
			switch(_B::GetElementPos()) {
				case LEFT_OF_GRAPH:
					dw.DrawText( _B::GetElementWidth()*scale/2-sz.cy/2, _B::GetFrame().GetHeight()/2+sz.cx/2 , 900, _label, scaledFont, styleGE->labelColor);
					break;
				case BOTTOM_OF_GRAPH:
					dw.DrawText( _B::GetFrame().GetWidth()/2-sz.cx/2, _B::GetElementWidth()*scale/2-sz.cy/2 , _label, scaledFont, styleGE->labelColor);
					break;
				case TOP_OF_GRAPH:
					dw.DrawText( _B::GetFrame().GetWidth()/2-sz.cx/2, _B::GetElementWidth()*scale/2-sz.cy/2 , _label, scaledFont, styleGE->labelColor);
					break;
				case RIGHT_OF_GRAPH:
					dw.DrawText( _B::GetElementWidth()*scale/2+sz.cy/2, _B::GetFrame().GetHeight()/2-sz.cx/2 , 2700, _label, scaledFont, styleGE->labelColor);
					break;
				case FLOAT_OVER_GRAPH:
					break;
			}
		}
	



		// =============================================================
		//      LegendElement
		// =============================================================

		void LegendElement::PaintElement(Draw& dw, int scale) {
			_B::PaintElementBckGround(dw, _B::GetFrame().GetSize(), style->geBase.lmntBackgnd  );
			DrawLegend(dw, scale);
		}

		void LegendElement::PaintFloatElement(Draw& dw, int scale){
			_B::PaintElementBckGround(dw, _B::GetFloatFrame().GetSize()*scale, style->lgdFloatBackgnd );
			DrawLegend(dw, scale);
		}

		void LegendElement::PrePaint( int scale ) {
			if (g_series==nullptr) {
				g_series = &_B::_parent->GetGSeries();
			}

			_legendWidth = 0;
			int count = (*g_series).GetCount();
			seriesLabelRectVector.SetCount(count);// Reserve(count); // TODO   do more optimal code (this is crap code !!)
			for (int c=0; c<count; ++c) {
				int textLength = GetTextSize((*g_series)[c].GetLegend(), style->lgdFont).cx;
				if(_legendWidth < textLength) _legendWidth = textLength;
			}
			_legendWidth += style->lgdStyleLength + style->lgdXSeparation;
		}

		void LegendElement::DrawLegend(Draw& w, const int scale)
		{
			if (g_series==nullptr) {
				String text = "LEGEND TEXT : no series defined";
				w.DrawText( 0,0 , text, style->lgdFont, SBlack());
				return;
			}

			int nmr = fround(_B::_frame.GetSize().cx/(_legendWidth*scale));	//max number of labels per row
			if (nmr <= 0) nmr = 1;
			int nLab = (*g_series).GetCount();	//number of labels
			int idx=0;
			int ix=0;
			int iy=0;
			Font scaledFont( style->lgdFont );
			int txtHeight = scaledFont.Height(scale * style->lgdFont.GetHeight() ).GetHeight();
			for (idx=0; idx<nLab; ++idx) {
				const GraphSerieDecorator& gsd = (*g_series)[idx];
				if ((gsd.IsShow()==false) || gsd.IsShowLegend() == false ) {
					seriesLabelRectVector[idx] = RectScreen(); // TODO   do more optimal code (this is crap code !!)
					continue;
				}
				
				if (idx<nLab) {
					int x = scale*ix*_legendWidth + txtHeight/2;
					int y = iy*txtHeight + txtHeight/2;
					RectScreen labelRect(Point(x, y+2*scale), Size(scale*_legendWidth-txtHeight, txtHeight) );
					Image img = gsd.MakeSerieIcon(txtHeight, scale);
					w.DrawImage(labelRect.left, labelRect.top, img);
					Color txtColor;
					if (style->lgdTxtColor.IsNullInstance())
						txtColor = gsd.GetGraphSerie().GetAutoColor();
					else
						txtColor = style->lgdTxtColor;
					
					seriesLabelRectVector[idx] = labelRect; // TODO   do more optimal code (this is crap code !!)
					if (gsd.HasDataSelected()) {
						ChPaint(w, labelRect, style->ldgStyle_SerieDataSelected);
						txtColor = style->ldgTextSelect;
					}
					if (gsd.IsSerieSelected()) {
						ChPaint(w, labelRect, style->ldgStyle_SerieSelected);
						txtColor = style->ldgTextSelect;
					}
					DrawText(w, x+scale*(style->lgdStyleLength+2), y, 0, gsd.GetLegend(), scaledFont, txtColor );
				}
				++ix;
				if (ix>=nmr) { ix=0; ++iy; }
			}
		}

		// =============================================================
		//      MarkerElement
		// =============================================================
		void MarkerElementData::Link(MarkerElementData* m) {
			//GDLOGBLOCK("MarkerElementData::Link");
			if (m == 0)  return;
			if (linkedMarkers.Find(m) >= 0) return;
			linkedMarkers.Add( m );
			m->Link(this);
		}
	
		void MarkerElementData::Unlink(MarkerElementData* m) {
			//GDLOGBLOCK("MarkerElementData::Unlink  REQUESTED");
			if (m == nullptr)  return;
			if ((linkedMarkers.Find(m)) < 0) return;
			//LOG("MarkerElementData::Unlink  removing link  count=" << linkedMarkers.GetCount());
			linkedMarkers.RemoveKey( m );
			//LOG("MarkerElementData::Unlink  removed        count=" << linkedMarkers.GetCount());
			m->Unlink(this);
		}
	
		void MarkerElementData::UnlinkAll() {
			//GDLOGBLOCK("MarkerElementData::UnlinkAll");
			while( linkedMarkers.GetCount() > 0) {
				Unlink(linkedMarkers[0]);
			}
		}
		
		void MarkerElementData::UpdateLinked(TypeMarkerUpdateCbk& cbk) {
			//GDLOGBLOCK("MarkerElementData::UnlinkAll");
			for (int c=(linkedMarkers.GetCount()-1); c>=0; --c) {
				linkedMarkers[c]->pos = pos;
				cbk( linkedMarkers[c]->ID, owner );
			}
		}



		SmartTextTickMark&  MarkerElement::AddMarker(int markerId, TypeGraphCoord pos) {
			MarkerElementData& markData = markers.Add(markerId);
			markData = pos;
			return markData.CreateMarker<SmartTextTickMark>(markerId, this);
		}

		SmartTextTickMark&  MarkerElement::AddMarker(int markerId, const String txt, TypeGraphCoord pos) {
			MarkerElementData& markData = markers.Add(markerId);
			markData = pos;
			SmartTextTickMark& m = markData.CreateMarker<SmartTextTickMark>(markerId, this);
			m.SetText(txt);
			return m;
		}

		void  MarkerElement::SetElementPos(ElementPosition v) {
			if (v==LEFT_OF_GRAPH || v==RIGHT_OF_GRAPH) {
				_B::DisablePos(BOTTOM_OF_GRAPH);
				_B::DisablePos(TOP_OF_GRAPH);
			} else {
				_B::DisablePos(LEFT_OF_GRAPH);
				_B::DisablePos(RIGHT_OF_GRAPH);
			}
			_B::SetElementPos(v);
		}


		void MarkerElement::PaintHLine(Draw& dw, int range)
		{
			if ( ! (styleGE->mrkLineColor.IsNullInstance()) )
			{
				MarkerPosList::Iterator iter = markers.Begin();
				MarkerPosList::ConstIterator endIter =  markers.End();
				while( iter != endIter)
				{
					MarkerElementData& markerData = *iter;
					if (_coordConverter.IsInGraphVisibleRange(markerData)) {
						const TypeScreenCoord y = _coordConverter.toScreen(markerData);
						dw.DrawLineOp( 0, y, range, y, styleGE->mrkLineWidth, styleGE->mrkLineColor );
					}
					++iter;
				}
			}
		}

		void MarkerElement::PaintVLine(Draw& dw, int range)
		{
			if (! (styleGE->mrkLineColor.IsNullInstance()) )
			{
				MarkerPosList::Iterator iter = markers.Begin();
				MarkerPosList::ConstIterator endIter =  markers.End();
				while( iter != endIter)
				{
					MarkerElementData& markerData = *iter;
					if (_coordConverter.IsInGraphVisibleRange(markerData)) {
						const TypeScreenCoord x = _coordConverter.toScreen(markerData);
						dw.DrawLineOp( x, 0, x, range, styleGE->mrkLineWidth, styleGE->mrkLineColor );
					}
					++iter;
				}
			}
		}

		void MarkerElement::PaintElement(Draw& dw, int scale)
		{
			_B::PaintElementBckGround(dw, _B::GetFrame().GetSize(), styleGE->geBase.lmntBackgnd );

			//dw.DrawLineOp(_B::GetElementWidth()*scale, _coordConverter.getScreenMin(), _B::GetElementWidth()*scale, _coordConverter.getScreenMax(), tyle->mrkLineWidth*scale, _color );
			MarkerPosList::Iterator iter = markers.Begin();
			MarkerPosList::ConstIterator endIter = markers.End();
			int c=0;
			while ( iter != endIter ) {
					MarkerElementData& markerData = *iter;
				if (_coordConverter.IsInGraphVisibleRange(markerData)) {
					switch( _B::GetElementPos() ) {
						case LEFT_OF_GRAPH:
							markerData.GetTickMark().Paint(dw, _B::GetElementPos(), scale, _B::GetElementWidth()*scale, _coordConverter.toScreen(markerData), styleGE->mrkTickColor);
							break;
						case BOTTOM_OF_GRAPH:
							markerData.GetTickMark().Paint(dw, _B::GetElementPos(), scale, _coordConverter.toScreen(markerData), 0, styleGE->mrkTickColor );
							break;
						case TOP_OF_GRAPH:
							markerData.GetTickMark().Paint(dw, _B::GetElementPos(), scale,  _coordConverter.toScreen(markerData), _B::GetElementWidth()*scale, styleGE->mrkTickColor );
							break;
						case RIGHT_OF_GRAPH:
							markerData.GetTickMark().Paint(dw, _B::GetElementPos(), scale, 0, _coordConverter.toScreen(markerData), styleGE->mrkTickColor );
							break;
						case FLOAT_OVER_GRAPH:
							break;
					}
				}
				++iter;
				++c;
			}
		}
		
		void MarkerElement::PaintOnPlot_overData(Draw& dw, int otherWidth, int scale)
		{
			switch( _B::GetElementPos() )
			{
				case LEFT_OF_GRAPH:
				case RIGHT_OF_GRAPH:
					PaintHLine(dw, otherWidth);
					break;
				case TOP_OF_GRAPH:
				case BOTTOM_OF_GRAPH:
					PaintVLine(dw, otherWidth);
					break;
				case FLOAT_OVER_GRAPH:
					break;
			}
			
		}
		// =============================================================
		//      Xxxxxxx
		// =============================================================

		// =============================================================
		//      Xxxxxxx
		// =============================================================

		// =============================================================
		//      Xxxxxxx
		// =============================================================

		// =============================================================
		//      Xxxxxxx
		// =============================================================

		// =============================================================
		//      Xxxxxxx
		// =============================================================

		// =============================================================
		//      Xxxxxxx
		// =============================================================

		// =============================================================
		//      Xxxxxxx
		// =============================================================


	
}}