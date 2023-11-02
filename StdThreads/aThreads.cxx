 #include <iostream>
 #include <thread>
 #include <unordered_map>
 #include <vector>
 #include <cstdint>

 static const int num_threads = 7;

 //This function will be called from a thread

 void call_from_thread(int tid, std::vector<uint64_t> *p) {
	 std::unordered_map<uint32_t,uint32_t> amap;
	 std::cout << "Launched by thread " << tid << " p: " << (*p)[tid] << std::endl;
	 amap.emplace(tid,(*p)[tid]);
 }

 int main() {
	std::vector<uint64_t> primes = {2,3,5,7,11,13,17,19};
	 
	 
	 
	 std::thread t[num_threads];

	 //Launch a group of threads
	 for (int i = 0; i < num_threads; ++i) {
		 t[i] = std::thread(call_from_thread, i, &primes);
	 }

	 std::cout << "Launched from the main\n";

	 //Join the threads with the main thread
	 for (int i = 0; i < num_threads; ++i) {
		 t[i].join();
	 }

	 return 0;
 }
