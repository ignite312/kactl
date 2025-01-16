/**
 * Author: Emon
 * Date: 
 * License:
 * Source: 
 * Description: ...
 * Time: O(\log N)
 */
#pragma once

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_pair_set tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set os;
// Example using ordered_set
os.insert(5);os.insert(1);os.insert(10);os.insert(3);
cout << "2nd smallest element: " << *os.find_by_order(2) << endl;  // Output: 5
cout << "Elements less than 6: " << os.order_of_key(6) << endl;  // Output: 3
// Example using ordered_pair_set
ordered_pair_set ops;
ops.insert({1, 100});ops.insert({2, 200});ops.insert({1, 150});ops.insert({3, 250});
cout << "1st smallest pair: (" << ops.find_by_order(0)->first << ", " << ops.find_by_order(0)->second << ")" << endl;  // Output: (1, 100)
cout << "Pairs less than (2, 150): " << ops.order_of_key({2, 150}) << endl;  // Output: 2
