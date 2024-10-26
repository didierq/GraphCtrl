
#include <plugin/jpg/jpg.h>
#include <plugin/tif/tif.h>

#include "GraphCtrl.h"


namespace Upp {

#define IMAGECLASS GraphCtrlImg
#define IMAGEFILE <GraphCtrl/GraphCtrl.iml>
#include <Draw/iml_source.h>


namespace GraphDraw_ns {


float GraphCtrl_Constants::ZOOM_STEP_FACTOR = 1.2;

enum { DUMMY_KEY = K_TAB | K_9 | K_M | K_CTRL_Z }; // default values are set by  GraphCtrl_Keys::Reset();   ==> so static init sets dummy values that will never be true

dword GraphCtrl_Keys::K_KBD_UNDO         = DUMMY_KEY;
dword GraphCtrl_Keys::K_KBD_REDO         = DUMMY_KEY;
dword GraphCtrl_Keys::K_KBD_SELECT_CLEAR = DUMMY_KEY;
dword GraphCtrl_Keys::K_KBD_SELECT_ALL   = DUMMY_KEY;
dword GraphCtrl_Keys::K_KBD_LEFT_SCROLL  = DUMMY_KEY;
dword GraphCtrl_Keys::K_KBD_RIGHT_SCROLL = DUMMY_KEY;
dword GraphCtrl_Keys::K_KBD_UP_SCROLL    = DUMMY_KEY;
dword GraphCtrl_Keys::K_KBD_DOWN_SCROLL  = DUMMY_KEY;

dword GraphCtrl_Keys::K_SCROLL                               = DUMMY_KEY;

dword GraphCtrl_Keys::K_PLOT_ZOOM                            = DUMMY_KEY;

dword GraphCtrl_Keys::K_PLOT_MEASURE_TOOL                    = DUMMY_KEY;

dword GraphCtrl_Keys::K_PLOT_POINT_SELECT_REPLACE            = DUMMY_KEY;
dword GraphCtrl_Keys::K_PLOT_POINT_SELECT_APPEND             = DUMMY_KEY;
dword GraphCtrl_Keys::K_PLOT_AREA_SELECT_REPLACE_INCLUDED    = DUMMY_KEY;
dword GraphCtrl_Keys::K_PLOT_AREA_SELECT_APPEND_INCLUDED     = DUMMY_KEY;
dword GraphCtrl_Keys::K_PLOT_AREA_SELECT_REPLACE_INTERSECT   = DUMMY_KEY;
dword GraphCtrl_Keys::K_PLOT_AREA_SELECT_APPEND_INTERSECT    = DUMMY_KEY;

dword GraphCtrl_Keys::K_GE_AXIS_SELECT  = DUMMY_KEY;
dword GraphCtrl_Keys::K_GE_AXIS_ZOOM    = DUMMY_KEY;
dword GraphCtrl_Keys::K_GE_AXIS_SCROLL  = DUMMY_KEY;

dword GraphCtrl_Keys::K_GE_FLOAT_RESIZE = DUMMY_KEY;
dword GraphCtrl_Keys::K_GE_FLOAT_MOVE   = DUMMY_KEY;


void GraphCtrl_Keys::Reset() {
	// ------ KEYBOARD ACTIONS ------
	K_KBD_UNDO         = K_CTRL_Z;
	K_KBD_REDO         = K_SHIFT_CTRL_Z;
	K_KBD_SELECT_CLEAR = K_ESCAPE;
	K_KBD_SELECT_ALL   = K_CTRL | K_A;
	K_KBD_LEFT_SCROLL  = K_LEFT;
	K_KBD_RIGHT_SCROLL = K_RIGHT;
	K_KBD_UP_SCROLL    = K_UP;
	K_KBD_DOWN_SCROLL  = K_DOWN;
	
	//  ------ MOUSE ACTIONS ------ (+ CTRL/SHIFT/ALT )
	// In PLOT area  &  GraphElement area

	// In PLOT AREA
	//   SHIFT : select data
	//    CTRL : APPEND
	//    ALT  : INTERSECT
	
	// K_MOUSEMIDDLE  K_MOUSELEFT  K_MOUSERIGHT
	K_SCROLL                                = 0;
	K_PLOT_ZOOM                             = K_CTRL;
	K_PLOT_MEASURE_TOOL                     = K_ALT;

	K_PLOT_POINT_SELECT_REPLACE             = K_SHIFT;
	K_PLOT_POINT_SELECT_APPEND              = K_SHIFT | K_CTRL;  // activate APPEND on pt selection
	
	K_PLOT_AREA_SELECT_REPLACE_INCLUDED     = K_SHIFT;
	K_PLOT_AREA_SELECT_REPLACE_INTERSECT    = K_SHIFT | K_ALT;
	K_PLOT_AREA_SELECT_APPEND_INTERSECT     = K_SHIFT | K_ALT | K_CTRL;
	K_PLOT_AREA_SELECT_APPEND_INCLUDED      = K_SHIFT | K_CTRL;

	// In GRAPH ELEMENT AREA
	K_GE_AXIS_SELECT = K_SHIFT;
	K_GE_AXIS_ZOOM   = K_PLOT_ZOOM | K_GE_AXIS_SELECT;
	K_GE_AXIS_SCROLL = K_SCROLL    | K_GE_AXIS_SELECT;

	K_GE_FLOAT_RESIZE = K_CTRL;
	K_GE_FLOAT_MOVE   = 0;
}


void SaveImageToFile(String fileName, const Image& img)
{
	if (GetFileExt(fileName) == ".png") {
		PNGEncoder encoder;
		encoder.SaveFile(fileName, img);
	} else if (GetFileExt(fileName) == ".jpg") {
		JPGEncoder encoder(90);
		encoder.SaveFile(fileName, img);
	} else if (GetFileExt(fileName) == ".tif") {
		TIFEncoder encoder;
		encoder.SaveFile(fileName, img);
	} else {
		Exclamation(Format(t_("File format \"%s\" not found"), GetFileExt(fileName)));
	}
}



};


}; // namespace Upp


