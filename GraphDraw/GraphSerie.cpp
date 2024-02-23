#include "GraphDraw.h"

namespace Upp
{
namespace GraphDraw_ns
{


	GraphSerieEditorInterface::~GraphSerieEditorInterface() {
		if (dlg) {
			RetrieveFromDlg.Clear();
			WhenDlgAction.Clear();
			DeleteDlg();
			DeleteDlg.Clear();
			DeleteTmpStyle();
			DeleteTmpStyle.Clear();
			dlg = nullptr;
			
		}
	}

// ======================================================================


	void SimpleGraphSerie::PaintSerie(BufferPainter& dw, const bool doFastPaint, int scale, const MCoordinateConverter& coordConv )
	{
		unsigned int count=GetCount();
		const RectGraph gr = coordConv.GetGraphMinMax();
		for (unsigned int c=0; c<count; ++c) {
			// paint only visible data points
			if (Get(c).Intersects(gr)) Get(c).PaintDataPoint(dw, scale, CustomData::DEFAULT_STYLE, coordConv);
		}
	}

	void SimpleGraphSerie::PaintSelected(BufferPainter& dw, const bool doFastPaint, int scale, const MCoordinateConverter& coordConv )
	{
		unsigned int count=GetCount();
		const RectGraph gr = coordConv.GetGraphMinMax();
		for (unsigned int c=0; c<count; ++c) {
			// paint only visible data points
			CustomData& dat = Get(c);
			if (dat.IsSelected() && dat.Intersects(gr)) dat.PaintDataPoint(dw, scale, CustomData::HIGHLIGHT_STYLE, coordConv);
		}
	}

	
	void SimpleGraphSerie::PaintOne(unsigned int index, int style, BufferPainter& dw, int scale, const MCoordinateConverter& coordConv ) const
	{
		if (index < GetCount()) {
			Get(index).PaintDataPoint(dw, scale, CustomData::DEFAULT_STYLE, coordConv);
		}
	}
	
	bool SimpleGraphSerie::Contains(const PointGraph p, unsigned int& pIndexOut) const {
		unsigned int count=GetCount();
		for (unsigned int c=0; c<count; ++c) {
			if (Get(c).Contains(p)) {
				pIndexOut = c;
				return true;
			}
		}
		return false;
	}

	bool SimpleGraphSerie::Intersects(const RectGraph rect, unsigned int& pIndexOut) const {
		unsigned int count=GetCount();
		for (unsigned int c=0; c<count; ++c) {
			if (Get(c).Intersects(rect)) {
				pIndexOut = c;
				return true;
			}
		}
		return false;
	}

	// Serie Data selection
	hash_t SimpleGraphSerie::GetSelectHashValue() const {
		CombineHash hash;
		hash << IsSelectable() << isSerieSelected;
		if ( IsSelectable() ) {
			const unsigned int count=GetCount();
			for (unsigned int c=0; c<count; ++c) {
				if (Get(c).IsSelected()) hash << c;
			}
		}
		return hash;
	}

	bool SimpleGraphSerie::HasDataSelected() const {
		return (GetSelectDataCount() > 0);
	}

	bool SimpleGraphSerie::IsDataSelected(unsigned int dataIndex) const {
		return Get(dataIndex).IsSelected();
	}

	unsigned int SimpleGraphSerie::GetSelectDataCount() const {
		const unsigned int count=GetCount();
		int selCount = 0;
		for (unsigned int c=0; c<count; ++c) {
			selCount += Get(c).IsSelected();
		}
		return selCount;
	}

	
	void SimpleGraphSerie::SelectAllData()
	{
		const unsigned int count=GetCount();
		for (unsigned int c=0; c<count; ++c) {
			Get(c).Select(true);
		}
	}

	void SimpleGraphSerie::ClearDataSelection()
	{
		const unsigned int count=GetCount();
		for (unsigned int c=0; c<count; ++c) {
			Get(c).Select(false);
		}
	}
	

	void SimpleGraphSerie::InvertDataSelection()
	{
		const unsigned int count=GetCount();
		for (unsigned int c=0; c<count; ++c) {
			CustomData& dat = Get(c);
			dat.Select( !dat.IsSelected() );
		}
	}
	
	Vector<unsigned int> SimpleGraphSerie::GetDataSelection() const {
		unsigned int selCount = GetSelectDataCount();
		Vector<unsigned int> vec;
		if (selCount>0) {
			vec.Reserve(selCount);
			const unsigned int count=GetCount();
			for (unsigned int c=0; c<count; ++c) {
				if ( Get(c).IsSelected() ) vec.Add(c);
			}
		}
		return vec;
	}

	Vector<unsigned int> SimpleGraphSerie::GetInvertedDataSelection() const {
		unsigned int selCount = GetSelectDataCount();
		Vector<unsigned int> vec;
		if (selCount>0) {
			vec.Reserve(selCount);
			const unsigned int count=GetCount();
			for (unsigned int c=0; c<count; ++c) {
				if ( !Get(c).IsSelected() ) vec.Add(c);
			}
		}
		return vec;
	}
	
	void SimpleGraphSerie::SelectData(const Vector<unsigned int>& dataIndexList, bool append)
	{
		if (append == false) ClearDataSelection();
		
		int count=dataIndexList.GetCount();
		for (unsigned int c=0; c<count; ++c) {
			Get( dataIndexList[c] ).Select(true);
		}
	}

	void SimpleGraphSerie::UnselectData(const Vector<unsigned int>& dataIndexList)
	{
		int count=dataIndexList.GetCount();
		for (unsigned int c=0; c<count; ++c) {
			Get( dataIndexList[c] ).Select(false);
		}
	}
	
	
	unsigned int SimpleGraphSerie::SelectData(RectGraph rect, bool instersect, bool append)
	{
		unsigned int selectInRectCount=0;
		const unsigned int count=GetCount();
		if (append) {
			if (instersect) {
				for (unsigned int c=0; c<count; ++c) {
					CustomData& dat = Get(c);
					if (dat.Intersects(rect)) { dat.Select(true); ++selectInRectCount; }
				}
			}
			else
			{
				for (unsigned int c=0; c<count; ++c) {
					CustomData& dat = Get(c);
					if (dat.Contained(rect)) { dat.Select(true); ++selectInRectCount; }
				}
			}
		}
		else {
			if (instersect) {
				for (unsigned int c=0; c<count; ++c) {
					CustomData& dat = Get(c);
					dat.Select(false);
					if (dat.Intersects(rect)) { dat.Select(true); ++selectInRectCount; }
				}
			}
			else
			{
				for (unsigned int c=0; c<count; ++c) {
					CustomData& dat = Get(c);
					dat.Select(false);
					if (dat.Contained(rect)) { dat.Select(true); ++selectInRectCount; }
				}
			}
		}
		return selectInRectCount;
	}
	
	Vector<unsigned int> SimpleGraphSerie::SelectOneData(RectGraph rect, bool append) {
		const unsigned char NB_MAX_SELECTED = 32; // will never return more than 32 data points
		if (!append) ClearDataSelection();
		Vector<unsigned int> vec;
		vec.Reserve(NB_MAX_SELECTED);
		const unsigned int count=GetCount();
		for (unsigned int c=0; (c<count) && (vec.GetCount()<NB_MAX_SELECTED); ++c) {
			CustomData& dat = Get(c);
			if ( dat.Intersects(rect) ) {
				dat.SelectFlip();
				vec.Add(c);
			}
		}
		return vec;
	}
	

	
	// Selection painting
	
			
} }