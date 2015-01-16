#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <tchar.h>
#include "dric.h"
#include "bitmap2console.h"
#include "sorting.h"
#include <time.h>
#include <ctime>
#include <chrono>
using namespace std;

void bubbleOpen(void);
void bubbleEff(void);
void bubbleDiagram(void);
void bubbleRun(void);
void heapOpen(void);
void heapEff(void);
void heapDiagram(void);
void heapRun(void);
void insertionOpen(void);
void insertionEff(void);
void insertionDiagram(void);
void insertionRun(void);
void quickOpen(void);
void quickEff(void);
void quickDiagram(void);
void quickRun(void);
void mergeOpen(void);
void mergeEff(void);
void mergeDiagram(void);
void mergeRun(void);
void proxmapOpen(void);
void proxmapEff(void);
void proxmapDiagram(void);
void proxmapRun(void);
void radixOpen(void);
void radixEff(void);
void radixDiagram(void);
void radixRun(void);
void selectionOpen(void);
void selectionEff(void);
void selectionDiagram(void);
void selectionRun(void);
void shellOpen(void);
void shellEff(void);
void shellDiagram(void);
void shellRun(void);
void treeOpen(void);
void treeEff(void);
void treeDiagram(void);
void treeRun(void);

void genEff(int);
void genDiagram(int, int);
void userList(void);
void randList(void);
void loadFolder(const char * , int, int, int, int);

void loadCPICs(void);

char sortNames[][15] = {
    "Bubble Sort",
    "Heap Sort",
    "Insertion Sort",
    "Quick Sort",
    "Merge Sort",
    "Proxmap Sort",
    "Radix Sort",
    "Selection Sort",
    "Shell Sort",
    "Tree Sort"
};
char averageEff[][25] = {
    "O(n^2)",
    "O(n log(n))",
    "O(n^2)",
    "O(n log(n))",
    "O(n log(n))",
    "O(n)",
    "O(nk)",
    "O(n^2)",
    "depends on gap sequence",
    "O(n log n)"
};
char bestEff[][15] = {
    "O(n)",
    "O(n log(n))",
    "O(n)",
    "O(n log(n))",
    "O(n log(n))",
    "O(n)",
    "O(nk)",
    "O(n^2)",
    "O(n log^2 n)",
    "O(n)"
};
char worstEff[][15] = {
    "O(n^2)",
    "O(n log(n))",
    "O(n^2)",
    "O(n^2)",
    "O(n log(n))",
    "O(n^2)",
    "O(nk)",
    "O(n^2)",
    "O(n^2)",
    "O(n^2)"
};
char sortPara[][1000] = { //bubble
    "We can imagine that sorted numbers are bubbles, the ones with lower value are lighter than "
    "the ones with higher value, hence they ascend to the surface faster.\n"
    "Bubble sort advances similarly. In every step it compares two adjacent elements and if the "
    "lower value is on the left side of the higher, bubble sort swaps them (lighter value ascends "
    "to the end of the array) and with the same logic algorithm proceeds to the next item."
    "After one iteration the lowest value is located at the end of the array. Algorithm now repeats "
    "the procedure with reduced array (the last element is already sorted). After n-1 iterations is "
    "the array completely sorted, because the last bubble is sorted trivially.",
    //heap
    "Heapsort is based on usage of the binary heap � data structure which acts as a priority queue. "
    "If we insert all elements of the array into the priority queue, the operation poll will always "
    "return (and remove) the element of the heap, which has the highest priority. If we use poll "
    "operation n times, we will obtain list of sorted elements.",
    //insertion
    "1. One element is sorted trivially.\n"
    "2. Pick element next to the already sorted sequence and insert it to the correct place - being "
    "move every element of the already sorted sequence, which has a higher value than the element "
    "sorted, one place right, than put the element into the gap (correct place within the sequence).\n"
    "3. While array contains any unsorted elements GOTO: 2.",
    //quick
    "Algorithm picks one random element of the input array (pivot). In next steps it reorganizes "
    "the array in such a way, that all elements with higher value than the pivot are located before "
    "the pivot and all elements with lower value than the pivot are after it. We can see that the "
    "pivot itself is located at the correct position (i.e. it is already sorted).\n"
    "Algorithm now repeats the procedure described above on both (unsorted) halves of the array. "
    "When the algorithm reaches all the subproblems of size 1, which are solved trivially (one "
    "element itself is already sorted), the whole array is sorted in descending order.",
    //merge
    "MergeSort is a recursive sorting procedure that uses O(n log n) comparisons in the worst case. "
    "To sort an array of n elements, we perform the following three steps in sequence:\n"
    "If n<2 then the array is already sorted. Stop now."
    "Otherwise, n>1, and we perform the following three steps in sequence:\n"
    "1. Sort the left half of the the array."
    "2. Sort the right half of the the array."
    "3. Merge the now-sorted left and right halves.",
    //proxmap
    "ProxMap Sorting uses a different approach to sorting, which conceptually is similar to "
    "hashing. This technique uses a variation on hashing with buckets, but with buckets of "
    "different sizes.",
    //radix
    "Radix sort iteratively orders all the strings by their n-th character � in the first iteration, "
    "the strings are ordered by their last character. In the second run, the strings are ordered in "
    "respect to their penultimate character. And because the sort is stable, the strings, which have "
    "the same penultimate character, are still sorted in accordance to their last characters. After "
    "n-th run the strings are sorted in respect to all character positions.",
    //selection
    "The idea of selection sort is, that if we sort the array from largest to smallest element, "
    "than the first element of the sorted array will be the one with the largest value. Second "
    "will be the largest element of the rest of the array. Third will be the largest element of "
    "the new rest of the array (initial array without the two already sorted elements)...\n"
    "So we can iteratively select the largest element of the (reduced) array, swap it with the "
    "first element and than reduce the problem size by 1 (sort only the rest of the array). When "
    "there remains only one element to sort, the algorithm terminates.",
    //shell
    "An ordinary insertion sort maintains a list of already sorted elements. Than it picks the "
    "element next to the list and places it at the correct position within the list. By iteratively "
    "repeating this procedure (starting with a list of one element) the array gets sorted in n steps."
    "Shell sort operates analogously. The main difference is, that Shell sort uses so called "
    "diminishing increment. It means that in every step only elements at some distance are compared "
    "(for example the first with the fifth, second with the sixth...). This approach ensures that "
    "elements with high and low value are moved to the appropriate side of the array very quickly. "
    "In every iteration the gap between the compared elements is reduced. In the iteration step, the "
    "gap is set to one � the algorithm degrades to an ordinary insertion sort, which terminates very "
    "quickly, because now the array contains only few misplaced elements.",
    //tree
    "A tree sort is a sort algorithm that builds a binary search tree from the keys to be sorted, "
    "and then traverses the tree (in-order) so that the keys come out in sorted order. Its typical "
    "use is sorting elements adaptively: after each insertion, the set of elements seen so far is "
    "available in sorted order."
};

vector < vector < CPIC * > > sortDiagrams(10);
int globalSortNum = 4;
void( * globalSortFunc)(int[], int) = mergeSort;

menu mainMenu(11, "Sorting Algorithms");
menu bubble(4, sortNames[0]);
menu heap(4, sortNames[1]);
menu insertion(4, sortNames[2]);
menu quick(4, sortNames[3]);
menu mergeMenu(4, sortNames[4]);
menu proxmap(4, sortNames[5]);
menu radix(4, sortNames[6]);
menu selection(4, sortNames[7]);
menu shell(4, sortNames[8]);
menu tree(4, sortNames[9]);
menu genRunMenu(3, "Test Sorting Algorithm");

int main() {
    SetConsoleTitle(_T("Sorting Algorithms"));
    srand(time(NULL));
    cout << "Loading..." << endl;

    optionList mainOptions = {
        "Bubble",
        "Heap",
        "Insertion",
        "Quick",
        "Merge",
        "Proxmap",
        "Radix",
        "Selection",
        "Shell",
        "Tree",
        "Exit"
    };

    function mainFunctions[] = {
        bubbleOpen,
        heapOpen,
        insertionOpen,
        quickOpen,
        mergeOpen,
        proxmapOpen,
        radixOpen,
        selectionOpen,
        shellOpen,
        treeOpen,
        EXIT
    };
    mainMenu.setOptions(mainOptions);
    mainMenu.setFunctions(mainFunctions);

    optionList sortOptions = {
        "Efficiency",
        "Diagram",
        "Run with created list",
        "Go Back"
    };

    function bubbleFunctions[] = {
        bubbleEff,
        bubbleDiagram,
        bubbleRun,
        goBack
    };
    bubble.setOptions(sortOptions);
    bubble.setFunctions(bubbleFunctions);

    function heapFunctions[] = {
        heapEff,
        heapDiagram,
        heapRun,
        goBack
    };
    heap.setOptions(sortOptions);
    heap.setFunctions(heapFunctions);

    function insertionFunctions[] = {
        insertionEff,
        insertionDiagram,
        insertionRun,
        goBack
    };
    insertion.setOptions(sortOptions);
    insertion.setFunctions(insertionFunctions);

    function quickFunctions[] = {
        quickEff,
        quickDiagram,
        quickRun,
        goBack
    };
    quick.setOptions(sortOptions);
    quick.setFunctions(quickFunctions);

    function mergeFunctions[] = {
        mergeEff,
        mergeDiagram,
        mergeRun,
        goBack
    };
    mergeMenu.setOptions(sortOptions);
    mergeMenu.setFunctions(mergeFunctions);

    function proxmapFunctions[] = {
        proxmapEff,
        proxmapDiagram,
        proxmapRun,
        goBack
    };
    proxmap.setOptions(sortOptions);
    proxmap.setFunctions(proxmapFunctions);

    function radixFunctions[] = {
        radixEff,
        radixDiagram,
        radixRun,
        goBack
    };
    radix.setOptions(sortOptions);
    radix.setFunctions(radixFunctions);

    function selectionFunctions[] = {
        selectionEff,
        selectionDiagram,
        selectionRun,
        goBack
    };
    selection.setOptions(sortOptions);
    selection.setFunctions(selectionFunctions);

    function shellFunctions[] = {
        shellEff,
        shellDiagram,
        shellRun,
        goBack
    };
    shell.setOptions(sortOptions);
    shell.setFunctions(shellFunctions);

    function treeFunctions[] = {
        treeEff,
        treeDiagram,
        treeRun,
        goBack
    };
    tree.setOptions(sortOptions);
    tree.setFunctions(treeFunctions);

    optionList genRunMenuOptions = {
        "Create List",
        "Random List",
        "Go Back"
    };

    function genRunMenuFunctions[] = {
        userList,
        randList,
        goBack
    };
    genRunMenu.setOptions(genRunMenuOptions);
    genRunMenu.setFunctions(genRunMenuFunctions);

    loadCPICs();

    mainMenu.open();
    system("PAUSE");
    return EXIT_SUCCESS;
}

void loadCPICs(void) {
    for (int i = 0; i < 10; i++) {
        vector < CPIC * > temp; //(500, CPIC(63,63));
        sortDiagrams.push_back(temp);
    }
    loadFolder("bubble", 0, 432, 63, 63);
    loadFolder("heap", 1, 137, 63, 63);
    loadFolder("insertion", 2, 242, 63, 63);
    loadFolder("quick", 3, 156, 63, 63);
    loadFolder("merge", 4, 150, 63, 63);
    loadFolder("proxmap", 5, 255, 45, 70);
    loadFolder("radix", 6, 0, 63, 63);
    loadFolder("selection", 7, 466, 63, 63);
    loadFolder("shell", 8, 431, 63, 63);
    loadFolder("tree", 9, 12, 75, 56);
}

void loadFolder(const char * folder, int sortNum, int numFiles, int width, int height) {
    for (int i = 0; i < numFiles; i++) {
        char path[100]; // = "e:/c++/sortingRichardson/";
        char temp[9];
        path[0] = '\0';
        strcat(path, folder);
        strcat(path, "/");
        itoa(i, temp, 10);
        strcat(path, temp);
        strcat(path, ".cpic\0");
        ifstream infile;
        infile.open(path, ios::binary | ios:: in );
        CPIC * cpic = new CPIC(width, height);
        cpic - > load(infile);
        sortDiagrams[sortNum].push_back(cpic);
    }
}

void genEff(int sortNum) {
    system("cls");
    cout << sortNames[sortNum] << endl;
    cout << endl;
    cout << "Description:" << endl << endl;
    cout << sortPara[sortNum] << endl;
    cout << endl;
    cout << "Best: " << bestEff[sortNum] << endl;
    cout << "Average: " << averageEff[sortNum] << endl;
    cout << "Worst: " << worstEff[sortNum] << endl;
    cout << endl;
    system("PAUSE");
}

void genDiagram(int sortNum, int numPics) {
    HWND hWnd;
    hWnd = FindWindow(NULL, _T("Sorting Algorithms"));
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int width = 80;
    int height = 25;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, & csbi);
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    COORD NewSBSize = GetLargestConsoleWindowSize(hOut);
    SMALL_RECT DisplayArea = {
        0,
        0,
        0,
        0
    };

    SetConsoleScreenBufferSize(hOut, NewSBSize);

    DisplayArea.Right = NewSBSize.X - 1;
    DisplayArea.Bottom = NewSBSize.Y - 1;

    SetConsoleWindowInfo(hOut, TRUE, & DisplayArea);

    ShowWindow(hWnd, SW_MAXIMIZE);

    set_window_size(80, 80);

    system("cls");
    cout << sortNames[sortNum] << endl;
    cout << endl;
    COORD pos = {
        0,
        2
    };
    for (int i = 0; i < numPics; i++) {
        SetConsoleCursorPosition(hOut, pos);
        sortDiagrams[sortNum][i] - > display();
        if (kbhit())
            break;
    }
    system("PAUSE");

    SMALL_RECT r;
    COORD c;

    r.Left = 0;
    r.Top = 0;
    r.Right = width - 1;
    r.Bottom = height - 1;
    SetConsoleWindowInfo(hOut, TRUE, & r);

    c.X = width;
    c.Y = height;
    SetConsoleScreenBufferSize(hOut, c);
}

void userList() {
    system("cls");
    cout << sortNames[globalSortNum] << endl;
    cout << endl;
    int num;
    do {
        cout << "How many items to sort: ";
        input( & num, 3, INT_);
    } while (num < 2);
    int * sortList = new int[num];
    for (int i = 0; i < num; i++) {
        cout << "Item " << i + 1 << ": ";
        input( & sortList[i], 6, INT_);
    }
    chrono::time_point < chrono::steady_clock > start, end;
    start = chrono::steady_clock::now();

    globalSortFunc(sortList, num);

    end = chrono::steady_clock::now();

    chrono::duration < double > elapsed_seconds = end - start;

    cout << "Sorted List: ";
    for (int i = 0; i < num - 1; i++)
        cout << sortList[i] << ", ";
    cout << sortList[num - 1] << endl << endl;

    cout << "Elapsed time: " << elapsed_seconds.count() << " s\n";

    system("PAUSE");
}

void randList() {
    system("cls");
    cout << sortNames[globalSortNum] << endl;
    cout << endl;
    int sortList[1000];
    int orderedList[1000];
    for (int i = 0; i < 1000; i++) {
        orderedList[i] = i + 1;
    }
    int r = 0;
    int i = 0;
    int n = 1000;
    while (n > 0) {
        r = rand() % n;
        sortList[i] = orderedList[r];
        orderedList[r] = orderedList[n - 1];
        n--;
        i++;
    }
    cout << "List of 1000 random numbers: " << sortList[0] << ", " << sortList[1] << ", ..., " << sortList[998] << ", " << sortList[999] << endl;
    chrono::time_point < chrono::steady_clock > start, end;
    start = chrono::steady_clock::now();

    globalSortFunc(sortList, 1000);

    end = chrono::steady_clock::now();

    chrono::duration < double > elapsed_seconds = end - start;

    cout << "Sorted List: " << sortList[0] << ", " << sortList[1] << ", ..., " << sortList[998] << ", " << sortList[999] << endl;

    cout << "Elapsed time: " << elapsed_seconds.count() << " s\n";

    system("PAUSE");
}

void bubbleOpen(void) {
    bubble.open();
}
void bubbleEff(void) {
    genEff(0);
}

void bubbleDiagram(void) {
    genDiagram(0, 432);
}

void bubbleRun(void) {
    globalSortNum = 0;
    globalSortFunc = bubbleSort;
    genRunMenu.open();
    //genRun(0,bubbleSort);
}
void heapOpen(void) {
    heap.open();
}

void heapEff(void) {
    genEff(1);
}

void heapDiagram(void) {
    genDiagram(1, 137);
}

void heapRun(void) {
    globalSortNum = 1;
    globalSortFunc = heapSort;
    genRunMenu.open();
}

void insertionOpen(void) {
    insertion.open();
}

void insertionEff(void) {
    genEff(2);
}

void insertionDiagram(void) {
    genDiagram(2, 242);
}

void insertionRun(void) {
    globalSortNum = 2;
    globalSortFunc = insertionSort;
    genRunMenu.open();
}

void quickOpen(void) {
    quick.open();
}

void quickEff(void) {
    genEff(3);
}

void quickDiagram(void) {
    genDiagram(3, 156);
}

void quickRun(void) {
    globalSortNum = 3;
    globalSortFunc = quickSort;
    genRunMenu.open();
}

void mergeOpen(void) {
    mergeMenu.open();
}

void mergeEff(void) {
    genEff(4);
}

void mergeDiagram(void) {
    genDiagram(4, 150);
}

void mergeRun(void) {
    globalSortNum = 4;
    globalSortFunc = mergeSort;
    genRunMenu.open();
}

void proxmapOpen(void) {
    proxmap.open();
}

void proxmapEff(void) {
    genEff(5);
}

void proxmapDiagram(void) {
    genDiagram(5, 255);
}

void proxmapRun(void) {
    globalSortNum = 5;
    globalSortFunc = proxmapSort;
    genRunMenu.open();
}

void radixOpen(void) {
    radix.open();
}

void radixEff(void) {
    genEff(6);
}

void radixDiagram(void) {
    genDiagram(6, 0);
}

void radixRun(void) {
    globalSortNum = 6;
    globalSortFunc = radixSort;
    genRunMenu.open();
}

void selectionOpen(void) {
    selection.open();
}

void selectionEff(void) {
    genEff(7);
}

void selectionDiagram(void) {
    genDiagram(7, 466);
}

void selectionRun(void) {
    globalSortNum = 7;
    globalSortFunc = selectionSort;
    genRunMenu.open();
}

void shellOpen(void) {
    shell.open();
}

void shellEff(void) {
    genEff(8);
}

void shellDiagram(void) {
    genDiagram(8, 431);
}

void shellRun(void) {
    globalSortNum = 8;
    globalSortFunc = shellSort;
    genRunMenu.open();
}

void treeOpen(void) {
    tree.open();
}

void treeEff(void) {
    genEff(9);
}

void treeDiagram(void) {
    genDiagram(9, 12);
}

void treeRun(void) {
    globalSortNum = 9;
    globalSortFunc = treeSort;
    genRunMenu.open();
}
