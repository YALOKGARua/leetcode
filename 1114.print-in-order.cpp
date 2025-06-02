/*
 * @lc app=leetcode id=1114 lang=cpp
 *
 * [1114] Print in Order
 *
 * https://leetcode.com/problems/print-in-order/description/
 *
 * concurrency
 * Easy (71.48%)
 * Likes:    1522
 * Dislikes: 214
 * Total Accepted:    195.3K
 * Total Submissions: 273.2K
 * Testcase Example:  '[1,2,3]'
 *
 * Suppose we have a class:
 * 
 * 
 * public class Foo {
 * ⁠ public void first() { print("first"); }
 * ⁠ public void second() { print("second"); }
 * ⁠ public void third() { print("third"); }
 * }
 * 
 * 
 * The same instance of Foo will be passed to three different threads. Thread A
 * will call first(), thread B will call second(), and thread C will call
 * third(). Design a mechanism and modify the program to ensure that second()
 * is executed after first(), and third() is executed after second().
 * 
 * Note:
 * 
 * We do not know how the threads will be scheduled in the operating system,
 * even though the numbers in the input seem to imply the ordering. The input
 * format you see is mainly to ensure our tests' comprehensiveness.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3]
 * Output: "firstsecondthird"
 * Explanation: There are three threads being fired asynchronously. The input
 * [1,2,3] means thread A calls first(), thread B calls second(), and thread C
 * calls third(). "firstsecondthird" is the correct output.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,3,2]
 * Output: "firstsecondthird"
 * Explanation: The input [1,3,2] means thread A calls first(), thread B calls
 * third(), and thread C calls second(). "firstsecondthird" is the correct
 * output.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * nums is a permutation of [1, 2, 3].
 * 
 * 
 */

// @lc code=start
#include <mutex>
#include <condition_variable>
#include <functional>
using namespace std;

class Foo {
private:
    std::mutex mtx;
    std::condition_variable cv1, cv2;
    bool firstDone = false;
    bool secondDone = false;

public:
    Foo() {
    }

    void first(function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        
        std::lock_guard<std::mutex> lock(mtx);
        firstDone = true;
        cv1.notify_all();
    }

    void second(function<void()> printSecond) {
        std::unique_lock<std::mutex> lock(mtx);
        cv1.wait(lock, [this]() { return firstDone; });
        
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        
        secondDone = true;
        cv2.notify_all();
    }

    void third(function<void()> printThird) {
        std::unique_lock<std::mutex> lock(mtx);
        cv2.wait(lock, [this]() { return secondDone; });
        
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
// @lc code=end

