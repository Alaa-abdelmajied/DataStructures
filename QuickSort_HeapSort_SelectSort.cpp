#include <iostream>
#include <fstream>
#include <vector> 
#include <chrono> 

using namespace std;
using namespace std::chrono;

void getData(vector <int>  &file1Numbers, vector <int>  &file2Numbers, vector <int>  &file3Numbers)
{
    int temp;
    string fileName;
    cout << "Enter The First File Path: ";
    cin >> fileName;
    ifstream file(fileName);
    while (!file.is_open())
    {
        cout<<"Wrong Path !" << "\n" << "Reenter The First File Path: ";
        cin >> fileName;
        file.open(fileName);
    }
    while (file >> temp)
    {
        file1Numbers.push_back(temp);
    }
    cout << "First File Loaded !" << "\n";
    file.close();
    cout << "Enter The Second File Path: ";
    cin >> fileName;
    file.open(fileName);
    while (!file.is_open())
    {
        cout << "Wrong Path !" << "\n" << "Reenter The Second File Path: ";
        cin >> fileName;
        file.open(fileName);
    }
    while (file >> temp)
    {
        file2Numbers.push_back(temp);
    }
    cout << "Second File Loaded !" << "\n";
    file.close();
    cout << "Enter The Third File Path: ";
    cin >> fileName;
    file.open(fileName);
    while (!file.is_open())
    {
        cout << "Wrong Path !" << "\n" << "Reenter The Third File Path: ";
        cin >> fileName;
        file.open(fileName);
    }
    while (file >> temp)
    {
        file3Numbers.push_back(temp);
    }
    cout << "Third File Loaded !" << "\n";
    file.close();
}

void selectionSort(int numbers[], int count)
{
    int min = 0, temp = 0;

    for (int i = 0; i < count - 1; i++)
    {
        min = i;

        for (int j = i; j < count; j++)
        {
            if (numbers[j] < numbers[min])
                min = j;
        }

        temp = numbers[min];
        numbers[min] = numbers[i];
        numbers[i] = temp;

    }
}

void printSelectionSorted(vector <int> numbers)
{
    cout << "\n" << "Second File Selection Sorted" << "\n";
    for (int i = numbers.size() - 1; i >= 0; i--)
    {
        cout << numbers[i] << " ";
    }
    cout << "\n";
}

int partition(int numbers[], int low, int high, int pivot)
{
    while (low <= high)
    {
        while (numbers[low] < pivot)
        {
            low++;
        }
        while (numbers[high] > pivot)
        {
            high--;
        }
        if (low <= high)
        {
            swap(numbers[low], numbers[high]);
            low++;
            high--;
        }
    }
    return low;
}

void quickSort(int numbers[], int low, int high)
{
    if (low < high)
    {
        int pivot = numbers[(high + low) / 2];
        int index = partition(numbers, low, high, pivot);
        quickSort(numbers, low, index - 1);
        quickSort(numbers, index, high);
    }
}

void printQuickSorted(vector <int> numbers)
{
    cout << "\n" << "Third File Quick Sorted" << "\n";
    for (int i = numbers.size() - 1; i >= 0; i--)
    {
        cout << numbers[i] << " ";
    }
    cout << "\n";
}

bool compare(vector <int> file2Numbers, vector <int> file3Numbers)
{
    if (file2Numbers.size() == file3Numbers.size())
    {
        for (int i = 0; i < file2Numbers.size(); i++)
        {
            if (file2Numbers[i] != file3Numbers[i])
            {
                return false;
                break;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

void maxHeapify(int numbers[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left <= n && numbers[left] > numbers[largest])
        largest = left;
    if (right <= n && numbers[right] > numbers[largest])
        largest = right;

    if (largest != i)
    {
        swap(numbers[largest], numbers[i]);
        maxHeapify(numbers, n, largest);
    }

}

void heapSort(int numbers[], int n)
{
    for (int i = (n - 1) / 2; i >= 0; i--)
    {
        maxHeapify(numbers, n, i);
    }
}

int extractMaximum(int numbers[], int n)
{
    int max = numbers[0];
    numbers[0] = numbers[n - 1];
    numbers[n - 1] = max;
    maxHeapify(numbers, n - 2, 0);
    return numbers[n - 1];
}

void printHeapSorted(vector <int> numbers)
{
    cout << "First File Heap Sorted" << "\n";
    for (int i = numbers.size(); i > 0; i--)
    {
        cout << extractMaximum(numbers.data(), i) << " ";

    }
    cout << "\n";
}

int main()
{
    vector <int>  file1Numbers;
    vector <int>  file2Numbers;
    vector <int>  file3Numbers;
    getData(file1Numbers, file2Numbers, file3Numbers);
    auto startHeap = high_resolution_clock::now();
    heapSort(file1Numbers.data(), file1Numbers.size());
    auto stopHeap = high_resolution_clock::now();
    auto durationHeap = duration_cast<milliseconds>(stopHeap - startHeap);
    auto startSelection = high_resolution_clock::now();
    selectionSort(file2Numbers.data(), file2Numbers.size());
    auto stopSelection = high_resolution_clock::now();
    auto durationSelection = duration_cast<milliseconds>(stopSelection - startSelection);
    auto startQuick = high_resolution_clock::now();
    quickSort(file3Numbers.data(), 0, file3Numbers.size() - 1);
    auto stopQuick = high_resolution_clock::now();
    auto durationQuick = duration_cast<milliseconds>(stopQuick - startQuick);
    cout << "\n" << "File Comparison Result: ";
    if (compare(file2Numbers, file3Numbers))
    {
            cout << "Identical" << "\n";
    }
    else
    {
        cout << "Not Identical" << "\n";
    }   
    cout << "\n" << "Running time for Heap sort is " << durationHeap.count() << "ms" << endl;
    cout << "Running time for Selection sort is " << durationSelection.count() << "ms" << endl;
    cout << "Running time for Quick sort is " << durationQuick.count() << "ms" << endl;   
    cout << "\n" << "Sorted Lists" << endl;
    printHeapSorted(file1Numbers);
    printSelectionSorted(file2Numbers);
    printQuickSorted(file3Numbers);
}
