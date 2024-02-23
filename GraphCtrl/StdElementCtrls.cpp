#include "GraphCtrl.h"

namespace Upp {
namespace GraphDraw_ns {


template < class ELEMENT_CTRL, template <class T1, class T2> class DLG>
static ElementPropertiesDlgInterface* STMakePropertiesCtrl_1(ELEMENT_CTRL& lmntCtrl, typename ELEMENT_CTRL::StyleGE& st )
{
	typedef DLG<ELEMENT_CTRL,typename ELEMENT_CTRL::StyleGE> EditorDlgType;
	EditorDlgType* editor = new EditorDlgType();
	editor->InitDlg(lmntCtrl, &st);
	return editor;
}

template < class ELEMENT_CTRL, template <class T1, class T2> class DLG>
static ElementPropertiesDlgInterface* STMakePropertiesCtrl_2(ELEMENT_CTRL& lmntCtrl, typename ELEMENT_CTRL::StyleGE& st )
{
	typedef DLG<ELEMENT_CTRL,typename ELEMENT_CTRL::StyleGE> EditorDlgType;
	EditorDlgType* editor = new EditorDlgType();
	editor->InitDlg(lmntCtrl, lmntCtrl.GetCoordConverter(), &st);
	return editor;
}

template < class ELEMENT_CTRL, template <class T1, class T2> class DLG>
static ElementPropertiesDlgInterface* STMakeSeriesPropertiesCtrl(ELEMENT_CTRL& lmntCtrl, typename ELEMENT_CTRL::StyleGE& st )
{
	typedef DLG<ELEMENT_CTRL,typename ELEMENT_CTRL::StyleGE> EditorDlgType;
	EditorDlgType* editor = new EditorDlgType();
	editor->InitDlg(lmntCtrl, lmntCtrl.GetParent()->GetGSeries(), &st);
	return editor;
}


#define INIT_GE_EDITOR_CB(GE_CLASS, DLG_CLASS,  MAKE_METH) \
	{\
		GE_CLASS::MakeGEEditorCB f = [](GE_CLASS& lmnt, typename GE_CLASS::StyleGE& styl) ->ElementPropertiesDlgInterface* { return MAKE_METH<GE_CLASS, DLG_CLASS>(lmnt, styl); };\
		GE_CLASS::SetDefaultMakeEditorFct( f );\
	}


void InitGraphElementCtrls() {
	INIT_GE_EDITOR_CB( StdLabelECtrl,     LabelPropertiesDlg     , STMakePropertiesCtrl_1);
	INIT_GE_EDITOR_CB( StdBlankAreaECtrl, BlankAreaPropertiesDlg , STMakePropertiesCtrl_1);
	INIT_GE_EDITOR_CB( StdMarkerECtrl,    MarkerPropertiesDlg    , STMakePropertiesCtrl_1);
	
	INIT_GE_EDITOR_CB( StdGridAxisECtrl,  GridAxisPropertiesDlg  , STMakePropertiesCtrl_2);

	INIT_GE_EDITOR_CB( StdLegendECtrl,    LegendPropertiesDlg    , STMakeSeriesPropertiesCtrl);
}

}
}