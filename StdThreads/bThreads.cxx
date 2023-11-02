 #include <iostream>
 #include <thread>
 #include <unordered_map>
 #include <vector>
 #include <cstdint>
 
 // Thread data block
 typedef struct {
	size_t id;
	std::vector<uint64_t> *p;
	uint64_t result;
} TDB;	 

 static const int num_threads = 7;

 //This function will be called from a thread

 void call_from_thread(int tid, std::vector<uint64_t> *p) {
	 std::unordered_map<uint32_t,uint32_t> amap;
	 std::cout << "Launched by thread " << tid << " p: " << (*p)[tid] << std::endl;
	 amap.emplace(tid,(*p)[tid]);
 }

 int main() {
	std::vector<uint64_t> primes = {2,3,5,7,11,13,17,19};
	std::vector<std::thread> th;

	 //Launch a group of threads
	 for (uint64_t i = 0; i < num_threads; ++i) {
		 TDB temp = {i, &primes,0};
		 th.push_back(std::thread(call_from_thread, i, &primes));
	 }

	 std::cout << "Launched from the main\n";

	 //Join the threads with the main thread
	 for( auto i = th.begin(); i != th.end(); i++) i->join();

	 return 0;
 }
