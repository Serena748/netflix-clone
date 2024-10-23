# Netflix Recommendation Platform
I made a Netflix-inspired Recommendation Platform in C++ that loads a database of 100,000 users and 20,000 movies from a text file in under a second and recommends movies to users based on their prior watch history. 

Methodology: 
- I assigned weighted scores to movies, factoring in director (20 points), actor (30 points), and genre (1 point), resulting in top-ranked recommendations for user preferences.
- I used binary search trees (BST) in multimaps for O(n) lookups, utilized unordered maps and vectors to store and update movie rankings for O(n log n) time complexity. 

