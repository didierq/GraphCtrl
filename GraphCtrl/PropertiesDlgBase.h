#ifndef _GraphCtrl_PropertiesDlgBase_h_
#define _GraphCtrl_PropertiesDlgBase_h_






// ============================================================================================
//                        ElementPropertiesDlgInterface
// ============================================================================================

class ElementPropertiesDlgInterface : public ParentCtrl {
	public:
		ElementPropertiesDlgInterface() { }
		virtual ~ElementPropertiesDlgInterface() {}
		virtual void Retrieve() = 0;

		typedef Vector<ElementPropertiesDlgInterface*> VList;
};


//class SeriesPropertiesDlgInterface : public ElementPropertiesDlgInterface {
//	protected:
//		GraphSeriesDecoratorVector& series;
//		
//	public:
//		SeriesPropertiesDlgInterface(GraphSeriesDecoratorVector& s) : series(s) { }
//		virtual ~SeriesPropertiesDlgInterface() {}
//};


//// GraphElement editor dialog info
class ElementPropertiesDlgInfo {
	public:
		Function<void()> DeleteDlg;
		Function<void()> RetrieveFromDlg;
		Function<void()> WhenDlgAction;

		ElementPropertiesDlgInfo()  = delete;
		ElementPropertiesDlgInfo(ElementPropertiesDlgInterface* p) : dlg(p) {}
		ElementPropertiesDlgInfo(const ElementPropertiesDlgInfo& p) : dlg(p.dlg) { copyFunctions(p); }
		ElementPropertiesDlgInfo(      ElementPropertiesDlgInfo& p) : dlg(p.dlg) { copyFunctions(p); }
		ElementPropertiesDlgInfo& operator= (const ElementPropertiesDlgInfo& p) { dlg = p.dlg; copyFunctions(p); return *this; }
		ElementPropertiesDlgInfo& operator= (      ElementPropertiesDlgInfo& p) { dlg = p.dlg; copyFunctions(p); return *this; }

		~ElementPropertiesDlgInfo() {};

		void Free() {
			if (dlg) {
				RetrieveFromDlg.Clear();
				DeleteDlg();
				DeleteDlg.Clear();
				dlg = nullptr;
			}
		}

		const ElementPropertiesDlgInterface* GetCtrl()        const { return dlg; }

	private:
		ElementPropertiesDlgInterface* dlg;
		void copyFunctions(const ElementPropertiesDlgInfo& p) {
			DeleteDlg = p.DeleteDlg;
			RetrieveFromDlg = p.RetrieveFromDlg;
			WhenDlgAction = p.WhenDlgAction;
		}

		ElementPropertiesDlgInfo(ElementPropertiesDlgInfo&& p)            = delete;
		ElementPropertiesDlgInfo& operator=(ElementPropertiesDlgInfo&& p) = delete;
};



template <class BASE>
class ElementPropertiesContainer : public BASE {
	private:
		ElementPropertiesDlgInterface::VList elemPropDlgList;

	public:
		ElementPropertiesContainer() {}
		virtual ~ElementPropertiesContainer() {
			ElementPropertiesDlgInterface::VList::Iterator  iter = elemPropDlgList.begin();
			while(iter != elemPropDlgList.end()) {
				delete (*iter);
				++iter;
			}
		}

		int GetCountSubElement() const { return elemPropDlgList.GetCount(); }
		
		template <class ELEMENT, class ESTYLE>
		void AddSubElement(int sepWidth, int& minWidth, int& yOffset, ELEMENT& ELEM_, ESTYLE& STYL_) {
			auto ps = &STYL_;
			Value v = RawToValue(ps);
			
			ElementPropertiesDlgInterface* sdlg = ELEM_.makePropertiesCtrl( v );
			if (sdlg) {
				elemPropDlgList.Add(sdlg);
				int tmp = sdlg->GetSize().cy;
				minWidth = Upp::max(minWidth, sdlg->GetSize().cx);
				sdlg->HSizePos(sepWidth, sepWidth).TopPos( yOffset, tmp);
				yOffset += tmp + sepWidth;
				BASE::Add(*sdlg);
			}
		}

		template <class ELEMENT, class ESTYLE>
		void AddSubElement(int sepWidth, int& yOffset, ELEMENT& ELEM_, ESTYLE& STYL_) {
			int minWidth = 0;
			AddSubElement<ELEMENT, ESTYLE>(sepWidth, minWidth, yOffset, ELEM_, STYL_);
		}
		
		
		virtual void Retrieve() {
			ElementPropertiesDlgInterface::VList::Iterator iter = elemPropDlgList.begin();
			while(iter != elemPropDlgList.end()) {
				(*iter)->Retrieve();
				++iter;
			}
		}
};

//class PropertiesTabBase : public WithElementDlgLayout<ElementPropertiesContainer<ElementPropertiesDlgInterface> > {
class PropertiesTabBase : public ElementPropertiesContainer<ElementPropertiesDlgInterface> {
	public:
		PropertiesTabBase() {}
		virtual ~PropertiesTabBase() {}
};



class PropertiesBaseDlg : public WithElementPropertiesLayout<ElementPropertiesContainer<TopWindow> > {
	public:
		PropertiesBaseDlg() {
			CtrlLayoutOKCancel(*this, t_("Properties"));
			Sizeable();
		}
		
		void AdjustSize(int xSize, int propertiesHeight) {
			Size sz = GetSize();
			sz.cy += propertiesHeight;
			sz.cx = xSize;
			this->SetMinSize(sz);
		}
		
		
		virtual ~PropertiesBaseDlg() {}
};


#endif
