var debounce = function(fn, t) {
    let timeoutId = null;
    
    return function(...args) {
        if (timeoutId) {
            clearTimeout(timeoutId);
        }
        
        timeoutId = setTimeout(() => {
            fn.apply(this, args);
            timeoutId = null;
        }, t);
    }
}; 