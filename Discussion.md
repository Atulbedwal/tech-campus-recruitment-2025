1.	Memory-Mapped File I/O (Final Solution)

Approach:
	•   In this solution, the log file is mapped directly into memory. This means the entire file is available in memory, and we can access it quickly without needing to repeatedly read from the disk.
	•	We scan through the file in memory and extract logs that match the specified date.

Pros:
	•	Memory Efficiency: The system handles memory usage, which keeps things light.
	•	Speed: Memory mapping allows us to access the file quickly, so it’s faster than reading from the disk every time.
	•	Low Overhead: No need to do extra work like sorting or indexing, making it great for large files (like a 1 TB file).

Cons:
	•	We have to read through the file line by line, which might be slower than some other methods (like indexing or binary search), but it works well for this kind of task.

2.	Indexing (Alternative Solution)

Approach:
	•	This method involves creating an index that records where each log entry is located by date. The index allows quick access to the logs for a specific date.

Pros:
	•	Fast Retrieval: Once the index is built, finding logs for a date is very quick because we can go straight to the relevant section of the file.
	•	Good for Repeated Queries: After the index is created, it speeds up future searches, reducing the time it takes to retrieve logs.

Cons:
	•	Initial Overhead: The index needs to be built by processing the entire log file, which can take time and extra space.
	•	Complexity: Keeping the index updated and managing it can add complexity, especially for huge files.

Final Solution Summary:

I chose Memory-Mapped File I/O as the final solution because:

	•	It’s simple and works well for large files without needing extra steps like sorting or indexing.
	•	Memory mapping allows us to process the file directly in memory, making it faster and more efficient.
	•	We only need to process the file once, so sequential reading works well here.
	•	Buffered writing helps reduce disk I/O, improving overall performance.

Although Indexing could be faster for repeated queries, it requires a lot of extra work at the beginning (building the index), and it’s not necessary for a one-time log extraction like this.

This makes Memory-Mapped File I/O the best choice for the task.
Steps to run file:

1.	Clone the Repository
2.  Compile the code using : "g++ -std=c++17 -o extract_logs extract_logs.cpp"
3.  Run the program using : "./extract_logs 2024-12-01"