/***********************************************************************
 * Header:
 *    HASH
 * Summary:
 *    Our custom implementation of std::unordered_Set
 *        ____     _______        __
 *      .' __ '.  |  _____|   _  / /
 *      | (__) |  | |____    (_)/ /
 *      .`____'.  '_.____''.   / / _
 *     | (____) | | \____) |  / / (_)
 *     `.______.'  \______.' /_/
 * 
 *    This will contain the class definition of:
 *        unordered_set           : A class that represents a hash
 *        unordered_set::iterator : An interator through hash
 * Author
 *    <Your name here>
 ************************************************************************/

#pragma once

#include <cmath>            // for std::abs
#include <cassert>          // for assert()
#include <initializer_list> // for std::initializer_list
#include <utility>          // for std::move()


#include <iostream>
   
#define HASH_EMPTY_VALUE -1

class TestHash;             // forward declaration for Hash unit tests

namespace custom
{
/************************************************
 * UNORDERED SET
 * A set implemented as a hash
 ************************************************/
class unordered_set
{
   friend class ::TestHash;   // give unit tests access to the privates
public:
   //
   // Construct
   //
   unordered_set()
   {
      numElements = 0;
      for (int i = 0; i < 10; i++)
      {
         this->buckets[i] = -1;
      }
   }
   unordered_set(unordered_set&  rhs) 
   {
      numElements = rhs.numElements;
      for (int i = 0; i < 10; i++)
      {
         this->buckets[i] = rhs.buckets[i];
      }
   }
   unordered_set(unordered_set&& rhs) noexcept
   {
      for (int i = 0; i < 10; i++)
      {
         this->buckets[i] = rhs.buckets[i];
      }
   }
   template <class Iterator>
   unordered_set(Iterator first, Iterator last)
   {
      for (auto it = first; it != last; it++)
      {
         insert(*it);
      }

   }

   //
   // Assign
   //
   unordered_set& operator=(unordered_set& rhs);
   unordered_set& operator=(unordered_set&& rhs) noexcept;
   unordered_set& operator=(const std::initializer_list<int>& il);
   void swap(unordered_set& rhs)
   {
   }

   // 
   // Iterator
   //
   class iterator;
   iterator begin();
   iterator end();

   // Access
   size_t bucket(const int & t)
   {
      return 99;
   }
   iterator find(const int& t);

   //   
   // Insert
   //
   iterator insert(const int& t);
   void insert(const std::initializer_list<int> & il);


   // 
   // Remove
   //
   void clear() noexcept
   {
      for (int i = 0; i < 10; i++)
      {
         buckets[i] = HASH_EMPTY_VALUE;
      }

   }
   iterator erase(const int& t);

   //
   // Status
   //
   size_t size() const 
   { 
      return 99;      
   }
   bool empty() const 
   { 
      return false; 
   }
   size_t bucket_count() const 
   { 
      return 99;   
   }
   size_t bucket_size(size_t i) const
   {
      return 99;
   }

private:
 
   int buckets[10];     // exactly 10 buckets of pointers. buckets[iBucket] == HASH_EMPTY_VALUE means it is not filled
   int numElements;     // number of elements in the Hash
};


/************************************************
 * UNORDERED SET ITERATOR
 * Iterator for an unordered set
 ************************************************/
class unordered_set::iterator
{
   friend class ::TestHash;   // give unit tests access to the privates
public:
   // 
   // Construct
   iterator()  
   {  
   }
   iterator(int * pBucket, int * pBucketEnd)
   {
      this->pBucket = pBucket;
      this->pBucketEnd = pBucketEnd;
   }
   iterator(const iterator& rhs) 
   { 
      this->pBucket = rhs.pBucket;
      this->pBucketEnd = rhs.pBucketEnd;
   }

   //
   // Assign
   //
   iterator& operator = (const iterator& rhs)
   {
      this->pBucket = rhs.pBucket;
      this->pBucketEnd = rhs.pBucketEnd;
      return *this;
   }

   //
   // Compare
   //
   bool operator != (const iterator& rhs) const 
   { 
      return true;
   }
   bool operator == (const iterator& rhs) const 
   { 
      return true;
   }

   // 
   // Access
   //
   int& operator * ()
   {
      return *(new int(99));
   }

   //
   // Arithmetic
   //
   iterator& operator ++ ();
   iterator operator ++ (int postfix)
   {
      return *this;
   }

private:
   int* pBucket;
   int* pBucketEnd;
};


/*****************************************
 * UNORDERED SET ::ASSIGN
 ****************************************/
inline unordered_set& unordered_set::operator=(unordered_set& rhs)
{
   return *this;
}
inline unordered_set& unordered_set::operator=(unordered_set&& rhs) noexcept
{
   return *this;
}
inline unordered_set& unordered_set::operator=(const std::initializer_list<int>& il)
{
   return *this;
}


/*****************************************
 * UNORDERED SET :: BEGIN / END
 * Points to the first valid element in the has
 ****************************************/
inline typename unordered_set::iterator  unordered_set::begin()
{
   // find the first non-empty bucket
   for (int i = 0; i < 10; i++)
   {
      if (buckets[i] > 0)
      {
         return unordered_set::iterator(buckets + i, buckets + 10);
      }

   }
   
   return unordered_set::iterator(buckets + 10, buckets + 10);

   
}
inline typename unordered_set::iterator  unordered_set::end()
{
   return unordered_set::iterator(buckets+10, buckets+10);
}


/*****************************************
 * UNORDERED SET :: ERASE
 * Remove one element from the unordered set
 ****************************************/
inline typename unordered_set::iterator unordered_set::erase(const int& t)
{
   return unordered_set::iterator();
}


/*****************************************
 * UNORDERED SET :: INSERT
 * Insert one element into the hash
 ****************************************/
inline custom::unordered_set::iterator unordered_set::insert(const int& t)
{
   int buckettemp = 0;
   if (t == 0)
   {
      this->buckets[0] = t;
      numElements++;
      return unordered_set::iterator(buckets + 0, buckets + 10);
   }

   buckettemp =  t % 10;


   if ((this->buckets[buckettemp] != t) && (this->buckets[buckettemp] == HASH_EMPTY_VALUE) )
   {
      this->buckets[buckettemp] = t;
      numElements++;
   }
   else
   {
      this->buckets[buckettemp] = t;
   }






   return unordered_set::iterator(buckets + buckettemp, buckets + 10);
}

inline void unordered_set::insert(const std::initializer_list<int> & il)
{


}

/*****************************************
 * UNORDERED SET :: FIND
 * Find an element in an unordered set
 ****************************************/
inline typename unordered_set::iterator unordered_set::find(const int& t)
{
   return unordered_set::iterator();
}

/*****************************************
 * UNORDERED SET :: ITERATOR :: INCREMENT
 * Advance by one element in an unordered set
 ****************************************/
inline typename unordered_set::iterator & unordered_set::iterator::operator ++ ()
{
   return *this;
}

/*****************************************
 * SWAP
 * Stand-alone unordered set swap
 ****************************************/
inline void swap(unordered_set& lhs, unordered_set& rhs)
{
}

}
