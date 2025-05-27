int sumOfEncryptedInt(int* a, int n) {
    int s = 0;
    for(int i = 0; i < n; ++i) {
        int x = a[i], d = 0, l = 0, t = x;
        while(t) d = d > t % 10 ? d : t % 10, t /= 10, ++l;
        int y = 0;
        for(int v = 0; v < l; ++v) y = y * 10 + d;
        s += y;
    }
    return s;
} 