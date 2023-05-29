#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"


TEST(TrojanMapStudentTest, Test1) {
  EXPECT_EQ(true, true);
}


TEST(TrojanMapTest, Autocomplete) {
  TrojanMap m;

  
  // Test the simple case
  auto names = m.Autocomplete("Chi");
  std::unordered_set<std::string> gt = {"Chick-fil-A", "Chipotle", "Chinese Street Food"}; // groundtruth for "Ch"
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  //empty
  names = m.Autocomplete("");
  success = 0;
  int count=0;
  for (auto& n: names) {
    
    count++;
    EXPECT_EQ(gt.count(n) > 0, false) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  std::cout<<count<<std::endl;
  EXPECT_EQ(success, 0);

  // Test the lower case
  names = m.Autocomplete("chi");
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the lower and upper case 
  names = m.Autocomplete("cHi"); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the upper case 
  names = m.Autocomplete("CHI"); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
}

// Test FindPosition function
TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  
 
  auto position = m.GetPosition("Pico & Maple");
  std::pair<double, double> gt1(34.0348800,-118.2576900); 
  EXPECT_EQ(position, gt1);
  //Test empty
  position =  m.GetPosition("");
  std::pair<double, double> gt0(-1,-1);
  EXPECT_EQ(position, gt0);

  position = m.GetPosition("San Julian & 12th");
  std::pair<double, double> gt2(34.0342100,-118.2545900); 
  EXPECT_EQ(position, gt2);
  
  // Test Unknown
  position = m.GetPosition("XXX");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
  position = m.GetPosition("FedEx Print and Ship Center");
  std::pair<double, double> gt5(34.0252789,-118.2859130);
  EXPECT_EQ(position, gt5);
  
}

TEST(TrojanMapTest, CalculateEditDistance) {
  TrojanMap m;
  EXPECT_EQ(m.CalculateEditDistance("horse", "ros"), 3);
  EXPECT_EQ(m.CalculateEditDistance("intention", "execution"), 5);
  EXPECT_EQ(m.CalculateEditDistance("", "execution"),9 );
  EXPECT_EQ(m.CalculateEditDistance("Ralphs", "Ralphs"),0 );

}
//Test FindClosestName function
TEST(TrojanMapTest, FindClosestName) {
  TrojanMap m;
  EXPECT_EQ(m.FindClosestName("Rolphs"), "Ralphs");
  EXPECT_EQ(m.FindClosestName("Targeety"), "Target");
  EXPECT_EQ(m.FindClosestName("Starfocks"), "Starbucks");
  EXPECT_EQ(m.FindClosestName("STARBUCK"), "Starbucks");
  EXPECT_EQ(m.FindClosestName("Kcc"), "KFC");

}
TEST(TrojanMapTest,GetAllLocationsFromCategory){
  TrojanMap m;
// Test the simple case
  auto names = m.GetAllLocationsFromCategory("cafe");
  std::unordered_set<std::string> gt = {"9307516740","5261316290","4547476734","4399693642","4162647227","3810143804","4540761794","5567718696","614990288","4089614984"}; // groundtruth for "Ch"
  int success = 0;
  
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
}
TEST(TrojanMapTest,GetAllLocationsFromCategory2){
  TrojanMap m;
// Test the simple case
  auto names = m.GetAllLocationsFromCategory("theatre");
  std::unordered_set<std::string> gt = {"4399693646","4089614983","2817034895","368171514","4089614986","368171609"}; // groundtruth for "Ch"
  int success = 0;
  
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
}
TEST(TrojanMapTest,GetAllLocationsFromCategory3){
  TrojanMap m;
// Test the simple case
  auto names = m.GetAllLocationsFromCategory("museum");
  std::unordered_set<std::string> gt = {"4399693647"}; // groundtruth for "Ch"
  int success = 0;
  
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
}
TEST(TrojanMapTest, GetID) {
  TrojanMap m;
  EXPECT_EQ(m.GetID("Ralphs"), "2578244375");
  EXPECT_EQ(m.GetID("Target"), "5237417650");

}
TEST(TrojanMapTest, GetLocationRegex1) {
  TrojanMap m;
  std::set<std::string> expected_set;
  auto actual = m.GetLocationRegex(std::regex("Ammy"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(actual_set, expected_set);
}
TEST(TrojanMapTest, GetLocationRegex2) {
  TrojanMap m;
  std::set<std::string> expected_set = { "3810143804", "4162647227", "4399693642", "5261316290" };
  auto actual = m.GetLocationRegex(std::regex("Sta.?bu.+"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(expected_set, actual_set);
}
TEST(TrojanMapTest, GetLocationRegex3) {
  TrojanMap m;
  std::set<std::string> expected_set = { "5237417649"};
  auto actual = m.GetLocationRegex(std::regex("Tra.?de.+"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(expected_set, actual_set);
}
// Phase 2
// Test CalculateShortestPath_Dijkstra function
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Dijkstra("KFC", "Chick-fil-A");
  std::vector<std::string> gt=m.CalculateShortestPath_Bellman_Ford("KFC", "Chick-fil-A"); // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Dijkstra("Chick-fil-A", "KFC");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra2) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Dijkstra("KFC", "Starbucks 2");
  std::vector<std::string> gt=m.CalculateShortestPath_Bellman_Ford("KFC", "Starbucks 2"); // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Dijkstra("Starbucks 2", "KFC");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra3) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Dijkstra("Massman Theatre", "Starbucks 2");
  std::vector<std::string> gt=m.CalculateShortestPath_Bellman_Ford("Massman Theatre", "Starbucks 2"); // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Dijkstra("Starbucks 2", "Massman Theatre");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "KFC");
  std::vector<std::string> gt=m.CalculateShortestPath_Dijkstra("Ralphs", "KFC"); // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Bellman_Ford("KFC", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford2) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Bellman_Ford("Massman Theatre", "KFC");
  std::vector<std::string> gt=m.CalculateShortestPath_Dijkstra("Massman Theatre", "KFC"); // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Bellman_Ford("KFC", "Massman Theatre");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford3) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Bellman_Ford("Massman Theatre", "Target");
  std::vector<std::string> gt=m.CalculateShortestPath_Dijkstra("Massman Theatre", "Target"); // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Bellman_Ford("Target", "Massman Theatre");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}
// // Test cycle detection function
TEST(TrojanMapTest, CycleDetection) {
  TrojanMap m;
  // Test case 1
  std::vector<double> square1 = {-118.297, -118.279, 34.030, 34.021};
  auto sub1 = m.GetSubgraph(square1);
  bool result1 = m.CycleDetection(sub1, square1);
  EXPECT_EQ(result1, true);

  // Test case 2
  std::vector<double> square2 = {-118.290, -118.289, 34.030, 34.020};
  auto sub2 = m.GetSubgraph(square2);
  auto result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, false);
  // Test case 3
   square2 = {-118.297, -118.283, 34.030, 34.021};
  sub2 = m.GetSubgraph(square2);
  result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, true);
  // Test case 4
   square2 = {-118.298, -118.292, 34.028, 34.021};
  sub2 = m.GetSubgraph(square2);
  result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, true);
  // Test case 5
  square2 = {-118.300, -118.298, 34.028, 34.021};
  sub2 = m.GetSubgraph(square2);
  result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, false);
  
}

TEST(TrojanMapTest, TopologicalSort) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Ralphs", "Chick-fil-A", "KFC"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, {"KFC","Chick-fil-A"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Ralphs", "KFC","Chick-fil-A"};
  EXPECT_EQ(result, gt);
}
TEST(TrojanMapTest, TopologicalSort2) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Ralphs", "Chick-fil-A", "KFC", "Ahmanson Commons"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, {"KFC","Chick-fil-A"},{"KFC","Ahmanson Commons"},{"Ahmanson Commons","Chick-fil-A"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Ralphs", "KFC","Ahmanson Commons","Chick-fil-A"};
  EXPECT_EQ(result, gt);
}
TEST(TrojanMapTest, TopologicalSort3) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Ralphs", "Chick-fil-A", "KFC", "Ahmanson Commons","Target"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","KFC"}, {"KFC","Chick-fil-A"}, {"Chick-fil-A","Ahmanson Commons"},{"Ahmanson Commons","Target"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Ralphs", "KFC","Chick-fil-A","Ahmanson Commons","Target"};
  EXPECT_EQ(result, gt);
}
TEST(TrojanMapTest, TopologicalSort_cycle) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Ralphs", "Chick-fil-A", "KFC"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","KFC"}, {"Chick-fil-A","Ralphs"}, {"KFC","Chick-fil-A"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={};
  EXPECT_EQ(result, gt);
}

TEST(TrojanMapTest, TSP1) {
  TrojanMap m;
  std::vector<std::string> input{"6819019976","6820935923","2871010060","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "6820935923", "7771782316", "6816180153", "8566227783", "2871010060", "8566227656", "1873055993", "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  EXPECT_EQ(flag, true);
  
}
TEST(TrojanMapTest, TSP2) {
  TrojanMap m;
  std::vector<std::string> input{"6819019976","6820935923","122702233","2871010065","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "1873055993", "8566227656", "2871010065", "122702233", "6816180153", "7771782316", "6820935923", "6819019976" }; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  EXPECT_EQ(flag, true);
  
}
TEST(TrojanMapTest, TSP3) {
  TrojanMap m;
  std::vector<std::string> input{"6819019976","2871010068","122702233","2871010065","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "2871010068", "2871010065", "122702233", "7771782316", "6816180153", "8566227656", "1873055993", "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  EXPECT_EQ(flag, true);
  
}


TEST(TrojanMapTest, TSP4) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","2871010060","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "6820935923", "7771782316", "6816180153", "8566227783", "2871010060", "8566227656", "1873055993", "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}
TEST(TrojanMapTest, TSP5) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","2871010065","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "1873055993", "8566227656", "2871010065", "122702233", "6816180153", "7771782316", "6820935923", "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}
TEST(TrojanMapTest, TSP6) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","2871010068","122702233","2871010065","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "2871010068", "2871010065", "122702233", "7771782316", "6816180153", "8566227656", "1873055993", "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}
TEST(TrojanMapTest, TSP7) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","2871010060","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "6820935923", "7771782316", "6816180153", "8566227783", "2871010060", "8566227656", "1873055993", "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}
TEST(TrojanMapTest, TSP8) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","2871010065","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "1873055993", "8566227656", "2871010065", "122702233", "6816180153", "7771782316", "6820935923", "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}



TEST(TrojanMapTest, TSP9) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}
TEST(TrojanMapTest, TSP10) {
  TrojanMap m;
  
  std::vector<std::string> input{"4547476733","4547476733","4547476733","4547476733","4547476733","4547476733","4547476733","4547476733"
       }; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"4547476733","4547476733"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, FindNearby) {
  TrojanMap m;
  
  auto result = m.FindNearby("supermarket", "Ralphs", 10, 10);
  std::vector<std::string> ans{"5237417649", "6045067406", "7158034317"};
  EXPECT_EQ(result, ans);
}
TEST(TrojanMapTest, FindNearby2) {
  TrojanMap m;
  
  auto result = m.FindNearby("supermarket", "Ralphs", 0.1, 10);
  std::vector<std::string> ans{};
  EXPECT_EQ(result, ans);
}
TEST(TrojanMapTest, FindNearby3) {
  TrojanMap m;
  
  auto result = m.FindNearby("supermarket", "Target", 100, 10);
  std::vector<std::string> ans={"5237417649", "6045067406", "2578244375", "7158034317" };
  EXPECT_EQ(result, ans);
}

// Test CalculateShortestPath_TrojanPath function
TEST(TrojanMapTest, CalculateShortestPath_TrojanPath) {
  TrojanMap m;
  
  // Test for Ralphs, KFC and Chick-fil-A 
  std::vector<std::string> input = {"KFC", "Ralphs", "Chick-fil-A"};
  auto path = m.TrojanPath(input);
  std::vector<std::string> gt{
      "2578244375","4380040154","4380040158","4380040167","6805802087","8410938469","6813416131",
      "7645318201","6813416130","6813416129","123318563","452688940","6816193777","123408705",
      "6816193774","452688933","452688931","123230412","6816193770","6787470576","4015442011",
      "6816193692","6816193693","6816193694","3398621886","3398621887","6816193695","5690152756",
      "6804883324","3398621888","6813416123","6813416171","6807536647","6807320427","6807536642",
      "6813416166","7882624618","7200139036","122814440","6813416163","7477947679","7298150111",
      "6787803640","6807554573","2613117890","4835551096","4835551101","4835551097","4835551100",
      "3088547686","4835551100","4835551099","4835551098","6813565307","6813565306","6813565305",
      "6813565295","6813565296","3402814832","4835551107","6813379403","6813379533","3402814831",
      "6813379501","3402810298","6813565327","3398574883","6813379494","6813379495","6813379544",
      "6813379545","6813379536","6813379546","6813379547","6814916522","6814916523","1732243620",
      "4015372469","4015372463","6819179749","1732243544","6813405275","348121996","348121864",
      "6813405280","1472141024","6813411590","216155217","6813411589","1837212103","1837212101",
      "6814916516","6814916515","6820935910","4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  input = {"Ralphs", "Chick-fil-A", "KFC"};
  path = m.TrojanPath(input);
  EXPECT_EQ(path, gt);

  input = {"Ralphs", "KFC", "Chick-fil-A"};
  path = m.TrojanPath(input);
  EXPECT_EQ(path, gt);

}
TEST(TrojanMapTest, Queries) {
  TrojanMap m;
  std::vector<std::pair<double, std::vector<std::string>>> input {{0.05, {"Target", "Ralphs"}},
                                                                  {0.01, {"Ralphs", "Target"}},
                                                                  {0.02, {"KFC", "Target"}},
                                                                  {999, {"dummy", "dummy"}}};
  auto actual = m.Queries(input);
  std::vector<bool> expected {true, false, false, false};
  EXPECT_EQ(expected, actual);
}