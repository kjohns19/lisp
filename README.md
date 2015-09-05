# Lisp
I found this when going through old personal projects. I thought I'd put it on github. It's a [Lisp](https://en.wikipedia.org/wiki/Lisp_%28programming_language%29) interpreter with some extra features, such as [currying](https://en.wikipedia.org/wiki/Currying) and [lazy evaluation](https://en.wikipedia.org/wiki/Lazy_evaluation).

Requires cmake 2.8 and g++ (with C++11)

## Eamples
Examples follow this format:
```
# comment
> code
result
```
### Basics
```
# Calculate 1 + 2
> (+ 1 2)
3

# Calculate 3 * (4 + 5)
> (* 3 (+ 4 5))
27

# Conditional (if 3 > 4, return 1, otherwise return 2)
> (if (> 3 4) 1 2)
2

# Create a list
> (cons 1 (cons 2 ()))
(1 2)

# Create a list using literal notation
> '(1 2)
(1 2)

# Head of list
> (car '(3 5 7))
3

# Rest of list
> (cdr '(3 5 7))
(5 7)

# Define f(x) = x*x
> (define f (lambda (x) (* x x)))
()
# Calculate f(4)
> (f 4)
16
```

### Currying
```
# Define times10(x) = 10 * x using currying
> (define times10 (* 10))
()
> (times10 7)
70
```

### Lazy Evaluation - Infinite lists!
```
# Iteration sequence: s(1) = x, s(N) = f(s(N-1))
> (define iterate (lambda (f x) (cons x (iterate f (f x)))))
()

# Numbers 1-10 (take is defined elsewhere!)
> (take 10 (iterate (+ 1) 1))
(1 2 3 4 5 6 7 8 9 10)

# Fibonacci sequence (recursive definition!)
> (define fib (cons 1 (cons 1 (zipWith + fib (drop 1 fib)))))
()
> (take 10 fib)
(1 1 2 3 5 8 13 21 34 55)
```
