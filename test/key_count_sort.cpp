#include <utility>
#include <string>
#include <vector>

using namespace std;

const int COUNT_SIZE = 11;

void key_count_sort(vector<pair<int, string>>& std_table)
{
    int count[COUNT_SIZE] = {0};
    //��һ��
    for (auto v : std_table)
    {
        count[v.first+1]++;
    }
    //�ڶ���
    for (int i = 1; i < COUNT_SIZE; i++)
    {
        count[i] = count[i] + count[i-1];
    }
    //������
    vector<pair<int, string>> std_sort_table(std_table.size());
    for (auto v : std_table)
    {
        std_sort_table[count[v.first]] = v;
    }
    //��д
    for (int i = 0; i < std_table.size(); ++i)
    {
        std_table[i] = std_sort_table[i];
    }
}

int main()
{
    vector<pair<int, string>> std_table;
    std_talbe.push_back(make_pair(4, "str"));
    std_talbe.push_back(make_pair(3, "stj"));
    std_talbe.push_back(make_pair(3, "sti"));
    std_talbe.push_back(make_pair(1, "sto"));
    std_talbe.push_back(make_pair(2, "stp"));
    std_talbe.push_back(make_pair(2, "stk"));
    std_talbe.push_back(make_pair(4, "stl"));
    key_count_sort(std_table);
}
