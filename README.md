EE538 TrojanMap final report
## Presentation video
https://youtu.be/UJvASAmtQnw
## The Data Structure

Each point on the map is represented by the class **Node** shown below and defined in [trojanmap.h](src/lib/trojanmap.h).

```cpp
// A Node is the location of one point in the map.
class Node {
 public:
  Node(){};
  Node(const Node &n) {
    id = n.id;
    lat = n.lat;
    lon = n.lon;
    name = n.name;
    neighbors = n.neighbors;
    attributes = n.attributes;
  };
  std::string id;    // A unique id assigned to each point.
  double lat;        // Latitude
  double lon;        // Longitude
  std::string name;  // Name of the location. E.g. "Bank of America".
  std::vector<std::string>
      neighbors;  // List of the ids of all neighbor points.
  std::unordered_set<std::string>
      attributes;  // List of the attributes of the location.
};
```

---
## Functions
## Item 1: Autocomplete The Location Name (Phase 1)

Firstly, converting all the letter in input to uppercase. Then, going through every node in data and check its name.
Runtime is O(N). N is the number of nodes

## Item 2-1: Find the place's coordinates in the Map (Phase 1)

Firstly, converting all the letter in input to uppercase. Then, going through every node in data and check its name. If found, return the node's latitude and longtitude.
Runtime is O(N). N is the number of nodes


## Item 2-2: Check Edit Distance Between Two Location Names (Phase 2)

```c++
int CalculateEditDistance(std::string name1, std::string name2);
```
Levenshtein distance
created a m by n matrix, m is the length of the first string, n is the length of the second string. Using two for loop to fullfill this matrix.
The time complexity is O(|n|*|m|). where |n| and |m| are length of string.

```c++
std::string FindClosestName(std::string name);
```
Going through all nodes in data, compare the edit distances and keep the smallest one.
The time complexity is O(N), where N is the number of nodes.

## Item 3: Get All Categories (Phase 2)

```c++
std::vector<std::string> GetAllCategories();
```

Inserting all attributes onto unordered set. Duplicates can not be inserted.

The time complexity is O(N), where N is the number of nodes.

## Item 4: Get All Locations In A Category (Phase 2)

```c++
std::vector<std::string> GetAllLocationsFromCategory(std::string category);
```

Going through all node's attributes. If attribute match catergory, push it onto result.

The time complexity is O(N), where N is the number of nodes.

## Item 5: Get Locations Using A Regular Expression (Phase 2)

```c++
std::vector<std::string> GetLocationRegex(std::regex location);
```

Fristly, verify if the input regular expression was correct. If not, return empty. If so, return locations ids.

## Item 6: CalculateShortestPath between two places (Phase 2)

```c++
std::vector<std::string> CalculateShortestPath_Dijkstra(std::string &location1_name,std::string &location2_name);
```
Find the shortest route from A to B using Dijkstra algorithm.
Min-queue was used in this program to implement non-recursive Dijkstra algorithm. For nodes in queue, computing the distance between it and its neighbors. If found a shorter distance, update it and push this neighbor onto queue.

```c++
std::vector<std::string> CalculateShortestPath_Bellman_Ford(std::string &location1_name,
                                               std::string &location2_name);
```
Find the shortest route from A to B using Bellman_Ford algorithm.
Using an unordered map to store the distance to the start node. Initializing distance to maximum except for the start node. Use a for loop to iterate all nodes in data. Check the distance from neighbor to the start point and update distance unordered map. If the distance does not change anymore, make an early stop.

In the worst case, it need to do n-1 iterations(n is the number of nodes). In each iteration, going through all nodes. Thus, the time complexity is O(N^2)

| Point A to Point B  | Dijkstra | Bellman Ford|
| -------------------- | ----------- |-------|
|Starbucks 3 to Target|30|8873|
|Holy Name School to Target|80|12513|
|National Schools to Target|89|9922|
|Saint Patricks Catholic Church to Target|101|10618|
|North Star Auditorium to Target|77|11495|
|McDonald's to Target|29|126|
|Subway to Target|86|9395|
|Burger King to Target|97|11191|
|Shell to Target|96|11635|
|Chevron to Target|89|8787|
|Farmdale 1 to Target|53|14835|
|Farmdale to Target|83|14568|
|Kedren Community Health Center to Target|106|11100|
|Ralphs to Target|65|9307|
|The Sonshine Shop Thrift Store to Target|79|11398|
|Dornsife Spatial Sciences Institute to Target|54|7884|

## Item 7: Cycle Detection (Phase 2)

```c++
bool CycleDetection(std::vector<double> &square);
```
DFS algorithm was used in this function. This non-recursive function was realized by using stack.
Push unvisited node onto stack. If the visited node exists in the stack, there is a cycle. If not, there is not cycle.

Example 1:
```shell
Input: square = {-118.297, -118.279, 34.030, 34.021}
Output: true
```
Example 2:
```shell
Input: square = {-118.297, -118.283, 34.030, 34.021}
Output: true
```
Example 3:
```shell
Input: square = {-118.298, -118.292, 34.028, 34.021}
Output: true
```
Example 4:
```shell
Input: square = {-118.300, -118.298, 34.028, 34.021}
Output: false
```
Example 5:
```shell
Input: square = {-118.299, -118.298, 34.025, 34.021}
Output: false
```
## Item 8: Topological Sort (Phase 2)

Firstly, compute the degree of nodes in input. Pick the 0-degree node as root.  Pushing the root onto stack. Pop a node from the stack and push its unvisited neighbor onto stack. If the node pop from stack is already visited, remove it from stack and push it onto result. At the end, reverse the order of the result.

The time complexity is O(N), where N is the number of locations in input.

Example:
dependencies
Ralphs
Chick-fil-A
Chick-fil-A
KFC
KFC
Ahmanson Commons
Ahmanson Commons
Target
Target
Shell
locations
Ralphs
KFC
Chick-fil-A
Ahmanson Commons
Target
Shell
locations end
*************************Results******************************
Topological Sorting Results:
Ralphs
Chick-fil-A
KFC
Ahmanson Commons
Target
Shell
**************************************************************
Time taken by function: 0 ms

Example2:
dependencies
Ralphs
Chick-fil-A
Chick-fil-A
KFC
KFC
Ahmanson Commons
Ahmanson Commons
Shell
Shell
Target
locations
Ralphs
KFC
Chick-fil-A
Ahmanson Commons
Target
Shell
locations end
*************************Results******************************
Topological Sorting Results:
Ralphs
Chick-fil-A
KFC
Ahmanson Commons
Shell
Target
**************************************************************
Time taken by function: 0 ms


## Item 9: The Traveling Trojan Problem (AKA Traveling Salesman!) (Phase 3)

```c++
std::pair<double, std::vector<std::vector<std::string>>> TravelingTrojan_Brute_force(
      std::vector<std::string> location_ids);
```
Using for loop to get all permutation of locations. Then computing the distance of all permutations. Keeping the shortest one.
The time complexity is O(N^2)
<p align="center"><img src="img/output.gif" alt="TSP videos" width="500"/></p>

```c++
std::pair<double, std::vector<std::vector<std::string>>> TravelingTrojan_Backtracking(
      std::vector<std::string> location_ids);
```
TSP_aux helper function was used in this function. It push locations onto current path and compute the length of current path. if reach at leaf, store the current path and update the min cost. if current cost is larger than min cost, don't need to go deeper and return to upper level.

The time complexity is O(N!), where N is the number of locations.
```c++
std::pair<double, std::vector<std::vector<std::string>>> TravelingTrojan_2opt(
      std::vector<std::string> location_ids);
```
Push all locations onto current path. Then, going through all permutations of two nodes. If the exchange of two nodes lead to shorter length, exchange the order of two nodes.

The time complexity is O(N^2), where N is the number of locations.



| Number of nodes| Time with Brute_force | Time with Backtracking|Time with 2opt |
| -------------------- | ----------- |----|----|
|6            |  2        | 1    |0|
|6            |  2        | 1    |0|
|5            |  0        | 0    |0|
|7|19|5|0|
|7|20|7|0|
|8|332|45|0|


## Item 10: Find Nearby (Phase 3)

```c++
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k);
```

Firstly, getting all locations from Category. Check the distance from other locations to target location. If the length is larger than r, skip it. Otherwise, push it onto min-queue. Then, pop nodes from the min-queue and push onto result.

The time complexity is O(N), where N is the number of nodes.

## Item 11: Find the Shortest Path to Visit All locations (Phase 3)
```c++
std::vector<std::string> TrojanMap::TrojanPath(std::vector<std::string> &location_names)
```

Using TSP helper function to calcualte the shortest path permutation. Then, using Dijkstra to calculate shortest path. and push onto res.

The time complexity is O(N!), where N is the number of locations.

## Item 12: Check the existence of the path with a constrained gas tank (Phase 3)

```c++
// Takes in a vector of queries. Each query consists of a pair: <tank_capacity, [source, destination]>.
// Returns the result of each query in a vector.
std::vector<bool> Queries(const std::vector<std::pair<double, std::vector<std::string>>> &q);
```

CalculateShortestPath_Dijkstra_helper: Given 2 locations, return the shortest path with limitation from gas tank. This helper function is almost the same as CalculateShortestPath_Dijkstra. But a if section. If the distance between neighbor and current node is larger than gan tank, skip this neighbor.

The time complexity is O(N), where N is the number of nodes in graph.
