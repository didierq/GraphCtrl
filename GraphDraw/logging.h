#ifndef _GraphDraw_logging_h_
#define _GraphDraw_logging_h_


#ifdef  BLITZ_INDEX__
#define MK__gd            MK__s_(COMBINE3(BLITZ_INDEX__, _GD_, __LINE__))
#else
#define MK__gd            MK__s_(COMBINE( _GD_, __LINE__))
//#define MK__gd            MK__s_(__LINE__)
#endif

#ifdef _DEBUG
#define GDLOGBLOCK(a)  Upp::StringStream MK__gd; MK__gd << "(" << (unsigned int) this << ")  " << a; LOGBLOCK(MK__gd.GetResult().Begin())
#else
#define GDLOGBLOCK(a)  LOG_NOP
#endif


namespace Upp {

struct DebugLogBlockString
{
	DebugLogBlockString(const String name, bool cond) : name(name), printLogs(cond) { if (printLogs) { VppLog() << name << EOL << LOG_BEGIN; } }
	~DebugLogBlockString()                                                          { if (printLogs) { VppLog() << LOG_END << "//" << name << EOL; } }
	const String name;
	bool printLogs;
};
END_UPP_NAMESPACE

#define RLOGBLOCK_STR(COND, TXT) StringStream MK__gd; MK__gd << TXT; DebugLogBlockString DLBS( MK__gd.GetResult(), COND )
#define RLOG_STR(COND, TXT)      {if ( bool(COND) ) { StringStream str; str << TXT; VppLog() << str.GetResult()<< EOL; }}



#endif
