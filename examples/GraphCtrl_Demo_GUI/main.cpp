#include <CtrlLib/CtrlLib.h>
#include <GraphCtrl_Demo/GraphCtrl_Demo.h>


using namespace Upp;



struct sChLook_LabelBox {
	Image img;
};

Value Make_ChLook_LabelBox(const Image& img)
{
	sChLook_LabelBox x;
/*
	CORNER_TOP_LEFT = 0x01,
	CORNER_TOP_RIGHT = 0x02,
	CORNER_BOTTOM_LEFT = 0x04,
	CORNER_BOTTOM_RIGHT = 0x08,
*/

//	x.img = MakeButton(8, img, 2, Blue(), CORNER_BOTTOM_RIGHT);
	x.img = MakeButton(8, img, 2, Blue());
	return RawToValue(x);
}

Value ChLookFn_LabelBox(Draw& w, const Rect& r, const Value& v, int op, Color ink) {
	
	if( v.Is<sChLook_LabelBox>() )
	{
		const sChLook_LabelBox& e = v.To<sChLook_LabelBox>();
		ChPaint(w, r, e.img);
		return 1;
	}
	return Null;
}

INITBLOCK {
	ChLookFn(ChLookFn_LabelBox);
}

GUI_APP_MAIN
{
	RLOG("START TEST");

//	GUI_GlobalStyle_Write(GUISTYLE_X);
	//LabelBox::SetLook(GraphCtrl_DemoImg::CTRL_BACKGND());
//	LabelBox::SetLook(White());
//	LabelBox::SetLook(WithHotSpots(MakeButton(8, GraphCtrl_DemoImg::CTRL_BACKGND(), 5, Blue()), DPI(8), DPI(8), 0, 0));
//	LabelBox::SetLook( MakeButton(4, GraphCtrl_DemoImg::CTRL_BACKGND(), 2, Null) );

//	ChDarkSkin();
	
	static const Value myLabelBoxLook = Make_ChLook_LabelBox(GraphCtrl_DemoImg::CTRL_BACKGND());
	LabelBox::SetLook( myLabelBoxLook );
//	TopWindow::StyleDefault().Write().background = GraphCtrl_DemoImg::APP_BACKGND();



	GraphCtrl_Demo().Run();
}
