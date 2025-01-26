#ifndef _GraphDraw_UpdateCounter_h_
#define _GraphDraw_UpdateCounter_h_


namespace GraphDraw_ns
{
	// ============================================================================================
	template <class T>
	class UpdateCounter {
		private:
		UpdateCounter(const UpdateCounter<T>& p)  = delete;
		UpdateCounter(      UpdateCounter<T>& p)  = delete;
		UpdateCounter(const UpdateCounter<T>&& p) = delete;
		UpdateCounter(      UpdateCounter<T>&& p) = delete;
	
		public:
		static volatile Atomic globalUpdateCounter;
		Atomic::value_type currUpdateCount;
	
		UpdateCounter() : currUpdateCount(-1) {}
		~UpdateCounter(){}
	
		UpdateCounter<T>& operator=(const UpdateCounter<T>& p)  { currUpdateCount = p.currUpdateCount; return *this; }
		UpdateCounter<T>& operator=(      UpdateCounter<T>& p)  { currUpdateCount = p.currUpdateCount; return *this; }
		UpdateCounter<T>& operator=(const UpdateCounter<T>&& p) { currUpdateCount = p.currUpdateCount; return *this; }
		UpdateCounter<T>& operator=(      UpdateCounter<T>&& p) { currUpdateCount = p.currUpdateCount; return *this; }
		
		inline void Inc() { currUpdateCount = AtomicInc( globalUpdateCounter ); }
		
		inline bool operator==(const UpdateCounter<T>& p) const { return currUpdateCount == p.currUpdateCount; } 
		inline bool operator!=(const UpdateCounter<T>& p) const { return currUpdateCount != p.currUpdateCount; } 
	};
	
	template <class T>
	volatile Atomic UpdateCounter<T>::globalUpdateCounter(0);
}


#endif
