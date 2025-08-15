import sys

def to_codes(s):
    return [ord(c)-65 for c in s]

w = int(sys.stdin.readline().strip())
words = sys.stdin.readline().strip().split()
words = [s.upper() for s in words]
L = 6
N = len(words)
codes = [to_codes(s) for s in words]
masks = []
for c in codes:
    m = 0
    for x in set(c):
        m |= 1 << x
    masks.append(m)
all_idx = list(range(N))
presentMask = 0
absentMask = 0
fixed = [-1]*L
banned = [0]*L
last_guess = None
last_codes = None
cand_idx = all_idx

def filter_candidates():
    res = []
    pm = presentMask
    am = absentMask
    fx = fixed
    bd = banned
    for i in cand_idx:
        if (masks[i] & pm) != pm:
            continue
        if (masks[i] & am) != 0:
            continue
        ci = codes[i]
        ok = True
        for p in range(L):
            v = ci[p]
            if fx[p] != -1 and v != fx[p]:
                ok = False
                break
            if bd[p] & (1 << v):
                ok = False
                break
        if ok:
            res.append(i)
    return res

def choose_guess(cands):
    if len(cands) <= 1:
        return cands[0] if cands else 0
    freq_any = [0]*26
    freq_pos = [[0]*26 for _ in range(L)]
    for i in cands:
        ci = codes[i]
        sm = 0
        for p in range(L):
            v = ci[p]
            freq_pos[p][v] += 1
            sm |= 1 << v
        bm = sm
        while bm:
            b = bm & -bm
            j = (b.bit_length()-1)
            freq_any[j] += 1
            bm ^= b
    # prefer picking inside current candidates to avoid loops
    pool = cands if len(cands) < 8000 else all_idx
    best = None
    best_score = -1
    for i in pool:
        ci = codes[i]
        used = 0
        sum_any = 0
        uniq = 0
        sum_pos = 0
        penalty = 0
        for p in range(L):
            v = ci[p]
            sum_pos += freq_pos[p][v]
            if not (used & (1 << v)):
                used |= 1 << v
                uniq += 1
                sum_any += freq_any[v]
            if (absentMask & (1 << v)):
                penalty += 100
            if fixed[p] == -1 and (banned[p] & (1 << v)):
                penalty += 10
        sc = 3*sum_pos + 1*sum_any + 6*uniq - penalty
        if sc > best_score:
            best_score = sc
            best = i
    return best

while True:
    line = sys.stdin.readline()
    if not line:
        break
    parts = line.strip().split()
    if len(parts) != L:
        print(words[0], flush=True)
        last_guess = words[0]
        last_codes = codes[0]
        cand_idx = all_idx
        continue
    states = [int(x) for x in parts]
    if last_guess is not None:
        pos_present = 0
        pos_absent = 0
        occ = [[] for _ in range(26)]
        for p in range(L):
            s = states[p]
            v = last_codes[p]
            if s == 3:
                fixed[p] = v
                pos_present |= 1 << v
            elif s == 2:
                banned[p] |= 1 << v
                pos_present |= 1 << v
            elif s == 1:
                pos_absent |= 1 << v
            occ[v].append(s)
        pos_absent &= ~pos_present
        presentMask |= pos_present
        absentMask = (absentMask | pos_absent) & ~pos_present
        # If all occurrences of a letter in guess are 1 (absent), keep it in absentMask unless it was set as present elsewhere
    cand_idx = filter_candidates()
    if not cand_idx:
        cand_idx = all_idx
    gi = choose_guess(cand_idx)
    last_guess = words[gi]
    last_codes = codes[gi]
    print(last_guess, flush=True)
