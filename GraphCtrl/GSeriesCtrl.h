#ifndef _GraphCtrl_GSeriesCtrl_h_
#define _GraphCtrl_GSeriesCtrl_h_



struct GSeriesIconGridDisplay : public GridDisplay {
	Value backGround;
	
	GSeriesIconGridDisplay() { backGround = SWhite(); }
	virtual void Paint(Draw &w, int x, int y, int cx, int cy, const Value &val, dword style,
	                   Color &fg, Color &bg, Font &fnt, bool found = false, int fs = 0, int fe = 0);
};

// ==========================================

class GSeriesCtrlDlg : public WithGSeriesManagementLayout<ElementPropertiesDlgInterface> {
	typedef GSeriesCtrlDlg CLASSNAME;
	
	static Id ID_SHOW_COLUMN;
	static Id ID_ICON_COLUMN;
	static Id ID_LEGEND_COLUMN;
	static Id ID_CTRLREF_COLUMN;

	hash_t seriesHash;
	GraphSeriesDecoratorVector& series;
	int currSelection;
	const CH_EmptyGraphDraw::StyleGD& graphStyle;
	static GSeriesIconGridDisplay iconGridDisplay;
	void loadConfigFromSelectedSerie(void);
	void arrayLineEdited(void);
	void updateArrayShow(void);
	void updateArrayLegend(void);
	void updateSeriePreview(void);
	void showAll(bool showHide = true);
	
	GSeriesCtrlDlg() = delete;
	
public:
	GSeriesCtrlDlg( GraphSeriesDecoratorVector& s, const CH_EmptyGraphDraw::StyleGD& styl);
	~GSeriesCtrlDlg();
	
	virtual void SetModify()        override;
	virtual void ClearModify()      override;
	virtual bool IsModified() const override;
	virtual void Retrieve()         override;
	void   RevertChanges();

};


#endif
