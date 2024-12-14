#ifndef _GraphCtrl_PropertiesDlgBase_h_
#define _GraphCtrl_PropertiesDlgBase_h_




enum GECommonPropEditorLevel {
	GE_CommonProp_MANADATORY=0,
	GE_CommonProp_FULL,
	GE_CommonProp_FULLWITHEXTRAS,
};


// ============================================================================================
//                        GEPropertiesDlgInterface
// ============================================================================================

class GEPropertiesDlgInterface : public ParentCtrl {
	public:
		GEPropertiesDlgInterface() { }
		virtual ~GEPropertiesDlgInterface() {}
		virtual void Retrieve() = 0;

		typedef Vector<GEPropertiesDlgInterface*> VList;
};


// ============================================================================================
//                        MultiGEPropertiesDlgList
// ============================================================================================
template <class BASE>
class MultiGEPropertiesDlgList : public BASE {
	private:
		GEPropertiesDlgInterface::VList elemPropDlgList;

	public:
		MultiGEPropertiesDlgList() {}
		virtual ~MultiGEPropertiesDlgList() {
			GEPropertiesDlgInterface::VList::Iterator  iter = elemPropDlgList.begin();
			while(iter != elemPropDlgList.end()) {
				delete (*iter);
				++iter;
			}
		}

		int GetCountSubElement() const { return elemPropDlgList.GetCount(); }
		
				
		template <class ELEMENT, class ESTYLE>
		void AddSubElement(int sepDist, int& minWidth, int& yOffset, ELEMENT& ELEM_, ESTYLE& STYL_) {
			Value v = RawToValue(&STYL_);
			
			GEPropertiesDlgInterface* sdlg = ELEM_.MakeGEPropertiesCtrlCB( v );
			if (sdlg) {
				elemPropDlgList.Add(sdlg);
				int tmp = sdlg->GetSize().cy;
				minWidth = Upp::max(minWidth, sdlg->GetSize().cx);
				sdlg->HSizePos(0, 0).TopPos( yOffset+sepDist, tmp);
				yOffset += tmp + sepDist;
				BASE::Add(*sdlg);
			}
		}

		template <class ELEMENT, class ESTYLE>
		void AddSubElement(int sepDist, int& yOffset, ELEMENT& ELEM_, ESTYLE& STYL_) {
			int minWidth = 0;
			AddSubElement<ELEMENT, ESTYLE>(sepDist, minWidth, yOffset, ELEM_, STYL_);
		}
		

		template <class ELEMENT>
		void AddSubCElement(GECommonPropEditorLevel lvl, int sepDist, int& minWidth, int& yOffset, ELEMENT& ELEM_, int sepHeight=0) {
			Value v = RawToValue(&ELEM_);
			GEPropertiesDlgInterface* sdlg = ELEM_.MakeGECommonPropertiesCtrlCB( v, lvl );
			if (sdlg) {
				elemPropDlgList.Add(sdlg);
				int tmp = sdlg->GetSize().cy;
				minWidth = Upp::max(minWidth, sdlg->GetSize().cx);
				sdlg->HSizePos(0, 0).TopPos( yOffset+sepDist, tmp + sepHeight);
				yOffset += tmp + sepDist + sepHeight;
				BASE::Add(*sdlg);
			}
		}

		template <class ELEMENT>
		void AddSubCElement(GECommonPropEditorLevel lvl, int sepDist, int& yOffset, ELEMENT& ELEM_, int sepHeight=0) {
			int minWidth = 0;
			AddSubCElement<ELEMENT>(lvl, sepDist, minWidth, yOffset, ELEM_, sepHeight);
		}
		
		
		virtual void Retrieve() {
			GEPropertiesDlgInterface::VList::Iterator iter = elemPropDlgList.begin();
			while(iter != elemPropDlgList.end()) {
				(*iter)->Retrieve();
				++iter;
			}
		}
};

class PropertiesTabBase : public MultiGEPropertiesDlgList<GEPropertiesDlgInterface> {
	public:
		PropertiesTabBase() {}
		virtual ~PropertiesTabBase() {}
};



class GEPropertiesBaseDlg : public WithOKCancelLayout<MultiGEPropertiesDlgList<TopWindow> > {
	
	public:
		GEPropertiesBaseDlg() {
			CtrlLayoutOKCancel(*this, t_("Properties"));
			Sizeable();
		}
		
		void AdjustSize(int xSize, int propertiesHeight) {
			Size sz = GetSize();
			sz.cy += propertiesHeight;
			sz.cx = xSize;
			this->SetMinSize(sz);
		}
		
		virtual ~GEPropertiesBaseDlg() {}
};


template <class ELEMENT, class STYL=int>
class GECommonSubPropertiesDlg : public WithGEDlgCommonMandatoryLayout<GEPropertiesDlgInterface> {
	public:
	CtrlRetriever r1;
	ELEMENT*      elem;
	int           pos;
	int           elementWidth;
	bool          hide;
	int           stackPrio;

	public:
	typedef GECommonSubPropertiesDlg<ELEMENT, STYL>  CLASSNAME;
	typedef WithGEDlgCommonMandatoryLayout<GEPropertiesDlgInterface> _B;

	
	GECommonSubPropertiesDlg() : elem(nullptr), pos(100) {
		SetLayout_GEDlgCommonMandatoryLayout(*this, true);
		Size sz = _B::GetLayoutSize();
		_B::SetMinSize(sz);
		_B::SetRect(sz);
	}
	virtual ~GECommonSubPropertiesDlg() {}

	
	void InitDlg(ELEMENT& element, STYL* styl=nullptr) {
		//_B::Title(element.GetElementName());
		elem = &element;
		bPosition.SetVertical();
		bPosition.Add(FLOAT_OVER_GRAPH, t_("FLOAT") );
		bPosition.Add(TOP_OF_GRAPH, t_("TOP") );
		bPosition.Add(BOTTOM_OF_GRAPH, t_("BOTTOM") );
		bPosition.Add(LEFT_OF_GRAPH, t_("LEFT") );
		bPosition.Add(RIGHT_OF_GRAPH, t_("RIGHT") );

		for (int c=0; c<bPosition.GetCases().GetCount(); ++c) {
			 const Switch::Case& caseData = bPosition.GetCases()[c];
			if ((elem->GetAllowedPosMask() & caseData.value.To<int>()) == 0 ) bPosition.DisableValue(caseData.value);
		}

		pos = elem->GetElementPos();
		elementWidth = elem->GetElementWidth();
		hide = elem->IsHidden();
		stackPrio = elem->GetStackingPriority();

		r1( bWidth, elementWidth)
		  ( bHide, hide)
		  ( bStackingPrio, stackPrio)
		  ( bPosition, pos )
		  ;
	}
	
	virtual void Retrieve() {
		r1.Retrieve();
		elem->SetElementPos(static_cast<ElementPosition>(pos));
		elem->SetElementWidth(elementWidth);
		elem->Hide(hide);
		elem->SetStackingPriority(stackPrio);
		elem->_parent->RefreshFromChild( REFRESH_FULL );
	}
};
// ============================================================================================


#endif
