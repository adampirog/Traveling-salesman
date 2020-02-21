#ifndef TIMER_H
#define TIMER_H


class Timer
{
	private:
		double PCFreq;
		__int64 CounterStart;
	public:
		void startCounter();
		double getCounter();
			
	
};
#endif