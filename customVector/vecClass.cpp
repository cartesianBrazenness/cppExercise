/**************************************************************************/
/*	Author		: Pavan Acharya C
	file		: Source file for vecClass
	IDE/ver		: Dev-C++ 5.11, C++ 11
	comments	: This file contains the class member defeinitions for the vec Class. 
				  It is encapsulated in the namespace custom_std.
				  reference - Accelerated C++
*/
/**************************************************************************/

//#include <iostream>
#include "vecClass.h"

namespace custom_std{
	
	inline namespace v1{
		
		// Constructor Definition
		template<class T> vec<T>::vec(size_type n, const T& val)
		{
			// call private membet create to handle memory allocation and initialization
			create(n,val);
		}
		
		// copy Constructor
		template<class T> vec<T>::vec(const vec& v)
		{
			// call create with iterators to handle mem and initialize value
			create(v.begin(), v.end());
		}
		
		//Destructor
		template<class T> vec<T>::~vec()
		{
			// call destroy to manage and deallocate mem
			destroy();
		}
		
		// Overloaded Operator, subscript
		template<class T> vec<T>& vec<T>::operator[] (size_type i)
		{
			return (data[i]);
		}
		
		//Overloaded Operator, Assignement
		template<class T> vec<T>& vec<T>::operator= (const vec& v)
		{
			//Check for self assignment
			if(this != &v)
			{
				// Destroy current object
				destroy();
				
				//create new object with received argument
				create(v.begin(), v.end());
			}
		}
		
		// Private init,
		template<class T> void vec<T>::init()
		{
			//Reset class pointers
			data = 0;
			endData = 0;
			limit = 0;
		}
		
		// Create(it,it)
		template<class T> void vec<T>::create(iterator beg, iterator end)
		{
			//get size of memory to be allocated and allocate
			ptrdiff_t size = end - begin;
			data = memManage.allocate(size);
			//Initilize memory with data delimited by iterators
			endData = uninitialized_copy(begin,end,data);
			limit = endData;
		}
		
		//create(size_type,const T&)
		template<class T> void vec<T>::create(size_type n, const T& val)
		{
			data = memManage.allocate(n);
			endData = data + n;
			uninitialized_fill(data,endData,val);
			limit = endData;
		}
		
		//Destroy
		template<class T> void vec<T>::destroy()
		{
			// Check if Data exists
			if(data)
			{
				// first destroy, then deallocate
				iterator iter = endData;
				while(iter != data)
				{
					memManage.destroy(--iter);
				}
				memManage.deallocate(data,limit-data);
			}
			init(); //reset iterators
		}
		
		//grow
		template<class T> void vec<T>::grow()
		{
			//To ensure low overhead, preallocate
			//Everytime grow request arrives, allocate tiwce the number of 
			//current mem allocated
			
			size_type new_size = max(2*(limit-data),ptrdiff_t(1));
			
			// allocate and copy data to new region
			iterator new_data = memManage.allocate(new_size);
			iterator new_endData = uninitialized_copy(data,endData,new_data);
			
			//Destroy old region
			destroy();
			
			//update iterator members
			data = new_data;
			endData = new_endData;
			limit = data + new_size;
		}
		
		//Append
		template<class T> void vec<T>::append(const T& val)
		{
			memManage(endData++,val);
		}
	}
}
