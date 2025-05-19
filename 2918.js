/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var minSum = function(nums1, nums2) {
    let sum1 = 0, sum2 = 0, zero1 = 0, zero2 = 0;
    
    for (let x of nums1) {
        if (x === 0) zero1++;
        else sum1 += x;
    }
    
    for (let x of nums2) {
        if (x === 0) zero2++;
        else sum2 += x;
    }
    
    const min1 = sum1 + zero1;
    const min2 = sum2 + zero2;
    
    if (zero1 === 0 && min1 < min2) return -1;
    if (zero2 === 0 && min2 < min1) return -1;
    
    return Math.max(min1, min2);
}; 