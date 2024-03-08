#include "GraphDraw.h"


#define IMAGECLASS GraphDrawImg
#define IMAGEFILE <GraphDraw/GraphDraw.iml>
#include <Draw/iml_source.h>

namespace Upp {
	
namespace GraphDraw_ns
{
	ElementBorderPosition GetElementSubArea( PointScreen p, RectScreen r, int borderWidth ) {
		if ( ! r.Contains(p) ) return  ELEMENT_BORDER_NONE;
		int result = 0;
		if      ( r.left<=p.x && p.x<=(r.left + borderWidth) ) result |= ELEMENT_BORDER_LEFT;
		else if ((r.right-borderWidth)<=p.x && p.x<=r.right)   result |= ELEMENT_BORDER_RIGHT;
		
		if      ( r.top<=p.y && p.y<=(r.top + borderWidth) )   result |= ELEMENT_BORDER_TOP;
		else if ((r.bottom-borderWidth)<=p.y && p.y<=r.bottom) result |= ELEMENT_BORDER_BOTTOM;
	
		if (result) return  (ElementBorderPosition) result;
		return ELEMENT_BORDER_CENTER;
	};

	Size GetSmartTextSize(const char *text, const Font scaledFont, int scale, int cx) {
		if(*text == '\1') {
			RichText txt = ParseQTF(text + 1);
			txt.ApplyZoom(GetRichTextStdScreenZoom());
			Size sz;
			sz.cx = min(cx, txt.GetWidth());
			sz.cy = txt.GetHeight(Zoom(1, 1), sz.cx);
			return sz*scale;
		}
		return GetTLTextSize(ToUnicode(text, CHARSET_DEFAULT), scaledFont);
	}
	
	int GetSmartTextHeight(const char *s, int cx, const Font font, int scale) {
		if(*s == '\1') {
			RichText txt = ParseQTF(s + 1);
			txt.ApplyZoom(GetRichTextStdScreenZoom());
			return txt.GetHeight(Zoom(scale, 1), cx);
		}
		int cy = font.Info().GetHeight();
		int h = cy;
		while(*s) {
			if(*s == '\n')
				h += cy;
			s++;
		}
		return h;
	}
	

	void DrawSmartText(Draw& draw, int x, int y, int cx, const char *text, const Font scaledFont, Color ink, int scale) {
		if(*text == '\1') {
			RichText txt = ParseQTF(text + 1, 0);
			txt.ApplyZoom(GetRichTextStdScreenZoom());
			txt.Paint(Zoom(scale, 1), draw, x, y, cx);
			return;
		}
		DrawTLText(draw, x, y, cx, ToUnicode(text, CHARSET_DEFAULT), scaledFont, ink, 0);
	}

};

};

