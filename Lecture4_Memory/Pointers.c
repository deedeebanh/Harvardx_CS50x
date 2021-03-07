#include <cs50.h>
#include <stdio.h>

/*If only one number
  Return
Else
    Sort left half of number
    Sort right half of number
    Merge sorted halves
*/

int *bubbleSort(int numbers[], int arrayLength);
int *selectionSort(int numbers[], int arrayLength);

int main(void)
{
    int numbers[] = {6,3,8,5,2,7,4,1};
    int arrayLength = sizeof(numbers)/sizeof(numbers[0]);
    int halfwayIndex = arrayLength/2;
    int *leftHalf = numbers;
    int *rightHalf = numbers + halfwayIndex;
    // base case

    // Sort left half of number
    int *sortedLeftHalf = selectionSort(leftHalf, halfwayIndex);
    for (int i = 0; i < halfwayIndex; i++)
    {
        printf("%i", sortedLeftHalf[i]);
    }
    printf("\n");

    // Sort right half of number
    int *sortedRightHalf = selectionSort(rightHalf, halfwayIndex);
    for (int i = 0; i < halfwayIndex; i++)
    {
        printf("%i", sortedRightHalf[i]);
    }
    printf("\n");
    // Merge sorted halves


    return 0;
}



int *bubbleSort(int numbers[], int arrayLength)
{
    int smallerNum;

    for (int j = 0; j < arrayLength; j++)
    {
        // Compare each element with the next one and swap
        for (int i = 0; i < arrayLength-1 ; i++)
        {
            if (numbers[i] > numbers[i+1])
            {
                smallerNum = numbers[i+1];
                numbers[i+1] = numbers[i];
                numbers[i] = smallerNum;
            }
        }
    }
    return numbers;
}

int *selectionSort(int numbers[], int arrayLength)
{
    int smallest;
    int temp;
    for (int j = 0; j < arrayLength; j++)
    {
        smallest = numbers[j];
        // Compare first number with each element in the array
        // to find the smallest number
        for (int i = j; i < arrayLength; i++)
        {
            if (smallest > numbers[i])
            {
                smallest = numbers[i];
            }
        }
        temp = smallest;
        // find the index of the smallest number and with the
        // first number being compared
        for (int i = 0; i < arrayLength; i++)
        {
            if (numbers[i] == smallest)
            {
                numbers[i] = numbers[j];
            }
        }
        numbers[j] = temp;
    }
    return numbers;
}