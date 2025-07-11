(ns Solution
  (:require [clojure.string :as str])
  (:gen-class))

(defn output [msg] (println msg) (flush))
(defn debug [msg] (binding [*out* *err*] (println msg) (flush)))

(defn precompute-rides [groups L]
  (let [n (count groups)]
    (reduce 
     (fn [memo start-pos]
       (let [result 
             (loop [pos start-pos
                    people 0
                    capacity L]
               (let [group-size (nth groups pos)
                     new-capacity (- capacity group-size)]
                 (if (>= new-capacity 0)
                   (let [new-people (+ people group-size)
                         next-pos (mod (inc pos) n)]
                     (if (= next-pos start-pos)
                       {:people new-people :next-pos next-pos}
                       (recur next-pos new-people new-capacity)))
                   {:people people :next-pos pos})))]
         (assoc memo start-pos result)))
     {}
     (range n))))

(defn calculate-earnings [L C groups]
  (let [ride-cache (precompute-rides groups L)]
    (loop [rides-left C
           current-pos 0  
           total-earnings 0]
      (if (zero? rides-left)
        total-earnings
        (let [{:keys [people next-pos]} (get ride-cache current-pos)]
          (recur (dec rides-left)
                 next-pos
                 (+ total-earnings people)))))))

(defn find-cycle [groups L]
  (let [ride-cache (precompute-rides groups L)]
    (loop [pos 0
           visited {}
           step 0]
      (if (contains? visited pos)
        (let [cycle-start (get visited pos)
              cycle-length (- step cycle-start)]
          {:cycle-start cycle-start
           :cycle-length cycle-length
           :ride-cache ride-cache})
        (let [{:keys [next-pos]} (get ride-cache pos)]
          (recur next-pos
                 (assoc visited pos step)
                 (inc step)))))))

(defn solve-roller-coaster [L C groups]
  (let [n (count groups)]
    (if (<= C (* 2 n))
      (calculate-earnings L C groups)
      (let [{:keys [cycle-start cycle-length ride-cache]} (find-cycle groups L)]
        (if (< C cycle-start)
          (calculate-earnings L C groups)
          (let [
                pre-cycle-earnings (loop [pos 0
                                         rides 0
                                         earnings 0]
                                    (if (= rides cycle-start)
                                      earnings
                                      (let [{:keys [people next-pos]} (get ride-cache pos)]
                                        (recur next-pos (inc rides) (+ earnings people)))))
                
                cycle-start-pos (nth (iterate #(:next-pos (get ride-cache %)) 0) cycle-start)
                cycle-earnings (loop [pos cycle-start-pos
                                     rides 0
                                     earnings 0]
                                (if (= rides cycle-length)
                                  earnings
                                  (let [{:keys [people next-pos]} (get ride-cache pos)]
                                    (recur next-pos (inc rides) (+ earnings people)))))
                
                remaining-rides (- C cycle-start)
                full-cycles (quot remaining-rides cycle-length)
                partial-rides (rem remaining-rides cycle-length)]
            
            (+ pre-cycle-earnings
               (* full-cycles cycle-earnings)
               (if (> partial-rides 0)
                 (loop [pos cycle-start-pos
                        rides 0
                        earnings 0]
                   (if (= rides partial-rides)
                     earnings
                     (let [{:keys [people next-pos]} (get ride-cache pos)]
                       (recur next-pos (inc rides) (+ earnings people)))))
                 0))))))))

(defn -main [& args]
  (let [[L C N] (map #(Integer/parseInt %) (filter #(not-empty %) (str/split (read-line) #" ")))
        groups (vec (repeatedly N #(Integer/parseInt (read-line))))]
    
    (output (solve-roller-coaster L C groups)))) 