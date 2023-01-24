#include <iostream>
#include <stack>
#include <functional>
#include <fstream>
#include <sys/time.h>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <cstdlib>
#include <algorithm>
using namespace std;
struct fields
{
    int index;
    string organizationID;
    string Name;
    string country;
    string website;
    string description;
    string founded;
    string industry;
    int numberOfEmployees;
};
class customer
{

public:
    vector<fields> global_vector;
    vector<fields> createRecord(int index, string organizationID, string name, string website, string country, string description, string founded, string industry, int numberOfEmployees)
    {
        fields vect;
        vect.Name = name;
        vect.index = index;
        vect.organizationID = organizationID;
        vect.country = country;
        vect.website = website;
        vect.description = description;
        vect.founded = founded;
        vect.industry = industry;
        vect.numberOfEmployees = numberOfEmployees;
        global_vector.push_back(vect);
        return global_vector;
    }
    void bubble_Sort()
    {
        for (int x = 0; x < global_vector.size() - 1; x++)
        {
            for (int y = 0; y < global_vector.size() - x - 1; y++)
            {
                if (global_vector.at(y).numberOfEmployees > global_vector.at(y + 1).numberOfEmployees)
                {
                    swap(global_vector[y],global_vector[y+1]);
                    // swap(global_vector[y].index, global_vector[y + 1].index);
                    // swap(global_vector[y].organizationID, global_vector[y + 1].organizationID);
                    // swap(global_vector[y].Name, global_vector[y + 1].Name);
                    // swap(global_vector[y].founded, global_vector[y + 1].founded);
                    // swap(global_vector[y].industry, global_vector[y + 1].industry);
                    // swap(global_vector[y].description, global_vector[y + 1].description);
                    // swap(global_vector[y].numberOfEmployees, global_vector[y + 1].numberOfEmployees);
                    // swap(global_vector[y].website, global_vector[y + 1].website);
                    // swap(global_vector[y].country, global_vector[y + 1].country);
                }
            }
        }
    }
    void  MAIN_READ_FUNCTION(int no_file,customer &obj){
if (no_file == 1)
        {
            string path = "organizations-100.csv";
            obj.Read_Data(path);
        }
        else if (no_file == 2)
        {
            obj.Read_Data("organizations-1000.csv");
        }
        else if (no_file == 3)
        {
            obj.Read_Data("organizations-10000.csv");
        }
        else if (no_file == 4)
        {
            obj.Read_Data("organizations-100000.csv");
        }
        else if (no_file == 5)
        {
            obj.Read_Data("organizations-500000.csv");
        }
}
    int findMinimum(int start, int end)
    {
        int min = global_vector[start].numberOfEmployees;
        int minIndex = start;
        for (int x = start; x < end; x++)
        {
            if (min > global_vector[x].numberOfEmployees)
            {
                min = global_vector[x].numberOfEmployees;
                minIndex = x;
            }
        }
        return minIndex;
    }
    void selection_Sort()
    {
        for (int x = 0; x < global_vector.size() - 1; x++)
        {
            int minIndex = findMinimum(x, global_vector.size());
            swap(global_vector[x], global_vector[minIndex]);
        }
    }
    void insertion_Sort()
    {
        for (int x = 1; x < global_vector.size(); x++)
        {
            int key = global_vector[x].numberOfEmployees;
            int y = x - 1;
            while (y >= 0 && global_vector[y].numberOfEmployees > key)
            {
                swap(global_vector[y + 1], global_vector[y]);
                y--;
            }
            global_vector[y + 1].numberOfEmployees = key;
        }
    }
    void merge_Sort(vector<fields> &t, int start, int end)
    {
        if (start < end)
        {
            int mid = (start + end) / 2;
            merge_Sort(global_vector, start, mid);
            merge_Sort(global_vector, mid + 1, end);
            merge(global_vector, start, mid, end);
        }
    }
    void merge(vector<fields> &arr, int start, int mid, int end)
    {
        int i = start;
        int j = mid + 1;
        queue<fields> global_vectorArr;
        while (i <= mid && j <= end)
        {
            if (arr[i].numberOfEmployees < arr[j].numberOfEmployees)
            {
                global_vectorArr.push(arr[i]);
                i++;
            }
            else
            {
                global_vectorArr.push(arr[j]);
                j++;
            }
        }
        while (i <= mid)
        {
            global_vectorArr.push(arr[i]);
            i++;
        }
        while (j <= end)
        {
            global_vectorArr.push(arr[j]);
            j++;
        }
        for (int x = start; x <= end; x++)
        {
            arr[x] = global_vectorArr.front();
            global_vectorArr.pop();
        }
    }
    vector<fields> get_vector()
    {
        return global_vector;
    }
    void Read_Data(string path)
    {
        fstream myFile;
        myFile.open(path, ios::in);
        string line;
        int index;
        string organizationID;
        string name;
        string website;
        string city;
        string country;
        string description;
        string founded;
        string industry;
        int numberOfEmployees = 0;
        int count = 0;
        string global_vector;
        while (!(myFile.eof()))
        {
            getline(myFile, line);
            if (count == 0)
            {
                count = 1;
            }
            else
            {
                string a = parseData(line, 1);
                stringstream s(a);
                s >> index;
                organizationID = parseData(line, 2);
                name = parseData(line, 3);
                website = parseData(line, 4);
                country = parseData(line, 5);
                description = parseData(line, 6);
                founded = parseData(line, 7);
                industry = parseData(line, 8);
                global_vector = parseData(line, 9);
                stringstream i(global_vector);
                i >> numberOfEmployees;
                createRecord(index, organizationID, name, website, country, description, founded, industry, numberOfEmployees);
            }
        }
    }
    string parseData(string record, int field)
    {
        int comma = 1;
        string item = "";
        for (int x = 0; x < record.length(); x++)
        {
            if (record[x] == ',')
            {
                comma++;
            }
            else if (comma == field)
            {
                item = item + record[x];
            }
        }
        return item;
    }
void heapify(vector<fields>  &heapArr,int size, int index){
 int maxIndex;
 while (true){
 int lIdx = leftChildIndex(index);
 int rIdx = rightChildIndex(index);
 if (rIdx >= size){
 if (lIdx >= size)
 return;
 else
 maxIndex = lIdx;
 }
 else{
 if (heapArr[lIdx].numberOfEmployees >= heapArr[rIdx].numberOfEmployees)
 maxIndex = lIdx;
 else
 maxIndex = rIdx;
 }
 if (heapArr[index].numberOfEmployees < heapArr[maxIndex].numberOfEmployees){
 fields t=heapArr[maxIndex];
 heapArr[maxIndex]=heapArr[index];
 heapArr[index]=t;
 index=maxIndex;
 }
 else
 return;
 }
}
//  concern for heapSort datatype
  void heapSort()
{
 for (int x = (global_vector.size() / 2) - 1; x >= 0; x--)
 {
 heapify(global_vector,global_vector.size(),x);
 }
 for (int x = global_vector.size() - 1; x > 0; x--)
 {
     fields t=global_vector[0];
 global_vector[0]=global_vector[x];
 global_vector[x]=t;

 heapify(global_vector, x,0);
 }
}
void bucketSort(){
    vector<fields> output;
    int min=global_vector[0].numberOfEmployees;
    int max=global_vector[0].numberOfEmployees;
    for(int x=0;x<global_vector.size();x++){
        if(min>global_vector[x].numberOfEmployees){
            min=global_vector[x].numberOfEmployees;
        }
        if(max<global_vector[x].numberOfEmployees){
            max=global_vector[x].numberOfEmployees;
        }
    }
    int number_buckets=max-min+1;
    vector<vector<fields>>  buckets(number_buckets);
    for(int i=0;i<number_buckets;i++){
        buckets[i]=vector<fields>();

    }
    for(int i=0;i<global_vector.size();i++){
        int selectedBucket=(global_vector[i].numberOfEmployees/number_buckets);
        buckets[selectedBucket].push_back(global_vector[i]);
    }
    for(int i=0;i<number_buckets;i++){
    //   sort(buckets[i].begin(),buckets[i].end(),LessThan());
       bucket_inner_sort(buckets[i]);
      for(int j=0;j<buckets[i].size();j++){
        output.push_back(buckets[i][j]);
      }
    }
    for(int i=0;i<global_vector.size();i++){
        global_vector[i]=output[i];
    }

}


   void  bucket_inner_sort(vector<fields> &in_bucket){
            for (int x = 0; x < in_bucket.size() - 1; x++)
        {
            for (int y = 0; y < in_bucket.size() - x - 1; y++)
            {
                if (in_bucket.at(y).numberOfEmployees > in_bucket.at(y + 1).numberOfEmployees)
                {
                    swap(in_bucket[y].index, in_bucket[y + 1].index);
                    swap(in_bucket[y].organizationID, in_bucket[y + 1].organizationID);
                    swap(in_bucket[y].Name, in_bucket[y + 1].Name);
                    swap(in_bucket[y].founded, in_bucket[y + 1].founded);
                    swap(in_bucket[y].industry, in_bucket[y + 1].industry);
                    swap(in_bucket[y].description, in_bucket[y + 1].description);
                    swap(in_bucket[y].numberOfEmployees, in_bucket[y + 1].numberOfEmployees);
                    swap(in_bucket[y].website, in_bucket[y + 1].website);
                    swap(in_bucket[y].country, in_bucket[y + 1].country);
                }
            }
        }
    }



    void quickSort(vector<fields> &new_vector, int start, int end)
    {
        if (start < end)
        {
            int pivot = start;
            int mid = partition(global_vector, start + 1, end, pivot);
            quickSort(global_vector, start, mid - 1);
            quickSort(global_vector, mid + 1, end);
        }

    }
    int largest_element(vector<fields> &arr)
    {
        int largest =0;

        for (int x = 0; x < arr.size(); x++)
        {
            if (arr[x].numberOfEmployees > largest)
            {
                largest = arr[x].numberOfEmployees;
            }
        }
     
        return largest;
    }
    void countingSort(vector<fields> &arr)
    {
        int max = largest_element(arr);
        vector<int> count(max + 1);
        vector<fields> output(arr.size());
        for (int x = 0; x < arr.size(); x++)
        {
            count[arr[x].numberOfEmployees]++;
        }
        for (int x = 1; x < count.size(); x++)
        {
            count[x] = count[x - 1] + count[x];
        }
        for (int x = arr.size() - 1; x >= 0; x--)
        {
        
  output[count[arr[x].numberOfEmployees] - 1]=arr[x];
            count[arr[x].numberOfEmployees]--;
            // output[index] = arr[x];
        }
        for (int x = 0; x < output.size(); x++)
        {
            arr[x] = output[x];
        }
        global_vector=arr;
    }
    void Radix_countingSort(vector<fields> &global_vector, int place)
    {
       
        vector<int> count(10);
        vector<fields> output(global_vector.size());
        for (int x = 0; x < global_vector.size(); x++)
        {
            count[(global_vector[x].numberOfEmployees / place) % 10]++;
        }
        for (int x = 1; x < count.size(); x++)
        {
            count[x] = count[x - 1] + count[x];
        }
        for (int x = global_vector.size() - 1; x >= 0; x--)               
        {
         output[count[(global_vector[x].numberOfEmployees/place)%10] - 1]=global_vector[x];

            count[(global_vector[x].numberOfEmployees/place)%10]--;
        }
        for (int x = 0; x < output.size(); x++)
        {
            global_vector[x] = output[x];
        }
    }
    int partition(vector<fields> &new_vector, int start, int end, int pivot)
    {

        int left = start;
        int right = end;
        while (left <= right)
        {
            while (new_vector[left].numberOfEmployees < new_vector[pivot].numberOfEmployees && left <= end)
            {
                left++;
            }
            while (new_vector[right].numberOfEmployees >= new_vector[pivot].numberOfEmployees && right >= start)
            {
                right--;
            }
            if (left < right)
                swap(new_vector[left], new_vector[right]);
        }
        swap(new_vector[right], new_vector[pivot]);
        return right;
    }
int parentIndex(int i)
{
 return (i - 1) / 2;
}
int leftChildIndex(int i)
{
 return (2 * i) + 1;
}
int rightChildIndex(int i)
{
 return (2 * i) + 2;
}
void  MAIN_READ_FUNCTION(int no_file,customer &obj){
if (no_file == 1)
        {
            string path = "organizations-100.csv";
            obj.Read_Data(path);
        }
        else if (no_file == 2)
        {
            obj.Read_Data("organizations-1000.csv");
        }
        else if (no_file == 3)
        {
            obj.Read_Data("organizations-10000.csv");
        }
        else if (no_file == 4)
        {
            obj.Read_Data("organizations-100000.csv");
        }
        else if (no_file == 5)
        {
            obj.Read_Data("organizations-500000.csv");
        }
}
void radixSort(vector<fields> &arr)
    {
        int max = largest_element(arr);
        int place = 1;
        while ((max / place) > 0)
        {
            Radix_countingSort(global_vector, place);
            place = place * 10;
        }
    }

    bool writeData(string path)
    {
        fstream file;
        file.open(path, ios::out);
        if (file.is_open())
        {
            file << "Index"
                 << ","
                 << "Organization"
                 << ","
                 << "Name"
                 << ","
                 << "Website"
                 << ","
                 << "Country"
                 << ","
                 << "Description"
                 << ","
                 << "Founded"
                 << ","
                 << "Industry"
                 << ","
                 << "Number Of Employee" << endl;
            for (int i = 0; i < global_vector.size(); i++)
            {
                file << global_vector[i].index << "," << global_vector[i].organizationID << "," << global_vector[i].Name << "," << global_vector[i].website << "," << global_vector[i].country << "," << global_vector[i].description << "," << global_vector[i].founded << "," << global_vector[i].industry << "," << global_vector[i].numberOfEmployees << endl;
            }
            file.close();
            return true;
        }
        else
        {
            return false;
        }
    }
};
int loadMenu()
{
    cout << "press 1. Load 100 Records " << endl;
    cout << "press 2. Load 1000 Records " << endl;
    cout << "press 3. Load 10000 Records " << endl;
    cout << "press 4. Load 100000 Records " << endl;
    cout << "press 5. Load 500000 Records " << endl;
    cout << " Back: ";
    cout << "Your Option:  ";
    int option = 0;
    cin >> option;
    return option;
}

int SORT_MENU()
{
    cout << "press 1. Bubble Sort " << endl;
    cout << "press 2. Selection Sort " << endl;
    cout << "press 3. Insertion Sort " << endl;
    cout << "press 4. Merge Sort " << endl;
    cout << "press 5-Quick sort" << endl;
    cout << "press 6-counting sort" << endl;
    cout << "press 7-Radix sort" << endl;
    cout << "press 8-Bucket sort" << endl;
    cout << "press 9-Heap sort" << endl;
    cout << "you Option " << endl;
    int option;
    cin >> option;
    return option;
}

long getTime()
{
    struct timeval start;
    gettimeofday(&start, NULL);
    return start.tv_sec * 1000000 + start.tv_usec;
}
int main()
{
    customer obj;

    while (true)
    {
        int no_file = loadMenu();
       obj.MAIN_READ_FUNCTION(no_file,obj);
        while (true)
        {
            int sortOption = SORT_MENU();
            if (sortOption == 1)
            {
                                   vector<fields> vect=obj.global_vector;

                long start = getTime();
                obj.bubble_Sort();
                long end = getTime();
                cout << "Algorithem takes:" << end - start << " milliseconds" << endl;
                obj.writeData("bubble_file.csv");
                // for refresh 
                   obj.global_vector=vect;

            }
            else if (sortOption == 2)
            {
                                  vector<fields> vect=obj.global_vector;


                long start = getTime();
                obj.selection_Sort();
                long end = getTime();
                cout << "Algorithem takes:" << end - start << " milliseconds" << endl;
                obj.writeData("selection_file.csv");
                 // for refresh 
                   obj.global_vector=vect;
            }
            else if (sortOption == 3)
            {
                                vector<fields> vect=obj.global_vector;


                long start = getTime();
                obj.insertion_Sort();
                long end = getTime();
                cout << "Algorithem takes:" << end - start << " milliseconds" << endl;
                obj.writeData("insertion_file.csv");
                 // for refresh 
                   obj.global_vector=vect;
            }
            else if (sortOption == 4)
            {
                                   vector<fields> vect=obj.global_vector;

                int start1 = 0;
                int end1 = vect.size() - 1;
                long start = getTime();
                obj.merge_Sort(vect, start1, end1);
                long end = getTime();
                cout << "Algorithem takes:" << end - start << " milliseconds" << endl;
                obj.writeData("merge_file.csv");
                  // for refresh 
                   obj.global_vector=vect;
            }
            else if (sortOption == 5)
            {
                                  vector<fields> vect=obj.global_vector;

                int start1 = 0;
                int end1 = vect.size() - 1;
                long start = getTime();
                obj.quickSort(vect, start1, end1);
                long end = getTime();
                cout << "Algorithem takes:" << end - start << " milliseconds" << endl;
                obj.writeData("quick_file.csv");
                  // for refresh 
                   obj.global_vector=vect;
            }

            else if (sortOption == 6)
            {
                                    vector<fields> vect=obj.global_vector;

                long start = getTime();
                obj.countingSort(vect);
                long end = getTime();
                cout << "Algorithem takes:" << end - start << " milliseconds" << endl;
                obj.writeData("counting_file.csv");
                  // for refresh 
                   obj.global_vector=vect;
            }
             else if(sortOption == 7)
                {
                    vector<fields> vect=obj.global_vector;
                    long start = getTime();
                    obj.radixSort(vect);
                    long end = getTime();
                    cout << "Algorithem takes:" << end - start << " milliseconds" << endl;
                    obj.writeData("radix_file.csv");
                      // for refresh 
                   obj.global_vector=vect;
                }
             else if(sortOption == 8)
                {
                    vector<fields> vect=obj.global_vector;
                   
                    long start = getTime();
                    obj.bucketSort();
                    long end = getTime();
                    cout << "Algorithem takes:" << end - start << " milliseconds" << endl;
                    obj.writeData("bucket_file.csv");
                       // for refresh 
                   obj.global_vector=vect;
                }
             else if(sortOption == 9)
                {
                    vector<fields> vect=obj.global_vector;
                                    
    long start = getTime();
                    obj.heapSort();
                    long end = getTime();
                    cout << "Algorithem takes:" << end - start << " milliseconds" << endl;
                    obj.writeData("heap_file.csv");
                      // for refresh 
                   obj.global_vector=vect;
                }
        }
    }
}