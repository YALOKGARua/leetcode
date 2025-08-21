<?php
fscanf(STDIN, "%d", $n);
fscanf(STDIN, "%d", $cap);
$idx = $x = $y = $d = 0;
$nodes = array_fill(0, $n, [0,0,0,0]);
for ($i = 0; $i < $n; $i++) {
    fscanf(STDIN, "%d %d %d %d", $idx, $x, $y, $d);
    $nodes[$idx] = [$idx, $x, $y, $d];
}
$D = array_fill(0, $n, array_fill(0, $n, 0));
for ($i = 0; $i < $n; $i++) {
    for ($j = 0; $j < $n; $j++) {
        $dx = $nodes[$i][1] - $nodes[$j][1];
        $dy = $nodes[$i][2] - $nodes[$j][2];
        $D[$i][$j] = (int)round(sqrt($dx*$dx + $dy*$dy));
    }
}
$routes = [];
$routeDem = [];
$which = array_fill(0, $n, -1);
for ($i = 1; $i < $n; $i++) {
    $routes[] = [$i];
    $routeDem[] = $nodes[$i][3];
    $which[$i] = count($routes) - 1;
}
$S = [];
for ($i = 1; $i < $n; $i++) {
    for ($j = $i + 1; $j < $n; $j++) {
        $s = $D[0][$i] + $D[0][$j] - $D[$i][$j];
        $S[] = [$i, $j, $s];
    }
}
usort($S, function($a,$b){ return $b[2] <=> $a[2]; });
foreach ($S as $sv) {
    $i = $sv[0];
    $j = $sv[1];
    $ri = $which[$i];
    $rj = $which[$j];
    if ($ri === -1 || $rj === -1 || $ri === $rj) continue;
    if ($routeDem[$ri] + $routeDem[$rj] > $cap) continue;
    $A = $routes[$ri];
    $B = $routes[$rj];
    $iFront = ($A[0] === $i);
    $iBack = ($A[count($A)-1] === $i);
    $jFront = ($B[0] === $j);
    $jBack = ($B[count($B)-1] === $j);
    if (!($iFront || $iBack) || !($jFront || $jBack)) continue;
    if ($iBack && $jFront) {
        $new = array_merge($A, $B);
        $usedB = $B;
    } elseif ($iFront && $jBack) {
        $new = array_merge($B, $A);
        $usedB = $B;
    } elseif ($iFront && $jFront) {
        $A = array_reverse($A);
        $new = array_merge($A, $B);
        $usedB = $B;
    } elseif ($iBack && $jBack) {
        $B = array_reverse($B);
        $new = array_merge($A, $B);
        $usedB = $B;
    } else {
        continue;
    }
    $routes[$ri] = $new;
    foreach ($usedB as $v) $which[$v] = $ri;
    $routes[$rj] = [];
    $routeDem[$ri] += $routeDem[$rj];
    $routeDem[$rj] = 0;
}
$finalRoutes = [];
foreach ($routes as $r) if (!empty($r)) $finalRoutes[] = $r;
$twoOpt = function(array &$r) use ($D) {
    $m = count($r);
    if ($m < 3) return false;
    $bestDelta = 0; $bi = -1; $bj = -1;
    for ($i = 0; $i < $m - 1; $i++) {
        $a = ($i === 0) ? 0 : $r[$i-1];
        $b = $r[$i];
        for ($j = $i + 1; $j < $m; $j++) {
            $c = $r[$j];
            $d = ($j === $m - 1) ? 0 : $r[$j+1];
            $before = $D[$a][$b] + $D[$c][$d];
            $after = $D[$a][$c] + $D[$b][$d];
            $delta = $after - $before;
            if ($delta < $bestDelta) { $bestDelta = $delta; $bi = $i; $bj = $j; }
        }
    }
    if ($bestDelta < 0) { $slice = array_reverse(array_slice($r, $bi, $bj - $bi + 1)); array_splice($r, $bi, $bj - $bi + 1, $slice); return true; }
    return false;
};
for ($k = 0; $k < count($finalRoutes); $k++) {
    $iter = 0;
    while ($iter < 50 && $twoOpt($finalRoutes[$k])) $iter++;
}
$totalCost = function(array $routes) use ($D) {
    $sum = 0;
    foreach ($routes as $r) {
        $prev = 0;
        foreach ($r as $v) { $sum += $D[$prev][$v]; $prev = $v; }
        $sum += $D[$prev][0];
    }
    return $sum;
};
$routeCost = function(array $r) use ($D) {
    $c = 0; $prev = 0;
    foreach ($r as $v) { $c += $D[$prev][$v]; $prev = $v; }
    $c += $D[$prev][0];
    return $c;
};
$bestRoutes = $finalRoutes;
$bestCost = $totalCost($bestRoutes);
$loads = [];
for ($i = 0; $i < count($finalRoutes); $i++) { $s = 0; foreach ($finalRoutes[$i] as $v) $s += $nodes[$v][3]; $loads[$i] = $s; }
$target = 85000;
$orOpt1 = function(array &$r) use ($D) {
    $m = count($r);
    if ($m < 3) return false;
    $bestDelta = 0; $bi = -1; $bj = -1;
    for ($i = 0; $i < $m; $i++) {
        $a = ($i === 0) ? 0 : $r[$i-1];
        $b = $r[$i];
        $c = ($i === $m-1) ? 0 : $r[$i+1];
        $rem = $D[$a][$c] - ($D[$a][$b] + $D[$b][$c]);
        for ($j = 0; $j <= $m; $j++) {
            if ($j === $i || $j === $i+1) continue;
            $p = ($j === 0) ? 0 : $r[$j-1];
            $n = ($j === $m) ? 0 : $r[$j];
            $ins = $D[$p][$b] + $D[$b][$n] - $D[$p][$n];
            $delta = $rem + $ins;
            if ($delta < $bestDelta) { $bestDelta = $delta; $bi = $i; $bj = $j; }
        }
    }
    if ($bestDelta < 0) {
        $v = $r[$bi];
        array_splice($r, $bi, 1);
        array_splice($r, $bj > $bi ? $bj-1 : $bj, 0, [$v]);
        return true;
    }
    return false;
};
$orOptK = function(array &$r, int $k) use ($D) {
    $m = count($r);
    if ($m < $k + 1) return false;
    $bestDelta = 0; $bi = -1; $bj = -1;
    for ($i = 0; $i + $k - 1 < $m; $i++) {
        $s0 = $r[$i];
        $sk = $r[$i + $k - 1];
        $a = ($i === 0) ? 0 : $r[$i-1];
        $c = ($i + $k - 1 === $m - 1) ? 0 : $r[$i + $k];
        $rem = $D[$a][$c] - ($D[$a][$s0] + $D[$sk][$c]);
        for ($j = 0; $j <= $m; $j++) {
            if ($j >= $i && $j <= $i + $k) continue;
            $p = ($j === 0) ? 0 : $r[$j - 1];
            $n = ($j === $m) ? 0 : $r[$j];
            $ins = $D[$p][$s0] + $D[$sk][$n] - $D[$p][$n];
            $delta = $rem + $ins;
            if ($delta < $bestDelta) { $bestDelta = $delta; $bi = $i; $bj = $j; }
        }
    }
    if ($bestDelta < 0) {
        $seg = array_slice($r, $bi, $k);
        array_splice($r, $bi, $k);
        array_splice($r, $bj > $bi ? $bj - $k : $bj, 0, $seg);
        return true;
    }
    return false;
};
$deadline = microtime(true) + 0.8;
$demOf = array_column($nodes, 3);
while (microtime(true) < $deadline) {
    $improved = false;
    $Rcnt = count($finalRoutes);
    for ($ri = 0; $ri < $Rcnt && !$improved; $ri++) {
        for ($rj = 0; $rj < $Rcnt && !$improved; $rj++) {
            if ($ri === $rj) continue;
            $A =& $finalRoutes[$ri];
            $B =& $finalRoutes[$rj];
            if (empty($A) || empty($B)) continue;
            $demA = $loads[$ri];
            $demB = $loads[$rj];
            $bestDelta = 0; $bestMove = null;
            for ($ia = 0; $ia < count($A); $ia++) {
                $aPrev = ($ia === 0) ? 0 : $A[$ia-1];
                $aNode = $A[$ia];
                $aNext = ($ia === count($A)-1) ? 0 : $A[$ia+1];
                $remDelta = $D[$aPrev][$aNext] - ($D[$aPrev][$aNode] + $D[$aNode][$aNext]);
                if ($demB + $demOf[$aNode] <= $cap) {
                    for ($jb = 0; $jb <= count($B); $jb++) {
                        $bPrev = ($jb === 0) ? 0 : $B[$jb-1];
                        $bNext = ($jb === count($B)) ? 0 : $B[$jb];
                        $insDelta = $D[$bPrev][$aNode] + $D[$aNode][$bNext] - $D[$bPrev][$bNext];
                        $delta = $remDelta + $insDelta;
                        if ($delta < $bestDelta) { $bestDelta = $delta; $bestMove = ['type'=>'rel', 'ia'=>$ia, 'ri'=>$ri, 'rj'=>$rj, 'jb'=>$jb]; }
                    }
                }
                for ($jb = 0; $jb < count($B); $jb++) {
                    $bPrev = ($jb === 0) ? 0 : $B[$jb-1];
                    $bNode = $B[$jb];
                    $bNext = ($jb === count($B)-1) ? 0 : $B[$jb+1];
                    $before = $D[$aPrev][$aNode] + $D[$aNode][$aNext] + $D[$bPrev][$bNode] + $D[$bNode][$bNext];
                    $after = $D[$aPrev][$bNode] + $D[$bNode][$aNext] + $D[$bPrev][$aNode] + $D[$aNode][$bNext];
                    if ($demA - $demOf[$aNode] + $demOf[$bNode] <= $cap && $demB - $demOf[$bNode] + $demOf[$aNode] <= $cap) {
                        $delta = $after - $before;
                        if ($delta < $bestDelta) { $bestDelta = $delta; $bestMove = ['type'=>'swap', 'ia'=>$ia, 'jb'=>$jb, 'ri'=>$ri, 'rj'=>$rj]; }
                    }
                }
            }
            if ($bestMove && $bestDelta < 0) {
                if ($bestMove['type'] === 'rel') {
                    $ia = $bestMove['ia']; $jb = $bestMove['jb'];
                    $v = $finalRoutes[$ri][$ia];
                    array_splice($finalRoutes[$ri], $ia, 1);
                    array_splice($finalRoutes[$rj], $jb, 0, [$v]);
                    $loads[$ri] -= $demOf[$v];
                    $loads[$rj] += $demOf[$v];
                } else {
                    $ia = $bestMove['ia']; $jb = $bestMove['jb'];
                    $va = $finalRoutes[$ri][$ia];
                    $vb = $finalRoutes[$rj][$jb];
                    $finalRoutes[$ri][$ia] = $vb;
                    $finalRoutes[$rj][$jb] = $va;
                    $loads[$ri] += $demOf[$vb] - $demOf[$va];
                    $loads[$rj] += $demOf[$va] - $demOf[$vb];
                }
                $twoOpt($finalRoutes[$ri]);
                $twoOpt($finalRoutes[$rj]);
                $improved = true;
                $curCost = $totalCost($finalRoutes);
                if ($curCost < $bestCost) { $bestCost = $curCost; $bestRoutes = $finalRoutes; }
                if ($bestCost <= $target) { $deadline = microtime(true); }
            }
        }
    }
    if (!$improved) break;
}
$changed = true; $it = 0;
while ($changed && $it < 30) {
    $changed = false; $it++;
    for ($k = 0; $k < count($finalRoutes); $k++) {
        if ($orOpt1($finalRoutes[$k])) { $twoOpt($finalRoutes[$k]); $changed = true; }
        if ($orOptK($finalRoutes[$k], 2)) { $twoOpt($finalRoutes[$k]); $changed = true; }
        if ($orOptK($finalRoutes[$k], 3)) { $twoOpt($finalRoutes[$k]); $changed = true; }
    }
}
$routeLoad = function(array $r, array $demOf) { $s = 0; foreach ($r as $v) $s += $demOf[$v]; return $s; };
$deadline2 = microtime(true) + 0.8;
while (microtime(true) < $deadline2) {
    $improved = false;
    $R = count($finalRoutes);
    for ($ri = 0; $ri < $R && !$improved; $ri++) {
        for ($rj = $ri + 1; $rj < $R && !$improved; $rj++) {
            $A = $finalRoutes[$ri];
            $B = $finalRoutes[$rj];
            $ma = count($A); $mb = count($B);
            if ($ma == 0 || $mb == 0) continue;
            $best = 0; $bi = -1; $bj = -1; $newA = null; $newB = null;
            for ($ia = 0; $ia < $ma - 1; $ia++) {
                for ($jb = 0; $jb < $mb - 1; $jb++) {
                    $A1 = array_slice($A, 0, $ia + 1);
                    $A2 = array_slice($A, $ia + 1);
                    $B1 = array_slice($B, 0, $jb + 1);
                    $B2 = array_slice($B, $jb + 1);
                    $candA = array_merge($A1, $B2);
                    $candB = array_merge($B1, $A2);
                    $loadA = $routeLoad($candA, $demOf);
                    $loadB = $routeLoad($candB, $demOf);
                    if ($loadA > $cap || $loadB > $cap) continue;
                    $delta = ($routeCost($candA) + $routeCost($candB)) - ($routeCost($A) + $routeCost($B));
                    if ($delta < $best) { $best = $delta; $bi = $ia; $bj = $jb; $newA = $candA; $newB = $candB; }
                }
            }
            if ($bi !== -1 && $best < 0) {
                $finalRoutes[$ri] = $newA;
                $finalRoutes[$rj] = $newB;
                $twoOpt($finalRoutes[$ri]);
                $twoOpt($finalRoutes[$rj]);
                $improved = true;
                $curCost = $totalCost($finalRoutes);
                if ($curCost < $bestCost) { $bestCost = $curCost; $bestRoutes = $finalRoutes; }
                if ($bestCost <= $target) { $deadline2 = microtime(true); }
            }
        }
    }
    if (!$improved) break;
}
$curCostFinal = $totalCost($finalRoutes);
if ($curCostFinal < $bestCost) { $bestCost = $curCostFinal; $bestRoutes = $finalRoutes; }
$twoOptCycle = function(array &$seq) use ($D) {
    $m = count($seq);
    if ($m < 3) return false;
    $improved = false;
    for ($iter = 0; $iter < 50; $iter++) {
        $bestDelta = 0; $bi = -1; $bj = -1;
        for ($i = 0; $i < $m - 1; $i++) {
            $pi = ($i == 0) ? 0 : $seq[$i-1];
            $vi = $seq[$i];
            for ($j = $i + 1; $j < $m; $j++) {
                $vj = $seq[$j];
                $nj = ($j == $m - 1) ? 0 : $seq[$j+1];
                if ($i + 1 == $j && $pi != 0 && $nj != 0) continue;
                $before = $D[$pi][$vi] + $D[$vj][$nj];
                $after = $D[$pi][$vj] + $D[$vi][$nj];
                $delta = $after - $before;
                if ($delta < $bestDelta) { $bestDelta = $delta; $bi = $i; $bj = $j; }
            }
        }
        if ($bestDelta < 0) {
            $slice = array_reverse(array_slice($seq, $bi, $bj - $bi + 1));
            array_splice($seq, $bi, $bj - $bi + 1, $slice);
            $improved = true;
        } else break;
    }
    return $improved;
};
$buildSplit = function() use ($n, $D, $nodes, $cap, $twoOptCycle, $twoOpt, $totalCost) {
    $demOf = array_column($nodes, 3);
    $cust = [];
    for ($i = 1; $i < $n; $i++) $cust[] = $i;
    $start = 1;
    $md = -1;
    foreach ($cust as $v) { if ($D[0][$v] > $md) { $md = $D[0][$v]; $start = $v; } }
    $unv = array_fill(0, $n, true); $unv[0] = false; foreach ($cust as $v) $unv[$v] = true; $unv[$start] = false;
    $seq = [$start]; $last = $start;
    for ($k = 1; $k < count($cust); $k++) {
        $best = PHP_INT_MAX; $bj = -1;
        for ($j = 1; $j < $n; $j++) if ($unv[$j]) { $dd = $D[$last][$j]; if ($dd < $best) { $best = $dd; $bj = $j; } }
        $seq[] = $bj; $unv[$bj] = false; $last = $bj;
    }
    $twoOptCycle($seq);
    $m = count($seq);
    $prefD = array_fill(0, $m + 1, 0);
    for ($i = 0; $i < $m; $i++) $prefD[$i+1] = $prefD[$i] + $demOf[$seq[$i]];
    $edge = array_fill(0, $m, 0);
    for ($i = 0; $i < $m - 1; $i++) $edge[$i] = $D[$seq[$i]][$seq[$i+1]];
    $prefE = array_fill(0, $m, 0);
    for ($i = 1; $i < $m; $i++) $prefE[$i] = $prefE[$i-1] + $edge[$i-1];
    $INF = 1e15;
    $dp = array_fill(0, $m, $INF);
    $prev = array_fill(0, $m, -1);
    for ($j = 0; $j < $m; $j++) {
        for ($i = 0; $i <= $j; $i++) {
            $dem = $prefD[$j+1] - $prefD[$i];
            if ($dem > $cap) break;
            $seg = $D[0][$seq[$i]] + ($i == $j ? 0 : $prefE[$j] - $prefE[$i]) + $D[$seq[$j]][0];
            $cand = $seg + ($i > 0 ? $dp[$i-1] : 0);
            if ($cand < $dp[$j]) { $dp[$j] = $cand; $prev[$j] = $i - 1; }
        }
    }
    $routes = [];
    $j = $m - 1;
    while ($j >= 0) {
        $i = $prev[$j] + 1;
        $r = [];
        for ($k = $i; $k <= $j; $k++) $r[] = $seq[$k];
        $routes[] = $r;
        $j = $prev[$j];
    }
    $routes = array_reverse($routes);
    for ($i = 0; $i < count($routes); $i++) { $iter = 0; while ($iter < 50 && $twoOpt($routes[$i])) $iter++; }
    return $routes;
};
$splitRoutes = $buildSplit();
$costSplit = $totalCost($splitRoutes);
if ($costSplit < $bestCost) { $bestCost = $costSplit; $bestRoutes = $splitRoutes; }
$repair = function(array $routes) use ($n, $D, $cap, $nodes, $routeLoad, $twoOpt) {
    $seen = array_fill(0, $n, false);
    $demOf = array_column($nodes, 3);
    $clean = [];
    foreach ($routes as $r) {
        $nr = [];
        foreach ($r as $v) {
            if (!$seen[$v]) { $seen[$v] = true; $nr[] = $v; }
        }
        if (!empty($nr)) $clean[] = $nr;
    }
    $missing = [];
    for ($v = 1; $v < $n; $v++) if (!$seen[$v]) $missing[] = $v;
    foreach ($missing as $v) {
        $bestDelta = PHP_INT_MAX; $bi = -1; $bj = -1;
        for ($i = 0; $i < count($clean); $i++) {
            $load = $routeLoad($clean[$i], $demOf);
            if ($load + $demOf[$v] > $cap) continue;
            $m = count($clean[$i]);
            for ($j = 0; $j <= $m; $j++) {
                $prev = ($j == 0) ? 0 : $clean[$i][$j-1];
                $next = ($j == $m) ? 0 : $clean[$i][$j];
                $delta = $D[$prev][$v] + $D[$v][$next] - $D[$prev][$next];
                if ($delta < $bestDelta) { $bestDelta = $delta; $bi = $i; $bj = $j; }
            }
        }
        if ($bi == -1) {
            $clean[] = [$v];
        } else {
            array_splice($clean[$bi], $bj, 0, [$v]);
        }
    }
    $feasible = [];
    foreach ($clean as $r) {
        $cur = [];
        $curLoad = 0;
        foreach ($r as $v) {
            $dv = $demOf[$v];
            if ($curLoad + $dv <= $cap) {
                $cur[] = $v;
                $curLoad += $dv;
            } else {
                if (!empty($cur)) $feasible[] = $cur;
                $cur = [$v];
                $curLoad = $dv;
            }
        }
        if (!empty($cur)) $feasible[] = $cur;
    }
    for ($i = 0; $i < count($feasible); $i++) { $iter = 0; while ($iter < 30 && $twoOpt($feasible[$i])) $iter++; }
    return $feasible;
};
$finalRoutes = $repair($finalRoutes);
$bestRoutes = $repair($bestRoutes);
$curA = $totalCost($finalRoutes);
$curB = $totalCost($bestRoutes);
if ($curA < $curB) $bestRoutes = $finalRoutes;
$out = [];
foreach ($bestRoutes as $r) $out[] = implode(' ', $r);
echo implode(';', $out) . "\n";
?>