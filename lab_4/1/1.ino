const int PRECISION 		= 10000000;
const int SIZE      		= 1000;
const int MIN_RANGE 		= 33;
const int MAX_RANGE 		= 126;
const int DEFAULT_FREQUENCY = 240;
int 	  FREE_HEAP_SIZE    = 0;
int 	  FREE_STACK_SIZE   = 0;


template<typename T>
using FunctionOfGenerateRandomArray = void (*)(T array[], int size, T min, T max);

void GenerateRandomIntArray   (int    array[], int size, int    min, int    max);
void GenerateRandomDoubleArray(double array[], int size, double min, double max);
void GenerateRandomFloatArray (float  array[], int size, float  min, float  max);
void GenerateRandomCharArray  (char   array[], int size, char   min, char   max);

void PrintEnd  (char type_name[]);
void PrintStart(char type_name[]);

template<typename T>
void PrintSizeOfArray(int size, T type);

template<typename T>
void CopyArray(T source[], T destination[], int size);

template<typename T>
void HandleType(FunctionOfGenerateRandomArray<T> function, char type_name[]);

void HandleIntegerType();
void HandleDoubleType ();
void HandleFloatType  ();
void HandleCharType   ();

template<typename T>
void BubbleSort(T array[], int n);

template<typename T>
void PrintArray(T array[], int size);

template<typename T>
void BenchmarkBubbleSort(T array[], int size, int frequency);

template<typename T>
void RunHandleTypeAtFrequency(int frequency, T array[], int size);

template<typename T>
void Print(T data);

template<typename T>
void Println(T data);

void Println();

void PrintFreeMemory();
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
	HandleIntegerType();
	HandleDoubleType ();
	HandleFloatType  ();
	HandleCharType   ();
	delay(20000);
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
void Print(T data)
{
	Serial.print(data);
	delay(2);
}

template<typename T>
void Println(T data)
{
	Serial.println(data);
	delay(2);
}

void Println()
{
	Serial.println();
	delay(2);
}

void PrintStart(char type_name[])
{
	Print(type_name);
	Print("-----------------------------------------------------------------");
	Println();
}

void PrintEnd(char type_name[])
{
	Print("END ");
	Print(type_name);
	Println("-------------------------------------------------------------");
	Println();
	Println();
}

template<typename T>
void PrintSizeOfArray(int size, T type)
{
	Print("Size of array: ");
	Print(sizeof(type) * size);
	Println(" bytes");
	Println();
}

template<typename T>
void CopyArray(T source[], T destination[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		destination[i] = source[i];
	}
}

template<typename T>
void HandleType(FunctionOfGenerateRandomArray<T> function, char type_name[])
{
	PrintStart(type_name);

	T *array 	 = new T[SIZE];
	T *temporary = new T[SIZE];
	function(array, SIZE, static_cast<T>(MIN_RANGE), static_cast<T>(MAX_RANGE));

	//Println("Array: ");
	//PrintArray(array, SIZE);

	CopyArray(array, temporary, SIZE);
	RunHandleTypeAtFrequency(240, temporary, SIZE);

	CopyArray(array, temporary, SIZE);
	RunHandleTypeAtFrequency(160, temporary, SIZE);

	CopyArray(array, temporary, SIZE);
	RunHandleTypeAtFrequency(80, temporary, SIZE);

	RunHandleTypeAtFrequency(40, array, SIZE);

	//Println("Sorted array: ");
	//PrintArray(array, SIZE);

	PrintSizeOfArray(SIZE, T{});
	PrintMemoryUsage();

	delete[] array;
	delete[] temporary;

	PrintEnd(type_name);
}

void HandleIntegerType()
{
	HandleType(GenerateRandomIntArray, "INTEGER");
}

void HandleDoubleType()
{
	HandleType(GenerateRandomDoubleArray, "DOUBLE");
}

void HandleFloatType()
{
	HandleType(GenerateRandomFloatArray, "FLOAT");
}

void HandleCharType()
{
	HandleType(GenerateRandomCharArray, "CHAR");
}

void GenerateRandomIntArray(int array[], int size, int min, int max)
{
	for (int i = 0; i < size; ++i)
	{
		array[i] = min + esp_random() % (max - min + 1);
	}
}

void GenerateRandomDoubleArray(double array[], int size, double min, double max)
{
	for (int i = 0; i < size; ++i)
	{
		int random_int = esp_random() % PRECISION;
		double random_double = static_cast<double>(random_int) / static_cast<double>(PRECISION) * (max - min) + min;
		array[i] = random_double;
	}
}

void GenerateRandomFloatArray(float array[], int size, float min, float max)
{
	for (int i = 0; i < size; ++i)
	{
		int random_int = esp_random() % PRECISION;
		float random_float = static_cast<float>(random_int) / static_cast<float>(PRECISION) * (max - min) + min;
		array[i] = random_float;
	}
}

void GenerateRandomCharArray(char array[], int size, char min, char max)
{
	for (int i = 0; i < size; ++i)
	{
		int random_int = esp_random() % (max - min + 1);
		char random_char = static_cast<char>(min + random_int);
		array[i] = random_char;
	}
}

template<typename T>
void BubbleSort(T array[], int size)
{
	bool swapped{false};

	for(int i = 0; i < size - 1; ++i)
	{
		swapped = false;
		for(int j = 0; j < size - i - 1; j++)
		{
			if(array[j] > array[j + 1])
			{
				std::swap(array[j], array[j + 1]);
				swapped = true;
			}
		}

		if(not swapped)
		{
			break;
		}
	}
}

template<typename T>
void PrintArray(T array[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		Print(array[i]);
		Print(" ");
	}

	Println();
}

template<typename T>
void BenchmarkBubbleSort(T array[], int size, int frequency)
{
	setCpuFrequencyMhz(frequency);
	int64_t start_time = esp_timer_get_time();
	BubbleSort(array, size);
	int64_t end_time = esp_timer_get_time();
	setCpuFrequencyMhz(DEFAULT_FREQUENCY);

	int64_t execution_time = end_time - start_time;
	Print("Execution time: ");
	Print(execution_time);
	Println(" microseconds");
}

template<typename T>
void RunHandleTypeAtFrequency(int frequency, T array[], int size)
{
	Print("CPU frequency: ");
	Print(frequency);
	Println(" MHz");

	BenchmarkBubbleSort(array, size, frequency);
}
