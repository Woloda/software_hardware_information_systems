#include <queue>
#include <vector>


const int NUMBER_VERTICES	= 10;
const int DEFAULT_FREQUENCY = 240;

int FREE_HEAP_SIZE  = 0;
int FREE_STACK_SIZE = 0;


class Graph;

void FillGraph(const Graph &graph);
void HandleGraph();
void BenchmarkGraph(const Graph &graph, const int frequency);
void RunHandleGraphAtFrequency(const int frequency, const Graph &graph);

template<typename T>
void Print(const T data);
template<typename T>
void Println(const T data);
void Println();

void PrintFreeMemory();
void PrintMemoryUsage();
void PrintResultBFS(const std::vector<int> &result);
void PrintExecutionTime(const int64_t end_time, const int64_t start_time);
void PrintMemoryUsage();

void setup()
{
	Serial.begin(115200);
	while(not Serial){}

	Println();
	Println();
	Println("MEMORY USAGE-----------------------------------------------------------------");
	PrintFreeMemory();
	Println("END MEMORY USAGE-------------------------------------------------------------");
	Println();
	Println();
}

void loop()
{
	HandleGraph();
	delay(20000);
}

class Graph
{
public:
	Graph(const int size);

	void AddVertex(const int v, const int w);

	std::vector<int> BFS(const int start_vertex) const;
private:
	int m_size;

	std::vector<std::vector<int>> m_matrix;
};

Graph::Graph(const int size)
	: m_size(size), m_matrix(size)
{
}

void Graph::AddVertex(const int row, const int column)
{
	m_matrix[row].push_back(column);
}

std::vector<int> Graph::BFS(const int start_vertex) const
{
	std::vector<int> result;
	std::vector<bool> visited(this->m_size, false);
	std::queue<int> queue;

	visited[start_vertex] = true;
	queue.push(start_vertex);

	while(not queue.empty())
	{
		int current_vertex = queue.front();
		result.push_back(current_vertex);
		queue.pop();

		for(int neighbor : m_matrix[current_vertex])
		{
			if (not visited[neighbor])
			{
				visited[neighbor] = true;
				queue.push(neighbor);
			}
		}
	}

	return result;
}

void PrintFreeMemory()
{
	Print("Free Heap: ");
	FREE_HEAP_SIZE = esp_get_free_heap_size();
	Print(FREE_HEAP_SIZE);
	Println(" bytes");

	Print("Free Stack: ");
	FREE_STACK_SIZE = uxTaskGetStackHighWaterMark(NULL);
	Print(FREE_STACK_SIZE);
	Println(" bytes");
}

void PrintMemoryUsage()
{
	Print("Memory Usage: ");
	Print(FREE_HEAP_SIZE - esp_get_free_heap_size());
	Println(" bytes");

	Print("Stack Usage: ");
	Print(FREE_STACK_SIZE - uxTaskGetStackHighWaterMark(NULL));
	Println(" bytes");
}

template<typename T>
void Print(const T data)
{
	Serial.print(data);
	delay(2);
}

template<typename T>
void Println(const T data)
{
	Serial.println(data);
	delay(2);
}

void Println()
{
	Serial.println();
	delay(2);
}

void FillGraph(Graph &graph)
{
	graph.AddVertex(0, 1);

	graph.AddVertex(1, 2);

	graph.AddVertex(2, 5);
	graph.AddVertex(2, 9);

	graph.AddVertex(3, 2);

	graph.AddVertex(4, 2);
	graph.AddVertex(4, 1);

	graph.AddVertex(6, 5);

	graph.AddVertex(7, 6);
	graph.AddVertex(7, 1);

	graph.AddVertex(8, 9);
	graph.AddVertex(8, 3);
	graph.AddVertex(8, 7);

	graph.AddVertex(9, 6);
	graph.AddVertex(9, 7);
}

void HandleGraph()
{
	Println("START-----------------------------------------------------------------");
	Graph graph(NUMBER_VERTICES);
	FillGraph(graph);

	RunHandleGraphAtFrequency(240, graph);
	RunHandleGraphAtFrequency(160, graph);
	RunHandleGraphAtFrequency(80,  graph);
	RunHandleGraphAtFrequency(40,  graph);

	PrintMemoryUsage();
	Println("END---------------------------------------------------------------------");
	Println();
	Println();
}

void PrintResultBFS(const std::vector<int> &result)
{
	Print("Result: ");

	for(int vertex : result)
	{
		Print(vertex);
		Print(" ");
	}

	Println();
}

void PrintExecutionTime(const int64_t end_time, const int64_t start_time)
{
	int64_t execution_time = end_time - start_time;
	Print("Execution time: ");
	Print(execution_time);
	Println(" microseconds");
}

void BenchmarkGraph(const Graph &graph, const int frequency)
{
	setCpuFrequencyMhz(frequency);
	int64_t start_time = esp_timer_get_time();
	std::vector<int> result = graph.BFS(0);
	int64_t end_time = esp_timer_get_time();
	setCpuFrequencyMhz(DEFAULT_FREQUENCY);

	PrintExecutionTime(end_time, start_time);
	PrintResultBFS(result);
}

void RunHandleGraphAtFrequency(const int frequency, const Graph &graph)
{
	Print("CPU frequency: ");
	Print(frequency);
	Println(" MHz");

	BenchmarkGraph(graph, frequency);
	Println();
}
