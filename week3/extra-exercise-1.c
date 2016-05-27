void
transform_to_absolute_value(double *array, size_t n)
{
	for (size_t i = 0; i < n; i++) {
		//array[i] = fabs(array[i]);
		if (array[i] < 0) {
			array[i] = -array[i];
		}
	}
}
