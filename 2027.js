/**
 * @param {string} s
 * @return {number}
 */
var minimumMoves = function(s) {
    let i = 0;
    let moves = 0;
    
    while (i < s.length) {
        if (s[i] === 'X') {
            moves++;
            i += 3;
        } else {
            i++;
        }
    }
    
    return moves;
}; 