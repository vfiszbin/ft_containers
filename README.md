# ft_containers
In this project from the 42 cursus, I have fully reimplemented the container types of the C++ standard template library.

The implemented containers are :
- **Vector**
- **Map** : the inner data structure is an AVL tree to ensure $O(log(n))$ complexity on operations such as search.
- **Stack**

All functions (C++98) found in the documentation (e.g [Map documentation](https://cplusplus.com/reference/map/map/)) have been reimplemented, along with the iterators used in each container.

The performance of these containers has been compared to that of the STL containers to ensure they are similar or close in performance.

## How to run it
To compile the project and run the performance test:
```
./speed_benchmark.sh
```
