# Quicksort Demo

A tiny C demo showing the Quicksort algorithm (Lomuto partition scheme).

Simple explanation:
- Pick a pivot (this demo uses the last element).
- Rearrange the array so values <= pivot come before it, and values > pivot come after it.
- Recursively apply the same process to the left and right parts until the array is sorted.

How to compile and run (Windows / PowerShell):

```powershell
gcc quicksort.c -o quicksort.exe
.\quicksort.exe
```

How to compile and run (Linux/macOS):

```bash
gcc quicksort.c -o quicksort
./quicksort
```

The program prints the array before and after sorting.
