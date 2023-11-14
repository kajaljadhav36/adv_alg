#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include <chrono>

using namespace std::chrono;

// Add your name and blazer id here
std::string name = "Rahul Saini";
std::string blazer_id = "sainir";

/* For all questions, please do not hard-code your algorithms for testing inputs.
You code should work with any input with arbitrary sizes. If you hard-code your algorithms, 10 points
will be deduced per question.

/*
Question 1 (20 points): Implement a dyanamic programming algorithm to solve the Rod Cutting Problem.
Input:
price_table: market prices of rod of different lengths
rod_length: length of given rod
Output:
std::vector<int>: a series of rod lengths after cut that provide the maximum profit
The sum of all lengths should equal to rod_length.
Lengths in vector can be in any order.
Example:
Given price_table = {1, 2, 8, 9} and rod_length = 4.
The algorithm should return a set of length including {2, 2}
*/
std::vector<int> rod_cutting_problem(std::vector<int> price_table, int rod_length)
{
  // Implement your algorithm here...
  std::vector<int> revenue(rod_length + 1);
  std::vector<int> result(2);
  revenue[0] = 0;
  for (int i = 1; i <= rod_length; i++)
  {
    int max_revenue = INT_MIN;
    for (int j = 1; j <= i; j++)
    {
      if (max_revenue < price_table[j - 1] + revenue[i - j])
      {
        max_revenue = price_table[j - 1] + revenue[i - j];
        result.insert(result.begin(), j);
        result.insert(result.begin() + 1, i - j);
      }
    }

    revenue[i] = max_revenue;
  }
  return {result[0], result[1]}; // should be replaced with your result
}

/*
Question 2 (20 points): Implement a dyanamic programming algorithm to solve the Maximum Subarray Problem.
Input:
A: input array containing a series of integers
Output:
std::vector<int>: a vector of intergers containing two intergers representing the start and end index of the maximum subarray
Index starts from 0.
Example:
Given array A = {-23 18 20 -7 12}
The algorithm should return two indices {1, 4}
*/
std::vector<int> maximum_subarray(std::vector<int> A)
{
  // Implement your algorithm here...
  int n = A.size();
  int sum[n];
  sum[0] = A[0];

  for (int i = 1; i < n; i++)
  {
    if (A[i] < sum[i - 1] + A[i])
    {
      sum[i] = sum[i - 1] + A[i];
    }
    else
    {
      sum[i] = A[i];
    }
  }
  int maxSum = INT_MIN;
  int maxSumIndex = -1;
  int minSum = INT_MAX;
  int minSumIndex = -1;
  for (int i = 0; i < n; i++)
  {
    if (minSum > sum[i])
    {
      minSum = sum[i];
      minSumIndex = i;
    }
    if (maxSum < sum[i])
    {
      maxSum = sum[i];
      maxSumIndex = i;
    }
  }
  return {minSumIndex + 1, maxSumIndex}; // should be replaced with your result
}

/*
Question 3 (20 points): Implement a dyanamic programming algorithm to solve the Matrix Chain Product Problem.
Input:
A: input array containing a series of matrix dimensions
For N matrices, the total number of dimensions is N+1 and the total number of multiplications is N-1
Output:
std::vector<int>: a vector of intergers containing N-1 intergers representing the order of the multiplications (order starts from 1)
e.g., 1 presents the first multiplication and N-1, represents the last multiplication.
Example:
Given 3 matrics, the dimension array = {100, 2, 50, 6} representing matrix A1(100*2), A2(2*50), A3(50*6).
The algorithm should return two intergers for the 2 matrix multiplications {2, 1} i.e., A1*(A2*A3)
*/
std::function<void(std::vector<int> &, std::vector<std::vector<int>> &, int, int, int)> traceOrder = [](std::vector<int> &order, std::vector<std::vector<int>> &s, int i, int j, int n)
{
  if (i == j)
  {
    return;
  }
  order.push_back(s[i][j]);
  traceOrder(order, s, i, s[i][j], n);
  traceOrder(order, s, s[i][j] + 1, j, n);
};
std::vector<int> matrix_chain_product(std::vector<int> matrix_dimensions)
{
  // Implement your algorithm here...
  int n = matrix_dimensions.size();
  std::vector<std::vector<int>> m(n, std::vector<int>(n, 0));
  std::vector<std::vector<int>> s(n, std::vector<int>(n, 0));

  for (int L = 2; L < n; L++)
  {
    for (int i = 1; i < n - L + 1; i++)
    {
      int j = i + L - 1;
      m[i][j] = INT_MAX;
      for (int k = i; k < j; k++)
      {
        int cost = m[i][k] + m[k + 1][j] + matrix_dimensions[i - 1] * matrix_dimensions[k] * matrix_dimensions[j];
        if (cost < m[i][j])
        {
          m[i][j] = cost;
          s[i][j] = k;
        }
      }
    }
  }

  std::vector<int> order;
  traceOrder(order, s, 1, n - 1, n);

  std::reverse(order.begin(), order.end());
  return order; // should be replaced with your result
}

/*
Question 4 (20 points): Implement a dyanamic programming algorithm to solve the 0/1 Knapsack Problem.
Input:
Two input arrays containing a series of weights and profits
An integer K representing the knapsack capacity.
Output:
std::vector<int>: a 0/1 vector of indicating which items are selected (0: not selected; 1: selected)
Example:
Given 4 items with weight = {5, 4, 6, 3} and profit = [10, 40, 30, 50]
The algorithm should return array = {0, 1, 0, 1} represeting the second and the last item are selected.
*/
std::vector<int> SelectKnapSackItems(std::vector<std::vector<int>> s, std::vector<int> weight, int K)
{
  std::vector<int> result;
  int i = s.size() - 1;
  int j = K - 1;

  while (i > 0 && j >= 0)
  {
    if (s[i][j] == 1)
    {
      result.push_back(1);
      j -= weight[i - 1];
      i--;
    }
    else
    {
      result.push_back(0);
      i--;
    }
  }

  std::reverse(result.begin(), result.end());
  return result;
}
std::vector<int> zero_one_knapsack(std::vector<int> weight, std::vector<int> profit, int K)
{
  // Implement your algorithm here...
  int n = weight.size() + 1;
  std::vector<std::vector<int>> m(n, std::vector<int>(n, 0));
  std::vector<std::vector<int>> s(n, std::vector<int>(n, 0));

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j <= K; j++)
    {
      if (i == 0 || j == 0)
      {
        m[i].insert(m[i].begin() + j, 0);
        s[i].insert(s[i].begin() + j, 0);
      }
      else if (weight[i - 1] > j)
      {
        m[i].insert(m[i].begin() + j, m[i - 1][j]);
        s[i].insert(s[i].begin() + j, 0);
      }
      else
      {
        int PI = profit[i - 1] + m[i - 1][j - weight[i - 1]];
        int PE = m[i - 1][j];

        if (PI >= PE)
        {
          m[i].insert(m[i].begin() + j, PI);
          s[i].insert(s[i].begin() + j, 1);
        }
        else
        {
          m[i].insert(m[i].begin() + j, PE);
          s[i].insert(s[i].begin() + j, 0);
        }
      }
    }
  }

  return SelectKnapSackItems(s, weight, K + 1); // should be replaced with your result
}

/*
Question 5 (20 points): Implement the Radix sort algorithm. For sorting each digit you should use counting sort.
Input:
An input arrays containing a series of integers. Each interger has maximum K digits. The range of each digit is from 0 to 9.
Note that some integers may have less than K digits.
Output:
std::vector<int>: sorted array
Example:
Given array = {15, 24, 26, 3} and K = 2
The algorithm should return sorted array  {3, 15, 24, 26}.
*/
void counting_sort(std::vector<int> &A, int exp, int range)
{
  int n = A.size();
  std::vector<int> output(n, 0);
  std::vector<int> count(range + 1, 0);

  for (int i = 0; i < n; i++)
  {
    int index = (A[i] / exp) % 10;
    count[index]++;
  }
  for (int i = 0; i <= range; i++)
  {
    count[i] += count[i - 1];
  }

  for (int i = n - 1; i >= 0; i--)
  {
    int index = (A[i] / exp) % 10;
    output[count[index] - 1] = A[i];
    count[index]--;
  }
  for (int i = 0; i < n; i++)
  {
    A[i] = output[i];
  }
}
std::vector<int> radix_sort(std::vector<int> A, int K)
{
  // Implement your algorithm here...
  int exp = 1;
  for (int i = 0; i < K; i++)
  {
    for (int max_num = *max_element(A.begin(), A.end()); max_num / exp > 0; exp *= 10)
      counting_sort(A, exp, 10);
    exp *= 10;
  }
  return A; // should be replaced with your result
}

/*
Question 6 (20 points): Implement the activity selection algorithm using greedy appraoch.
Input:
Two input arrays containing a series of start time and finish time
Output:
std::vector<int>: a 0/1 vector of indicating which activities are selected (0: not selected; 1: selected)
Example:
Given N=4 items with start time = {1, 3, 0, 5, 8, 5} and finish time = [2, 4, 6, 7, 9, 9]
The algorithm should return array =  {1, 1, 0, 1, 1, 0} represeting the 4 activites: (1, 2), (3, 4), (5, 7), (8, 9) are selected.
*/
std::vector<int> activity_selection(std::vector<int> start_time, std::vector<int> finish_time)
{
  // Implement your algorithm here...
  int n = start_time.size();
  std::vector<int> A(n, 0);
  std::vector<int> indices(n);
  for (int i = 0; i < n; i++)
    indices[i] = i;

  std::sort(indices.begin(), indices.end(), [&finish_time](int a, int b)
            { return finish_time[a] < finish_time[b]; });

  A[indices[0]] = 1;
  int k = 0;
  for (int i = 1; i < n; i++)
  {
    if (start_time[indices[i]] >= finish_time[indices[k]])
    {
      A[indices[i]] = 1;
      k = i;
    }
  }
  return A; // should be replaced with your result
}

/* ########### DO NOT MODIFY CODE BELOW THIS LINE ############# */

bool verify_rod_cutting(std::vector<int> price_table, std::vector<int> result, int true_result)
{
  int sum = 0;
  for (int l : result)
  {
    sum += price_table[l - 1];
  }
  return true_result == sum;
}

bool verify_max_subarray(std::vector<int> A, std::vector<int> result, int true_result)
{
  int sum = 0;
  for (int i = result[0]; i <= result[1]; i++)
  {
    sum += A[i];
  }
  return true_result == sum;
}

bool verify_matrix_chain(std::vector<int> result, std::vector<int> true_result)
{
  for (int i = 0; i < true_result.size(); i++)
  {
    if (result[i] != true_result[i])
    {
      return false;
    }
  }
  return true;
}

bool verify_zero_one_knapsack(std::vector<int> weight, std::vector<int> profit, std::vector<int> result, int true_result, int K)
{
  int total_weight = 0;
  int total_profit = 0;
  for (int i = 0; i < result.size(); i++)
  {
    if (result[i])
    {
      total_weight += weight[i];
      total_profit += profit[i];
    }
  }
  return total_weight <= K && total_profit == true_result;
}

bool verify_radix_sort(std::vector<int> result, std::vector<int> true_result)
{
  for (int i = 0; i < true_result.size(); i++)
  {
    if (result[i] != true_result[i])
    {
      return false;
    }
  }
  return true;
}

bool verify_activity_selection(std::vector<int> result, std::vector<int> true_result)
{
  for (int i = 0; i < true_result.size(); i++)
  {
    if (result[i] != true_result[i])
    {
      return false;
    }
  }
  return true;
}

int main()
{

  std::vector<int> result;
  int sum;
  bool pass;
  time_point<std::chrono::high_resolution_clock> start, stop;
  double duration;

  std::cout << "Name: " << name << " Blazer ID: " << blazer_id << "\n";

  std::cout << "---------- Rod Cutting Problem ---------\n";
  std::vector<int> price_table_1 = {1, 5, 8, 9};
  result = rod_cutting_problem(price_table_1, price_table_1.size());
  pass = verify_rod_cutting(price_table_1, result, 10);
  std::cout << "Case 1: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;
  std::vector<int> price_table_2 = {2, 3, 6, 9, 10, 17, 17};
  result = rod_cutting_problem(price_table_2, price_table_2.size());
  pass = verify_rod_cutting(price_table_2, result, 19);
  std::cout << "Case 2: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;

  std::cout << "------ Maximum Subarray Problem ------\n";
  std::vector<int> array_1 = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
  result = maximum_subarray(array_1);
  pass = verify_max_subarray(array_1, result, 43);
  std::cout << "Case 1: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;
  std::vector<int> array_2 = {-2, -3, 4, -1, -2, 1, 5, -3};
  result = maximum_subarray(array_2);
  pass = verify_max_subarray(array_2, result, 7);
  std::cout << "Case 2: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;

  std::cout << "---------------------- Matrix Chain Product ---------------------\n";
  std::vector<int> matrix_dimensions_1 = {100, 2, 50, 6};
  result = matrix_chain_product(matrix_dimensions_1);
  pass = verify_matrix_chain(result, {2, 1});
  std::cout << "Case 1: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;
  std::vector<int> matrix_dimensions_2 = {100, 60, 70, 30, 100};
  result = matrix_chain_product(matrix_dimensions_2);
  pass = verify_matrix_chain(result, {2, 1, 3});
  std::cout << "Case 2: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;

  std::cout << "---------------------- 0/1 Knapsack Problem ---------------------\n";
  std::vector<int> weight_1 = {10, 20, 30};
  std::vector<int> profit_1 = {60, 100, 120};
  result = zero_one_knapsack(weight_1, profit_1, 50);
  pass = verify_zero_one_knapsack(weight_1, profit_1, result, 220, 50);
  std::cout << "Case 1: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;
  std::vector<int> weight_2 = {5, 4, 6, 3};
  std::vector<int> profit_2 = {10, 40, 30, 50};
  result = zero_one_knapsack(weight_2, profit_2, 10);
  pass = verify_zero_one_knapsack(weight_2, profit_2, result, 90, 10);
  std::cout << "Case 2: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;

  std::cout << "---------------------- Radix Sort ---------------------\n";
  array_1 = {23, 12, 65, 89, 62, 38, 48};
  result = radix_sort(array_1, 2);
  pass = verify_radix_sort(result, {12, 23, 38, 48, 62, 65, 89});
  std::cout << "Case 1: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;
  array_2 = {1047, 2992, 9473, 7362, 1938, 4845, 3838, 5693, 9128};
  result = radix_sort(array_2, 4);
  pass = verify_radix_sort(result, {1047, 1938, 2992, 3838, 4845, 5693, 7362, 9128, 9473});
  std::cout << "Case 2: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;

  std::cout << "---------------------- Activity Selection Problem ---------------------\n";
  std::vector<int> start_1 = {1, 3, 0, 5, 8, 5};
  std::vector<int> finish_1 = {2, 4, 6, 7, 9, 9};
  result = activity_selection(start_1, finish_1);
  pass = verify_activity_selection(result, {1, 1, 0, 1, 1, 0});
  std::cout << "Case 1: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;
  std::vector<int> start_2 = {4, 3, 2, 5, 1, 3, 6, 1, 7, 4};
  std::vector<int> finish_2 = {6, 6, 4, 7, 2, 5, 7, 3, 9, 7};
  result = activity_selection(start_2, finish_2);
  pass = verify_activity_selection(result, {1, 0, 1, 0, 1, 0, 1, 0, 1, 0});
  std::cout << "Case 2: "
            << " Correct: " << (pass ? "Yes" : "No") << std::endl;

  return 0;
}