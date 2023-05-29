#include "trojanmap.h"

//-----------------------------------------------------
// TODO: Students should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return
 * -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string &id) { 
  if(!data.count(id)){
    return -1;
  }
  return data[id].lat;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist,
 * return -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string &id) {
  if(!data.count(id)){
    return -1;
  }
  return data[id].lon;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return
 * "NULL".
 *
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string &id) {
  if(!data.count(id)){
    return "";
  }
  return data[id].name;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return
 * an empty vector.
 *
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string &id) {
  std::vector<std::string> res;
  if(!data.count(id)){
    return {};
  }
  for(auto neighber:data[id].neighbors){
    res.push_back(neighber);

  }
  return res;
}

/**
 * GetID: Given a location name, return the id.
 * If the node does not exist, return an empty string.
 * The location name must be unique, which means there is only one node with the name.
 *
 * @param  {std::string} name          : location name
 * @return {std::string}               : id
 */
std::string TrojanMap::GetID(const std::string &name) {
  std::string res = "";
  for(const auto &element:data){
    if(element.second.name==name){
      res=element.second.id;
    }
  }
  return res;
}

/**
 * GetPosition: Given a location name, return the position. If id does not
 * exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);
  //if location is empty, return (-1,-1) 
  if(name.empty()){
    return results;
  }
  //example:
  //Chi>>Chi
  //CHI>>Chi
  //chi>>Chi
  //convert all the letter to uppercase 
  for (auto &element:name){
    element=toupper(element);
     
  }

  for(const auto &id:data){
    std::string temp=id.second.name;
    // convert temp to uppercase
    for (auto &element:temp){
    element=toupper(element);
  }
  //example: name=HON
  //"Honeybird" >>"HONEYBIRD"
  //          found^
    std::size_t found=temp.find(name);
    if(found==0){ 
      results.first=id.second.lat;
      results.second=id.second.lon;
    }
  }
  
  return results;
  

}

/**
 * CalculateEditDistance: Calculate edit distance between two location names
 * @param  {std::string} a          : first string
 * @param  {std::string} b          : second string
 * @return {int}                    : edit distance between two strings
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b) {  
  //example:
  //Chi>>Chi
  //CHI>>Chi
  //chi>>Chi
  //convert all the letter to uppercase 
  for (auto &element:a){
    element=toupper(element); 
  }
  for (auto &element:b){
    element=toupper(element);
  }
  int m = a.length();
  int n = b.length();
  // Levenshtein distance
  int dis[m+1][n+1];

  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == 0) {
        dis[i][j] = j;
      } else if (j == 0) {
        dis[i][j] = i;
      } else if (a[i-1] == b[j-1]) {
        dis[i][j] = dis[i-1][j-1];
      } else {
        dis[i][j] = 1 + std::min({dis[i-1][j], dis[i][j-1], dis[i-1][j-1]});
      }
    }
  }
  return dis[m][n];

  
}

/**
 * FindClosestName: Given a location name, return the name with the smallest edit
 * distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : the closest name
 */
std::string TrojanMap::FindClosestName(std::string name) {
  std::string tmp = ""; // Start with a dummy word
  if(name.empty()){
    return tmp;
  }
  int dis=100;
  int dis_temp=0;
  //go through every node in data and check its name
  for(const auto &id:data){
    std::string temp=id.second.name;
    dis_temp=CalculateEditDistance(temp,name);
    if(dis>dis_temp){
      dis=dis_temp;
      tmp=temp;
    }
    if(dis==0){
      return tmp;
    }
  }
  
  
  return tmp;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name) {
  std::vector<std::string> results;
  if(name.empty()){
    return results;
  }
  //example:
  //Chi>>Chi
  //CHI>>Chi
  //chi>>Chi
  //convert all the letter to uppercase 
  for (auto &element:name){
    element=toupper(element);
     
  }
  //load the data form csv file, name_data is a vector. The k th element of vector is the k+2 line of data.csv file.
  //example: name_data={"the first line","the second line",...,"the last line"}
  // std::vector<std::string> name_data=ReadLocationsFromCSVFile("/Users/huangjie/spring2023_trojanmap-jhuang59/src/lib/data.csv");
  
  //go through every node in data and check its name
  for(const auto &id:data){
    std::string temp=id.second.name;
    // convert temp to uppercase
    for (auto &element:temp){
    element=toupper(element);
  }
  //example: name=HON
  //"Honeybird" >>"HONEYBIRD">>"HON"
  //                       found^
    std::size_t found=temp.substr(0,name.length()).find(name);
    if(found==0){ 
      results.push_back(id.second.name);
    }
  }
  
  
  return results;
}

/**
 * GetAllCategories: Return all the possible unique location categories, i.e.
 * there should be no duplicates in the output.
 *
 * @return {std::vector<std::string>}  : all unique location categories
 */
std::vector<std::string> TrojanMap::GetAllCategories() {
  std::unordered_set <std::string> result;
  std::unordered_set <std::string> temp;
  for(const auto &node:data){
    temp=node.second.attributes;
    result.insert(temp.begin(), temp.end());
}
std::vector<std::string> vector(result.begin(), result.end());

return vector;

}

/**
 * GetAllLocationsFromCategory: Return all the locations of the input category (i.e.
 * 'attributes' in data.csv). If there is no location of that category, return
 * (-1, -1). The function should be case-insensitive.
 *
 * @param  {std::string} category         : category name (attribute)
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetAllLocationsFromCategory(
    std::string category) {
      //ids of nodes
  std::vector<std::string> res;
  //attributes of current node
  std::unordered_set <std::string> temp;
  bool found=false;
  for(const auto &node:data){
    temp=node.second.attributes;
    for(auto element:temp){
      if(element==category){
        res.push_back(node.second.id);
        found=true;
    }
    }
}
if(found){
  return res;
}else{
  res=std::vector<std::string> {"(-1,-1)"};
  return res;
}
}

/**
 * GetLocationRegex: Given the regular expression of a location's name, your
 * program should first check whether the regular expression is valid, and if so
 * it returns all locations that match that regular expression.
 *
 * @param  {std::regex} location name      : the regular expression of location
 * names
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetLocationRegex(std::regex location) {
  std::vector<std::string> res;
  try
  {
    location;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return {};
  }
  for(const auto &node:data){
    std::string temp=node.second.name;
    if (std::regex_match (temp, location )){
      res.push_back(node.first);
    }
  }
  return res;

}

/**
 * CalculateDistance: Get the distance between 2 nodes.
 * We have provided the code for you. Please do not need to change this function.
 * You can use this function to calculate the distance between 2 nodes.
 * The distance is in mile.
 * The distance is calculated using the Haversine formula.
 * https://en.wikipedia.org/wiki/Haversine_formula
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id,
                                    const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2), 2.0) + cos(a.lat * M_PI / 180.0) *
                                           cos(b.lat * M_PI / 180.0) *
                                           pow(sin(dlon / 2), 2.0);
  double c = 2 * asin(std::min(1.0, sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations
 * inside the vector.
 * We have provided the code for you. Please do not need to change this function.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  if(path.empty()){
    return 0;
  }
  for (int i = 0; i < int(path.size()) - 1; i++) {
    sum += CalculateDistance(path[i], path[i + 1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path
 * which is a list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start node's name
 * @param  {std::string} location2_name     : goal node's name
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  std::vector<std::string> path;
  
  //pair(id,distance)
  std::unordered_map<std::string,double> distance;
  //previous node in the shortest route. example(id of current node, id of previous node)
  std::unordered_map<std::string,std::string> prev;
  //(distance to root,id) priority queue compare the value of the first element
  std::priority_queue<std::pair<double, std::string>,std::vector<std::pair<double, std::string>>,std::greater<std::pair<double, std::string>>> pq;
  //the id of current node
  std::string id;
  //id of start node
  std::string id_start=GetID(location1_name);
  //id of end node
  std::string id_end=GetID(location2_name);
  //initialize distance, start node is 0, others are max value
  for ( auto &element:data){
    if(element.first==id_start){
      distance.insert(std::pair<std::string,double> (id_start,0));
      continue;
    }
    distance.insert(std::pair<std::string,double> (element.first,std::numeric_limits<double>::max()));
  }
  //push start node into queue
  pq.push(std::pair<double, std::string> (0, id_start));
  //pop the min distance node from queue, and go through its neighbors and relax the distance of them
  while (!pq.empty())
  {
    id=pq.top().second;
    if(id==id_end){
      break;
    }
    //if the distance was already relaxed, passing it
    if(pq.top().first>distance[id]){
      pq.pop();
      continue;
    }
    pq.pop();
    //neighber: current node's neighbor,string,id
      for(auto neighber:data[id].neighbors){
        //temp:the distance between current node and its neighbor
        double temp=CalculateDistance(neighber,id)+distance[id];
        //if find shorter distance, updating it
        if (temp < distance[neighber]){
          distance[neighber]=temp;
          pq.push(std::pair<double, std::string> (temp, neighber));
          if(prev.count(neighber)){
            prev[neighber]=id;
          }else{
            prev.insert(std::pair<std::string,std::string> (neighber,id));
          }
        }
      }

  }
  //if goal node's id doesn't exists in prev, didn't find route
  if(!prev.count(id_end)){
    return {};
  }

  std::string path_id=id_end;
  while (path_id!=id_start)
  { 
    path.insert(path.begin(),path_id);
    path_id=prev[path_id];
  }
  path.insert(path.begin(),id_start);
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest
 * path which is a list of id. Hint: Do the early termination when there is no
 * change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name) {
  std::vector<std::string> path;
  //distance to start node
  std::unordered_map<std::string,double>  distance;
  //id of start node
  std::string id_start=GetID(location1_name);
  //id of end node
  std::string id_end=GetID(location2_name);
  //previous node in the shortest route. example(id of current node, id of previous node)
  std::unordered_map<std::string,std::string> prev;
  
  bool update=false;
  //initiliza distance of each node. distance of start node is 0, others are maximum
  for ( auto &element:data){
    if(element.first==id_start){
      distance.insert(std::pair<std::string,double> (id_start,0));
      continue;
    }
    distance.insert(std::pair<std::string,double> (element.first,std::numeric_limits<double>::max()));
  }
  //do the for loop at most n-1 times, the worst case is n-1 times
  for(int i=0;i<data.size();i++){
    update=false;
   //current: nodes in whole dataset
    for(auto current:data){
      //neighbor: neighber of each node
      for(auto neighbor:current.second.neighbors){
        //temp:distance from current node to statr point
        double temp=distance[neighbor]+CalculateDistance(neighbor,current.first);
        //update the distance 
        if(temp<distance[current.first]){
          distance[current.first]=temp;
          //if already exists, update. otherwise, create
          if(prev.count(neighbor)){
            prev[current.first]=neighbor;
          }else{
            prev.insert(std::pair<std::string,std::string> (current.first,neighbor));
          }
          //distance change, continue to update
          update=true;
        }
      }
    }
    // early stop, if distance doesn't change any more.
    if(!update){
      break;
    }
  }
  std::string path_id=id_end;
  while (path_id!=id_start)
  { 
    path.insert(path.begin(),path_id);
    path_id=prev[path_id];
  }
  path.insert(path.begin(),id_start);
  return path;
}
//helper function, copy all elements in vector but i th. 
std::vector<std::string> TrojanMap::copyallelementbutIth(std::vector<std::string> nums,int i){
  std::vector<std::string> copy;
  for (int j=0;j<nums.size();j++){
    if(j==i){
      continue;
    }
    copy.push_back(nums[j]);
  }
  return copy;
}
//helper function, input:std::vector<std::string> nums, output:vector of vectorstd::vector <std::vector<std::string>>
std::vector<std::vector<std::string>> TrojanMap::permutation_recursive(std::vector<std::string> &nums){
  std::vector<std::vector<std::string>> result;
  if(nums.size()==1){
    result.push_back(nums);
    return result;
  }
  for(int i=0;i<nums.size();i++){
    std::vector<std::string> next_nums=copyallelementbutIth(nums,i);
    auto next_result=permutation_recursive(next_nums);
    for (auto &e:next_result){
      e.insert(e.begin(),nums[i]);
      result.push_back(e);

    }
  }
  return result;
}



/**
 * Traveling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path, 
 *                                                                      for example: {10.3, {{0, 1, 2, 3, 4, 0}, {0, 1, 2, 3, 4, 0}, {0, 4, 3, 2, 1, 0}}},
 *                                                                      where 10.3 is the total distance, 
 *                                                                      and the first vector is the path from 0 and travse all the nodes and back to 0,
 *                                                                      and the second vector is the path shorter than the first one,
 *                                                                      and the last vector is the shortest path.
 */
// Please use brute force to implement this function, ie. find all the permutations.
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::vector<std::vector<std::string>> routes={};
  std::vector<std::vector<std::string>> permutations={};
  double distance=DBL_MAX;
  double temp;
  std::string first_location;
  //check input
  if(location_ids.size()<2){
    return {};
  }
  first_location=location_ids[0];
  location_ids.erase(location_ids.begin());
  permutations=permutation_recursive(location_ids);
  for(auto route:permutations){
    route.push_back(first_location);
    route.insert(route.begin(),first_location);
    temp=CalculatePathLength(route);
    if(temp<distance){
      distance=temp;
      routes.push_back(route);
      continue;
    }
    routes.insert(routes.begin(),route);
  }
  records=std::pair<double,std::vector<std::vector<std::string>>>(distance,routes);
  return records;
}
//example:  1             2        3          4
//       2    3    4   1  3  4   1  2  4   1  2  3
//      3 4  2 4  
//      4 3  4   
//TSP helper function
// @param  {std::string} start: start node
// @param  {std::vector<std::string>} location_list : a list of location's id needs to visit
// @param  {std::vector<std::string>} curr_path : a list of location's id
// @param  {double} min_cost : current min cost of path
// @param  {std::vector<std::string>} min_path: a list of location's id

void TrojanMap::TSP_aux(std::string start, std::vector<std::string> &location_list,std::vector<std::string> &curr_path, double &min_cost, std::vector<std::string> &min_path){
  //cost of current path plus start nodes
  double final_cost;
  if(curr_path.empty()){
     final_cost=0;
  }else{
    final_cost=CalculatePathLength(curr_path)+CalculateDistance(start,curr_path[0])+CalculateDistance(curr_path[curr_path.size()-1],start);
  }
  //if reach at leaf, store the current path and update the min cost
  if(curr_path.size()==location_list.size()){
    
    if(final_cost<min_cost){
      min_cost=final_cost;
      min_path=curr_path;
    }
    return;
  }
  //early backtracking. if current cost is larger than min cost, don't need to go deeper and return to upper
  if(final_cost>min_cost){
    return;
  }
  //go through all nodes in location list, add one non-curr_path node into curr_path and go deeper
  for(auto &location:location_list){
    if(std::find(curr_path.begin(),curr_path.end(),location)!=curr_path.end()){
      continue;
    }
    //push one non-curr_path node
    curr_path.push_back(location);
    //go deeper
    TSP_aux(start,location_list,curr_path,min_cost,min_path);
    //remove the node just push onto
    curr_path.pop_back();
  }
}

// Please use backtracking to implement this function
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  //initialize min_cost==maximum
  double min_cost=DBL_MAX;
  //store paths
  std::vector<std::vector<std::string>> routes;
  //current path
  std::vector<std::string> curr_path={};
  //minimum length path
  std::vector<std::string> min_path;
  //start node
  std::string first_location;
  //check input
  if(location_ids.size()<2){
    return {};
  }
  first_location=location_ids[0];
  //remove the start node from location list
  location_ids.erase(location_ids.begin());
  //call helper function
  TSP_aux(first_location,location_ids,curr_path,min_cost,min_path);
  //push start point onto the end of path, insert start node into the start of path
  min_path.push_back(first_location);
  min_path.insert(min_path.begin(),first_location);
  routes.push_back(min_path);
  records=std::pair<double,std::vector<std::vector<std::string>>>(min_cost,routes);

  return records;
}

// Hint: https://en.wikipedia.org/wiki/2-opt
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_2opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  //store paths
  std::vector<std::vector<std::string>> routes;
  //current path
  std::vector<std::string> curr_path={};
  std::unordered_set<std::string> unique_locations;
  //push locations onto current path
  for(auto &location:location_ids){
  if(unique_locations.find(location) == unique_locations.end()){
    unique_locations.insert(location);
    curr_path.push_back(location);
  }
}
  // check duplicates in input
  // for(auto location:location_ids){
  //   std::vector<std::string>::iterator it=std::find(curr_path.begin(),curr_path.end(),location);
  //   if(location==location_ids[0]){
  //     continue;
  //   }
  //   if(it!=curr_path.end()){
  //     continue;
  //   }else{
  //     curr_path.push_back(location);
  //   }
  // }
  
  //push start node onto the end of current path
  curr_path.push_back(location_ids[0]);
  // check input. there should be more than 3 locations in input
  
  if(curr_path.size()<=2){
    routes.push_back(curr_path);
    return records=std::pair<double,std::vector<std::vector<std::string>>>(CalculatePathLength(curr_path),routes);
  }
  
  //The cost of current path
  double curr_cost=CalculatePathLength(curr_path);
  //improvement flag, set improvement=true if found length less than 0
  bool improvement=true;
  //example:{0,1,2,3,4,5}
  //          i^  j^
  //length=distance(0,3)-distance(0,1)+distance(1,4)-distance(3,4)
  double length=0;
  //if improvement==true,do the while loop
  while(improvement){
    improvement=false;
    //example:{0,1,2,3,4,5,6,7,8,9,10}
    //           ^i start form second node
    //                           ^j stop at the last second node
    //don't touch the first and the last node, they are start nodes
    for(int i=1;i<curr_path.size()-2;i++){
      for(int j=i+1;j<curr_path.size()-1;j++){
        length=-CalculateDistance(curr_path[i-1],curr_path[i])-CalculateDistance(curr_path[j],curr_path[j+1])+CalculateDistance(curr_path[i],curr_path[j+1])+CalculateDistance(curr_path[i-1],curr_path[j]);
        //to avoid ifinite loop
        if(length<-1e-15){
          //if the length less than 0, reverse the order
          //example:{0,1,2,3,4,5,6,7,8,9,10}
          //            i^      j^
          //reversed:{0,1,6,5,4,3,2,7,8,9,10}
          std::reverse(curr_path.begin()+i,curr_path.begin()+j+1);
          curr_cost=curr_cost+length;
          routes.push_back(curr_path);
          improvement=true;
        }
      }
    }
  }
  
  records=std::pair<double,std::vector<std::vector<std::string>>>(CalculatePathLength(curr_path),routes);
  return records;
}

// This is optional
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_3opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 * We have provided the code for you. Please do not need to change this function.
 * Example: 
 *   Input: "topologicalsort_locations.csv"
 *   File content:
 *    Name
 *    Ralphs
 *    KFC
 *    Chick-fil-A
 *   Output: {"Ralphs", "KFC", "Chick-fil-A"}
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(
    std::string locations_filename) {
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, word)) {
    location_names_from_csv.push_back(word);
  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 * We have provided the code for you. Please do not need to change this function.
 * Example: 
 *   Input: "topologicalsort_dependencies.csv"
 *   File content:
 *     Source,Destination
 *     Ralphs,Chick-fil-A
 *     Ralphs,KFC
 *     Chick-fil-A,KFC
 *   Output: {{"Ralphs", "Chick-fil-A"}, {"Ralphs", "KFC"}, {"Chick-fil-A", "KFC"}}
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(
    std::string dependencies_filename) {
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);
    std::vector<std::string> dependency;
    while (getline(s, word, ',')) {
      dependency.push_back(word);
    }
    dependencies_from_csv.push_back(dependency);
  }
  fin.close();
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a
 * sorting of nodes that satisfies the given dependencies. If there is no way to
 * do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(
    std::vector<std::string> &locations,
    std::vector<std::vector<std::string>> &dependencies) {
  //sorted node in topological order
  std::vector<std::string> result;
  //contain the root
  std::unordered_map<std::string,int> degree_zero;
  //visited node=true, unvisited node=false
  std::unordered_map<std::string,bool> visited;
  //last in, first out
  std::stack<std::string> stack;
  //the id of current node
  std::string id;

  std::cout<<"dependencies"<<std::endl;
  for (auto &vector:dependencies){
    for (auto &element:vector){
      std::cout<<element<<std::endl;
    }
  }
  //check input
  if(locations.empty()||dependencies.empty()){
    return std::vector<std::string>();
  }
  //push all nodes onto degree_zero and initialize visited
  std::cout<<"locations"<<std::endl;
  for(auto element:locations){
    if(degree_zero.count(element)){
      degree_zero[element]++;
    }else{
      degree_zero.emplace(element,0);
    }
    visited.emplace(element,false);
    std::cout<<element<<std::endl;
  }
//calculate the degree of location. example: degree of root=0
  for( auto element:dependencies){
     if(degree_zero.count(element[1])){
      degree_zero[element[1]]++;
    }else{
      degree_zero.emplace(element[1],1);
    }
   }
  std::cout<<"locations end"<<std::endl;
  //
  int i=0;
  std::string root;
  //if two roots exist, return empty
  for(auto roots:degree_zero){
    if(roots.second==0){
      i++;
      root=roots.first;
    }
    if(i>1){
        std::vector<std::string>();
    }
  }
  
  //push the root into stack
  stack.push(root);
  while (!stack.empty())
  {
    //pick the last node in stack
    id=stack.top();
    
    //if current node has already been visited, remove it from stack and push it onto result
    if(visited[id]){
      stack.pop();
      result.push_back(id);
      continue;
      //if current node has not been visited yet, mark it as visited and push its unvisited neighbors onto the stack.
    }else{
      visited[id]=true;
    }
      for(auto dependence:dependencies){
      if(dependence[0]==id&&visited[dependence[1]]==false){
        stack.push(dependence[1]);
      }else{
        continue;
      }
    }
    
  }

  if(result.size()!=locations.size()){
    return std::vector<std::string>();
  }
  //reverse the order of sorted node
  std::reverse(result.begin(),result.end());
  return result;
    
}

/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
  std::vector<std::string> subgraph=GetSubgraph(square);
  auto it = std::find(subgraph.begin(), subgraph.end(), id);
      if(it==subgraph.end()){
        return false;
      }


  return true;
}


/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location
 * ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square
 * area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the
 * square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  //left, right, upper, and lower bounds
  double left=square[0];
  double right=square[1];
  double upper=square[2];
  double lower=square[3];
  for (const auto &element:data){
    if(element.second.lat>upper||element.second.lat<lower){
      continue;
    }
    if(element.second.lon>right||element.second.lon<left){
      continue;
    }
    subgraph.push_back(element.first);
  }
  return subgraph;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true
 * if there is a cycle path inside the square, false otherwise.
 *
 * @param {std::vector<std::string>} subgraph: list of location ids in the
 * square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) {
  //visited node
  std::unordered_set<std::string> visited;
  std::stack<std::string> stack;
  //the id of current node
  std::string id;
  //randomly push a node into stack
  stack.push(subgraph[10]);
  while (!stack.empty())
  {
    id=stack.top();
    stack.pop();
    
    if(!visited.count(id)){
      visited.insert(id);
    }else{
      return true;
    }
    //neighbors of current node
    for(auto neighbor:data[id].neighbors){
      //if neighber is in subgraph
      if(inSquare(neighbor,square)){
        //if neighbor has not been visited
        if(!visited.count(neighbor)){
        stack.push(neighbor);
        }
      }else{
        continue;
      }
    }
  }
  

  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r,
 * find all locations in class C on the map near L with the range of r and
 * return a vector of string ids
 *
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {double} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k) {
  std::vector<std::string> res;
  //path from name to others attributesName
  std::vector<std::string> path;
  //location: ids of same category nodes
  std::vector<std::string> locations=GetAllLocationsFromCategory(attributesName);
  //(distance to root,id) priority queue compare the value of the first element
  std::priority_queue<std::pair<double, std::string>,std::vector<std::pair<double, std::string>>,std::greater<std::pair<double, std::string>>> pq;
  //length of path
  double length=DBL_MAX;

  for(auto &location:locations){
  //don't include start node 
  if(GetName(location)==name){
    continue;
  }
  //input should be name, not id
  path=CalculateShortestPath_Dijkstra(name,GetName(location));
  length=CalculatePathLength(path);
  //if length larger than r, skip it
  if(length>r){
    continue;
  }
  //push location onto min queue
  pq.push(std::pair<double,std::string> (length,location));
  }
  
  //the size of full queue
  int pq_size=pq.size();
  //pop the min distance node from queue and push onto res
  for (int i=0;i<pq_size;i++){
    if(i>=k){
      break;
    }
    res.push_back(pq.top().second);
    pq.pop();
  }

  return res;
}
//Modified TSP helper function
// @param  {std::vector<std::string>} location_list : a list of location's id needs to visit
// @param  {std::vector<std::string>} curr_path : a list of location's id
// @param  {double} min_cost : current min cost of path
// @param  {std::vector<std::string>} min_path: a list of location's id

void TrojanMap::TSP_aux_trojanpath(std::vector<std::string> &location_list,std::vector<std::string> &curr_path, double &min_cost, std::vector<std::string> &min_path){
  //cost of current path plus start nodes
  double final_cost;
  if(curr_path.empty()){
     final_cost=0;
  }else{
    final_cost=CalculatePathLength(curr_path);
  }
  //if reach at leaf, store the current path and update the min cost
  if(curr_path.size()==location_list.size()){
    
    if(final_cost<min_cost){
      min_cost=final_cost;
      min_path=curr_path;
    }
    return;
  }
  //early backtracking. if current cost is larger than min cost, don't need to go deeper and return to upper
  if(final_cost>min_cost){
    return;
  }
  //go through all nodes in location list, add one non-curr_path node into curr_path and go deeper
  for(auto &location:location_list){
    if(std::find(curr_path.begin(),curr_path.end(),location)!=curr_path.end()){
      continue;
    }
    //push one non-curr_path node
    curr_path.push_back(location);
    //go deeper
    TSP_aux_trojanpath(location_list,curr_path,min_cost,min_path);
    //remove the node just push onto
    curr_path.pop_back();
  }
}
/**
 * Shortest Path to Visit All Nodes: Given a list of locations, return the shortest
 * path which visit all the places and no need to go back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::vector<std::string>}      : the shortest path
 */
std::vector<std::string> TrojanMap::TrojanPath(std::vector<std::string> &location_names) {
    //a list of location ids
    std::vector<std::string> res;
    //ids
    std::vector<std::string> curr_path={};
    //store the path from min_path[i] to min_path[i+1]
    std::vector<std::string> temp;
    double min_cost=DBL_MAX;
    //reorder location list, min distance ids
    std::vector<std::string> min_path;
    //store locations ids
    std::vector<std::string> location_list;
    //convert names to ids
    for(auto &name:location_names){
      location_list.push_back(GetID(name));
    }
    //use TSP helper function to calcualte the shortest path permutation
    TSP_aux_trojanpath(location_list,curr_path, min_cost, min_path);
    //use Dijkstra to calculate shortest path. and push onto res
    for(int i=0;i<min_path.size()-1;i++){
      temp=CalculateShortestPath_Dijkstra(GetName(min_path[i]),GetName(min_path[i+1]));
      res.insert(res.end(),temp.begin(),temp.end()-1);
    }
    res.push_back(min_path[min_path.size()-1]);
    return res;
}
// * CalculateShortestPath_Dijkstra_helper: Given 2 locations, return the shortest path with limitation from gas tank
//  * which is a list of id. Hint: Use priority queue.
//  *
//  * @param  {std::string} location1_name     : start node's name
//  * @param  {std::string} location2_name     : goal node's name
//    @param  {int} gas_tank  : size 0f gas tank
//  * @return {std::vector<std::string>}       : path
//  */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra_helper(
    std::string location1_name, std::string location2_name, double gas_tank) {
  std::vector<std::string> path;
  
  //pair(id,distance)
  std::unordered_map<std::string,double> distance;
  //previous node in the shortest route. example(id of current node, id of previous node)
  std::unordered_map<std::string,std::string> prev;
  //(distance to root,id) priority queue compare the value of the first element
  std::priority_queue<std::pair<double, std::string>,std::vector<std::pair<double, std::string>>,std::greater<std::pair<double, std::string>>> pq;
  //the id of current node
  std::string id;
  //id of start node
  std::string id_start=GetID(location1_name);
  //id of end node
  std::string id_end=GetID(location2_name);
  double dist_neighbor;
  //initialize distance, start node is 0, others are max value
  for ( auto &element:data){
    if(element.first==id_start){
      distance.insert(std::pair<std::string,double> (id_start,0));
      continue;
    }
    distance.insert(std::pair<std::string,double> (element.first,std::numeric_limits<double>::max()));
  }
  //push start node into queue
  pq.push(std::pair<double, std::string> (0, id_start));
  //pop the min distance node from queue, and go through its neighbors and relax the distance of them
  while (!pq.empty())
  {
    id=pq.top().second;
    if(id==id_end){
      break;
    }
    //if the distance was already relaxed, passing it
    if(pq.top().first>distance[id]){
      pq.pop();
      continue;
    }
    pq.pop();
    //neighber: current node's neighbor,string,id
      for(auto neighber:data[id].neighbors){
        dist_neighbor=CalculateDistance(neighber,id);
        //if the distance between neighbor and current node is larger than gan tank, skip
        if(dist_neighbor>gas_tank){
          continue;
        }
        //temp:the distance between current node and its neighbor
        double temp=dist_neighbor+distance[id];
        //if find shorter distance, updating it
        if (temp < distance[neighber]){
          distance[neighber]=temp;
          pq.push(std::pair<double, std::string> (temp, neighber));
          if(prev.count(neighber)){
            prev[neighber]=id;
          }else{
            prev.insert(std::pair<std::string,std::string> (neighber,id));
          }
        }
      }

  }
  //if goal node's id doesn't exists in prev, didn't find route
  if(!prev.count(id_end)){
    return {};
  }
  std::string path_id=id_end;
  while (path_id!=id_start)
  { 
    path.insert(path.begin(),path_id);
    path_id=prev[path_id];
  }
  path.insert(path.begin(),id_start);
  return path;
}


/**
 * Given a vector of queries, find whether there is a path between the two locations with the constraint of the gas tank.
 *
 * @param  {std::vector<std::pair<double, std::vector<std::string>>>} Q : a list of queries
 * @return {std::vector<bool> }      : existence of the path
 */
std::vector<bool> TrojanMap::Queries(const std::vector<std::pair<double, std::vector<std::string>>>& q) {
    std::vector<bool> ans(q.size());
    std::vector<std::string> path;
    for (int i=0;i<ans.size();i++){
      path=CalculateShortestPath_Dijkstra_helper(q[i].second[0],q[i].second[1],q[i].first);
      if(path.empty()){
        ans[i]=false;
      }else{
        ans[i]=true;
      }
      
    }

    return ans;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * We have provided the code for you. Please do not need to change this function.
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0])) n.attributes.insert(word);
        if (isdigit(word[0])) n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}
