(ns analysis.core
  (:require [clojure.java.io :as io])
  (:use (incanter core io charts svg)))

;; Notes on Incanter
;; -----------------
;; 
;; Documentation (API)
;; http://liebke.github.io/incanter/
;;
;; Get the firt column as a list
;; ($ 0 data)
;; Get the first element
;; ($ 0 0 data)
;;
;; (view data)
;; (col-names data)

;; List all the result files.
;; (It will list _all_ file (recursivly) in the specified directory)
(def all-result-files (doall (remove #(io/.isDirectory %) (file-seq (io/file "../results")))))

;;;; Define some functions

(defn interpret-result-filename [filename]
  "Take a filename return ALGO and THRESHOLD."
  (let [[_ algo threshold] (re-matches #".*result_([01])_([0-9]+).csv$" filename)] 
               (map #(Integer/parseInt %) [algo threshold])))

;; Tests:
;; (interpret-result-filename "result_1_23.csv") => [1 23]

(defn interpret-testset-filename [filename]
  "Take a filename return N and SET."
  ;; #(Integer/parseInt %) from http://stackoverflow.com/a/6197026/1564492
  (map #(Integer/parseInt %) 
       (subvec (re-matches #".*testset_([0-9]+)_([0-9]+).txt$" filename) 1)))

;; Tests:
;; (interpret-filename filename)
;; (map #(second (interpret-filename %)) ($ 0 data))

(defn load-result-file [file]
  (let [filename (io/.getPath file)
        data (rename-cols {:col0 :file :col1 :n :col2 :time}
                                                 (read-dataset filename))
        [algo threshold] (interpret-result-filename filename)]
    (add-column :algo (repeat algo) 
                (add-column :threshold (repeat threshold)
                            (add-derived-column :set [:file] #(second (interpret-testset-filename %)) data)))))

;; Get _ALL_ the data in one dataset (ignoring the "file" column).
(def results (doall (sel (reduce conj-rows (map load-result-file all-result-files)) :except-cols :file)))
;; (dim results) Should give 3600 (because I ran "sort" 3600 times.
;; (view results)


;; Create a bar chart for a specified N, one bar per threshold.
;; Save the chart as chart1.svg
(defn main []
	(save results "results.csv")

  (let [n 500000
        chart (bar-chart :threshold :time
                         :data ($order :threshold :asc ($where {:n {:eq n}} results))
                         :x-label "Seuil"
                         :y-label "Temps")]
    (doto chart
      (set-title (str "Temps par seuils (N = " n ")")))
  ;;  (view chart)
    (save-svg chart "chart1.svg")))

                    
