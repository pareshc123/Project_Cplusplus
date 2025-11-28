/*
	
	Three types of SmartPointers.
	1.	unique_ptr
	2. shared_ptr
	3. weak_ptr

	Note: They reside in #include <memory> library

	Two ways to create them:
	
	Step 1: Manual --> Syntax std::smart_pointer<type> name(new type(value));

		A. Unique_ptr: std::unique_ptr<int> uPtr(new int(10))
			
			- new int(10) creates memory on the heap.
			- unique_ptr takes ownership.
			- When p goes out of scope memory released automatically.
			
			Why use it?
				To safely manage resources without remembering delete.

		B. shared_ptr: std::shared_ptr<int> p1(new int(20));
					   std::shared_ptr<int> p2 = p1;   // shared ownership

			- Both p1 and p2 are owners.
			- Reference count = 2
			- When both are destroyed --> memory is freed.

		C. weak_ptr: std::shared_ptr<int> sp(new int(50));
					 std::weak_ptr<int> wp = sp;

					 if (auto locked = wp.lock()) {
				 		 std::cout << *locked << "\n";
					 }

			- weak_ptr does not own memory.
			- They are always created from shared_ptr
			- Must always lock() before use.


	Step 2: The Make function

		Why ? They are
			1. faster (shared_ptr only)
			2. Safer
			3. Cleaner and Shorter

		1. Unique_ptr: auto uPtr = std::make_unique<int>(10);
		2. shared_ptr: auto cPtr = std::make_shared<Car>("BMW");
		3. weak_ptr: std::weak_ptr<Car> wPtr = cPtr (always created from shared_ptr)

*/