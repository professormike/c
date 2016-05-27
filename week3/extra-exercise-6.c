bool
one_is_true(void const *array, size_t num_elements, size_t element_size,
bool (*f)(void const *))
{
	for (size_t i = 0; i < num_elements; i++) {
		if ((*f)(&array[i * element_size])) {
			return true;
		}
	}
	return false;
}

bool
is_even(void const *num_)
{
	int const *num = num_;
	return *num % 2 == 0;
}
