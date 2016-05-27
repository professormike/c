int
diff_between_largest_and_smallest(int const *array, size_t n)
{
	int largest = array[0];
	int smallest = array[0];
	for (size_t i = 0; i < n; i++) {
		if (array[i] < smallest) {
			smallest = array[i];
		}
		if (array[i] > largest) {
			largest = array[i];
		}
	}
	return largest - smallest;
}
