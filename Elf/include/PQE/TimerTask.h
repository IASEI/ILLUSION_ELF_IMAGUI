#ifndef __TIMERTASK_H__
#define __TIMERTASK_H__

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <Windows.h>

namespace PQE
{
	class TimerTask
	{
	public:
		TimerTask();

		TimerTask(std::string mName);

		~TimerTask();

		//�̶߳�ʱ��------------------------------------------------------------

		//������ʱ��
		void start(int interval, std::function<void()> task);

		void startOnce(int delay, std::function<void()> task);

		//������ʱ
		void stop();

		//��ͨ��ʱ��------------------------------------------------------------

		//һ�㶨ʱ��
		void runTimer(unsigned long  interval, std::function<void()> task);

		bool runTimer(unsigned long  interval);
		bool runTimerInterruption(unsigned long  interval);
		bool resetRunTimer();
	private:
		std::string name;
		//�̶߳�ʱ��
		std::atomic<bool> expired; // timer stopped status
		std::atomic<bool> try_to_expire; // timer is in stop process
		std::mutex mutex;
		std::condition_variable expired_cond;
		//��ͨ��ʱ��
		LARGE_INTEGER begin, end, freq;
		bool timeStart;
	};
}
#endif

