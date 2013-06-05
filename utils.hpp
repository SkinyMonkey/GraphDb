#ifndef __UTILS__
#define __UTILS__

template<typename T>
void remove_element(std::vector<T>& v, T n)
{
	int		i;

	for	(i = 0; i < v.size(); ++i)
	{
		if (*(v.begin() + i) == n)
			v.erase(v.begin() + i);
	}
}

#endif /* __UTILS__ */
