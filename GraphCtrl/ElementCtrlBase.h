#ifndef _GraphCtrl_ElementCtrlBase_h_
#define _GraphCtrl_ElementCtrlBase_h_





// ============================================================================================


typedef Function<ElementPropertiesDlgInterface* (Value&)> MakeGEPropEditorCtrlFunction;

template<class ELEMENT_CLASS>
class GraphElementCtrl_Base : public ELEMENT_CLASS {
	public:
		typedef GraphElementCtrl_Base<ELEMENT_CLASS> CLASSNAME;
		typedef ELEMENT_CLASS _B;
	
		Function<void()> openPropertiesDlgCB;
		MakeGEPropEditorCtrlFunction makePropertiesCtrl;
		
	template <class STYL, class GE>
	static void TOpenPropertiesDlg(GE& lmnt, const STYL** pStyle)
	{
		STYL styl = **pStyle; // make local copy of style
		hash_t hash1 = memhash(&styl, sizeof(styl) );
		PropertiesBaseDlg dlg;
		int baseOffset = dlg.commonParamsBox.GetSize().cy;
		CtrlRetriever r1;
		int elementWidth;
		int           pos;
		int yOffset = baseOffset;
		int minWidth=0;
		
		
		//_B::Title(element.GetElementName());
		auto elem = &lmnt; //this;
		dlg.position.SetVertical();
		dlg.position.Add(FLOAT_OVER_GRAPH, t_("FLOAT") );
		dlg.position.Add(TOP_OF_GRAPH, t_("TOP") );
		dlg.position.Add(BOTTOM_OF_GRAPH, t_("BOTTOM") );
		dlg.position.Add(LEFT_OF_GRAPH, t_("LEFT") );
		dlg.position.Add(RIGHT_OF_GRAPH, t_("RIGHT") );

		for (int c=0; c<dlg.position.GetCases().GetCount(); ++c) {
			 const Switch::Case& caseData = dlg.position.GetCases()[c];
			if ((lmnt._allowedPosMask & caseData.value.To<int>()) == 0 ) dlg.position.DisableValue(caseData.value);
		}

		pos = lmnt._pos;
		elementWidth = lmnt.GetElementWidth();

		r1( dlg.width, elementWidth)
		  ( dlg.hide, lmnt._hide)
		  ( dlg.stackingPrio, lmnt._stackingPriority)
		  ( dlg.position, pos)
		  ;
		
		dlg.AddSubElement(3, minWidth, yOffset, lmnt, styl);
		dlg.AdjustSize(minWidth, yOffset-baseOffset);
		if ( dlg.Execute()==IDOK) {
			r1.Retrieve();
			lmnt.SetElementPos(static_cast<ElementPosition>(pos));
			lmnt.SetElementWidth(elementWidth);
			lmnt._parent->RefreshFromChild( REFRESH_FULL );

			dlg.Retrieve();
			hash_t hash2 = memhash(&styl, sizeof(styl) );
			if (hash1 != hash2) // local copy has been modified
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
		ElementPropertiesDlgInterface* TMakePropertiesCtrl(Value& v )
		{
			if ( v.Is<typename ELEMENT_CTRL::StyleGE*>() ) {
				typename ELEMENT_CTRL::StyleGE* st =  v.To<typename ELEMENT_CTRL::StyleGE*>();
				return static_cast<ELEMENT_CTRL*>(this)->makeGEEditorCB( * static_cast<ELEMENT_CTRL*>(this), *st );
			}
			return nullptr;
		}

	
	public:
		GraphElementCtrl_Base() {}
		virtual ~GraphElementCtrl_Base() {}
	
		template <class PARAM>
		GraphElementCtrl_Base(PARAM& p) : ELEMENT_CLASS(p) { }
		
		template <class PARAM1, class PARAM2>
		GraphElementCtrl_Base(PARAM1& p1, PARAM2 p2) : ELEMENT_CLASS(p1, p2) {}
		
		template <class PARAM1, class PARAM2, class PARAM3>
		GraphElementCtrl_Base(PARAM1& p1, PARAM2 p2, PARAM3 p3) : ELEMENT_CLASS(p1, p2, p3) {}
		
	public:

		virtual void OpenPropertiesDlg(void) {
			openPropertiesDlgCB();
		}
		
		//virtual bool Contains(PointScreen p) const                { return (_B::_frame.Contains(p)); }
		virtual void LeftDouble (PointScreen p, dword keyflags)   { OpenPropertiesDlg(); }
		virtual void ContextMenu(Bar& bar)                        { bar.Add(t_("Edit properties"), THISBACK(OpenPropertiesDlg)); }
		virtual void RightDown(PointScreen p, dword keyflags)     { MenuBar::Execute(THISBACK(ContextMenu)); }
		virtual Image  CursorImage(PointScreen p, dword keyflags) { return GraphCtrlImg::ACTIVE_CROSS(); }
};




#include "ElementCtrlDecorators.h"


#endif
