#ifndef _GraphCtrl_ElementCtrlBase_h_
#define _GraphCtrl_ElementCtrlBase_h_





// ============================================================================================

typedef Function<GEPropertiesDlgInterface* (Value&)> MakeGEPropEditorCtrlFunction;
typedef Function<GEPropertiesDlgInterface* (Value&, GECommonPropEditorLevel lvl)> MakeGECommonPropEditorCtrlFunction;

template<class ELEMENT_CLASS>
class GraphElementCtrl_Base : public ELEMENT_CLASS {
	public:
		typedef GraphElementCtrl_Base<ELEMENT_CLASS> CLASSNAME;
		typedef ELEMENT_CLASS _B;
	
		Function<void()> OpenGEPropertiesDlgCB;
		MakeGEPropEditorCtrlFunction       MakeGEPropertiesCtrlCB;
		MakeGECommonPropEditorCtrlFunction MakeGECommonPropertiesCtrlCB;
	
	template <class STYL, class GE>
	static void TOpenGEPropertiesDlg(GE& lmnt, const STYL** pStyle)
	{
		STYL styl = **pStyle; // make local copy of style before modification
		hash_t hash1 = memhash(&styl, sizeof(styl) );
		GEPropertiesBaseDlg dlg;
		int yOffset = 0;
		int minWidth=0;
		auto elem = &lmnt;

		dlg.AddSubCElement(GE_CommonProp_FULLWITHEXTRAS, 3, minWidth, yOffset, lmnt, 0);
		dlg.AddSubElement(3, minWidth, yOffset, lmnt, styl);

		dlg.AdjustSize(minWidth, yOffset);

		if ( dlg.Execute()==IDOK) {
			dlg.Retrieve();
			hash_t hash2 = memhash(&styl, sizeof(styl) );
			if (hash1 != hash2) // local style copy has been modified
			{
				const STYL* pstylOrig = *pStyle;
				lmnt._parent->RequestChStyleLocal();
				if ( pstylOrig != *pStyle ) {
					// If owner Graph calls SetGEStyle() for this GraphElement : then pStyle pointer will have changed value (it now points on the local style :)
					// ==> pStyle can now be updated with new values
					* const_cast<STYL*>(*pStyle) = styl;
					lmnt._parent->RefreshFromChild( GraphDraw_ns::REFRESH_DEFAULT );
				}
				else {
					// If owner DOES NOT call SetGEStyle() ... then this means that this GraphElement was added dynamically
					// ==> it has to manage it's own local style !!  TODO
					* const_cast<STYL*>(*pStyle) = styl;  // TODO
					lmnt._parent->RefreshFromChild( GraphDraw_ns::REFRESH_DEFAULT );
				}
			}
		}
	}

	protected:
		template <class ELEMENT_CTRL>
		GEPropertiesDlgInterface* TMakeGEPropertiesCtrl(Value& v)
		{
			if ( v.Is<typename ELEMENT_CTRL::StyleGE*>() ) {
				typename ELEMENT_CTRL::StyleGE* st =  v.To<typename ELEMENT_CTRL::StyleGE*>();
				return static_cast<ELEMENT_CTRL*>(this)->makeGEEditorCB( * static_cast<ELEMENT_CTRL*>(this), *st );
			}
			return nullptr;
		}

		GEPropertiesDlgInterface* MakeGECommonPropertiesCtrl(Value& v, GECommonPropEditorLevel lvl)
		{
			GECommonSubPropertiesDlg<CLASSNAME>& dlg = * new GECommonSubPropertiesDlg<CLASSNAME>();
			if (lvl == GE_CommonProp_FULLWITHEXTRAS) {
				SetLayout_GEDlgCommonWithExtrasLayout(dlg);
				Size sz = WithGEDlgCommonWithExtrasLayout<Ctrl>::GetLayoutSize();
				//SetLayout_Size(dlg, sz.cx, sz.cy);
				dlg.SetMinSize(sz);
				dlg.SetRect(sz);
			}
			dlg.InitDlg(*this);
			return &dlg;
		}

		void InitGECtrlBase() {
			MakeGECommonPropertiesCtrlCB = [=](Value& v, GECommonPropEditorLevel lvl) ->GEPropertiesDlgInterface* { return MakeGECommonPropertiesCtrl(v, lvl); };
		}
			
	public:
		GraphElementCtrl_Base() { InitGECtrlBase(); }
		virtual ~GraphElementCtrl_Base() {}
	
		template <class PARAM>
		GraphElementCtrl_Base(PARAM& p) : ELEMENT_CLASS(p) { InitGECtrlBase(); }
		
		template <class PARAM1, class PARAM2>
		GraphElementCtrl_Base(PARAM1& p1, PARAM2 p2) : ELEMENT_CLASS(p1, p2) { InitGECtrlBase(); }
		
		template <class PARAM1, class PARAM2, class PARAM3>
		GraphElementCtrl_Base(PARAM1& p1, PARAM2 p2, PARAM3 p3) : ELEMENT_CLASS(p1, p2, p3) { InitGECtrlBase(); }
		
	public:

		virtual void OpenGEPropertiesDlg() {
			OpenGEPropertiesDlgCB();
		}
		
		//virtual bool Contains(PointScreen p) const                { return (_B::_frame.Contains(p)); }
		virtual void LeftDouble (PointScreen p, dword keyflags)   { }
		virtual void ContextMenu(Bar& bar)                        { bar.Add(t_("Edit properties"), THISBACK(OpenGEPropertiesDlg)); }
		virtual void RightDown(PointScreen p, dword keyflags)     { MenuBar::Execute(THISBACK(ContextMenu)); }
		virtual Image  CursorImage(PointScreen p, dword keyflags) { return GraphCtrlImg::ACTIVE_CROSS(); }
};




#include "ElementCtrlDecorators.h"


#endif
