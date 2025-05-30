/*
 * @lc app=leetcode id=1154 lang=typescript
 *
 * [1154] Day of the Year
 */

// @lc code=start
function dayOfYear(date: string): number {
    const [year, month, day] = date.split('-').map(Number)
    const isLeapYear = (year % 4 === 0 && year % 100 !== 0) || year % 400 === 0
    const daysInMonth = [31, isLeapYear ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    return daysInMonth.slice(0, month - 1).reduce((acc, curr) => acc + curr, day)
}
// @lc code=end

