# Data_Structures  
### Skiplist  
The skiplist is a data structure based on probabilities. It allows a search complexity and insertion complexity of O(log N) in a sorted skiplist.  
In consequence it provides better advantages complexity-wise over clasicall linked lists and aloso over arrays.  
It is built in layers and usually for better memory management the height does not exceed 10 (ususally height of order log N)  
A search for a number starts at the head element and continues untill it finds the element or the reached number is bigger.  
If the number is bigger we proceed to a lower level for search. If we have searched all levels and not found the element it means it does not exist.  
There are various techniques for building "de-randomized"/quasi-randomized skiplist but the classic version proves to be efficient.  

### Segment trees(arbori de intervale)  
The segment trees are another tipe of data structure that bring improvements.  
It allows queries on interval in log N time and also the update of elements is done in logarithmic time.  
