#ifndef _GraphCtrl_ElementCtrlDecorators_h_
#define _GraphCtrl_ElementCtrlDecorators_h_




template<class BASE>
class AutoHideElementCtrl : public  BASE {
	public:
	typedef AutoHideElementCtrl<BASE>  CLASSNAME;
	typedef BASE _B;

	bool isActive;

	virtual ~AutoHideElementCtrl() {}
	template <class PAR> AutoHideElementCtrl(PAR& p) : _B(p), isActive(false) {}
	template <class PAR1, class PAR2> AutoHideElementCtrl(PAR1& p1, PAR2 p2) : _B(p1, p2), isActive(false) {}
	template <class PAR1, class PAR2, class PAR3> AutoHideElementCtrl(PAR1& p1, PAR2 p2, PAR3 p3) : _B(p1, p2, p3), isActive(false) {}

	virtual void MouseEnter(PointScreen p, dword keyflags)  { isActive = true;  _B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_KEEP_DATA ); }
	virtual void MouseLeave()                         { isActive = false; _B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_KEEP_DATA ); }

	virtual void PaintElement(Draw& dw, int scale) {
		if ( isActive ) _B::PaintElement(dw, scale);
	}
};




template <class BASE >
class GraphElementCtrl_FloatMoveResize : public BASE
{
	private:
	PointScreen prevMousePoint;
	Ctrl* parentCtrl; // TODO a remplacer par GetParentCtrl() de GraphElement
	int moveBorderWidth;
	bool useRectTracker;

	public:
	typedef GraphElementCtrl_FloatMoveResize<BASE> CLASSNAME;
	typedef BASE _B;


	static Image GetMoveResizeCursor( GraphDraw_ns::ElementBorderPosition p )
	{
		switch(p) {
			case GraphDraw_ns::ELEMENT_BORDER_LEFT : return Image::SizeHorz();
			case GraphDraw_ns::ELEMENT_BORDER_TOP : return Image::SizeVert();
			case GraphDraw_ns::ELEMENT_BORDER_RIGHT : return Image::SizeHorz();
			case GraphDraw_ns::ELEMENT_BORDER_BOTTOM : return Image::SizeVert();
			case GraphDraw_ns::ELEMENT_BORDER_CENTER : return Image::SizeAll();
			case GraphDraw_ns::ELEMENT_BORDER_TOP_LEFT : return Image::SizeTopLeft();
			case GraphDraw_ns::ELEMENT_BORDER_TOP_RIGHT : return Image::SizeTopRight();
			case GraphDraw_ns::ELEMENT_BORDER_BOTTOM_RIGHT : return Image::SizeBottomRight();
			case GraphDraw_ns::ELEMENT_BORDER_BOTTOM_LEFT : return Image::SizeBottomLeft();
			default:
				return Image::SizeAll();
				break;
		}
	}


	GraphElementCtrl_FloatMoveResize() : parentCtrl(nullptr), moveBorderWidth(4), useRectTracker(false) {}

	template <class PARAM>
	GraphElementCtrl_FloatMoveResize(PARAM& p) : _B(p), parentCtrl(nullptr), moveBorderWidth(4), useRectTracker(false) {}

	template <class PAR1, class PAR2>
	GraphElementCtrl_FloatMoveResize(PAR1& p1, PAR2 p2) : _B(p1, p2), parentCtrl(nullptr), moveBorderWidth(4), useRectTracker(false) {}

	template <class PAR1, class PAR2, class PAR3>
	GraphElementCtrl_FloatMoveResize(PAR1& p1, PAR2 p2, PAR3 p3) : _B(p1, p2, p3), parentCtrl(nullptr), moveBorderWidth(4), useRectTracker(false) {}

	GraphElementCtrl_FloatMoveResize(Ctrl& p) : parentCtrl(&p) {}
	
	private:
	GraphElementCtrl_FloatMoveResize( GraphElementCtrl_FloatMoveResize& p) : _B(p), parentCtrl(p.parentCtrl), moveBorderWidth(4), useRectTracker(false)  {}
	
	template<int MOVETYPE>
	void _MoveElement (PointScreen p, dword keyflags) {
		if (keyflags & K_MOUSELEFT)
		{
			RectScreen r;
			r.left = 0;
			switch( MOVETYPE ) {
					case GraphDraw_ns::ELEMENT_BORDER_LEFT : _B::_floatFrame.left += p.x-prevMousePoint.x; break;
					case GraphDraw_ns::ELEMENT_BORDER_TOP : _B::_floatFrame.top += p.y-prevMousePoint.y; break;
					case GraphDraw_ns::ELEMENT_BORDER_RIGHT :_B::_floatFrame.right += p.x-prevMousePoint.x; break;
					case GraphDraw_ns::ELEMENT_BORDER_BOTTOM :_B::_floatFrame.bottom += p.y-prevMousePoint.y; break;
					case GraphDraw_ns::ELEMENT_BORDER_CENTER : _B::_floatFrame.Offset(p-prevMousePoint); break;
					case GraphDraw_ns::ELEMENT_BORDER_TOP_LEFT : _B::_floatFrame.left += p.x-prevMousePoint.x; _B::_floatFrame.top += p.y-prevMousePoint.y; break;
					case GraphDraw_ns::ELEMENT_BORDER_TOP_RIGHT : _B::_floatFrame.right += p.x-prevMousePoint.x; _B::_floatFrame.top += p.y-prevMousePoint.y; break;
					case GraphDraw_ns::ELEMENT_BORDER_BOTTOM_RIGHT : _B::_floatFrame.right += p.x-prevMousePoint.x; _B::_floatFrame.bottom += p.y-prevMousePoint.y; break;
					case GraphDraw_ns::ELEMENT_BORDER_BOTTOM_LEFT : _B::_floatFrame.left += p.x-prevMousePoint.x; _B::_floatFrame.bottom += p.y-prevMousePoint.y; break;
			}
			prevMousePoint = p;
			_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_KEEP_DATA );
		}
	}

	
	public:
	virtual ~GraphElementCtrl_FloatMoveResize() {}

	void SetUseRectTracker(bool b = false) { useRectTracker = b; }
	virtual bool Contains(PointScreen p) const { return (_B::_frame.Contains(p)); }

	virtual Image  CursorImage(PointScreen p, dword keyflags) {
		if (_B::IsFloat()) {
			if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_FLOAT_RESIZE) ) {
				return ( GetMoveResizeCursor( GraphDraw_ns::GetElementSubArea(p, _B::_floatFrame, moveBorderWidth) ) );
			}
			else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_FLOAT_MOVE) ) {
				return GraphCtrlImg::ELEMENT_MOVE();
			}
		}
		return _B::CursorImage(p, keyflags);
	}
	
	
	Callback MakeRestoreElementPosCB() {
		return 	THISBACK1( _B::SetFloatFrame, _B::_floatFrame);
	}

	virtual void LeftDown(PointScreen p, dword keyflags) {
		prevMousePoint = p;
		if (parentCtrl == nullptr) {
			parentCtrl = _B::_parent->GetParentCtrl().template To<Ctrl*>();
		}
		if (_B::IsFloat() ) {
			
			if ( (parentCtrl != nullptr) && (keyflags & K_MOUSELEFT) )
			{
				RectTracker tracker(*parentCtrl);
				tracker.Dashed().Animation();
				tracker.MaxRect(parentCtrl->GetSize());
				tracker.SetCursorImage( CursorImage(p,keyflags) );
				UndoStackData undo;
				undo.undoAction << MakeRestoreElementPosCB();
				if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_FLOAT_RESIZE) ) { // DO RESIZE
					if (useRectTracker) {
						switch( GraphDraw_ns::GetElementSubArea(p, _B::_floatFrame, moveBorderWidth) ) {
							case GraphDraw_ns::ELEMENT_BORDER_LEFT : _B::_floatFrame = tracker.Track(_B::_floatFrame, ALIGN_LEFT, ALIGN_CENTER); break;
							case GraphDraw_ns::ELEMENT_BORDER_TOP : _B::_floatFrame = tracker.Track(_B::_floatFrame, ALIGN_CENTER, ALIGN_TOP); break;
							case GraphDraw_ns::ELEMENT_BORDER_RIGHT : _B::_floatFrame = tracker.Track(_B::_floatFrame, ALIGN_RIGHT, ALIGN_CENTER); break;
							case GraphDraw_ns::ELEMENT_BORDER_BOTTOM : _B::_floatFrame = tracker.Track(_B::_floatFrame, ALIGN_CENTER, ALIGN_BOTTOM); break;
							case GraphDraw_ns::ELEMENT_BORDER_CENTER : _B::_floatFrame = tracker.Track(_B::_floatFrame, ALIGN_CENTER, ALIGN_CENTER); break;
							case GraphDraw_ns::ELEMENT_BORDER_TOP_LEFT : _B::_floatFrame = tracker.Track(_B::_floatFrame, ALIGN_LEFT, ALIGN_TOP); break;
							case GraphDraw_ns::ELEMENT_BORDER_TOP_RIGHT : _B::_floatFrame = tracker.Track(_B::_floatFrame, ALIGN_RIGHT, ALIGN_TOP); break;
							case GraphDraw_ns::ELEMENT_BORDER_BOTTOM_RIGHT : _B::_floatFrame = tracker.Track(_B::_floatFrame, ALIGN_RIGHT, ALIGN_BOTTOM); break;
							case GraphDraw_ns::ELEMENT_BORDER_BOTTOM_LEFT : _B::_floatFrame = tracker.Track(_B::_floatFrame, ALIGN_LEFT, ALIGN_BOTTOM); break;
							default:
								_B::_floatFrame = tracker.Track(_B::_floatFrame, ALIGN_CENTER, ALIGN_BOTTOM);
								break;
						}
					}
					else {  // DO MOVE
						switch( GraphDraw_ns::GetElementSubArea(p, _B::_floatFrame, moveBorderWidth) ) {
							case GraphDraw_ns::ELEMENT_BORDER_LEFT : _B::_parent->DoLocalLoop( THISBACK( _MoveElement<ELEMENT_BORDER_LEFT> ) ); break;
							case GraphDraw_ns::ELEMENT_BORDER_TOP : _B::_parent->DoLocalLoop( THISBACK( _MoveElement<ELEMENT_BORDER_TOP> ) ); break;
							case GraphDraw_ns::ELEMENT_BORDER_RIGHT : _B::_parent->DoLocalLoop( THISBACK( _MoveElement<ELEMENT_BORDER_RIGHT> ) ); break;
							case GraphDraw_ns::ELEMENT_BORDER_BOTTOM : _B::_parent->DoLocalLoop( THISBACK( _MoveElement<ELEMENT_BORDER_BOTTOM> ) ); break;
							case GraphDraw_ns::ELEMENT_BORDER_CENTER : _B::_parent->DoLocalLoop( THISBACK( _MoveElement<ELEMENT_BORDER_CENTER> ) ); break;
							case GraphDraw_ns::ELEMENT_BORDER_TOP_LEFT : _B::_parent->DoLocalLoop( THISBACK( _MoveElement<ELEMENT_BORDER_TOP_LEFT> ) ); break;
							case GraphDraw_ns::ELEMENT_BORDER_TOP_RIGHT : _B::_parent->DoLocalLoop( THISBACK( _MoveElement<ELEMENT_BORDER_TOP_RIGHT> ) ); break;
							case GraphDraw_ns::ELEMENT_BORDER_BOTTOM_RIGHT : _B::_parent->DoLocalLoop( THISBACK( _MoveElement<ELEMENT_BORDER_BOTTOM_RIGHT> ) ); break;
							case GraphDraw_ns::ELEMENT_BORDER_BOTTOM_LEFT : _B::_parent->DoLocalLoop( THISBACK( _MoveElement<ELEMENT_BORDER_BOTTOM_LEFT> ) ); break;
							default:
								_B::_parent->DoLocalLoop( THISBACK( _MoveElement<ELEMENT_BORDER_CENTER> ) );
								break;
						}
					}
					_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_KEEP_DATA );
					
					if (p != (_B::_parent->GetParentCtrl().template To<Ctrl*>())->GetMouseViewPos()) {
						undo.redoAction << MakeRestoreElementPosCB();
						_B::_parent->AddUndoAction(undo);
					}
				}
				else if ( TEST_GC_KEYS(keyflags, GraphCtrl_Keys::K_GE_FLOAT_MOVE) ) {
					if (useRectTracker) {
						_B::_floatFrame = tracker.Track(_B::_floatFrame, ALIGN_CENTER, ALIGN_CENTER);
					}
					else {
						_B::_parent->DoLocalLoop( THISBACK( _MoveElement<ELEMENT_BORDER_CENTER> ) );
					}
					_B::_parent->RefreshFromChild( GraphDraw_ns::REFRESH_KEEP_DATA );

					if (p != (_B::_parent->GetParentCtrl().template To<Ctrl*>())->GetMouseViewPos()) {
						undo.redoAction << MakeRestoreElementPosCB();
						_B::_parent->AddUndoAction(undo);
					}
				}
			}
		}
		else
		{
			_B::LeftDown(p, keyflags);
		}
	}
};


#endif
