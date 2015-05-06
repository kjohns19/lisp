(define map (lambda (func lst)
    (if (null? lst)
        null
        (cons
            (func (car lst))
            (map func (cdr lst))))))

(define take (lambda (count lst)
    (if (or (null? lst) (== 0 count))
        null
        (cons (car lst) (take (- count 1) (cdr lst))))))
(define takeWhile (lambda (func lst)
    (if (null? lst)
        lst
        (let ((elem (car lst)))
            (if (func elem)
                (cons elem (takeWhile func (cdr lst)))
                null)))))

(define drop (lambda (count lst)
    (if (or (== count 0) (null? lst))
        lst
        (drop (- count 1) (cdr lst)))))

(define dropWhile (lambda (func lst)
    (if (null? lst)
        lst
        (if (func (car lst))
            (dropWhile func (cdr lst))
            lst))))

(define !! (lambda (index lst) (car (drop index lst))))

(define zipWith (lambda (func lst1 lst2)
    (if (or (null? lst1) (null? lst2))
        null
        (cons (func (car lst1) (car lst2)) (zipWith func (cdr lst1) (cdr lst2))))))

(define zip (zipWith list))

(define foldl (lambda (func val lst)
    (if (null? lst)
        val
        (foldl func (func val (car lst)) (cdr lst)))))

(define foldr (lambda (func val lst)
    (if (null? lst)
        val
        (func (car lst) (foldr func val (cdr lst))))))

(define foldl1 (lambda (func lst)
    (if (null? lst)
        (error "Cannot fold empty list" )
        (foldl func (car lst) (cdr lst)))))

(define foldr1 (lambda (func lst)
    (if (null? lst)
        (error "Cannot fold empty list" )
        (let ((head (car lst)) (tail (cdr lst)))
            (if (null? tail)
                head
                (func head (foldr1 func tail)))))))

(define filter (lambda (func lst)
    (if (null? lst)
        null
        (let ((elem (car lst)))
            (if (func elem)
                (cons elem (filter func (cdr lst)))
                (filter func (cdr lst)))))))

(define mergeWith (lambda (func lst1 lst2)
    (if (null? lst1)
        lst2
        (if (null? lst2)
            lst2
            (let ((val1 (car lst1)) (val2 (car lst2)))
                (if (func val1 val2)
                    (cons val1 (mergeWith func (cdr lst1) lst2))
                    (cons val2 (mergeWith func lst1 (cdr lst2)))))))))
(define merge (mergeWith <))

(define member (lambda (elem lst)
    (if (null? lst)
        (if (== elem (car lst))
            #t
            (member elem (cdr lst))))))

(define range (lambda (min max step)
    (if (> step 0)
        (takeWhile (>= max) (iterate (+ step) min))
        (takeWhile (<= max) (iterate (+ step) min)))))

(define maxWith (lambda (func lst)
    (foldl1 (lambda (a b) (if (func a b) a b)) lst)))

(define max (maxWith >))
(define min (maxWith <))

(define iterate (lambda (func start) (cons start (iterate func (func start)))))
(define count (lambda (a) (iterate (+ a) a)))

(define append (lambda (lst1 lst2)
    (if (null? lst1)
        lst2
        (cons (car lst1) (append (cdr lst1) lst2)))))


(define fib (cons 1 (cons 1 (zipWith + fib (drop 1 fib)))))

(define sortWith (lambda (func lst)
    (if (or (null? lst) (null? (cdr lst)))
        lst
        (let ((partition (lambda (func pivot lst left right)
            (if (null? lst)
                (list left right)
                (let ((elem (car lst)) (rest (cdr lst)))
                    (if (func pivot elem)
                        (partition func pivot rest left (cons elem right))
                        (partition func pivot rest (cons elem left) right)))))))
            (let ((parts (partition func (car lst) (cdr lst) null null)))
                (append (sortWith func (car parts)) (cons (car lst) (sortWith func (car (cdr parts))))))))))
(define sort (sortWith <))

(define diff (lambda (lst1 lst2)
    (let ((val1 (car lst1)) (val2 (car lst2)))
        (if (< val1 val2)
            (cons val1 (diff (cdr lst1) lst2))
            (if (> val1 val2)
                (diff lst1 (cdr lst2))
                (diff (cdr lst1) (cdr lst2)))))))

(define primes (cons 2 (cons 3 (cons 5 (diff (iterate (+ 2) 7) nonprimes)))))

(define nonprimes
    (let ((f (lambda (lst1 lst2) (cons (car lst1) (merge (cdr lst1) lst2))))
          (g (lambda (p) (map (* p) (iterate (+ 2) p)))))
    (foldr1 f (map g (cdr primes)))))
