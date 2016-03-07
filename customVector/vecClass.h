/**************************************************************************/
/*	Author		: Pavan Acharya C
	file		: Header File for vecClass
	IDE/ver		: Dev-C++ 5.11, C++ 11
	comments	: This file contains the class decleration for the vec Class. 
				  It is encapsulated in the namespace custom_std.
				  reference - Accelerated C++
*/
/**************************************************************************/


#ifndef VECCLASS_H
#define VECCLASS_H

#include <algorithm>
#include <memory>
#include <cstddef>

namespace custom_std{
	
	inline namespace v1{
	
		template<class T> class vec{
			
			// typedefs
			typedef T* iterator;
			typedef const T* const_iterator;
			typedef size_t size_type;
			
			
			public:
				
				//Constructors...
				//default
				vec():data(0),endData(0),limit(0) { /**/ }
				//Explicit
				explicit vec(size_type n, const T& val = T());
				//Copy
				vec(const vec& v);
				
				//Destructor
				~vec();
				
				
				//Overloaded Operators...
				//subscript, random access
				vec& operator[] (size_type i);
				//Assignement
				vec& operator= (const vec& v);
				
				//Interface Function Members
				
				//Iterators to objects
				iterator begin(){
					return data;
				}
				
				iterator end(){
					return endData;
				}
				
				//Const Iterators to objects
				const_iterator begin() const {
					return data;
				}
				
				const_iterator end() const {
					return endData;
				}
				
				// Container Information
				// return amount of objects contained
				size_type size() const {
					return (data - endData);
				}
				// return the size of allocated mem
				size_type capacity() const {
					return (data - limit);
				}
				// indicate if container has no objects
				bool empty() const {
					return (data == endData);
				}
				
				//Add data to container
				void push_back();
				
			private:
				//delineates the start of objects
				iterator data; 
				//delineates the end (+1) of objects
				iterator endData;
				//delineates the end (+1) of allocated memory
				iterator limit;
				
				//allocator object for raw memory control
				std::allocator<T> memManage;
				
				//Private functions to control cunstructors, assignments, destructors
				void init();
				void create(iterator beg, iterator end);
				void create(size_type n, const T& val);
				
				void grow();
				void append(const T& val);
				
				void destroy();
				
				
				
		};
	}
	
}


#endif
