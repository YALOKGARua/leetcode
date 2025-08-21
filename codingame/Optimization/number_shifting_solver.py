import sys, time

def idx(x, y, w):
    return y * w + x

class Move:
    __slots__ = ("x","y","d","o")
    def __init__(self, x, y, d, o):
        self.x = x; self.y = y; self.d = d; self.o = o

def gen_moves(g, w, h, out):
    out.clear()
    for y in range(h):
        base = y * w
        for x in range(w):
            v = g[base + x]
            if v <= 0: continue
            tx = x + v
            if tx < w and g[base + tx] != 0:
                out.append(Move(x, y, 'R', '+'))
                out.append(Move(x, y, 'R', '-'))
            tx = x - v
            if tx >= 0 and g[base + tx] != 0:
                out.append(Move(x, y, 'L', '+'))
                out.append(Move(x, y, 'L', '-'))
            ty = y + v
            if ty < h and g[ty * w + x] != 0:
                out.append(Move(x, y, 'D', '+'))
                out.append(Move(x, y, 'D', '-'))
            ty = y - v
            if ty >= 0 and g[ty * w + x] != 0:
                out.append(Move(x, y, 'U', '+'))
                out.append(Move(x, y, 'U', '-'))

def apply_move(m, g, w, h, nonzero):
    sx = m.x; sy = m.y
    si = sy * w + sx
    v = g[si]
    if v <= 0: return None
    if m.d == 'R': dx = sx + v; dy = sy
    elif m.d == 'L': dx = sx - v; dy = sy
    elif m.d == 'D': dx = sx; dy = sy + v
    else: dx = sx; dy = sy - v
    if dx < 0 or dx >= w or dy < 0 or dy >= h: return None
    di = dy * w + dx
    dv = g[di]
    if dv == 0: return None
    nd = dv + v if m.o == '+' else abs(dv - v)
    g[si] = 0
    g[di] = nd
    nz = nonzero
    nz -= 1
    if dv > 0 and nd == 0: nz -= 1
    return (sx, sy, dx, dy, v, dv, nd, nz)

def undo_move(state, g, w, h, nonzero):
    sx, sy, dx, dy, v, dv, nd, nz = state
    g[sy * w + sx] = v
    g[dy * w + dx] = dv
    return nonzero

def heuristic(nz):
    if nz <= 0: return 0
    return (nz + 1) >> 1

def ida_dfs(g, w, h, nz, depth, bound, path, seen, deadline):
    if nz == 0: return True
    if time.time() > deadline: return False
    f = depth + heuristic(nz)
    if f > bound: return False
    key = tuple(g)
    if key in seen: return False
    seen.add(key)
    moves = []
    gen_moves(g, w, h, moves)
    cand = []
    for m in moves:
        st = apply_move(m, g, w, h, nz)
        if not st: continue
        dec = 1 + (1 if st[5] > 0 and st[6] == 0 else 0)
        cand.append((dec * 100000 - st[6], m, st))
        undo_move(st, g, w, h, nz)
    cand.sort(key=lambda x: -x[0])
    for _, m, st in cand:
        st2 = apply_move(m, g, w, h, nz)
        if not st2: continue
        path.append(m)
        if ida_dfs(g, w, h, st2[7], depth + 1, bound, path, seen, deadline):
            return True
        path.pop()
        undo_move(st2, g, w, h, nz)
        if time.time() > deadline: break
    seen.remove(key)
    return False

def solve(w, h, grid, time_limit=9.0):
    g = grid[:]
    nz = sum(1 for v in g if v != 0)
    path = []
    deadline = time.time() + time_limit
    bound = heuristic(nz)
    while time.time() < deadline:
        seen = set()
        if ida_dfs(g, w, h, nz, 0, bound, path, seen, deadline):
            return path
        bound += 1
    return []

def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    w = int(next(it)); h = int(next(it))
    g = []
    for _ in range(h):
        for _ in range(w):
            g.append(int(next(it)))
    moves = solve(w, h, g, 9.0)
    for m in moves:
        print(m.x, m.y, m.d, m.o)

if __name__ == '__main__':
    main()