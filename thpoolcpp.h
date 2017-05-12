#ifdef __cplusplus
extern "C" {
#endif
#include "thpool.h"
#ifdef __cplusplus
}
#endif
#include "singleton.h"
#include <functional>
class ThreadJob {
	public:
		virtual void run() = 0;
};

class ThreadPool : public Singleton<ThreadPool>{
	private:	
		threadpool thpool = {0x00};
	public:
		ThreadPool(int num = 4) {
			thpool = thpool_init(num);
		}
		virtual ~ThreadPool(){
			if(thpool) {
				thpool_destroy(thpool);
			}
		}
		void wait() {
			if(thpool) {
				thpool_wait(thpool);
			}
		}
		void add(void*(*job)(void*), void* arg) {
			if(thpool && job) {
				thpool_add_work(thpool, job, arg);
			}
		}
		void add(ThreadJob* job) {
			if(thpool && job) {
				thpool_add_work(thpool, [](void* thiz)->void*{
						ThreadJob* job = static_cast<ThreadJob*>(thiz);	
						job->run();
						return NULL;
						}, job);
			}
		}
		
private:
	/*************************************************************************
		Copy constructor and assignment usage is denied.
	*************************************************************************/
	ThreadPool(const ThreadPool&) : Singleton <ThreadPool>() {}
	ThreadPool& operator=(const ThreadPool&) {return *this;}
};
