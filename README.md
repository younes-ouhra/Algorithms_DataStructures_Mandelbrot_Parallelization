# Algorithms and Data Strukturs - Mandelbrot and Parallelization
## About
This project was built along with the Laboratory Algorithms and Data Structures at the Technical University of Applied Sciences of Regensburg, Bavaria, Germany. Also, it simulates representing Mandelbrot-set with and without the parallelization, and measures the requered time to represent the Mandelbrot-set and the efficiency of the parallelization in this case.

## Conclusion
<p>The result of this project was that representing the Mandelbrot-set with the parallelization helped to achieve few simulation-time in comparison with the sequential process.</p>
<p>The reason why parallelization has a good result when representing the Mandelbrot-set is because the number of threads is ysize, which is the attribute of the class Mandelbrot and the width of the Mandelbrot. That means, the Mandelbrot will be represented as horizontal lines independently from each other and without interfering with each other.</p>


<img src="https://github.com/younes-ouhra/algorithms-datastructures-mandelbrot-parallelization/blob/main/Result%20-Mandelbrot-Set.png">
