/***********************************************************************
 * Header:
 *    TEST HASH
 * Summary:
 *    Unit tests for hash
 * Author
 *    Br. Helfrich
 ************************************************************************/

#pragma once

#ifdef DEBUG

#include "hash.h"
#include "unitTest.h"

#include <cassert>
#include <memory>
#include <functional>
#include <vector>

using std::cout;
using std::endl;


class TestHash : public UnitTest
{

public:
   void run()
   {
      reset();

      // Construct
      test_construct_default();
      test_constructIterator_standard();
      test_constructCopy_empty();
      test_constructCopy_standard();

      // Assign
      test_assign_emptyEmpty();
      test_assign_emptyStandard();
      test_assign_standardEmpty();
      test_assignMove_emptyEmpty();
      test_assignMove_emptyStandard();
      test_assignMove_standardEmpty();
      test_swapMember_emptyEmpty();
      test_swapMember_standardEmpty();
      test_swapMember_standardOther();
      test_swapNonMember_emptyEmpty();
      test_swapNonMember_standardEmpty();
      test_swapNonMember_standardOther();


      // Iterator
      test_iterator_begin_empty();
      test_iterator_begin_standard();
      test_iterator_end_empty();
      test_iterator_end_standard();
      test_iterator_increment_empty();
      test_iterator_increment_nextBucket();
      test_iterator_increment_toEnd();
      test_iterator_dereference();

      // Access
      test_bucket_empty0();
      test_bucket_empty7();
      test_bucket_empty58();
      test_find_empty();
      test_find_standardFront();
      test_find_standardBack();
      test_find_standardMissingEmptyList();
      test_find_standardMissingFilledList();

      // Insert
      test_insert_emptyTrivial();
      test_insert_emptyValue();
      test_insert_standardNew();
      test_insert_standardReplace();
      test_insert_standardDuplicate();

      // Remove
      test_clear_empty();
      test_clear_standard();
      test_erase_empty();
      test_erase_standardMissing();
      test_erase_standardAlone();
      test_erase_standardLast();

      // Status
      test_size_empty();
      test_size_standard();
      test_empty_empty();
      test_empty_standard();
      test_bucketSize_empty();
      test_bucketSize_standardEmpty();
      test_bucketSize_standardOne();

      report("Hash");
   }

   /***************************************
    * CONSTRUCTOR
    ***************************************/
   
   // create an unordered set
   void test_construct_default()
   {  // setup
      std::allocator<custom::unordered_set> alloc;
      custom::unordered_set us;
      us.numElements = 99;
      // exercise
      alloc.construct(&us);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(us);
   }  // teardown

   // create an unordered set from a vector iterator
   void test_constructIterator_standard()
   {  // setup
      std::vector<int> v{55, 67, 31};
      std::allocator<custom::unordered_set> alloc;
      custom::unordered_set us;
      us.numElements = 99;
      // exercise
      alloc.construct(&us, v.begin(), v.end());
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(us);
   }  // teardown

   // copy an empty unordered set
   void test_constructCopy_empty()
   {  // setup
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usSrc;
      custom::unordered_set usDes;
      std::allocator<custom::unordered_set> alloc;
      usDes.numElements = 99;
      // exercise
      alloc.construct(&usDes, usSrc);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(usSrc);
      assertEmptyFixture(usDes);
   }  // teardown

   // copy a standard set
   void test_constructCopy_standard()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usSrc;
      setupStandardFixture(usSrc);
      // exercise
      custom::unordered_set usDes(usSrc);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(usSrc);
      assertStandardFixture(usDes);
   }  // teardown

   /***************************************
    * ASSIGN
    ***************************************/
   
   // assign an empty set to an empty set
   void test_assign_emptyEmpty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usSrc;
      custom::unordered_set usDes;
      // exercise
      usDes = usSrc;
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(usSrc);
      assertEmptyFixture(usDes);
   }  // teardown
   
   // assign an empty set to a standard set
   void test_assign_emptyStandard()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usSrc;
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usDes;
      setupStandardFixture(usDes);
      // exercise
      usDes = usSrc;
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(usSrc);
      assertEmptyFixture(usDes);
   }  // teardown
   
   // assign an standard set to an empty set
   void test_assign_standardEmpty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usSrc;
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usDes;
      setupStandardFixture(usSrc);
      // exercise
      usDes = usSrc;
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(usSrc);
      assertStandardFixture(usDes);
      // teardown
   }
   
   // move-assign an empty set to an empty set
   void test_assignMove_emptyEmpty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usSrc;
      custom::unordered_set usDes;
      // exercise
      usDes = std::move(usSrc);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(usSrc);
      assertEmptyFixture(usDes);
   }  // teardown
   
   // move-assign an empty set to a standard set
   void test_assignMove_emptyStandard()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usSrc;
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usDes;
      setupStandardFixture(usDes);
      // exercise
      usDes = std::move(usSrc);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(usSrc);
      assertEmptyFixture(usDes);
   }  // teardown
   
   // move-assign an standard set to an empty set
   void test_assignMove_standardEmpty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    | = usSrc
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usSrc;
      setupStandardFixture(usSrc);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    | = usDes
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set usDes;
      // exercise
      usDes = std::move(usSrc);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    | = usSrc
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(usSrc);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    | = usDes
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(usDes);
      // teardown
   }
   
   // swap empty hashes use member swap
   void test_swapMember_emptyEmpty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us1;
      custom::unordered_set us2;
      // exercise
      us1.swap(us2);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(us1);
      assertEmptyFixture(us2);
   }  // teardown
   
   // swap standard hash with empty hash using memger functions
   void test_swapMember_standardEmpty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us1;
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us2;
      setupStandardFixture(us1);
      // exercise
      us1.swap(us2);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(us1);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(us2);
   }  // teardown
   
   // swap standard hash with single-element hash
   void test_swapMember_standardOther()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us1;
      setupStandardFixture(us1);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    | 20 |    |    | 23 | 24 |    |    | 27 | 28 |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us2;
      us2.buckets[0] = 20;
      us2.buckets[3] = 23;
      us2.buckets[4] = 24;
      us2.buckets[7] = 27;
      us2.buckets[8] = 28;
      us2.numElements = 5;
      // exercise
      us1.swap(us2);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    | 20 |    |    | 23 | 24 |    |    | 27 | 28 |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(us1.numElements == 5);
      assertUnit(us1.buckets[0] == 20);
      assertUnit(us1.buckets[1] == HASH_EMPTY_VALUE);
      assertUnit(us1.buckets[2] == HASH_EMPTY_VALUE);
      assertUnit(us1.buckets[3] == 23); // 23
      assertUnit(us1.buckets[4] == 24); // 24
      assertUnit(us1.buckets[5] == HASH_EMPTY_VALUE);
      assertUnit(us1.buckets[6] == HASH_EMPTY_VALUE);
      assertUnit(us1.buckets[7] == 27); // 27
      assertUnit(us1.buckets[8] == 28); // 28
      assertUnit(us1.buckets[9] == HASH_EMPTY_VALUE);

      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(us2);
   }  // teardown
   
   // swap empty hashs using non-member swap
   void test_swapNonMember_emptyEmpty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us1;
      custom::unordered_set us2;
      // exercise
      swap(us1, us2);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(us1);
      assertEmptyFixture(us2);
   }  // teardown
   
   // swap standard hash with empty hash using non-member functions
   void test_swapNonMember_standardEmpty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us1;
      setupStandardFixture(us1);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us2;
      // exercise
      swap(us1, us2);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(us1);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(us2);
   }  // teardown
   
   // swap standard hash with single-element hash
   void test_swapNonMember_standardOther()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us1;
      setupStandardFixture(us1);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    | 20 |    |    | 23 | 24 |    |    | 27 | 28 |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us2;
      us2.buckets[0] = 20;
      us2.buckets[3] = 23;
      us2.buckets[4] = 24;
      us2.buckets[7] = 27;
      us2.buckets[8] = 28;
      us2.numElements = 5;
      // exercise
      swap(us1, us2);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    | 20 |    |    | 23 | 24 |    |    | 27 | 28 |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(us1.numElements == 5);
      assertUnit(us1.buckets[0] == 20);
      assertUnit(us1.buckets[1] == HASH_EMPTY_VALUE);
      assertUnit(us1.buckets[2] == HASH_EMPTY_VALUE);
      assertUnit(us1.buckets[3] == 23); // 23
      assertUnit(us1.buckets[4] == 24); // 24
      assertUnit(us1.buckets[5] == HASH_EMPTY_VALUE);
      assertUnit(us1.buckets[6] == HASH_EMPTY_VALUE);
      assertUnit(us1.buckets[7] == 27); // 27
      assertUnit(us1.buckets[8] == 28); // 28
      assertUnit(us1.buckets[9] == HASH_EMPTY_VALUE);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(us2);
   } // teardown
   
   /***************************************
    * ITERATOR
    ***************************************/
   
   // beginning of empty hash
   void test_iterator_begin_empty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      custom::unordered_set::iterator it;
      // exercise
      it = us.begin();
      // verify
      //                                                          it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 10);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertEmptyFixture(us);
   }  // teardown
   
   // beginning of standard hash
   void test_iterator_begin_standard()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      custom::unordered_set::iterator it;
      // exercise
      it = us.begin();
      // verify
      //           it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 1);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertStandardFixture(us);
      // teardown
   }

   // end of empty hash
   void test_iterator_end_empty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      custom::unordered_set::iterator it;
      // exercise
      it = us.end();
      // verify
      //                                                         it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 10);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertEmptyFixture(us);
   }  // teardown
   
   // end of standard hash
   void test_iterator_end_standard()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      custom::unordered_set::iterator it;
      // exercise
      it = us.end();
      // verify
      //                                                         it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 10);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      // teardown
   }
   
   // increment of empty hash
   void test_iterator_increment_empty()
   {  // setup
      //                                                         it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      custom::unordered_set::iterator it = us.end();
      // exercise
      ++it;
      // verify
      //                                                         it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 10);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertEmptyFixture(us);
   }  // teardown  
   
   // increment of standard hash where we need to go to the next bucket
   void test_iterator_increment_nextBucket()
   {  // setup
      //           it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets + 1;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      ++it;
      // verify
      //                               it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 5);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertStandardFixture(us);
      // teardown
   }
   
   // increment of standard hash where we were at the last element
   void test_iterator_increment_toEnd()
   {  // setup
      //                                         it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets + 7;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      ++it;
      // verify
      //                                                         it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 10);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertStandardFixture(us);
   }
   
   // dereference the iterator
   void test_iterator_dereference()
   {  // setup
      //                               it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets + 5;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      int s = *it;
      // verify
      //                               it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(s == 55);
      assertUnit(it.pBucket == us.buckets + 5);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertStandardFixture(us);
      // teardown
   }
   

   /***************************************
    * ACCESS
    ***************************************/

    // find the bucket that the value 0 will go in the empty hash
    void test_bucket_empty0()
    {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
       custom::unordered_set us;
       size_t iBucket = 99;
       // exercise
       iBucket = us.bucket(0);  // 0 % 10 == 0
       // verify
       assertUnit(iBucket == 0);
       //    +----+----+----+----+----+----+----+----+----+----+
       //    |    |    |    |    |    |    |    |    |    |    |
       //    +----+----+----+----+----+----+----+----+----+----+
       //      0    1    2    3    4    5    6    7    8    9
       assertEmptyFixture(us);
    }  // teardown

    // find the bucket that the value 7 will go in the empty hash
    void test_bucket_empty7()
    {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
       custom::unordered_set us;
       size_t iBucket = 99;
       // exercise
       iBucket = us.bucket(7);    // 7 % 10 == 7
       // verify
       assertUnit(iBucket == 7);
       //    +----+----+----+----+----+----+----+----+----+----+
       //    |    |    |    |    |    |    |    |    |    |    |
       //    +----+----+----+----+----+----+----+----+----+----+
       //      0    1    2    3    4    5    6    7    8    9
       assertEmptyFixture(us);
    }  // teardown

    // find the bucket that the value 58 will go in the empty hash
    void test_bucket_empty58()
    {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
       custom::unordered_set us;
       size_t iBucket = 99;
       // exercise
       iBucket = us.bucket(58);  // 58 % 10 == 8
       // verify
       assertUnit(iBucket == 8);
       //    +----+----+----+----+----+----+----+----+----+----+
       //    |    |    |    |    |    |    |    |    |    |    |
       //    +----+----+----+----+----+----+----+----+----+----+
       //      0    1    2    3    4    5    6    7    8    9
       assertEmptyFixture(us);
    }  // teardown

    // find something from an empty hash
   void test_find_empty()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets;
      // exercise
      it = us.find(99);
      // verify
      //                                                        it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 10);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertEmptyFixture(us);
   }  // teardown

   // find something at the front of the list of a hash
   void test_find_standardFront()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets;
      setupStandardFixture(us);
      // exercise
      it = us.find(31);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 1);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertStandardFixture(us);
      // teardown
   }

   // find something at the back of the list of a hash
   void test_find_standardBack()
   {  // setup
      //     it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      custom::unordered_set::iterator it = us.begin();
      it.pBucket = us.buckets;
      setupStandardFixture(us);
      // exercise
      it = us.find(67);
      // verify
      //                                         it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 7);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertStandardFixture(us);
   }

   // find something missing from an empty list
   void test_find_standardMissingEmptyList()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      custom::unordered_set::iterator it = us.begin();
      it.pBucket = us.buckets;
      // exercise
      it = us.find(50);
      // verify
      //                                                        it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 10);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertEmptyFixture(us);
   }

   // find something missing from a filled list
   void test_find_standardMissingFilledList()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets;
      setupStandardFixture(us);
      // exercise
      it = us.find(69);
      // verify
      //                                                        it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(it.pBucket == us.buckets + 10);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertStandardFixture(us);
   }

   /***************************************
    * INSERT
    ***************************************/
   
   // test that we can insert 0 into an empty hash
   void test_insert_emptyTrivial()
   {  // setup
      //                          it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets + 4;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      it = us.insert(0);  // 0 % 10 == 0
      // verify
      //     itr
      //    +----+----+----+----+----+----+----+----+----+----+
      //    | 0  |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(us.numElements == 1);
      assertUnit(us.buckets[0] == 0);
      assertUnit(us.buckets[1] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[2] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[3] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[4] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[5] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[6] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[7] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[8] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[9] == HASH_EMPTY_VALUE);
      assertUnit(it.pBucket    == us.buckets + 0);
      assertUnit(it.pBucketEnd == us.buckets + 10);
   }  // teardown
   
   // test that we can insert 58 into an empty hash
   void test_insert_emptyValue()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      it = us.insert(58);  // 58 % 10 == 8
      // verify
      //                                              it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    | 58 |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(us.numElements == 1);
      assertUnit(us.buckets[0] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[1] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[2] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[3] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[4] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[5] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[6] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[7] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[8] == 58);
      assertUnit(us.buckets[9] == HASH_EMPTY_VALUE);
      assertUnit(it.pBucket    == us.buckets + 8);
      assertUnit(it.pBucketEnd == us.buckets + 10);
   }  // teardown
   
   // test that we can insert 3 into the standard hash
   void test_insert_standardNew()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      it = us.insert(3);  // 3 % 10 == 3
      // verify
      //                     it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |  3 |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(us.numElements == 4);
      assertUnit(us.buckets[0] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[1] == 31);
      assertUnit(us.buckets[2] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[3] == 3);
      assertUnit(us.buckets[4] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[5] == 55);
      assertUnit(us.buckets[6] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[7] == 67);
      assertUnit(us.buckets[8] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[9] == HASH_EMPTY_VALUE);
      assertUnit(it.pBucket    == us.buckets + 3);
      assertUnit(it.pBucketEnd == us.buckets + 10);
   }  // teardown
   
   // test that we can insert 7 into the standard hash
   void test_insert_standardReplace()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      it = us.insert(77);  // 77 % 10 == 7
      // verify
      //                                         it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 77 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(us.numElements == 3);
      assertUnit(us.buckets[0] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[1] == 31); 
      assertUnit(us.buckets[2] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[3] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[4] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[5] == 55);
      assertUnit(us.buckets[6] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[7] == 77); 
      assertUnit(us.buckets[8] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[9] == HASH_EMPTY_VALUE); 
      assertUnit(it.pBucket    == us.buckets + 7);
      assertUnit(it.pBucketEnd == us.buckets + 10);
   }  // teardown
   
   // test that we can insert 67 into the empty hash
   void test_insert_standardDuplicate()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      it = us.insert(67);  // 67 % 10 == 7
      // verify
      //                                         it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(us);
      assertUnit(it.pBucket    == us.buckets + 7);
      assertUnit(it.pBucketEnd == us.buckets + 10);
   }  // teardown

   /***************************************
    * REMOVE
    ***************************************/
   
   // clear an empty hash
   void test_clear_empty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      // exercise
      us.clear();
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(us);
   }  // teardown
   
   // clear all the elements from the standard fixture
   void test_clear_standard()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      // exercise
      us.clear();
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(us);
      // teardown
   }
   
   // erase an empty hash
   void test_erase_empty()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      it = us.erase(99);
      // verify
      //                                                        it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(us);
      assertUnit(it.pBucket    == us.buckets + 10);
      assertUnit(it.pBucketEnd == us.buckets + 10);
   }  // teardown
   
   // clear all the elements from the standard fixture
   void test_erase_standardMissing()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      it = us.erase(99);
      // verify
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(us);
      assertUnit(it.pBucket == us.buckets + 10);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      // teardown
   }
   
   // clear one element from the standard fixture
   void test_erase_standardAlone()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      it = us.erase(55);
      // verify
      //                                         it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    |    |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(us.numElements == 2);
      assertUnit(us.buckets[0] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[1] == 31);
      assertUnit(us.buckets[2] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[3] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[4] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[5] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[6] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[7] == 67);
      assertUnit(us.buckets[8] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[9] == HASH_EMPTY_VALUE);
      assertUnit(it.pBucketEnd == us.buckets + 10);
      assertUnit(it.pBucket == us.buckets + 7);
      assertUnit(it.pBucketEnd == us.buckets + 10);
   }  // teardown
   
   // erase the last element on the entire hash
   void test_erase_standardLast()
   {  // setup
      //      it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      custom::unordered_set::iterator it;
      it.pBucket = us.buckets;
      it.pBucketEnd = us.buckets + 10;
      // exercise
      it = us.erase(67);
      // verify
      //                                                        it
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertUnit(us.numElements == 2);
      assertUnit(us.buckets[0] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[1] == 31);
      assertUnit(us.buckets[2] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[3] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[4] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[5] == 55);
      assertUnit(us.buckets[6] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[7] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[8] == HASH_EMPTY_VALUE);
      assertUnit(us.buckets[9] == HASH_EMPTY_VALUE);
      assertUnit(it.pBucket == us.buckets + 10);
      assertUnit(it.pBucketEnd == us.buckets + 10);
   }  // teardown

   
   /***************************************
    * SIZE EMPTY 
    ***************************************/

    // size of an empty hash
   void test_size_empty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      // exercise
      size_t size = us.size();
      // verify
      assertUnit(0 == size);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(us);
   }  // teardown

   // size of the standard hash
   void test_size_standard()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      // exercise
      size_t size = us.size();
      // verify
      assertUnit(3 == size);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(us);
      // teardown
   }

   // empty hash empty?
   void test_empty_empty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      // exercise
      bool empty = us.empty();
      // verify
      assertUnit(true == empty);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(us);
   }  // teardown

   // standard hash empty?
   void test_empty_standard()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      // exercise
      bool empty = us.empty();
      // verify
      assertUnit(false == empty);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(us);
      // teardown
   }

   // verify the bucket size of an empty hash
   void test_bucketSize_empty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      size_t i = 0;
      size_t num = 0;
      // exercise
      num = us.bucket_size(i);
      // verify
      assertUnit(num == 0);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertEmptyFixture(us);
   }  // teardown

   // verify the bucket size of standard hash, empty bucket
   void test_bucketSize_standardEmpty()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      size_t i = 3;
      size_t num = 0;
      // exercise
      num = us.bucket_size(i);
      // verify
      assertUnit(num == 0);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(us);
      // teardown
   }

   // verify the bucket size of standard hash, bucket has one element
   void test_bucketSize_standardOne()
   {  // setup
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      custom::unordered_set us;
      setupStandardFixture(us);
      size_t i = 1;
      size_t num = 0;
      // exercise
      num = us.bucket_size(i);
      // verify
      assertUnit(num == 1);
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    | 31 |    |    |    | 55 |    | 67 |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      //      0    1    2    3    4    5    6    7    8    9
      assertStandardFixture(us);
      // teardown
   }



   /*************************************************************
    * SETUP STANDARD FIXTURE
    *    +----+----+----+----+----+----+----+----+----+----+
    *    |    | 31 |    |    |    | 55 |    | 67 |    |    |
    *    +----+----+----+----+----+----+----+----+----+----+
    *      0    1    2    3    4    5    6    7    8    9
    *************************************************************/
   void setupStandardFixture(custom::unordered_set & us)
   {
      // clear out whatever the default constructor created
      for (int i = 0; i < 10; i++)
         us.buckets[i] = HASH_EMPTY_VALUE;

      // set the values
      us.buckets[1] = 31;
      us.buckets[7] = 67;
      us.buckets[5] = 55;

      // set the number of elements
      us.numElements = 3;
   }



   /*************************************************************
    * VERIFY STANDARD FIXTURE
    *    +----+----+----+----+----+----+----+----+----+----+
    *    |    | 31 |    |    |    | 55 |    | 67 |    |    |
    *    +----+----+----+----+----+----+----+----+----+----+
    *      0    1    2    3    4    5    6    7    8    9
    *************************************************************/
   void assertStandardFixtureParameters(custom::unordered_set& us, int line, const char * function)
   {
      assertIndirect(us.numElements == 3);

      assertIndirect(us.buckets[0] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[1] == 31);
      assertIndirect(us.buckets[2] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[3] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[4] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[5] == 55);
      assertIndirect(us.buckets[6] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[7] == 67);
      assertIndirect(us.buckets[8] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[9] == HASH_EMPTY_VALUE); 

   }

   /*************************************************************
    * VERIFY EMPTY FIXTURE
    * 
    *    +----+----+----+----+----+----+----+----+----+----+
    *    |    |    |    |    |    |    |    |    |    |    |
    *    +----+----+----+----+----+----+----+----+----+----+
    *      0    1    2    3    4    5    6    7    8    9
    *************************************************************/
   void assertEmptyFixtureParameters(custom::unordered_set& us, int line, const char* function)
   {
      assertIndirect(us.numElements == 0);

      assertIndirect(us.buckets[0] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[1] == HASH_EMPTY_VALUE); 
      assertIndirect(us.buckets[2] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[3] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[4] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[5] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[6] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[7] == HASH_EMPTY_VALUE); 
      assertIndirect(us.buckets[8] == HASH_EMPTY_VALUE);
      assertIndirect(us.buckets[9] == HASH_EMPTY_VALUE); 
   }

};

#endif // DEBUG
