#include "GraphCtrl.h"
namespace Upp {

	INITIALIZER(GraphCtrl) {
		GraphDraw_ns::GraphCtrl_Keys::Reset();
		GraphDraw_ns::InitGraphElementCtrls();

	};
}
