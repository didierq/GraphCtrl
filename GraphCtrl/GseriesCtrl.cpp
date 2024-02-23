#include "GraphCtrl.h"

namespace Upp {
namespace GraphDraw_ns {



struct GSeriesIconGridDisplay2 : public GridDisplay {
	virtual void Paint(Draw &w, int x, int y, int cx, int cy, const Value &val, dword style,
	                   Color &fg, Color &bg, Font &fnt, bool found = false, int fs = 0, int fe = 0)
	{
		w.DrawRect(x,y,cx,cy, White());
		DrawFatFrame(w,x,y,cx,cy, bg, 3);
		GraphSerieDecorator* gsd = val.To<GraphSerieDecorator*>();
		ChPaint(w, x,y,cx,cy, gsd->MakeSerieIcon(Size(cx,cy), 1));
	}

};

void GSeriesIconGridDisplay::Paint(Draw &w, int x, int y, int cx, int cy, const Value &val, dword style,
                   Color &fg, Color &bg, Font &fnt, bool found, int fs, int fe)
{
	if (! val.IsNull() ) {
		w.DrawRect(x,y,cx,cy, White());
		ChPaint(w, x,y,cx,cy, backGround);
		
		DrawFatFrame(w,x,y,cx,cy, bg, 3);
		GraphSerieDecorator* gsd = val.To<GraphSerieDecorator*>();
		ChPaint(w, x,y,cx,cy, gsd->MakeSerieIcon(Size(cx,cy), 1));
	}
}

struct GSeriesIconDisplay : public Display {
	virtual void Paint(Draw& w, const RectScreen& r, const Value& val,
	                   Color ink, Color paper, dword style) const
	{
		w.DrawRect(r,White());
		DrawFatFrame(w,r,paper,3);
		GraphSerieDecorator* gsd = val.To<GraphSerieDecorator*>();
		ChPaint(w, r, gsd->MakeSerieIcon(r.GetSize(), 1));
	}
};




Id GSeriesCtrlDlg::ID_SHOW_COLUMN("SHOW");
Id GSeriesCtrlDlg::ID_ICON_COLUMN("ICON");
Id GSeriesCtrlDlg::ID_LEGEND_COLUMN("LEGEND");
Id GSeriesCtrlDlg::ID_CTRLREF_COLUMN("CtrlRef");

void GSeriesCtrlDlg::SetModify() {
	seriesHash++;
}

void GSeriesCtrlDlg::ClearModify() {
	CombineHash hash;
	for (int c=0; c<series.GetCount(); ++c) {
		hash << series[c].GetHashValue();
	}
	seriesHash = hash;
}

bool GSeriesCtrlDlg::IsModified() const {
	CombineHash hash;
	for (int c=0; c<series.GetCount(); ++c) {
		hash << series[c].GetHashValue();
	}
	return hash != seriesHash;
}


GSeriesIconGridDisplay GSeriesCtrlDlg::iconGridDisplay;


GSeriesCtrlDlg::GSeriesCtrlDlg( GraphSeriesDecoratorVector& s, const CH_EmptyGraphDraw::StyleGD& st )
: seriesHash(0)
, series(s)
, currSelection(-1)
, graphStyle(st)
{
	iconGridDisplay.backGround = graphStyle.plotBckgndStyle;
	serieBackGnd.Background( graphStyle.plotBckgndStyle );

	CtrlLayout(*this);//, "Data Series Properties");
	
	seriesGridCtrl.AddColumn(ID_SHOW_COLUMN, "Show", 23).Ctrls<Option>();
	seriesGridCtrl.AddColumn(ID_ICON_COLUMN, "Icon", 45).SetDisplay( iconGridDisplay );
	seriesGridCtrl.AddColumn(ID_LEGEND_COLUMN, "Legend", 120);
	seriesGridCtrl.AddColumn(ID_CTRLREF_COLUMN, "CTRL REF", 0).Hidden();
	seriesGridCtrl.ColumnWidths("23 45 230 0");
	seriesGridCtrl.SetToolBar();
	
	seriesGridCtrl.WhenChangeRow   =     THISFN(loadConfigFromSelectedSerie);
	seriesGridCtrl.WhenCtrlsAction =     THISFN(arrayLineEdited);
	show.WhenAction =                    THISFN(updateArrayShow);
	legend.WhenAction =                  THISFN(updateArrayLegend);
	ShowAllBt.WhenAction=   [&] () { showAll(true); };
	ClearAllBt.WhenAction=  [&] () { showAll(false); };
	CustomProperiesFrame.EnableScroll();
	CustomProperiesFrame.Layout();
	
	// Create all editors
	for (int c=0; c<series.GetCount(); ++c) {
		GraphSerieDecorator& gsd = series[c];
		GraphSerieEditorInterface* propEditorInfo = series[c].MakeGraphSerieEditorInfo();
		propEditorInfo->WhenDlgAction = [&] { updateSeriePreview(); Refresh(); };
		seriesGridCtrl.Add( gsd.IsShow() , RawToValue(&gsd), gsd.GetLegend(), RawToValue(propEditorInfo) );
	}
	
	if (series.GetCount() > 0) {
		seriesGridCtrl.GoBegin();
		loadConfigFromSelectedSerie();
	}
	
	ClearModify();
}

GSeriesCtrlDlg::~GSeriesCtrlDlg() {
	for (int c=0; c<seriesGridCtrl.GetCount(); ++c) {
		GraphSerieEditorInterface* propEditorInfo = seriesGridCtrl.Get(c, ID_CTRLREF_COLUMN).template To<GraphSerieEditorInterface*>();
		if (propEditorInfo) delete propEditorInfo;
	}
}

void GSeriesCtrlDlg::Retrieve(void) {
	for (int c=0; c<seriesGridCtrl.GetCount(); ++c) {
		GraphSerieEditorInterface* propEditorInfo = seriesGridCtrl.Get(c, ID_CTRLREF_COLUMN).template To<GraphSerieEditorInterface*>();
		int id = seriesGridCtrl.GetRowId(c);
		if (propEditorInfo) propEditorInfo->RetrieveFromDlg();
		series[id].Show( seriesGridCtrl.Get(c, ID_SHOW_COLUMN) );
		series[id].SetLegend( seriesGridCtrl.Get(c, ID_LEGEND_COLUMN) );
	}
}

void GSeriesCtrlDlg::RevertChanges(void) {
	for (int c=0; c<seriesGridCtrl.GetCount(); ++c) {
		GraphSerieEditorInterface* propEditorInfo = seriesGridCtrl.Get(c, ID_CTRLREF_COLUMN).template To<GraphSerieEditorInterface*>();
		propEditorInfo->RevertChanges();
	}
}

void GSeriesCtrlDlg::showAll(bool showHide) {
	for (int i = 0; i < series.GetCount(); ++i) {
		seriesGridCtrl.Set(i, ID_SHOW_COLUMN, showHide);
	}
	arrayLineEdited();
}

void GSeriesCtrlDlg::updateArrayShow(void) {
	seriesGridCtrl.Set(ID_SHOW_COLUMN, ~show);
}

void GSeriesCtrlDlg::updateArrayLegend(void) {
	seriesGridCtrl.Set(ID_LEGEND_COLUMN, ~legend);
}

void GSeriesCtrlDlg::arrayLineEdited(void) {
	show.SetData(seriesGridCtrl.Get(ID_SHOW_COLUMN));
	legend.SetData(seriesGridCtrl.Get(ID_LEGEND_COLUMN));
}


void GSeriesCtrlDlg::loadConfigFromSelectedSerie(void) {
	// Load new values
	currSelection = seriesGridCtrl.GetCurrentRow();
	
	if (currSelection >= 0) {
		GraphSerieEditorInterface* propEditorInfo = seriesGridCtrl.Get(currSelection, ID_CTRLREF_COLUMN).template To<GraphSerieEditorInterface*>();
		if (propEditorInfo) {
			propEditorInfo->GetCtrl()->Show();
			CustomProperiesFrame.AddPane( * ( propEditorInfo->GetCtrl() ) );
		}
		else {
			CustomProperiesFrame.ClearPane();
		}
		show.SetData( seriesGridCtrl.Get(currSelection, ID_SHOW_COLUMN) );
		legend.SetData( seriesGridCtrl.Get(currSelection, ID_LEGEND_COLUMN) );

		updateSeriePreview();
		Refresh();
	}
}

void GSeriesCtrlDlg::updateSeriePreview(void) {
	if (seriesGridCtrl.GetRowId() >= 0) {
		GraphSerieEditorInterface* propEditorInfo = seriesGridCtrl.Get(seriesGridCtrl.GetCurrentRow(), ID_CTRLREF_COLUMN).template To<GraphSerieEditorInterface*>();
		propEditorInfo->RetrieveFromDlg();  // TODO a ameliorer
		seriePreview.SetImage( series[ seriesGridCtrl.GetRowId() ].MakeSerieIcon(seriePreview.GetSize(),1) );

	}
}

} // namespace


}
